#!/bin/bash

PATH=/usr/sbin:/sbin:/usr/bin:/bin

AUDISP_DIR=/etc/audisp/plugins.d

AUDISP_CONF=$AUDISP_DIR/auoms.conf

AUOMS_BIN=/opt/microsoft/auoms/bin/auoms
AUOMS_OUTCONF_DIR=/etc/opt/microsoft/auoms/outconf.d

AUDIT_RULES_FILE=/etc/audit/audit.rules
OMS_AUDIT_RULES_PATH=/etc/audit/rules.d/oms-security-audit.rules

umask 027

get_plugin_state () {
    if [ ! -e $AUDISP_CONF ]; then
        echo None
    fi
    echo "$(grep '^ *active *= *' $AUDISP_CONF | tr -d ' ' | cut -d'=' -f2)"
}

set_plugin_state () {
    # Edit the conf file
    sed -i "s/^\( *active *= *\)[enosy]*/\1$1/" $AUDISP_CONF
    if [ $? -ne 0 ]; then
        return 1
    fi

    # Notify auditd of changes
    service auditd reload
    if [ $? -ne 0 ]; then
        return 1
    fi

    # Give auoms a chance to start or stop
    sleep 5

    if [ $1 = "yes" ]; then
        # Make sure auoms started
        pgrep -f $AUOMS_BIN 2>&1 >/dev/null
        if [ $? -ne 0 ]; then
            # Sometimes a reload isn't enough, do a restart
            service auditd restart
            sleep 3
            # On CentOS/RHEL 7 the restart may fail to start auditd
            # So, double check and start the service if restart failed
            pgrep -x auditd >/dev/null 2>&1
            if [ $? -ne 0 ]; then
                service auditd start
            fi
        fi
        pgrep -f $AUOMS_BIN 2>&1 >/dev/null
        if [ $? -ne 0 ]; then
            return 2
        fi
    else
        # make sure auoms stopped
        pgrep -f $AUOMS_BIN 2>&1 >/dev/null
        if [ $? -eq 0 ]; then
            pkill -KILL -f $AUOMS_BIN
        fi
    fi
}

use_augenrules () {
    if [ -e /sbin/augenrules -a -d /etc/audit/rules.d ]; then
        count=$(grep '## This file is automatically generated from' $AUDIT_RULES_FILE | wc -l)
        if [ $count -gt 0 ]; then
            return 0
        fi
    fi
    return 1
}

get_actual_rules () {
    if use_augenrules; then
        if [ -e $OMS_AUDIT_RULES_PATH ]; then
            cat $OMS_AUDIT_RULES_PATH
            return $?
        fi
        return 0
    else
        cat $AUDIT_RULES_FILE | awk '\
        BEGIN {
            emit = 0;
            start_found = 0;
            end_found = 0;
        }
        {
            if ($0 == "#### START OF OMS AUDIT RULES ####") { emit = 1; start_found = 1; next; }
            if ($0 == "#### END OF OMS AUDIT RULES ####") { emit = 0; end_found = 1; next; }
            if (emit == 1) { print; next; }
        }
        END {
            if (start_found != 1 || end_found != 1) { exit 1; }
        }'
        return $?
    fi
}

remove_rules () {
    if use_augenrules; then
        if [ -e $OMS_AUDIT_RULES_PATH ]; then
            rm -f $OMS_AUDIT_RULES_PATH
            if [ $? -ne 0 ]; then
                echo "Failed to remove $OMS_AUDIT_RULES_PATH" >&2
                return 1
            fi
            /sbin/augenrules
            if [ $? -ne 0 ]; then
                echo "Failed to re-generate $AUDIT_RULES_FILE" >&2
                return 1
            fi
        fi
    else
        TmpFile=$(mktemp /tmp/OMSAUditdPlugin.XXXXXXXX)
        cat $AUDIT_RULES_FILE | awk '\
        BEGIN {
            emit = 1;
            start_found = 0;
            end_found = 0;
        }
        {
            if ($0 == "#### START OF OMS AUDIT RULES ####") { emit = 0; start_found = 1; next; }
            if ($0 == "#### END OF OMS AUDIT RULES ####") { emit = 1; end_found = 1; next; }
            if (emit == 1) { print; next; }
        }
        END {
            if (start_found != 1 || end_found != 1) { exit 1; }
        }' > $TmpFile
        if [ $? -ne 0 ]; then
            echo "Failed to remove OMS audit rules from $AUDIT_RULES_FILE" >&2
            rm -f $TmpFile
            return 1
        fi
        cp $TmpFile $AUDIT_RULES_FILE
        if [ $? -ne 0 ]; then
            echo "Failed to edit $AUDIT_RULES_FILE" >&2
            rm -f $TmpFile
            return 1
        fi
        rm -f $TmpFile
    fi
}

