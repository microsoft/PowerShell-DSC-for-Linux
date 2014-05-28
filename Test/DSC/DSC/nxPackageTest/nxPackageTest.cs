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

namespace DSC
{
    class nxPackageTest : ProviderTestBase
    {
        private const string yum_install_cmmd = "yum install {0}";
        private const string rpm_install_cmmd = "rpm -ivh {0}"+".rpm";
        private const string rpm_check_cmmd = "rpm -qa | grep '{0}*'";
        private const string rpm_remove_cmmd = "package=`rpm -qa |grep '{0}*'`;rpm -e $package";

        private const string apt_install_cmmd = "apt-get install {0}";
        private const string dpkg_install_cmmd = "dpkg -i {0}"+".deb";
        private const string dpkg_groupinstall_cmmd = "dpkg -R {0}";
        private const string dpkg_check_cmmd = "dpkg -l | grep '{0}*'";
        private const string dpkg_remove_cmmd = "package=`dpkg -l |grep '{0}*'`;dpkg -P $package";

        private string localSrcPath = "";
        private bool IsPackageMngr;

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxPackageTest Setup Begin.");

            mofHelper = new PackageMofHelper();

            string initialInstallState = ctx.Records.GetValue("initialInstallState");
            localSrcPath = ctx.Records.GetValue("localSrcPath");
            string packageName = ctx.Records.GetValue("name");
            string manager = ctx.Records.GetValue("manager");
            string keyword = ctx.Records.GetValue("keyword");
            
            string orgInstallState = String.Empty;
            if (ctx.Records.GetValue("propString").Contains("Path:"))
                IsPackageMngr = true;
            else
                IsPackageMngr = false;

            initializeCmd = GetInitializeCmd(packageName, keyword, manager, initialInstallState, out orgInstallState);
            finalizeCmd = GetFinalizeCmd(packageName, keyword, manager, orgInstallState);

