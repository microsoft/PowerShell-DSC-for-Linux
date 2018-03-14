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
AUOMS_OUTCONF_DIR = '/etc/opt/microsoft/auoms/outconf.d'
AUOMS_PLUGIN_CONF = '/etc/audisp/plugins.d/auoms.conf'
SUDO_SCRIPT = '/opt/microsoft/omsconfig/Scripts/OMSAuditdPlugin.sh'
MODULE_RESOURCE_DIR = '/opt/microsoft/omsconfig/modules/nxOMSAuditdPlugin/DSCResources/MSFT_nxOMSAuditdPluginResource'
RESOURCE_OMSAGENT_CONF = MODULE_RESOURCE_DIR + '/conf/auditd_plugin.conf'
RESOURCE_AUOMS_V1_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v1.conf'
RESOURCE_AUOMS_V2_CONF = MODULE_RESOURCE_DIR + '/conf/auoms_v2.conf'
RESOURCE_OUTPUT_V1_CONF = MODULE_RESOURCE_DIR + '/conf/output_v1.conf'
RESOURCE_OUTPUT_V2_CONF = MODULE_RESOURCE_DIR + '/conf/output_v2.conf'
RESOURCE_AUDIT_RULES_V1 = MODULE_RESOURCE_DIR + '/rules/oms-security-audit-v1.rules'
RESOURCE_AUDIT_RULES_V2 = MODULE_RESOURCE_DIR + '/rules/oms-security-audit-v2.rules'
RESOURCE_SUDO_SCRIPT = MODULE_RESOURCE_DIR + '/Scripts/OMSAuditdPlugin.sh'

AUOMS_BIN = '/opt/microsoft/auoms/bin/auoms'
AUDITD_BIN = '/sbin/auditd'

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

def GetTmpAuomsOutputConfPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "output.conf")

def GetAuomOutputConfPath(WorkspaceId):
    return os.path.join(AUOMS_OUTCONF_DIR, WorkspaceId + ".conf")

def GetTmpAuditRulesPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "auditd_plugin.rules")

