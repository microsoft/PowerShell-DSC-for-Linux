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

namespace DSC
{
    class nxIPAddressTest : ProviderTestBase
    {
        private string interfaceName;
        private string ifcfg_bak;
        private bool isDU;
        private bool isSuse;
        private SshHelper sshHelper;
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
            ifcfg_bak = "/tmp/eth1_bak";

            try
            {
                // Store the orignal hostname.
                sshHelper.Execute("cat /proc/version", out sysinfo);
                if (sysinfo.Contains("Ubuntu") || sysinfo.Contains("Debian"))
                {
                    isDU = true;
                }
                if (sysinfo.Contains("SUSE"))
                {
                    isSuse = true;
                }
                initializeCmd = GetInitializeCmd(initalSet, isDU, isSuse);
                finalizeCmd = GetFinalizeCmd(isDU,isSuse);

                // Initialize Service State.
                //ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));

                //sshHelper.Execute(initializeCmd);

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
            string interf = string.Empty;
            string configVal = string.Empty;
            string ensureVal = string.Empty;
            string result = string.Empty;
            string addr = verificationMap["IPAddress"];
            string expectedAddr = verificationMap["IPAddress"];

            if (verificationMap.ContainsKey("Ensure"))
            {
                ensureVal = verificationMap["Ensure"];
            }

            if (!verificationMap.ContainsKey("InterfaceName"))
            {
                interf = interfaceName;
            }
            else
            {
                interf = verificationMap["InterfaceName"];
            }

            try
            {
                sshHelper.Execute("ifconfig " + interf, out configVal);
            }
            catch
            { }

            // Get AddressFamily type, the default is "IPV4"
            string addrFamily = "inet *addr";
            if (verificationMap.ContainsKey("AddressFamily"))
            {
                if (verificationMap["AddressFamily"].ToLower().Equals("ipv6"))
                {
                    addrFamily = "inet6 *addr";
                }
            }

            string bootPro = "Static";
            if (verificationMap.ContainsKey("BootProtocol"))
            {
                bootPro = verificationMap["BootProtocol"];
            }
            // Check IPAddress and AddressFamily.
            if (verificationMap.ContainsKey("IPAddress"))
            {
                if (ensureVal.ToLower().Equals("absent"))
                {
                    try
                    {
                        sshHelper.Execute(string.Format("ifconfig {0} |grep -i '{1}'", interfaceName, addr), out result);
                    }
                    catch (Exception ex1)
                    {
                        throw new VarFail(String.Format("Fail to get ip address. "));
                    }                  
                 
                    if (!string.IsNullOrEmpty(result))
                    {
                        throw new VarFail(String.Format("Fail to remove IPAddress {0}", verificationMap["IPAddress"]));

                    }

                }
                else
                {
                    if (bootPro.ToLower().Equals("static"))
                    {
                        //sshHelper.Execute(string.Format("ifconfig {0} |grep -i {1}", interfaceName, addr), out result);
                        sshHelper.Execute(string.Format("ifconfig {0} |grep -i '{1}'", interfaceName, addr), out result);

                        //Ensure is set to 'present'
                        if (string.IsNullOrEmpty(result))
                        {
                            throw new VarFail(String.Format("Fail to set IPAddress {0}", verificationMap["IPAddress"]));
                        }

                    }
                    else
                    {
                        sshHelper.Execute(string.Format("ifconfig {0} |grep -i '{1}'", interfaceName, addrFamily), out result);
                        if (string.IsNullOrEmpty(result))
                        {
                            throw new VarFail(String.Format("Fail to set IPAddress while BootProtocol set to automatic "));

                        }

                    }
                }

                //if (!verificationMap["IPAddress"].Equals(
                //    tmpAddr, StringComparison.InvariantCultureIgnoreCase))
                //{
                //    throw new VarFail(String.Format(
                //        "'{0}' State : expect - '{1}', actual - '{2}'",
                //        "IPAddress", verificationMap["IPAddress"], tmpAddr));
                //}



                // Check DefaultGateway
                if (verificationMap.ContainsKey("DefaultGateway"))
                {
                    string tmpDefaultGW = GetConfigVal("ip route", "default", 2);
                    if (!verificationMap["DefaultGateway"].Equals(
                        tmpDefaultGW, StringComparison.InvariantCultureIgnoreCase))
                    {
                        throw new VarFail(String.Format(
                            "'{0}' State : expect - '{1}', actual - '{2}'",
                            "DefaultGateway", verificationMap["DefaultGateway"], tmpDefaultGW));
                    }
                }

                // Check Mask 
                if (verificationMap.ContainsKey("PrefixLength"))
                {
                    string tmpPrefixLen = GetConfigVal("ifconfig " + interfaceName, "Mask", 1);
                    if (!verificationMap["PrefixLength"].Equals(
                        tmpPrefixLen, StringComparison.InvariantCultureIgnoreCase))
                    {
                        throw new VarFail(String.Format(
                            "'{0}' State : expect - '{1}', actual - '{2}'",
                            "PrefixLength", verificationMap["PrefixLength"], tmpPrefixLen));
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
            string interf = string.Empty;
            string ensureValue = "present";
            string addrFamily = "IPv4";
            if (!initialDict.ContainsKey("InterfaceName"))
            {
                interf = interfaceName;
            }
            else
            {
                interf = initialDict["InterfaceName"];
            }


            //set up the initial test environment if specified
            if (isDU)
            {
                string bootProto = "static";
                string path = "/etc/network/interfaces";

                config.AppendLine(String.Format("auto {0}", interf));

                if (initialDict.ContainsKey("AddressFamily"))
                {
                    addrFamily = initialDict["AddressFamily"];
                    if (addrFamily.ToLower().Equals("ipv6"))
                    {
                        addrFamily = "IPv6";
                    }
                }
                if (initialDict.ContainsKey("IPAddress"))
                {
                    config.AppendLine(String.Format("address {0}", initialDict["IPAddress"]));
                }
                else
                {
                    throw new ArgumentException("Please specify IPAddress value for the initial test environment establishment! ");
                }

                if (initialDict.ContainsKey("BootProtocol"))
                {

                    //should consider about "bootp"?
                    if (initialDict["BootProtocol"] == "Automatic")
                    {
                        bootProto = "dhcp";
                    }

                    if (addrFamily.Equals("IPv6"))
                    {
                        config.AppendLine(String.Format("iface {0} inet6 {1}", interf, bootProto));
                    }
                    else
                    {
                        config.AppendLine(String.Format("iface {0} inet {1}", interf, bootProto));
                    }
                }
                if (initialDict.ContainsKey("DefaultGateway"))
                {
                    config.AppendLine(String.Format("gateway {0}", initialDict["DefaultGateway"]));
                }
                if (initialDict.ContainsKey("PrefixLength"))
                {
                    config.AppendLine(String.Format("netmask {0}", initialDict["PrefixLength"]));
                }

                
                command.Append(String.Format("mv {0} {2}; echo {1} > {0}; /etc/init.d/networking restart", path, config.ToString(), ifcfg_bak));
            }
            else
            {
                string path = "/etc/sysconfig/network-scripts/ifcfg-" + interfaceName;
                if (isSuse)
                {
                     path = "/etc/sysconfig/network/ifcfg-" + interfaceName;
                }

                config.AppendLine(String.Format("DEVICE={0}", interfaceName));

                if (initialDict.ContainsKey("Ensure"))
                {
                    ensureValue = initialDict["Ensure"];
                }
                
                if (ensureValue.ToLower().Equals("absent"))
                {
                    command.AppendLine(string.Format("if [ -f {0} ]; then mv {0} {2}; fi;echo -e \"{1}\" > {0};/etc/init.d/network restart;", path, config.ToString(), ifcfg_bak));
                }
                else
                {
                    if (initialDict.ContainsKey("AddressFamily"))
                    {
                        if (initialDict["AddressFamily"].ToLower().Equals("ipv6"))
                        {
                            addrFamily = "IPv6";
                        }
                    }
                    if (initialDict.ContainsKey("IPAddress"))
                    {
                        if (addrFamily.Equals("IPv6"))
                        {
                            config.AppendLine(String.Format("IPV6ADDR={0}", initialDict["IPAddress"]));
                        }
                        else
                        {
                            config.AppendLine(String.Format("IPADDR={0}", initialDict["IPAddress"]));
                        }
                        
                    }
                    else
                    {
                        throw new ArgumentException("Please specify IPAddress value for the initial test environment establishment! ");
                    }

                    if (initialDict.ContainsKey("BootProtocol"))
                    { 

                        string bootProto = "Static";
                        if (addrFamily.Equals("IPv6"))
                        {
                            if (initialDict["BootProtocol"].ToLower().Equals("automatic"))
                            {
                                bootProto = "dhcp\n" + "IPV6INIT=\"yes\"\nIPV6_AUTOCONF=\"no\"";
                            }
                            else
                            {
                                bootProto = "None\n" + "IPV6INIT=\"yes\"\nIPV6_AUTOCONF=\"no\"";
                            }
                        }
                        else
                        {
                            if (initialDict["BootProtocol"].ToLower().Equals("automatic"))
                            {
                                bootProto = "dhcp";
                            }
                            else
                            {
                                bootProto = "None";
                            }

                        }

                        config.AppendLine(String.Format("BOOTPROTO={0}", bootProto));
                    }

                    if (initialDict.ContainsKey("DefaultGateway"))
                    {
                        //config.AppendLine(String.Format("GATEWAY={0}", initialDict["DefaultGateway"]));
                    }
                    if (initialDict.ContainsKey("PrefixLength"))
                    {
                        config.AppendLine(String.Format("NETMASK={0}", initialDict["PrefixLength"]));
                    }
                   

                    //command.Append(String.Format("if [ -f {0} ]; then mv {0} {0}-old; fi; echo -e \"{1}\" > {0}; ", path, config.ToString())); //TBD:etc/init.d/networking restart

                    command.Append(String.Format("if [ -f {0} ]; then mv {0} {2}; fi; echo -e \"{1}\" > {0}; ", path, config.ToString(), ifcfg_bak));
                }
            }
            return command.ToString();
        }

        private string GetFinalizeCmd(bool isDU, bool isSuse)
        {
            string path = "/etc/sysconfig/network-scripts/ifcfg-" + interfaceName;
            if (isDU)
            {
                path = "/etc/network/interfaces";
            }
            if (isSuse)
            {
                path = "/etc/sysconfig/network/ifcfg-" + interfaceName;
            }

            return String.Format("if [ -f {1} ]; then mv {1} {0}; fi;", path, ifcfg_bak);
        }

        private string Getifcfg_filepath(string sysinfo)
        {
            string filePath = "/etc/sysconfig/network/ifcfg";
            if (sysinfo.Contains("Ubuntu") || sysinfo.Contains("Debian"))
            {
                filePath = "/etc/network/interfaces";
            }

            if (sysinfo.Contains("SUSE"))
            {
                filePath = "/etc/sysconfig/network/ifcfg-";
            }

            return filePath;
        #endregion

        }
    }
}