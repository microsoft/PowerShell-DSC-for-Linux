#!/usr/bin/env python
#============================================================================
# Copyright (C) Microsoft Corporation, All rights reserved.
#============================================================================

import os
import sys
import imp
import codecs
import subprocess
import platform
import re

protocol = imp.load_source('protocol', '../protocol.py')
nxDSCLog = imp.load_source('nxDSCLog', '../nxDSCLog.py')

LG = nxDSCLog.DSCLog

LOG_FATAL = 'FATAL'
LOG_ERROR = 'ERROR'
LOG_INFO = 'INFO'
LOG_DEBUG = 'DEBUG'

WORKSPACE_ID_TMPL_STR = "%WORKSPACE_ID%"
AGENT_ETC_ROOT = '/etc/opt/microsoft/omsagent'
AGENT_VAR_ROOT = '/var/opt/microsoft/omsagent'
AUOMS_CONF_FILE = '/etc/opt/microsoft/auoms/auoms.conf'
AUOMSCOLLECT_CONF_FILE = '/etc/opt/microsoft/auoms/auomscollect.conf'
AUOMS_OUTCONF_DIR = '/etc/opt/microsoft/auoms/outconf.d'
AUOMS_RULES_DIR = '/etc/opt/microsoft/auoms/rules.d'
AUOMS_PLUGIN_CONF = '/etc/audisp/plugins.d/auoms.conf'
SUDO_SCRIPT = '/opt/microsoft/omsconfig/Scripts/OMSAuditdPlugin.sh'
MODULE_RESOURCE_DIR = '/opt/microsoft/omsconfig/modules/nxOMSAuditdPlugin/DSCResources/MSFT_nxOMSAuditdPluginResource'
RESOURCE_OMSAGENT_CONF = MODULE_RESOURCE_DIR + '/conf/auditd_plugin.conf'
RESOURCE_AUOMS_V1_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v1.conf'
RESOURCE_AUOMS_V2_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v2.conf'
RESOURCE_AUOMS_V3_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v3.conf'
RESOURCE_AUOMS_V4_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v4.conf'
RESOURCE_AUOMSCOLLECT_V3_CONF = MODULE_RESOURCE_DIR + '/conf/auomscollect_v3.conf'
RESOURCE_OUTPUT_V1_CONF = MODULE_RESOURCE_DIR + '/conf/output_v1.conf'
RESOURCE_OUTPUT_V2_CONF = MODULE_RESOURCE_DIR + '/conf/output_v2.conf'
RESOURCE_OUTPUT_V3_CONF = MODULE_RESOURCE_DIR + '/conf/output_v3.conf'
RESOURCE_OUTPUT_V4_CONF = MODULE_RESOURCE_DIR + '/conf/output_v4.conf'
RESOURCE_AUDIT_RULES_V1 = MODULE_RESOURCE_DIR + '/rules/oms-security-audit-v1.rules'
RESOURCE_AUDIT_RULES_V2 = MODULE_RESOURCE_DIR + '/rules/oms-security-audit-v2.rules'
RESOURCE_SUDO_SCRIPT = MODULE_RESOURCE_DIR + '/Scripts/OMSAuditdPlugin.sh'

MIN_AUOMS_VER_FOR_V2_CONFIG = '1.2'
MIN_AUOMS_VER_FOR_V3_CONFIG = '2.0'
MIN_AUOMS_VER_FOR_V2_RULES = '2.0'
MIN_AUOMS_VER_FOR_V3_COLLECT_CONFIG = '2.0'
MIN_AUOMS_VER_FOR_V4_CONFIG = '2.1'

AUOMS_BIN = '/opt/microsoft/auoms/bin/auoms'
AUOMSCTL_BIN = '/opt/microsoft/auoms/bin/auomsctl'
AUDITD_BIN = '/sbin/auditd'

TMP_AUOMS_STATE_FILE = 'auoms.state'
TMP_RULES_FILE = 'auditd_plugin.rules'
TMP_LOADED_RULES_FILE = 'auditd_loaded.rules'
TMP_AUDIT_STATE_FILE = 'audit.state'

def Set_Marshall(WorkspaceId, Ensure):
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    return Set(WorkspaceId, Ensure)

def Test_Marshall(WorkspaceId, Ensure):
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')
    return Test(WorkspaceId, Ensure)