set_rules () {
    if use_augenrules; then
        cp $1 $OMS_AUDIT_RULES_PATH
        if [ $? -ne 0 ]; then
            echo "Failed to create $OMS_AUDIT_RULES_PATH" >&2
            return 1
        fi
        chown root.root $OMS_AUDIT_RULES_PATH
        if [ $? -ne 0 ]; then
            echo "Failed to set ownership of $OMS_AUDIT_RULES_PATH" >&2
            rm -f $OMS_AUDIT_RULES_PATH
            return 1
        fi
        chmod 640 $OMS_AUDIT_RULES_PATH
        if [ $? -ne 0 ]; then
            echo "Failed to set permissions for $OMS_AUDIT_RULES_PATH" >&2
            rm -f $OMS_AUDIT_RULES_PATH
            return 1
        fi
        /sbin/augenrules
        if [ $? -ne 0 ]; then
            echo "Failed to re-generate $AUDIT_RULES_FILE" >&2
            rm -f $OMS_AUDIT_RULES_PATH
            return 1
        fi
    else
        TmpOutFile=$(mktemp /tmp/OMSAUditdPlugin.XXXXXXXX)
        cat $AUDIT_RULES_FILE | awk -v DSC_AUDIT_RULES_FILE=$1 '\
        BEGIN {
            emit = 1;
            start_found = 0;
            end_found = 0;
            count = 0;
            idx = 0;
        }
        {
            if (match($0, "^\\s*-e")) { if (idx == 0) {idx = count } next; }
            if ($0 == "#### START OF OMS AUDIT RULES ####") { emit = 0; start_found = 1; if (idx == 0) { idx = count;} next; }
            if ($0 == "#### END OF OMS AUDIT RULES ####") { emit = 1; end_found = 1; next; }
            if (emit == 1) { lines[count++] = $0; next; }
        }
        END {
            if (start_found != end_found) { exit 1; }
            if (idx == 0) { idx = count; }
            for (i = 0; i < idx; i++) { printf "%s\n", lines[i]; }
            print "#### START OF OMS AUDIT RULES ####"
            while(getline line<DSC_AUDIT_RULES_FILE){print line}
            print "#### END OF OMS AUDIT RULES ####"
            for (i = idx; i < count; i++) { printf "%s\n", lines[i]; }
        }' > $TmpOutFile
        if [ $? -ne 0 ]; then
            echo "Failed to add/replace OMS audit rules to $AUDIT_RULES_FILE" >&2
            rm -f $TmpOutFile
            return 1
        fi
        cp $TmpOutFile $AUDIT_RULES_FILE
        if [ $? -ne 0 ]; then
            echo "Failed to edit $AUDIT_RULES_FILE" >&2
            rm -f $TmpOutFile
            return 1
        fi
        rm -f $TmpOutFile
    fi
}

case $1 in
    get)
        AUDIT_VERSION=$(/sbin/auditctl -v | sed 's/^[^0-9]*\([0-9]\.[0-9]\).*$/\1/')
        if [ $? -ne 0 ]; then
            echo "Failed to determine auditctl version"
            exit 2
        fi
        # $2 tmp dir
        get_plugin_state > $2/auditd_plugin.state
        if [ $? -ne 0 ]; then
            rm $2/auditd_plugin.state
            exit 3
        else
            chown omsagent.omiusers $2/auditd_plugin.state
        fi
        get_actual_rules > $2/auditd_plugin.rules
        if [ $? -ne 0 ]; then
            rm $2/auditd_plugin.rules
            exit 4
        else
            chown omsagent.omiusers $2/auditd_plugin.rules
        fi
        echo $AUDIT_VERSION
        ;;
    set)
        # $2 restart or ""
        # $3 plugin state (or "" if it doesn't need to change)
        # $4 rules file path (or "" if it doesn't need to change)
        # $5 dest auoms outconf file name (or "" if it doesn't need to change)
        # $6 source auoms outconf file (only if $4 is not empty)
        if [ "$2" == "restart" ]; then
            /opt/microsoft/omsagent/bin/service_control restart
            if [ $? -ne 0 ]; then
                exit 2
            fi
        fi
        if [ -n "$3" ]; then
            set_plugin_state $3
            RET = $?
            if [ $RET -ne 0 ]; then
                if [ $RET -eq 2 ]; then
                    exit 6
                else
                    exit 3
                fi
            fi
        fi

        if [ -n "$4" ]; then
            if [ "$4" == "remove" ]; then
                remove_rules
            else
                set_rules $4
            fi
            if [ $? -ne 0 ]; then
                exit 4
            fi
        fi

        if [ -n "$5" ]; then
            cp $6 ${AUOMS_OUTCONF_DIR}/$5
            if [ $? -ne 0 ]; then
                exit 5
            fi
            chmod 644 ${AUOMS_OUTCONF_DIR}/$5
            if [ $? -ne 0 ]; then
                exit 5
            fi
        fi
        ;;
    *)
        echo "Invalid command '$1'"
        exit 1
        ;;
esac