            // Initialize Service State.
            ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));
            try
            {
                sshHelper.Execute(initializeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            base.Setup(ctx);
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
                    sshHelper.Execute(String.Format(dpkg_check_cmmd + "|awk -F ' ' '{print $2}'", key), out package);
                    break;
                case "zipper":
                    throw new ArgumentException("The package manager is 'zipper'!");
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }
            
        }

        private string GetInitializeCmd(string packageName, string package, string manager, string initialInstallState, out string orgInstallState)
        {
            string state = GetState(package, manager);
            if ("true" == state)
                orgInstallState = "installed";
            else
                orgInstallState = "uninstalled";

            return GetCmd(packageName, package, manager, initialInstallState);
        }

        private string GetFinalizeCmd(string packageName, string package, string manager, string finalInstallState)
        {
            return GetCmd(packageName, package, manager, finalInstallState);
        }

        private string GetState(string package, string manager)
        {
            string state = string.Empty;
            switch (manager.ToLower())
            {
                case "yum":
                    sshHelper.Execute(String.Format(rpm_check_cmmd + "|wc -l | tr -d '\n'", package), out state);
                    break;
                case "apt":
                    sshHelper.Execute(String.Format(dpkg_check_cmmd + "|wc -l | tr -d '\n'", package), out state);
                    break;
                case "zipper":
                    throw new ArgumentException("The package manager is 'zipper'!");
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }
            if ("0" == state)
                return "false";
            else
                return "true";
        }

        protected override void VerifyLinuxState(IContext ctx)
        {
            string verification = ctx.Records.GetValue("verification");

            if (String.IsNullOrEmpty(verification))
            {
                return;
            }

            var verificationMap = ConvertStringToPropMap(verification);

            string keyword = ctx.Records.GetValue("keyword");
            string manager = verificationMap["PackageManager"];
            string name = string.Empty;
            GetPackage(keyword, manager, out name);
            //string actualDescription = string.Empty;
            //string actualPublisher = string.Empty;
            //string actualInstallOn = string.Empty;
            //string actualSize = string.Empty;
            //string actualVersion = string.Empty;

            // Check package description if needed.
            if (verificationMap.ContainsKey("PackageDescription"))
            {
                string actualDescription = string.Empty;
                checkInfo(name, manager, "Description", out actualDescription);

                if (!verificationMap["PackageDescription"].Equals(
                    actualDescription, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["PackageDescription"], actualDescription));
                }
            }

            // Check package publisher if needed.
            if (verificationMap.ContainsKey("Publisher"))
            {
                string actualPublisher = string.Empty;
                checkInfo(name, manager, "Publisher", out actualPublisher);

                if (!verificationMap["Publisher"].Equals(
                    actualPublisher, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["Publisher"], actualPublisher));
                }
            }

            // Check installation date if needed.
            if (verificationMap.ContainsKey("InstalledOn"))
            {
                string actualInstallOn = string.Empty;
                checkInfo(name, manager, "InstalledOn", out actualInstallOn);

                if (!verificationMap["InstalledOn"].Equals(
                    actualInstallOn, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["InstalledOn"], actualInstallOn));
                }
            }

            // Check package size if needed.
            if (verificationMap.ContainsKey("Size"))
            {
                string actualSize = string.Empty;
                checkInfo(name, manager, "Size", out actualSize);

                if (!verificationMap["Size"].Equals(
                    actualSize, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["Size"], actualSize));
                }
            }

            // Check package version if needed.
            if (verificationMap.ContainsKey("Verison"))
            {
                string actualVerison = string.Empty;
                checkInfo(name, manager, "Verison", out actualVerison);

                if (!verificationMap["Verison"].Equals(
                    actualVerison, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["Verison"], actualVerison));
                }
            }

            // Check whether package is installed or not if needed.
            if (verificationMap.ContainsKey("Installed"))
            {
                string actualInstalled = string.Empty;
                actualInstalled = GetState(name, manager);

                if (!verificationMap["Installed"].ToLower().Equals(
                    actualInstalled, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["Installed"].ToLower(), actualInstalled));
                }
            }

        }

        private void checkInfo(string package, string manager, string property, out string info)
        {
            info = string.Empty;
            if ("yum" == manager.ToLower())
            {
                switch (property.ToLower())
                {
                    case "Description":
                        sshHelper.Execute(String.Format("rpm -qi {0} | awk 'n==1{print} $0~/Description/{n=1}'|grep -v '^$' |grep -v 'You have new mail in*'", package), out info);
                        break;
                    case "Version":
                        sshHelper.Execute(String.Format("rpm -qi {0}|grep '^Version' |sed 's/:/ /g' | sed 's/[ ][ ]*/\n/g'| sed -n '/{1}/{n;p}'", package), out info);
                        break;
                    case "Publisher":
                        sshHelper.Execute(String.Format("rpm -qi {0}|grep '^Vendor' |sed 's/:/ /g' | sed 's/[ ][ ]*/\n/g'| sed -n '/{1}/{n;p}'", package), out info);
                        break;
                    case "Size":
                        sshHelper.Execute(String.Format("rpm -qi {0}|grep '^Size' |sed 's/:/ /g' | sed 's/[ ][ ]*/\n/g'| sed -n '/{1}/{n;p}'", package), out info);
                        break;
                    case "InstalledOn":
                        sshHelper.Execute(String.Format("rpm -qi {0} |grep '^Install' | awk -F 'Build Host' '{print $1}'| awk -F 'Install Date: ' '{print $2}'", package), out info);
                        break;
                    default:
                        throw new ArgumentException("The package manager is invalid!");
                }
            }
            else if ("apt" == manager.ToLower())
            {
                switch (property.ToLower())
                {
                    case "Description":
                        sshHelper.Execute(String.Format("dpkg -p {0} | awk 'n==1{print} $0~/Description/{n=1}'|grep -v '^$' |grep -v 'You have new mail in*'", package), out info);
                        break;
                    case "Version":
                        sshHelper.Execute(String.Format("dpkg -p {0}|grep '^Version' |cut -d ':' -f 2| sed 's/^[ ]*//g'", package), out info);
                        break;
                    case "Publisher":
                        sshHelper.Execute(String.Format("dpkg -p {0}| grep '^Maintainer' |cut -d ':' -f 2| sed 's/^[ ]*//g'", package), out info);
                        break;
                    case "Size":
                        sshHelper.Execute(String.Format("dpkg -p {0}| grep '^Size' |cut -d ':' -f 2| sed 's/^[ ]*//g'", package), out info);
                        break;
                    case "InstalledOn":
                        break;
                    default:
                        throw new ArgumentException("The package manager is invalid!");
                }
            }
            else
            {

            }
        }

        private string GetCmd(string packageName, string package, string manager, string initialInstallState)
        {
            StringBuilder command = new StringBuilder();
            string state = GetState(package, manager);
            switch (manager.ToLower())
            {
                case "yum":
                    if ("true" == initialInstallState.ToLower() && "false" == state)
                    {
                        if (IsPackageMngr)
                            command.Append(String.Format(yum_install_cmmd, packageName));
                        else
                            command.Append(String.Format(rpm_install_cmmd, localSrcPath + packageName));
                    }
                    else if ("false" == initialInstallState.ToLower() && "true" == state)
                    {
                        command.Append(String.Format(rpm_remove_cmmd, package));
                    }
                    else { }
                    break;
                case "apt":
                    if ("true" == initialInstallState.ToLower() && "false" == state)
                    {
                        if (IsPackageMngr)
                            command.Append(String.Format(apt_install_cmmd, packageName));
                        else
                            command.Append(String.Format(dpkg_install_cmmd, localSrcPath + packageName));
                    }
                    else if ("false" == initialInstallState.ToLower() && "true" == state)
                    {
                        command.Append(String.Format(dpkg_remove_cmmd, package));
                    }
                    else { }
                    break;
                case "zipper":
                    throw new ArgumentException("The package manager is 'zipper'!");
                default:
                    throw new ArgumentException("The package manager is invalid!");
            }

            return command.ToString();
        }

    }
}