def Get_Marshall(WorkspaceId, Ensure):
    WorkspaceId = WorkspaceId.encode('ascii', 'ignore')
    Ensure = Ensure.encode('ascii', 'ignore')

    arg_names = list(locals().keys())

    retval = 0
    (retval, Ensure) = Get(WorkspaceId)

    WorkspaceId = protocol.MI_String(WorkspaceId)
    Ensure = protocol.MI_String(Ensure)

    retd = {}
    ld = locals()
    for k in arg_names:
        retd[k] = ld[k]
    return retval, retd

def IsUUID(uuidStr):
    try:
        uuidOut = re.match('^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$', uuidStr, re.I)
    except:
        return False
    return uuidOut is not None

# Compare versions
# Only the numeric parts are compared. For example this version "1.2.3.stuff" and "1.2.3-stuff" will be normalized to "1.2.3"
def CompareVersion(version1, version2):
    def normalize(v):
        parts = [re.sub(r'^\s*0*([0-9]+).*$', r'\1', x) for x in re.sub(r'^\s*([0-9]+(?:\.[0-9]+)*).*$', r'\1', v).split(".")]
        return [int(x) for x in parts]
    parts1 = normalize(version1)
    parts2 = normalize(version2)
    lendiff = len(parts1) - len(parts2)
    if lendiff > 0:
        parts2.extend([0] * lendiff)
    elif lendiff < 0:
        parts1.extend([0] * (-lendiff))

    for i, p in enumerate(parts1):
        if p < parts2[i]:
          return -1
        elif p > parts2[i]:
          return 1
    return 0

def IsValidWorkspaceId(WorkspaceId):
    if not IsUUID(WorkspaceId):
        return False
    return os.path.isdir(os.path.join(AGENT_VAR_ROOT, WorkspaceId))

def GetTmpDir(WorkspaceId):
    return os.path.join(AGENT_VAR_ROOT, WorkspaceId, "tmp")

def GetAgentConfDir(WorkspaceId):
    return os.path.join(AGENT_ETC_ROOT, WorkspaceId, "conf/omsagent.d")

def GetAgentRunDir(WorkspaceId):
    return os.path.join(AGENT_VAR_ROOT, WorkspaceId, "run")

def GetOMSAgentConfPath(WorkspaceId):
    return os.path.join(GetAgentConfDir(WorkspaceId), "auditd_plugin.conf")

def GetOMSAgentPidFilePath(WorkspaceId):
    return os.path.join(GetAgentRunDir(WorkspaceId), "omsagent.pid")

def GetTmpAuomsConfPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "auoms.conf")

def GetTmpAuomscollectConfPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "auomscollect.conf")

def GetTmpAuomsOutputConfPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "output.conf")

def GetAuomOutputConfPath(WorkspaceId):
    return os.path.join(AUOMS_OUTCONF_DIR, WorkspaceId + ".conf")

def GetTmpAuditRulesPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), TMP_RULES_FILE)

def GetTmpAuditLoadedRulesPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), TMP_LOADED_RULES_FILE)

def IsRootProcessRunning(comm):
    args = []
    args.append("/usr/bin/pgrep")
    args.append("-x")
    args.append("-U")
    args.append("0")
    args.append(comm)
    proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    exit_code = proc.wait()
    if exit_code == 0:
        return True
    return False

def IsAuditdRunning():
    return IsRootProcessRunning("auditd")

def IsAuomsRunning():
    return IsRootProcessRunning("auoms")

def IsAuomsCollectRunning():
    return IsRootProcessRunning("auomscollect")

