//-----------------------------------------------------------------------
// <copyright file="nxIPAddressTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

using System;
using System.Text;
using Infra.Frmwrk;
using System.Collections.Generic;

namespace DSCAzure
{
    class nxIPAddressTest : ProviderTestBase
    {
        private string interfaceName;
        private string configFile_bak;
        private string configFilePath;
        private string restartNetworkCmd;
        private bool isDU;
        private bool isSuse;
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxIPAddressTest Setup Begin.");

            mofHelper = new IPAddressMofHelper();

            string initalSet = ctx.Records.GetValue("initialSet");
            interfaceName = ctx.Records.GetValue("interfaceName");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            string sysinfo = string.Empty;
            isDU = false;
            isSuse = false;
            configFile_bak = "/tmp/configFile_bak";
            configFilePath = "/etc/sysconfig/network-scripts/ifcfg-" + interfaceName;
            restartNetworkCmd = "service network restart";
            try
            {
                // Store the orignal hostname.
                sshHelper.Execute("cat /proc/version", out sysinfo);
                if (sysinfo.Contains("Ubuntu") || sysinfo.Contains("Debian"))
                {
                    isDU = true;
                    configFilePath = "/etc/network/interfaces";
                    restartNetworkCmd = "service networking restart";
                }
                if (sysinfo.Contains("SUSE"))
                {
                    isSuse = true;
                    configFilePath = "/etc/sysconfig/network/ifcfg-" + interfaceName;
                }

                initializeCmd = GetInitializeCmd(initalSet, isDU, isSuse);
                finalizeCmd = GetFinalizeCmd(isDU, isSuse);

            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            base.Setup(ctx);

            ctx.Alw("nxIPAddressTest Setup End.");
        }