def GetTmpAuditLoadedRulesPath(WorkspaceId):
    return os.path.join(GetTmpDir(WorkspaceId), "auditd_loaded.rules")

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

    (audit_version, plugin_state, actual_audit_rules, actual_conf,
     actual_outconf, actual_plugin_conf, loaded_audit_rules) = GetState(WorkspaceId)
    if audit_version is None:
        return [1]

    (desired_plugin_state, desired_rules, desired_conf, desired_outconf,
     desired_plugin_conf) = GetDesiredState(WorkspaceId, Ensure, audit_version, plugin_state)
    if desired_plugin_state is None:
        return [1]

    arg1 = ""
    agent_restart_ignore_error = False
    if IsTextDifferent(actual_plugin_conf, desired_plugin_conf):
        LG().Log(LOG_INFO, "Actual Plugin conf differs from Desired plugin conf so omsagent will be restarted")
        arg1 = WorkspaceId
        if desired_plugin_conf is None:
            RemoveFile(GetOMSAgentConfPath(WorkspaceId))
        else:
            agent_restart_ignore_error = True
            WriteFile(GetOMSAgentConfPath(WorkspaceId), desired_plugin_conf)

    if arg1 == "" and OmsAgentNeedsRestart(WorkspaceId):
        LG().Log(LOG_INFO, "Plugin conf has changed since omsagent start, omsagent will be restarted")
        arg1 = WorkspaceId

    rules_file_path = ""
    if IsTextDifferent(actual_audit_rules, desired_rules):
        if desired_rules is None:
            LG().Log(LOG_INFO, "Auditd rules will be removed")
            rules_file_path = "remove"
        else:
            LG().Log(LOG_INFO, "Actual auditd rules differ from desired auditd rules")
            rules_file_path = GetTmpAuditRulesPath(WorkspaceId)
            WriteFile(rules_file_path, desired_rules)

    conf_path = ""
    if IsTextDifferent(actual_conf, desired_conf):
        LG().Log(LOG_INFO, "Actual auoms conf differs from desired conf")
        conf_path = GetTmpAuomsConfPath(WorkspaceId)
        WriteFile(conf_path, desired_conf)

    outconf_name = ""
    outconf_path = ""
    if IsTextDifferent(actual_outconf, desired_outconf):
        outconf_name = WorkspaceId + ".conf"
        if desired_outconf is None:
            LG().Log(LOG_INFO, "auoms output conf will be removed")
            outconf_path = "remove"
        else:
            LG().Log(LOG_INFO, "Actual auoms output conf differs from desired output conf")
            outconf_path = GetTmpAuomsOutputConfPath(WorkspaceId)
            WriteFile(outconf_path, desired_outconf)

    # On some systems the auditd reload will cause rule load as well
    # So, to prevent trying to load rules twice (and getting an error as a result)
    # Only check loaded rules if rules file already contains the rules
    # This may cause a 5 minute delay between when plugin is enabled
    # and when rules are actually loaded
    rules_diff = ""
    rules_diff_path = ""
    if actual_audit_rules is not None:
        rules_diff = DiffAuditRules(desired_rules, loaded_audit_rules)
        if rules_diff is not None:
            LG().Log(LOG_INFO, "Not all desired auditd rules are loaded")
            LG().Log(LOG_INFO, "Missing rules are: \n%s" % rules_diff)
            rules_diff_path = GetTmpAuditLoadedRulesPath(WorkspaceId)
            WriteFile(rules_diff_path, rules_diff)

    # Run script that will restart omsagent and enable+start/disable+stop auoms
    args = []
    args.append("/usr/bin/sudo")
    args.append(SUDO_SCRIPT)
    args.append("set")
    args.append(arg1)
    if plugin_state != desired_plugin_state:
        args.append(desired_plugin_state)
    else:
        args.append("")
    args.append(rules_file_path)
    args.append(outconf_name)
    args.append(outconf_path)
    args.append(rules_diff_path)
    args.append(conf_path)
    proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    exit_code = proc.wait()
    if exit_code != 0:
        out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
        err_txt = proc.stderr.read().decode('utf8', 'replace').encode('utf8', 'replace')
        LG().Log(LOG_ERROR, "Command failed: " + " ".join(args))
        LG().Log(LOG_INFO, "stdout: " + out_txt)
        LG().Log(LOG_INFO, "stderr: " + err_txt)
        if exit_code == 2:
            if agent_restart_ignore_error:
                LG().Log(LOG_ERROR, "Failed to restart omsagent")
            else:
                LG().Log(LOG_FATAL, "Failed to restart omsagent")
        elif exit_code == 3:
            if desired_plugin_state == "yes":
                LG().Log(LOG_FATAL, "Failed to enable OMS Auditd Plugin")
            else:
                LG().Log(LOG_FATAL, "Failed to disable OMS Auditd Plugin")
        elif exit_code == 4:
            LG().Log(LOG_FATAL, "Failed to change OMS auditd rules")
        elif exit_code == 5:
            LG().Log(LOG_FATAL, "Failed to change OMS Auditd Plugin output config")
        elif exit_code == 6:
            if desired_plugin_state == "yes":
                LG().Log(LOG_FATAL, "OMS Auditd Plugin failed to start")
            else:
                LG().Log(LOG_FATAL, "OMS Auditd Plugin failed to stop")
        elif exit_code == 7:
            LG().Log(LOG_FATAL, "Failed to change loaded OMS auditd rules")
        elif exit_code == 8:
            LG().Log(LOG_FATAL, "Failed to trigger auditd service reload")
        elif exit_code == 9:
            LG().Log(LOG_FATAL, "Failed to change OMS Auditd Plugin config")
        else:
            LG().Log(LOG_FATAL, "Unknown error while trying to apply desired OMS Auditd Plugin changes")

    RemoveFile(GetTmpAuomsConfPath(WorkspaceId))
    RemoveFile(GetTmpAuomsOutputConfPath(WorkspaceId))
    RemoveFile(GetTmpAuditRulesPath(WorkspaceId))
    RemoveFile(GetTmpAuditLoadedRulesPath(WorkspaceId))

    return [exit_code]