def Set(WorkspaceId, Ensure):
    if not IsValidWorkspaceId(WorkspaceId):
        return [1]

    if IsSudoScriptOutOfDate():
        LG().Log(LOG_INFO, "Updating sudo script")
        try:
            WriteFile(SUDO_SCRIPT, ReadFile(RESOURCE_SUDO_SCRIPT))
        except:
            LG().Log(LOG_FATAL, "Failed to update " + SUDO_SCRIPT)
            return [1]

    auoms_version = GetPackageVersion("auoms")
    if auoms_version is None:
        LG().Log(LOG_FATAL, "Failed to determine auoms version")
        # Failed to get auoms version, return fake success
        return [1]

    (audit_version, auoms_state, actual_audit_rules, actual_conf, actual_collect_conf,
     actual_outconf, actual_plugin_conf, loaded_audit_rules, audit_state) = GetState(WorkspaceId)
    if audit_version is None:
        return [1]

    (desired_auoms_state, desired_rules, desired_conf, desired_collect_conf, desired_outconf,
     desired_plugin_conf) = GetDesiredState(WorkspaceId, Ensure, audit_version, auoms_state, auoms_version)
    if desired_auoms_state is None:
        return [1]

    run_script = False
    if auoms_state != desired_auoms_state:
        run_script = True
        LG().Log(LOG_INFO, "Actual auoms state differs from desired auoms state")

    audit_enabled = GetEnabledFromAuditState(audit_state)

    arg1 = ""
    agent_restart_ignore_error = False
    if IsTextDifferent(actual_plugin_conf, desired_plugin_conf):
        run_script = True
        LG().Log(LOG_INFO, "Actual Plugin conf differs from Desired plugin conf so omsagent will be restarted")
        arg1 = WorkspaceId
        if desired_plugin_conf is None:
            RemoveFile(GetOMSAgentConfPath(WorkspaceId))
        else:
            agent_restart_ignore_error = True
            WriteFile(GetOMSAgentConfPath(WorkspaceId), desired_plugin_conf)

    if arg1 == "" and OmsAgentNeedsRestart(WorkspaceId):
        run_script = True
        LG().Log(LOG_INFO, "Plugin conf has changed since omsagent start, omsagent will be restarted")
        arg1 = WorkspaceId

    rules_file_path = ""
    if IsTextDifferent(actual_audit_rules, desired_rules):
        run_script = True
        if desired_rules is None:
            LG().Log(LOG_INFO, "Auditd rules will be removed")
            rules_file_path = "remove"
        else:
            LG().Log(LOG_INFO, "Actual auditd rules differ from desired auditd rules")
            rules_file_path = GetTmpAuditRulesPath(WorkspaceId)
            WriteFile(rules_file_path, desired_rules)

    conf_path = ""
    if IsTextDifferent(actual_conf, desired_conf):
        if desired_conf is not None:
            run_script = True
            LG().Log(LOG_INFO, "Actual auoms conf differs from desired conf")
            conf_path = GetTmpAuomsConfPath(WorkspaceId)
            WriteFile(conf_path, desired_conf)

    collect_conf_path = ""
    if IsTextDifferent(actual_collect_conf, desired_collect_conf):
        if desired_collect_conf is not None:
            run_script = True
            LG().Log(LOG_INFO, "Actual auomscollect conf differs from desired conf")
            collect_conf_path = GetTmpAuomscollectConfPath(WorkspaceId)
            WriteFile(collect_conf_path, desired_collect_conf)

    outconf_name = ""
    outconf_path = ""
    if IsTextDifferent(actual_outconf, desired_outconf):
        run_script = True
        outconf_name = WorkspaceId + ".conf"
        if desired_outconf is None:
            LG().Log(LOG_INFO, "auoms output conf will be removed")
            outconf_path = "remove"
        else:
            LG().Log(LOG_INFO, "Actual auoms output conf differs from desired output conf")
            outconf_path = GetTmpAuomsOutputConfPath(WorkspaceId)
            WriteFile(outconf_path, desired_outconf)

    rules_diff = ""
    rules_diff_path = ""
    # Only do loaded rules check if auoms version < 2.0
    if CompareVersion(auoms_version, '2.0') < 0:
        # On some systems the auditd reload will cause rule load as well
        # So, to prevent trying to load rules twice (and getting an error as a result)
        # Only check loaded rules if rules file already contains the rules
        # This may cause a 15 minute delay between when plugin is enabled
        # and when rules are actually loaded
        if actual_audit_rules is not None:
            rules_diff = DiffAuditRules(desired_rules, loaded_audit_rules)
            if rules_diff is not None and audit_enabled != "2":
                run_script = True
                LG().Log(LOG_INFO, "Not all desired auditd rules are loaded")
                LG().Log(LOG_INFO, "Missing rules are: \n%s" % rules_diff)
                rules_diff_path = GetTmpAuditLoadedRulesPath(WorkspaceId)
                WriteFile(rules_diff_path, rules_diff)

    script_failed = False
    exit_code = 0
    if run_script:
        # Run script that will restart omsagent and enable+start/disable+stop auoms
        args = []
        args.append("/usr/bin/sudo")
        args.append(SUDO_SCRIPT)
        args.append("set")
        args.append(arg1)
        if auoms_state != desired_auoms_state:
            args.append(desired_auoms_state)
        else:
            args.append("")
        args.append(rules_file_path)
        args.append(outconf_name)
        args.append(outconf_path)
        args.append(rules_diff_path)
        args.append(conf_path)
        args.append(collect_conf_path)
        proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = proc.wait()
        if exit_code != 0:
            script_failed = True
            out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
            err_txt = proc.stderr.read().decode('utf8', 'replace').encode('utf8', 'replace')
            LG().Log(LOG_ERROR, "Command failed: '" + "' '".join(args) + "'")
            LG().Log(LOG_INFO, "stdout: " + out_txt)
            LG().Log(LOG_INFO, "stderr: " + err_txt)
            if exit_code == 2:
                if agent_restart_ignore_error:
                    LG().Log(LOG_ERROR, "Failed to restart omsagent")
                else:
                    LG().Log(LOG_FATAL, "Failed to restart omsagent")
            elif exit_code == 3:
                if desired_auoms_state == "running":
                    LG().Log(LOG_FATAL, "Failed to enable OMS Auditd Plugin")
                else:
                    LG().Log(LOG_FATAL, "Failed to disable OMS Auditd Plugin")
            elif exit_code == 4:
                LG().Log(LOG_FATAL, "Failed to change OMS audit rules")
            elif exit_code == 5:
                LG().Log(LOG_FATAL, "Failed to change auoms output config")
            elif exit_code == 6:
                if desired_auoms_state == "running":
                    LG().Log(LOG_FATAL, "OMS Auditd Plugin failed to start")
                else:
                    LG().Log(LOG_FATAL, "OMS Auditd Plugin failed to stop")
            elif exit_code == 7:
                LG().Log(LOG_FATAL, "Failed to change loaded OMS audit rules")
            elif exit_code == 8:
                LG().Log(LOG_FATAL, "Failed to trigger auditd service reload")
            elif exit_code == 9:
                LG().Log(LOG_FATAL, "Failed to change auoms config")
            elif exit_code == 10:
                LG().Log(LOG_FATAL, "Failed to change auomscollect config")
            elif exit_code == 11:
                LG().Log(LOG_FATAL, "Failed to trigger auoms restart")
            elif exit_code == 12:
                LG().Log(LOG_FATAL, "Audit rules immutable (-e 2): reboot required so that desired rules can be loaded")
            elif exit_code == 13:
                LG().Log(LOG_FATAL, "Failed to enable auoms service")
            else:
                LG().Log(LOG_FATAL, "Unknown error while trying to apply desired OMS Auditd Plugin changes")

        RemoveFile(GetTmpAuomsConfPath(WorkspaceId))
        RemoveFile(GetTmpAuomsOutputConfPath(WorkspaceId))
        RemoveFile(GetTmpAuditRulesPath(WorkspaceId))
        RemoveFile(GetTmpAuditLoadedRulesPath(WorkspaceId))

    if not script_failed and Ensure == "Present":
        # Only report runnint state errors if script did not fail
        # If script failed, we don't want to last LOG_FATAL message to get overridden by running state error
        if os.path.isfile(AUOMSCTL_BIN):
            if os.path.isfile(AUDITD_BIN):
                if not IsAuditdRunning():
                    LG().Log(LOG_FATAL, "Auditd service needs to be started")
                    return [0]
                if not IsAuomsCollectRunning():
                    LG().Log(LOG_FATAL, "Auditd service is running, but auomscollect is not running")
                    return [0]
            else:
                if not IsAuomsCollectRunning():
                    LG().Log(LOG_FATAL, "Auoms service is running, but auomscollect is not running")
                    return [0]
        else:
            if not IsAuditdRunning():
                LG().Log(LOG_FATAL, "Auditd service needs to be started")
                return [0]
            if not IsAuomsRunning():
                LG().Log(LOG_FATAL, "Auditd service is running, but auoms is not running")
                return [0]
        if rules_diff is not None and audit_enabled == "2":
            LG().Log(LOG_FATAL, "Audit rules immutable (-e 2): reboot required so that desired rules can be loaded")
            return [0]

    return [exit_code]