        // Check Linux service's state and enabled state.
        protected override void VerifyLinuxState(IContext ctx)
        {
            string verification = ctx.Records.GetValue("verification");
            if (String.IsNullOrEmpty(verification))
            {
                return;
            }

            var verificationMap = ConvertStringToPropMap(verification);

            string addr = verificationMap["IPAddress"];

            string result = string.Empty;

            string interf = !verificationMap.ContainsKey("InterfaceName") ? interfaceName : verificationMap["InterfaceName"];

            string ensureVal = !verificationMap.ContainsKey("Ensure") ? "present" : verificationMap["Ensure"];

            string addrFamily = !verificationMap.ContainsKey("AddressFamily") ? "ipv4" : verificationMap["AddressFamily"];

            string bootPro = !verificationMap.ContainsKey("BootProtocol") ? "automatic" : verificationMap["BootProtocol"];

            string addrTag = !addrFamily.ToLower().Equals("ipv6") ? "inet *addr" : "inet6 *addr";

            // When Ensure set to 'Absent'
            if (ensureVal.ToLower().Equals("absent"))
            {
                if (isDU)
                {
                    try
                    {
                        sshHelper.Execute(string.Format("cat {0} |grep -i 'address {1}' 2>/dev/null", configFilePath, addr), out result);
                    }
                    catch (Exception)
                    {
                        if (!String.IsNullOrEmpty(result))
                        {
                            throw new VarFail(String.Format("Fail to remove IPAddress {0}", verificationMap["IPAddress"]));
                        }
                    }
                }
                else
                {
                    try
                    {
                        sshHelper.Execute(string.Format("ifconfig {0} |grep -i '{1}'| grep -i '{2}' 2>/dev/null", interfaceName, addrTag, addr), out result);
                    }
                    catch (Exception)
                    {
                        if (!String.IsNullOrEmpty(result))
                        {
                            throw new VarFail(String.Format("Fail to remove IPAddress {0}", verificationMap["IPAddress"]));
                        }

                    }
                }
            }

            //when Ensure set to 'Present'.
            if (ensureVal.ToLower() == "present")
            {
                ////when 'BOOTPROTO' set to Static
                if (bootPro.ToLower().Equals("static"))
                {
                    try
                    {
                        // Check 'IPAddress'
                        sshHelper.Execute(string.Format("ifconfig {0} |grep -i '{1}'|grep -i '{2}'", interfaceName, addrTag, addr), out result);
                    }
                    catch (Exception)
                    {
                        throw new VarFail(String.Format("Fail to set IPAddress {0}", verificationMap["IPAddress"]));
                    }

                }
                else
                {
                    //when 'BOOTPROTO' set to Automatic
                    if (isDU)
                    {
                        if (addrFamily.ToLower() == "ipv4")
                        {
                            try
                            {
                                sshHelper.Execute(string.Format("cat {0} |grep -i 'iface {1} inet dhcp'", configFilePath, interf), out result);
                            }
                            catch (Exception)
                            {
                                throw new VarFail(String.Format("Fail to set automatic ipv4 address to 'iface {0} inet dhcp'", interf));
                            }
                        }
                        else
                        {
                            // e.g. 'iface eth1 inet6 static'
                            try
                            {
                                sshHelper.Execute(string.Format("cat {0} |grep -i 'iface {1} inet6 static'", configFilePath, interf), out result);
                            }
                            catch (Exception)
                            {
                                throw new VarFail(String.Format("Fail to set automatic ipv6 address to 'iface {0} inet6 static'", interf));
                            }

                            //Check 'autoconf=1'
                            try
                            {
                                sshHelper.Execute(string.Format("cat {0} |grep -i 'autoconf 1'", configFilePath), out result);
                            }
                            catch (Exception)
                            {
                                throw new VarFail(String.Format("Fail to set autoconf to '1'"));
                            }
                        }
                    }
                    else
                    {
                        //Check on cent/oracle/sles/rhel

                        if (addrFamily.ToLower() == "ipv6")
                        {
                            try
                            {
                                sshHelper.Execute(string.Format("cat {0} |grep -i 'IPV6_AUTOCONF=yes'", configFilePath), out result);
                            }
                            catch (Exception)
                            {
                                throw new VarFail(String.Format("Fail to set IPV6_AUTOCONF to 'yes'"));
                            }
                        }

                        //Check 'BOOTPROTO=dhcp'
                        try
                        {
                            sshHelper.Execute(string.Format("cat {0} |grep -i 'BOOTPROTO=dhcp'", configFilePath), out result);
                        }
                        catch (Exception)
                        {
                            throw new VarFail(String.Format("Fail to set BOOTPROTO to 'dhcp'"));
                        }

                    }

                }

                // Check Mask 
                if (verificationMap.ContainsKey("PrefixLength"))
                {
                    string verifyMaskCmd = string.Format("ifconfig {0} |grep -i '{1}'|grep -i 'mask:{2}'", interfaceName, addrTag, verificationMap["PrefixLength"]);

                    if (addrFamily.ToLower() == "ipv6")
                    {
                        verifyMaskCmd = string.Format("ifconfig {0} |grep -i '{1}'|grep -i '/{2}'", interfaceName, addrTag, verificationMap["PrefixLength"]);
                    }

                    if (bootPro.ToLower().Equals("static"))
                    {
                        try
                        {
                            sshHelper.Execute(string.Format("{0}", verifyMaskCmd), out result);
                        }
                        catch (Exception)
                        {
                            throw new VarFail(String.Format("Fail to set net mask {0}", verificationMap["PrefixLength"]));
                        }
                    }
                }
            }
        }
        
        #region Private Methods

        private string GetConfigVal(string cmmd, string item, int step)
        {
            string reval = string.Empty;
            sshHelper.Execute(String.Format("{0}| grep 'inet addr' | awk -F'[ :]+' '{for (i=1;i<=NF;i){if({1} == $i) print $(i+{2})}}", cmmd, item, step), out reval);
            return reval.ToLower();
        }