def Test(WorkspaceId, DesiredEnsure):
    if not IsValidWorkspaceId(WorkspaceId):
        LG().Log(LOG_FATAL, "Invalid workspace id")
        # Failed to determine state, return fake success
        return [0]

    if not os.path.isfile(AUDITD_BIN):
        if DesiredEnsure == "Present":
            LG().Log(LOG_FATAL, "Auditd needs to be installed")
        return [0]

    if not os.path.isfile(AUOMS_BIN):
        if DesiredEnsure == "Present":
            LG().Log(LOG_FATAL, "OMS Auditd Plugin needs to be installed")
        return [0]

    if IsSudoScriptOutOfDate():
        LG().Log(LOG_INFO, "sudo script needs to be updated")
        return [-1]

    if OmsAgentNeedsRestart(WorkspaceId):
        LG().Log(LOG_INFO, "omsagent needs restart")
        return [-1]

    (audit_version, plugin_state, actual_audit_rules, actual_conf,
     actual_outconf, actual_plugin_conf, loaded_audit_rules) = GetState(WorkspaceId)
    if audit_version is None:
        # Failed to get state, return fake success
        return [0]

    (desired_plugin_state, desired_rules, desired_conf, desired_outconf,
     desired_plugin_conf) = GetDesiredState(WorkspaceId, DesiredEnsure, audit_version, plugin_state)
    if desired_plugin_state is None:
        # Failed to get desired state, return fake success
        return [0]

    if desired_plugin_state != plugin_state:
        LG().Log(LOG_INFO, "Plugin State does not match desired state")
        return [-1]

    if IsTextDifferent(desired_rules, actual_audit_rules):
        LG().Log(LOG_INFO, "Audit Rules do not match desired rules")
        return [-1]

    if IsTextDifferent(desired_conf, actual_conf):
        LG().Log(LOG_INFO, "auoms conf does not match desired conf")
        return [-1]

    if IsTextDifferent(desired_outconf, actual_outconf):
        LG().Log(LOG_INFO, "auoms outconf does not match desired conf")
        return [-1]

    if IsTextDifferent(desired_plugin_conf, actual_plugin_conf):
        LG().Log(LOG_INFO, "Plugin Conf does not match desired conf")
        return [-1]

    rules_diff = DiffAuditRules(desired_rules, loaded_audit_rules)
    if rules_diff is not None:
        LG().Log(LOG_INFO, "One or more desired audit rules are not loaded")
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
    

def GetDesiredAuditRules(AuditVersion):
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