def Test(WorkspaceId, DesiredEnsure):
    if not IsValidWorkspaceId(WorkspaceId):
        LG().Log(LOG_FATAL, "Invalid workspace id")
        # Failed to determine state, return fake success
        return [0]

    if not os.path.isfile(AUOMS_BIN):
        if DesiredEnsure == "Present":
            LG().Log(LOG_FATAL, "OMS Auditd Plugin needs to be installed")
        return [0]

    # Only auoms 2.0 has auomsctl. Only check for auditd if auoms version < 2.0.
    if not os.path.isfile(AUOMSCTL_BIN):
        if not os.path.isfile(AUDITD_BIN):
            if DesiredEnsure == "Present":
                LG().Log(LOG_FATAL, "Auditd needs to be installed")
            return [0]

    if IsSudoScriptOutOfDate():
        LG().Log(LOG_INFO, "sudo script needs to be updated")
        return [-1]

    if OmsAgentNeedsRestart(WorkspaceId):
        LG().Log(LOG_INFO, "omsagent needs restart")
        return [-1]

    auoms_version = GetPackageVersion("auoms")
    if auoms_version is None:
        LG().Log(LOG_FATAL, "Failed to determine auoms version")
        # Failed to get auoms version, return fake success
        return [0]

    (audit_version, auoms_state, actual_audit_rules, actual_conf, actual_collect_conf,
     actual_outconf, actual_plugin_conf, loaded_audit_rules, audit_state) = GetState(WorkspaceId)
    if audit_version is None:
        # Failed to get state, return fake success
        return [0]

    (desired_auoms_state, desired_rules, desired_conf, desired_collect_conf, desired_outconf,
     desired_plugin_conf) = GetDesiredState(WorkspaceId, DesiredEnsure, audit_version, auoms_state, auoms_version)
    if desired_auoms_state is None:
        # Failed to get desired state, return fake success
        return [0]

    if desired_auoms_state != auoms_state:
        LG().Log(LOG_INFO, "Auoms State does not match desired state")
        return [-1]

    if IsTextDifferent(desired_rules, actual_audit_rules):
        LG().Log(LOG_INFO, "Audit Rules do not match desired rules")
        return [-1]

    if desired_conf is not None and IsTextDifferent(desired_conf, actual_conf):
        LG().Log(LOG_INFO, "auoms conf does not match desired conf")
        return [-1]

    if desired_collect_conf is not None and IsTextDifferent(desired_collect_conf, actual_collect_conf):
        LG().Log(LOG_INFO, "auomscollect conf does not match desired conf")
        return [-1]

    if desired_outconf is not None and IsTextDifferent(desired_outconf, actual_outconf):
        LG().Log(LOG_INFO, "auoms outconf does not match desired conf")
        return [-1]

    if IsTextDifferent(desired_plugin_conf, actual_plugin_conf):
        LG().Log(LOG_INFO, "Plugin Conf does not match desired conf")
        return [-1]

    rules_diff = DiffAuditRules(desired_rules, loaded_audit_rules)
    if rules_diff is not None:
        LG().Log(LOG_INFO, "One or more desired audit rules are not loaded")
        return [-1]

    # If something isn't running that should be running, trigger a set so that it can report the actual issue
    if DesiredEnsure == "Present":
        if os.path.isfile(AUOMSCTL_BIN):
            if os.path.isfile(AUDITD_BIN):
                if not IsAuditdRunning():
                    return [-1]
            if not IsAuomsRunning() or not IsAuomsCollectRunning():
                return [-1]
        else:
            if not IsAuditdRunning() or not IsAuomsRunning():
                return [-1]
        if GetEnabledFromAuditState(audit_state) == "2":
            return [-1]

    return [0]