        private string GetInitializeCmd(string initial, bool isDU, bool isSuse)
        {
            StringBuilder command = new StringBuilder();
            StringBuilder config = new StringBuilder();
            Dictionary<string, string> initialDict = ConvertStringToPropMap(initial);

            string interf = !initialDict.ContainsKey("InterfaceName") ? interfaceName : initialDict["InterfaceName"]; 
            string ensureValue = !initialDict.ContainsKey("Ensure") ? "present" : initialDict["Ensure"]; 
            string addrFamily = !initialDict.ContainsKey("AddressFamily") ? "ipv4" : initialDict["AddressFamily"]; 
            string bootProto = !initialDict.ContainsKey("BootProtocol") ? "automatic" : initialDict["BootProtocol"]; 
            string autocConf = "autoconf 1";

            if (bootProto.ToLower() == "static")
            {
                autocConf = "autoconf 0";
            }

            if (isDU)
            {
                if (ensureValue.ToLower() == "present")
                {
                    config.AppendLine(String.Format("auto {0}", interf));

                    if (initialDict.ContainsKey("IPAddress"))
                    {
                        config.AppendLine(String.Format("address {0}", initialDict["IPAddress"]));
                    }

                    if (addrFamily.ToLower().Equals("ipv6"))
                    {
                        //no dhcp for ipv6, static is correct.
                        bootProto = "static";
                        config.AppendLine(String.Format("iface {0} inet6 {1}\n{2}", interf, bootProto, autocConf));
                    }
                    else
                    {
                        //ipv4
                        if (bootProto.ToLower() == "automatic")
                        {
                            bootProto = "dhcp";
                        }
                        config.AppendLine(String.Format("iface {0} inet {1}\n{2}", interf, bootProto, autocConf));
                    }

                    if (initialDict.ContainsKey("PrefixLength"))
                    {
                        config.AppendLine(String.Format("netmask {0}", initialDict["PrefixLength"]));
                    }

                    command.Append(String.Format("mv {0} {2}; echo {1} > {0}; {3};", configFilePath, config.ToString(), configFile_bak, restartNetworkCmd));
                }
            }
            else
            {
                // On Sles/Rhel/CentOs/Oracle
                config.AppendLine(String.Format("DEVICE={0}", interfaceName));

                if (ensureValue.ToLower().Equals("absent"))
                {
                    command.AppendLine(string.Format("if [ -f {0} ]; then mv {0} {2}; fi;echo -e \"{1}\" > {0};{3};", configFilePath, config.ToString(), configFile_bak, restartNetworkCmd));
                }
                else
                {

                    if (initialDict.ContainsKey("IPAddress"))
                    {

                        config.AppendLine(addrFamily.ToLower().Equals("ipv6")
                            ? String.Format("IPV6ADDR={0}\\nONBOOT=yes", initialDict["IPAddress"])
                            : String.Format("IPADDR={0}\\nONBOOT=yes", initialDict["IPAddress"]));

                    }

                    //set 'BOOTPROTO'
                    if (addrFamily.ToLower().Equals("ipv6"))
                    {
                        if (bootProto.ToLower().Equals("automatic"))
                        {
                            bootProto = "dhcp\n" + "IPV6INIT=\"yes\"\nIPV6_AUTOCONF=\"yes\"";
                        }
                        else
                        {
                            bootProto = "None\n" + "IPV6INIT=\"yes\"\nIPV6_AUTOCONF=\"no\"";
                        }

                    }
                    else
                    {
                        //IPv4
                        bootProto = bootProto.ToLower().Equals("automatic") ? "dhcp" : "None";

                    }
                    config.AppendLine(String.Format("BOOTPROTO={0}", bootProto));

                    if (initialDict.ContainsKey("PrefixLength"))
                    {
                        config.AppendLine(String.Format("NETMASK={0}", initialDict["PrefixLength"]));
                    }

                    command.Append(String.Format("if [ -f {0} ]; then mv {0} {2}; fi; echo -e \"{1}\" > {0};{3};", configFilePath, config.ToString(), configFile_bak, restartNetworkCmd));
                }
            }
            return command.ToString();
        }

        private string GetFinalizeCmd(bool isDU, bool isSuse)
        {
            return String.Format("if [ -f {1} ]; then mv {1} {0}; {2}; fi;", configFilePath, configFile_bak, restartNetworkCmd);
        }


        #endregion


    }
}