//-----------------------------------------------------------------------
// <copyright file="nxPackage.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------
using System;
using System.Text;
using Infra.Frmwrk;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace DSCAzure
{
    class nxPackageTest : ProviderTestBase
    {
        private const string yum_install_cmmd = "yum install -y {0}";
        private const string rpm_install_cmmd = "rpm -ivh {0}";
        private const string rpm_check_cmmd = "rpm -qa | grep '{0}*'";
        private const string rpm_remove_cmmd = "package=`rpm -qa |grep '{0}*'`;rpm -e $package";

        private const string apt_install_cmmd = "apt-get install {0} --allow-unauthenticated";
        private const string dpkg_install_cmmd = "dpkg -i {0}";
        private const string dpkg_groupinstall_cmmd = "dpkg -R {0}";
        private const string dpkg_check_cmmd = "dpkg -l {0}";
        private const string dpkg_remove_cmmd = "dpkg --purge {0}";

        private string localSrcPath = "";
        private bool IsPackageMngr;
        private string suffix = String.Empty;
        private string manager = String.Empty;
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxPackageTest Setup Begin.");
            
            //
            caseID = ((IVarContext)ctx).VarID.ToString();
            varID = "Node" + caseID;
            isNeedCompile = ctx.Records.GetValue("isNeedCompile");
            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
            configFilePath = ctx.Records.GetValue("configFilePath");
            configMofScriptPath = ctx.Records.GetValue("configMofScriptPath");

            pullServerDirectory = ctx.Records.GetValue("pullServerDirectory");
            psScripts = ctx.Records.GetValues("psScript");
            configAzure = ctx.Records.GetValues("configAzure");
            getNodeIdCmd = ctx.Records.GetValues("getNodeIdCmd");
            importConfigToAzure = ctx.Records.GetValues("importConfigToAzure");
            setAzureAutomation = ctx.Records.GetValues("setAzureAutomation");
            removeNode = ctx.Records.GetValues("removeNode");
            psErrorMsg = ctx.Records.GetValue("psErrorMsg");
            verificationCmd = ctx.Records.GetValue("verificationCmd");
            expectedValue = ctx.Records.GetValue("expectedValue");
            successfulyMsg = ctx.Records.GetValue("successfulMsg");
            failedMsg = ctx.Records.GetValue("failedMsg");
            forcePullpullServerCmd = ctx.Records.GetValue("forcePullpullServerCmd");
            azureMofFileName = ctx.Records.GetValue("azureMofFileName");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            string nxDomainName = ctx.Records.GetValue("nxDomainName");
            string configurationName = ctx.Records.GetValue("configurationName");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            metaFileName = nxHostName + "." + nxDomainName + ".meta.mof";
            tmpMofFileFullName = configFilePath + "\\" + azureMofFileName;
            newMofFileFullName = configFilePath + "\\" + metaFileName;

            string expectedInstallState = ctx.Records.GetValue("expectedInstallState");
            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);

            if (ctx.Records.GetValue("propString").Contains("FilePath:"))
            {
                string sysinfo = String.Empty;

                sshHelper.Execute("cat /proc/version", out sysinfo);
                if (sysinfo.ToLower().Contains("debian") || sysinfo.ToLower().Contains("ubuntu"))
                {
                    manager = "apt";
                }
                else if (sysinfo.ToLower().Contains("suse"))
                {
                    manager = "zypper";
                }
                else
                    manager = "yum"; 
            }
            else
            {
                manager = ctx.Records.GetValue("manager");
            }

            
            if ("apt" == manager)
            {
                suffix = "deb";
            }  
            else if ("zypper" == manager || "yum" == manager )
            {
                suffix = "rpm";
            }
            else
            {
                ctx.Alw("The package manager is invalid");
            }

            string orgInstallState = String.Empty;
            if (ctx.Records.GetValue("propString").Contains("Path:"))
                IsPackageMngr = true;
            else
                IsPackageMngr = false;

            string packageName = ctx.Records.GetValue("name");
            string initialInstallState = ctx.Records.GetValue("initialInstallState");
            localSrcPath = ctx.Records.GetValue("localSrcPath");
            if (!String.IsNullOrWhiteSpace(localSrcPath))
            {
                localSrcPath = localSrcPath + "." + suffix;
                string[] items = localSrcPath.Split('/');
                string name = items[items.Length - 1];
                try 
                {
                    sshHelper.Execute("rm /tmp/" + name);
                }
                catch { }
                    
                if (!localSrcPath.Contains("//"))
                {
                    try
                    {
                        PosixCopy psxCopy = new PosixCopy(nxHostName, nxUsername, nxpassword);
                        psxCopy.CopyTo("..\\Package\\" + name, "/tmp/" + name);
                    }
                    catch
                    {
                        ctx.Alw("Copy package: failed!");
                    }
                }    
                
            }
           
            initializeCmd = GetInitializeCmd(packageName, manager, initialInstallState, out orgInstallState);
            finalizeCmd = GetFinalizeCmd(packageName, manager, expectedInstallState, orgInstallState);

            // Initialize Service State.
            ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));
            ctx.Alw(String.Format("Finalize Linux state : '{0}'", finalizeCmd));
            try
            {
                sshHelper.Execute(initializeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            //connect to Azure.
            ctx.Alw(String.Format("Run PowerShell : '{0}'", configAzure));
            psHelper.Run(configAzure);

            // Prepare a configuration MOF file.
            mofHelper = new PackageMofHelper();
            propMap = ConvertStringToPropMap(propString);
            if (propMap.ContainsKey("FilePath"))
            {
                propMap["FilePath"] = propMap["FilePath"] + "." + suffix;
            }
            mofHelper.PrepareMofGenerator(propMap, configMofScriptPath, mofPath, varID, configurationName);
            ctx.Alw(String.Format("Prepare a MOF generator '{0}'",
                configMofScriptPath));

            // Add the config to the logs
            StreamReader sr = new StreamReader(configMofScriptPath);
            string line = null;
            StringBuilder configFile = new StringBuilder();
            line = sr.ReadLine();
            while (line != null)
            {
                line = line.Replace("{", "{{").Replace("}", "}}");
                configFile.Append(line);
                line = sr.ReadLine();
            }
            ctx.Alw(String.Format(configFile.ToString()));

            ctx.Alw("nxPackageTest Setup End.");
        }

        private void GetPackage(string key, string manager, out string package)
        {
            package = "";
            switch (manager.ToLower())
            {
                case "yum":
                    sshHelper.Execute(String.Format(rpm_check_cmmd, key), out package);
                    break;
                case "apt":
                    sshHelper.Execute(String.Format(dpkg_check_cmmd, key) + "|awk -F ' ' '{print $2}'|tr -d '\n'", out package);
                    break;
                case "zypper":
                    sshHelper.Execute(String.Format(dpkg_check_cmmd, key) + "|awk -F ' ' '{print $2}'|tr -d '\n'", out package);
                    break;
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }

        }

        private string GetInitializeCmd(string packageName, string manager, string initialInstallState, out string orgInstallState)
        {
            string state = GetState(packageName, manager).ToLower();
            orgInstallState = state;
            return GetCmd(packageName, manager, state, initialInstallState);
        }

        private string GetFinalizeCmd(string packageName, string manager, string expectedInstallState, string finalInstallState)
        {
            return GetCmd(packageName, manager, expectedInstallState, finalInstallState);
        }

        private string GetState(string package, string manager)
        {
            string state = string.Empty;
            switch (manager.ToLower())
            {
                case "yum":
                    try
                    {
                        sshHelper.Execute("rpm -qa|grep " + package + "| wc -l | tr -d '\n'", out state);
                        if ( "0" == state)
                        {
                            return "False";
                        }
                        else
                        {
                            return "True";
                        }
                    }
                    catch
                    {
                        return "False";
                    }
                case "apt":
                    try
                    {
                        sshHelper.Execute("dpkg-query -W -f='${Status}' " + package + "| tr -d '\n'", out state);
                        if (state.Contains("deinstall") || state.Contains("not-installed") )
                        {
                            return "False";
                        }
                        else
                        {
                            return "True";
                        }
                    }
                    catch
                    {
                        return "False";
                    }
                   
                case "zypper":
                    try
                    {
                         sshHelper.Execute("rpm -qa|grep " + package + "| wc -l | tr -d '\n'", out state);
                        if ( "0" == state)
                        {
                            return "False";
                        }
                        else
                        {
                            return "True";
                    }
                     }
                    catch
                    {
                        return "False";
                    }
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }
        }

        public override void Verify(IContext ctx)
        {
            ctx.Alw("Verify Begin.");

            if (String.IsNullOrWhiteSpace(psErrorMsg))
            {
                // Verify if the PowerShell cmdlets were executed without error.
                if (String.IsNullOrWhiteSpace(psHelper.ErrorMsg))
                {
                    try
                    {
                        sshHelper.Execute(forcePullpullServerCmd);
                    }
                    catch (Exception ex)
                    {
                        ctx.Alw(ex.Message);
                    }
                }
                else
                {
                    throw new VarFail(psHelper.ErrorMsg);
                }

                Dictionary<string, string> linuxMap = new Dictionary<string, string>();
                string name = ctx.Records.GetValue("Name");
                string verification = ctx.Records.GetValue("verification");
                Dictionary<string, string> verificationMap = new Dictionary<string, string>();
                if (!String.IsNullOrEmpty(verification))
                {
                    verificationMap = ConvertStringToPropMap(verification);

                    if (verificationMap.ContainsKey("FilePath"))
                    {
                        verificationMap["FilePath"] = verificationMap["FilePath"] + "." + suffix;
                    }
                }
                else
                {
                    ctx.Alw("No specified property need to be verified in varmap");
                }


                //Get property value from Linux
                linuxMap = GetLinuxValue(name, propMap);

                foreach (string key in verificationMap.Keys)
                {
                    if (!linuxMap.ContainsKey(key))
                    { continue; }
                    string actualDescription = linuxMap[key];

                    // Check property value with Get-DscConfiguration
                    if (!String.IsNullOrEmpty(actualDescription))
                    {
                        // Check property value specified in varmap
                        if (verificationMap.ContainsKey(key))
                        {
                            if (!verificationMap[key].Equals(actualDescription, StringComparison.InvariantCultureIgnoreCase))
                            {
                                throw new VarFail(String.Format(
                                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                                        key, verificationMap[key], actualDescription));
                            }
                        }
                    }
                }
            }
            else
            {
                try
                {
                    //Fail to execute force pull server command when it should send error message.
                    sshHelper.Execute(forcePullpullServerCmd);
                }
                catch (Exception)
                {
                    ctx.Alw(String.Format("Send the error message"));
                }
            }

            ctx.Alw("Verify End.");
        }

        private Dictionary<string, string> GetLinuxValue(string package, Dictionary<string, string> map)
        {
            string[] dpkgQuery = new string[6];
            string info = string.Empty;
            switch (manager.ToLower())
            {
                case "apt":
                    try
                    {
                        sshHelper.Execute("dpkg-query -W -f='PackageDescription:::${Description}|Publisher:::${Maintainer}|InstalledOn:::'Unknown'|Size:::${Installed-Size}|Version:::${Version}|Status:::${Status}' " + package, out info);
                        if (!info.Contains("not-installed") && !info.Contains("deinstall"))
                        {
                            //sshHelper.Execute("dpkg-query -W -f='PackageDescription:::${Description}|Publisher:::${Maintainer}|InstalledOn:::'Unknown'|Size:::${Installed-Size}|Version:::${Version}' " + package, out info);
                            dpkgQuery = (info + "|Installed:::True").Split('|');
                        }
                        else
                        {
                            dpkgQuery = (info + "|Installed:::False").Split('|');
                            //dpkgQuery = new string[] { "PackageDescription:::''", "Publisher:::''", "InstalledOn:::Unknown", "Size:::0", "Version:::''", "Installed:::False" };
                        }
                    }
                    catch
                    {
                        dpkgQuery = new string[] { "PackageDescription:::", "Publisher:::", "InstalledOn:::", "Size:::0", "Version:::", "Installed:::False" };
                    }
                    break;
                case "yum":
                    sshHelper.Execute("rpm -qa|grep " + package + " | wc -l | tr -d '\n' " , out info);
                    if ("1" == info )
                    {
                        sshHelper.Execute("rpm -q --queryformat 'PackageDescription:::%{SUMMARY}|Publisher:::%{PACKAGER}|InstalledOn:::%{INSTALLTIME}|Size:::%{SIZE}|Version:::%{VERSION}' " + package, out info);
                        dpkgQuery = (info + "|Installed:::True").Split('|');
                    }
                    else
                    {
                        dpkgQuery = new string[] { "PackageDescription:::", "Publisher:::", "InstalledOn:::", "Size:::0", "Version:::", "Installed:::False" };
                    }
                    break;
                case "zypper":
                    sshHelper.Execute("rpm -qa|grep " + package + " | wc -l | tr -d '\n' " , out info);
                    if ("1" == info )
                    {
                        sshHelper.Execute("rpm -q --queryformat 'PackageDescription:::%{SUMMARY}|Publisher:::%{PACKAGER}|InstalledOn:::%{INSTALLTIME}|Size:::%{SIZE}|Version:::%{VERSION}' " + package, out info);
                        dpkgQuery = (info + "|Installed:::True").Split('|');
                    }
                    else
                    {
                        dpkgQuery = new string[] { "PackageDescription:::", "Publisher:::", "InstalledOn:::", "Size:::0", "Version:::", "Installed:::False" };
                    }
                    break;
                default:
                    break;
            }
            foreach (string property in dpkgQuery)
            {
                string[] propDic = Regex.Split(property,":::");
                map[propDic[0]] = propDic[1];
            }
            if (String.IsNullOrEmpty(map["Size"]))
            {
                map["Size"] = "0";
            }
            map["PackageDescription"] = map["PackageDescription"].Replace("\n", "&#10;");
            return map;
        }        
           
        private string GetCmd(string packageName, string manager, string state, string initialInstallState)
        {
            StringBuilder command = new StringBuilder();
            state = state.ToLower();
            switch (manager.ToLower())
            {
                case "yum":
                    if ("true" == initialInstallState.ToLower() && "false" == state)
                    {
                        command.Append(IsPackageMngr
                            ? String.Format(rpm_install_cmmd, localSrcPath)
                            : String.Format(yum_install_cmmd, packageName));
                    }
                    else if ("false" == initialInstallState.ToLower() && "true" == state)
                    {
                        command.Append(String.Format(rpm_remove_cmmd, packageName));
                    }
                    else { }
                    break;
                case "apt":
                    if ("true" == initialInstallState.ToLower() && "false" == state)
                    {
                        command.Append(IsPackageMngr
                            ? String.Format(dpkg_install_cmmd, localSrcPath)
                            : String.Format(apt_install_cmmd, packageName));
                    }
                    else if ("false" == initialInstallState.ToLower() && "true" == state)
                    {
                        command.Append(String.Format(dpkg_remove_cmmd, packageName));
                    }
                    else { }
                    break;
                case "zypper":
                    if ("true" == initialInstallState.ToLower() && "false" == state)
                    {
                        command.Append(IsPackageMngr
                            ? String.Format(rpm_install_cmmd, localSrcPath)
                            : String.Format("zypper --non-interactive install", packageName));
                    }
                    else if ("false" == initialInstallState.ToLower() && "true" == state)
                    {
                        command.Append(String.Format(rpm_remove_cmmd, packageName));
                    }
                    else { }
                    break;
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }
            return command.ToString();
        }
    }
}