def Get(WorkspaceId):
    # Get not supported
    return (-1, "Absent")

def IsSudoScriptOutOfDate():
    actual = ReadFile(SUDO_SCRIPT)
    desired = ReadFile(RESOURCE_SUDO_SCRIPT)
    return IsTextDifferent(actual, desired)

def OmsAgentNeedsRestart(WorkspaceId):
    if os.path.exists(GetOMSAgentConfPath(WorkspaceId)) and os.path.exists(GetOMSAgentPidFilePath(WorkspaceId)):
        pid_stat = os.stat(GetOMSAgentPidFilePath(WorkspaceId))
        conf_stat = os.stat(GetOMSAgentConfPath(WorkspaceId))
        if conf_stat.st_mtime > pid_stat.st_mtime:
            return True
    return False

def GetOtherOutconfCounts(WorkspaceId):
    tcount = 0
    wcount = 0
    for name in os.listdir(AUOMS_OUTCONF_DIR):
        if name.endswith(".conf"):
            if name != WorkspaceId + ".conf":
                tcount += 1
                if IsValidWorkspaceId(name[:-5]):
                    wcount += 1
    return (tcount, wcount)

def HasExecveat():
    args = []
    args.append("/usr/bin/ausyscall")
    args.append("execveat")
    proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    exit_code = proc.wait()
    if exit_code == 0:
        return True
    else:
        return False
    