def GetAuomsVersion():
    deb_ver = None
    rpm_ver = None
    if os.path.isfile("/usr/bin/dpkg-query"):
        args = []
        args.append("/usr/bin/dpkg-query")
        args.append("-f")
        args.append("${Version}")
        args.append("-W")
        args.append("auoms")
        proc = subprocess.Popen(args, -1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        exit_code = proc.wait()
        out_txt = proc.stdout.read().decode('utf8', 'replace').encode('utf8', 'replace')
        if exit_code == 0:
            deb_ver = out_txt
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
        args.append("auoms")
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

def GetDesiredAuomsConf():
    conf_path = RESOURCE_AUOMS_V1_CONF
    outconf_path = RESOURCE_OUTPUT_V1_CONF
    auoms_ver = GetAuomsVersion()
    if auoms_ver is not None:
        ver_a = auoms_ver.split(".")
        if len(ver_a) >= 2:
            if ver_a[0] > 1 or ver_a[1] > 1:
                conf_path = RESOURCE_AUOMS_V2_CONF
                outconf_path = RESOURCE_OUTPUT_V2_CONF
    conf_txt = ReadFile(conf_path)
    outconf_txt = ReadFile(outconf_path)
    return (conf_txt, outconf_txt)

def GetDesiredState(WorkspaceId, Ensure, AuditVersion, CurrentPluginState):
    desired_plugin_state = "no"
    desired_rules = None
    desired_outconf = None
    desired_plugin_conf = None

    (other_conf_count, other_ws_conf_count) = GetOtherOutconfCounts(WorkspaceId)

    if Ensure == "Present":
        desired_plugin_state = "yes"
        desired_rules = GetDesiredAuditRules(AuditVersion)
        (desired_conf, desired_outconf) = GetDesiredAuomsConf()
        desired_plugin_conf = ReadFile(RESOURCE_OMSAGENT_CONF)

        if desired_rules is None:
            LG().Log(LOG_FATAL, "Failed to determine desired audit rules")
            return (None, None, None, None, None)

        if desired_conf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired auoms conf")
            return (None, None, None, None, None)

        if desired_outconf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired output conf")
            return (None, None, None, None, None)

        if desired_plugin_conf is None:
            LG().Log(LOG_FATAL, "Failed to determine desired plugin conf")
            return (None, None, None, None, None)

        desired_outconf = desired_outconf.replace(WORKSPACE_ID_TMPL_STR, WorkspaceId)
        desired_plugin_conf = desired_plugin_conf.replace(WORKSPACE_ID_TMPL_STR, WorkspaceId)

        if other_conf_count > 0 and other_conf_count > other_ws_conf_count:
            # There are non-OMS outconf present. This likely means AzSecPack is present
            # So, don't touch the auoms conf file.
            desired_conf = ReadFile(AUOMS_CONF_FILE)
    else:
        if other_conf_count > 0:
            if other_ws_conf_count > 0:
                # There are other workspace outconfs present, so the desired state is "yes"
                desired_plugin_state = "yes"
            else:
                # If the only other outconfs are non-OMS, then we don't
                # want to change the auoms plugin state
                desired_plugin_state = CurrentPluginState
        # If there are any other workspaces with auoms outconf files, then
        # we don't want to remove the audit rules
        if other_ws_conf_count > 0:
            desired_rules = GetDesiredAuditRules(AuditVersion)
            if desired_rules is None:
                LG().Log(LOG_FATAL, "Failed to determine desired audit rules")
                return (None, None, None, None, None)

    return (desired_plugin_state, desired_rules, desired_conf, desired_outconf, desired_plugin_conf)

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
            LG().Log(LOG_FATAL, "Failed to obtain current state of oms auditd rules")
        elif exit_code == 5:
            LG().Log(LOG_FATAL, "Failed to obtain current state of loaded auditd rules")
        else:
            LG().Log(LOG_FATAL, "Unknown error while trying to determine OMSAuditdPlugin state")
        return (None, None, None, None, None, None)

    audit_version = 2
    parts = out_txt.strip().split(".")
    if len(parts) >= 2:
        if parts[0] == "1" and int(parts[1]) < 8:
            audit_version = 1
    else:
        LG().Log(LOG_FATAL, "Could not determine auditd version: Invalid version string returned from 'OMSAuditdPlugin.sh get'")
        return (None, None, None, None, None, None, None)

    state_file = os.path.join(GetTmpDir(WorkspaceId), "auditd_plugin.state")
    rules_file = os.path.join(GetTmpDir(WorkspaceId), "auditd_plugin.rules")
    loaded_rules_file = os.path.join(GetTmpDir(WorkspaceId), "auditd_loaded.rules")
    plugin_state = ReadFile(state_file)
    if plugin_state is not None:
        plugin_state = plugin_state.strip()

    audit_rules = ReadFile(rules_file)
    loaded_audit_rules = ReadFile(loaded_rules_file)
    RemoveFile(state_file)
    RemoveFile(rules_file)
    RemoveFile(loaded_rules_file)

    if plugin_state != "no" and plugin_state != "yes":
        LG().Log(LOG_FATAL, "OMS-Auditd-Plugin configuration is missing or invalid")
        return (None, None, None, None, None, None, None)

    if audit_rules is not None and audit_rules.strip() == "":
        audit_rules = None

    actual_conf = ReadFile(AUOMS_CONF_FILE)
    actual_outconf = ReadFile(GetAuomOutputConfPath(WorkspaceId))
    actual_plugin_conf = ReadFile(GetOMSAgentConfPath(WorkspaceId))

    return (audit_version, plugin_state, audit_rules, actual_conf, actual_outconf, actual_plugin_conf, loaded_audit_rules)

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