def GetDesiredAuditRules(AuditVersion, AuomsVersion):
    if CompareVersion(AuomsVersion, MIN_AUOMS_VER_FOR_V2_RULES) >= 0:
        desired_rules = ReadFile(RESOURCE_AUDIT_RULES_V2)
        return desired_rules

    if AuditVersion == 1:
        desired_rules = ReadFile(RESOURCE_AUDIT_RULES_V1)
    else:
        desired_rules = ReadFile(RESOURCE_AUDIT_RULES_V2)
        if not HasExecveat():
            # This assumes that the rule is "-S execve,execveat"
            desired_rules = re.sub(r",execveat", r"", desired_rules)

    if platform.machine() != "x86_64" and desired_rules != None:
        lines = desired_rules.splitlines()
        new_lines = []
        for line in lines:
            if not 'b64' in line:
                new_lines.append(line)
        desired_rules = "\n".join(lines) + "\n"
    return desired_rules

def GetPackageVersion(PackageName):
    deb_ver = None
    rpm_ver = None
    if os.path.isfile("/usr/bin/dpkg-query"):
        args = []
        args.append("/usr/bin/dpkg-query")
        args.append("-f")
        args.append("${Version}")
        args.append("-W")
        args.append(PackageName)
        proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = proc.wait()
        out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
        if exit_code == 0:
            # Some packages have "1:" at rhe beginning of the version
            # So remove it.
            deb_ver = re.sub(r'^[0-9]+:', r'', out_txt)
        else:
            err_txt = proc.stderr.read().decode('utf8', 'replace').encode('utf8', 'replace')
            LG().Log(LOG_ERROR, "Command failed: " + " ".join(args))
            LG().Log(LOG_INFO, "stdout: " + out_txt)
            LG().Log(LOG_INFO, "stderr: " + err_txt)

    if os.path.isfile("/bin/rpm"):
        args = []
        args.append("/bin/rpm")
        args.append("-q")
        args.append("-a")
        args.append("--qf")
        args.append("%{VERSION}.%{RELEASE}")
        args.append(PackageName)
        proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = proc.wait()
        out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
        if exit_code == 0:
            rpm_ver = out_txt
        else:
            err_txt = proc.stderr.read().decode('utf8', 'replace').encode('utf8', 'replace')
            LG().Log(LOG_ERROR, "Command failed: " + " ".join(args))
            LG().Log(LOG_INFO, "stdout: " + out_txt)
            LG().Log(LOG_INFO, "stderr: " + err_txt)

    if deb_ver is None:
        return rpm_ver
    return deb_ver

def GetDesiredAuomsConf(AuomsVersion):
    conf_path = RESOURCE_AUOMS_V1_CONF
    outconf_path = RESOURCE_OUTPUT_V1_CONF
    collectconf_path = None
    if CompareVersion(AuomsVersion, MIN_AUOMS_VER_FOR_V4_CONFIG) >= 0:
        conf_path = RESOURCE_AUOMS_V4_CONF
        outconf_path = RESOURCE_OUTPUT_V4_CONF
        collectconf_path = RESOURCE_AUOMSCOLLECT_V3_CONF
    elif CompareVersion(AuomsVersion, MIN_AUOMS_VER_FOR_V3_CONFIG) >= 0:
        conf_path = RESOURCE_AUOMS_V3_CONF
        outconf_path = RESOURCE_OUTPUT_V3_CONF
        collectconf_path = RESOURCE_AUOMSCOLLECT_V3_CONF
    elif CompareVersion(AuomsVersion, MIN_AUOMS_VER_FOR_V2_CONFIG) >= 0:
        conf_path = RESOURCE_AUOMS_V2_CONF
        outconf_path = RESOURCE_OUTPUT_V2_CONF
    conf_txt = ReadFile(conf_path)
    outconf_txt = ReadFile(outconf_path)
    collectconf_txt = None
    if collectconf_path is not None:
        collectconf_txt = ReadFile(collectconf_path)
    return (conf_txt, outconf_txt, collectconf_txt)

def GetDesiredState(WorkspaceId, Ensure, AuditVersion, CurrentAuomsState, AuomsVersion):
    desired_auoms_state = "disabled"
    desired_rules = None
    desired_conf = None
    desired_outconf = None
    desired_plugin_conf = None
    desired_collect_conf = None

    (other_conf_count, other_ws_conf_count) = GetOtherOutconfCounts(WorkspaceId)

    if Ensure == "Present":
        if os.path.isfile(AUOMSCTL_BIN):
            desired_auoms_state = "running"
        else:
            desired_auoms_state = "enabled"
        desired_rules = GetDesiredAuditRules(AuditVersion, AuomsVersion)
        (desired_conf, desired_outconf, desired_collect_conf) = GetDesiredAuomsConf(AuomsVersion)
        desired_plugin_conf = ReadFile(RESOURCE_OMSAGENT_CONF)

        if desired_rules is None:
            LG().Log(LOG_FATAL, "Failed to determine desired audit rules")
            return (None, None, None, None, None, None)

        if desired_conf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired auoms conf")
            return (None, None, None, None, None, None)

        if desired_outconf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired output conf")
            return (None, None, None, None, None, None)

        if desired_plugin_conf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired plugin conf")
            return (None, None, None, None, None, None)
        
        if CompareVersion(AuomsVersion, MIN_AUOMS_VER_FOR_V3_COLLECT_CONFIG) >= 0:
            if desired_collect_conf is None:
                LG().Log(LOG_FATAL, "Failed to determine desired auomscollect conf")
                return (None, None, None, None, None, None)

        desired_outconf = desired_outconf.replace(WORKSPACE_ID_TMPL_STR, WorkspaceId)
        desired_plugin_conf = desired_plugin_conf.replace(WORKSPACE_ID_TMPL_STR, WorkspaceId)

        if other_conf_count > 0 and other_conf_count > other_ws_conf_count:
            # There are non-OMS outconf present. This likely means AzSecPack is present
            # So, don't touch the auoms conf file.
            desired_conf = ReadFile(AUOMS_CONF_FILE)
    else:
        if other_conf_count > 0:
            if other_ws_conf_count > 0:
                # There are other workspace outconfs present, so the desired state is "running"
                if os.path.isfile(AUOMSCTL_BIN):
                    desired_auoms_state = "running"
                else:
                    desired_auoms_state = "enabled"
            else:
                # If the only other outconfs are non-OMS, then we don't
                # want to change the auoms plugin state
                desired_auoms_state = CurrentAuomsState
        # If there are any other workspaces with auoms outconf files, then
        # we don't want to remove the audit rules
        if other_ws_conf_count > 0:
            desired_rules = GetDesiredAuditRules(AuditVersion, AuomsVersion)
            if desired_rules is None:
                LG().Log(LOG_FATAL, "Failed to determine desired audit rules")
                return (None, None, None, None, None, None)

    return (desired_auoms_state, desired_rules, desired_conf, desired_collect_conf, desired_outconf, desired_plugin_conf)

def GetState(WorkspaceId):
    args = []
    args.append("/usr/bin/sudo")
    args.append(SUDO_SCRIPT)
    args.append("get")
    args.append(GetTmpDir(WorkspaceId))
    proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    exit_code = proc.wait()
    out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
    if exit_code != 0:
        err_txt = proc.stderr.read().decode('utf8', 'replace').encode('utf8', 'replace')
        LG().Log(LOG_ERROR, "Command failed: " + " ".join(args))
        LG().Log(LOG_INFO, "stdout: " + out_txt)
        LG().Log(LOG_INFO, "stderr: " + err_txt)
        if exit_code == 2:
            LG().Log(LOG_FATAL, "Could not determine auditd version: Perhaps it isn't installed")
        elif exit_code == 3:
            LG().Log(LOG_FATAL, "Failed to obtain auoms plugin state")
        elif exit_code == 4:
            LG().Log(LOG_FATAL, "Failed to obtain current state of oms audit rules")
        elif exit_code == 5:
            LG().Log(LOG_FATAL, "Failed to obtain current state of loaded audit rules")
        else:
            LG().Log(LOG_FATAL, "Unknown error while trying to determine OMSAuditdPlugin state")
        return (None, None, None, None, None, None, None, None, None)

    audit_version = 2
    parts = out_txt.strip().split(".")
    if len(parts) >= 2:
        if parts[0] == "1" and int(parts[1]) < 8:
            audit_version = 1
    elif len(parts) == 1:
        audit_version = int(parts[0])
    else:
        LG().Log(LOG_FATAL, "Could not determine auditd version: Invalid version string returned from 'OMSAuditdPlugin.sh get'")
        return (None, None, None, None, None, None, None, None, None)

    auoms_state_file = os.path.join(GetTmpDir(WorkspaceId), TMP_AUOMS_STATE_FILE)
    rules_file = os.path.join(GetTmpDir(WorkspaceId), TMP_RULES_FILE)
    loaded_rules_file = os.path.join(GetTmpDir(WorkspaceId), TMP_LOADED_RULES_FILE)
    audit_state_file = os.path.join(GetTmpDir(WorkspaceId), TMP_AUDIT_STATE_FILE)

    auoms_state = ReadFile(auoms_state_file)
    if auoms_state is not None:
        auoms_state = auoms_state.strip()

    audit_state = ReadFile(audit_state_file)
    audit_rules = ReadFile(rules_file)
    loaded_audit_rules = ReadFile(loaded_rules_file)

    RemoveFile(auoms_state_file)
    RemoveFile(rules_file)
    RemoveFile(loaded_rules_file)
    RemoveFile(audit_state_file)

    if audit_rules is not None and audit_rules.strip() == "":
        audit_rules = None

    actual_conf = ReadFile(AUOMS_CONF_FILE)
    actual_collect_conf = ReadFile(AUOMSCOLLECT_CONF_FILE)
    actual_outconf = ReadFile(GetAuomOutputConfPath(WorkspaceId))
    actual_plugin_conf = ReadFile(GetOMSAgentConfPath(WorkspaceId))

    return (audit_version, auoms_state, audit_rules, actual_conf, actual_collect_conf, actual_outconf, actual_plugin_conf, loaded_audit_rules, audit_state)

def CanonicalizeAuditRule(txt):
    rule = txt.strip()
    if re.match("^\s*#", rule):
        return None
    if rule.strip() == "":
        return None

    if rule.find("LIST_RULES") == 0:
        rule = re.sub(r"\s+key=\S+", "", rule)
        if rule.find("perm=") > -1:
            rule = re.sub(r"LIST_RULES:\s+exit,always (?:watch|dir)=(\S+)(?: \(0x.\))? perm=(\S+)", r"-w \1 -p \2", rule)
        else:
            rule = re.sub(r"LIST_RULES:\s+exit,always", r"-a always,exit", rule)
            rule = re.sub(r"arch=1073741827 \(0x40000003\)", r"-F arch=b32", rule)
            rule = re.sub(r"arch=3221225534 \(0xc000003e\)", r"-F arch=b64", rule)
            rule = re.sub(r"syscall=(\S+)", r"-S \1", rule)
    else:
        rule = re.sub(r"\s+-k\s+\S+", "", rule)
        rule = re.sub(r"\s+key=\S+", "", rule)
        rule = re.sub(r"(-w\s+(?:/[^/ ]+)+)/?", r"\1", rule)
        rule = re.sub("arch=i386", "arch=b32", rule)
        rule = re.sub("arch=x86_64", "arch=b64", rule)
        rule = re.sub("exit,always", "always,exit", rule)
        rule = " ".join(rule.split())
    return rule

def DiffAuditRules(DesiredRules, LoadedRules):
    if LoadedRules is None or DesiredRules is None:
        return None

    lr = LoadedRules.split("\n")
    lrm = {}
    rules = []
    for r in lr:
        cr = CanonicalizeAuditRule(r)
        if cr is not None:
            lrm[cr] = 1
    dr = DesiredRules.split("\n")
    drm = {}
    for r in dr:
        cr = CanonicalizeAuditRule(r)
        if cr is not None and cr not in lrm:
            rules.append(r)
    if len(rules) == 0:
        return None
    return "\n".join(rules)

def GetEnabledFromAuditState(AuditState):
    for line in AuditState.split("\n"):
        m = re.match(r"^.*enabled[ =]([012])", line)
        if m:
            return m.group(1)
    return "-1"

def ReadFile(Path):
    if not os.path.isfile(Path):
        return None
    return codecs.open(Path, 'r', 'utf8').read().encode('ascii', 'ignore')

def WriteFile(Path, Text):
    codecs.open(Path, 'w', 'utf8').write(Text)

def RemoveFile(Path):
    if os.path.isfile(Path):
        os.remove(Path)

def IsTextDifferent(Text1, Text2):
    if Text1 is None and not Text2 is None:
        return True
    if not Text1 is None and Text2 is None:
        return True
    if Text1 is None and Text2 is None:
        return False

    txt1 = "\n".join(Text1.rstrip().splitlines())
    txt2 = "\n".join(Text2.rstrip().splitlines())

    return txt1 != txt2
