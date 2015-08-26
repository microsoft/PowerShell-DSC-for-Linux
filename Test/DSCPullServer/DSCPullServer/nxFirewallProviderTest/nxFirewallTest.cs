//-----------------------------------------------------------------------
// <copyright file="nxFirewallTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------
using System;
using System.Text;
using Infra.Frmwrk;
using System.Collections.Generic;

namespace DSCPullServer
{
    class nxFirewallTest : ProviderTestBase
    {
        private string initialSet;
        private string firewallType;
        private string iptableType;
        private const string beforeRule = "/tmp/before.rule";
        private const string afterRule = "/tmp/after.rule";
        private const string rulePath = "/root/ipt.rule";
        private const string firewalldCmd = "service firewalld stop; service firewalld start;";

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxFirewallTest Setup Begin.");
            mofHelper = new FirewallMofHelper();

            initialSet = ctx.Records.GetValue("initialSet");
            firewallType = ctx.Records.GetValue("type").ToLower();
            iptableType = firewallType.Equals("ip6tables") ? "ip6tables" : "iptables";

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);

            CheckfirewallTypeIsValid(ctx);

            initializeCmd = GetInitializeCmd();
            finalizeCmd = GetFinalizeCmd();

            base.Setup(ctx);

            ctx.Alw("nxFirewallTest Setup End.");
        }

        protected override void VerifyLinuxState(IContext ctx)
        {
            string verification = ctx.Records.GetValue("verification");
            if (string.IsNullOrEmpty(verification))
            {
                return;
            }

            var verificationMap = ConvertStringToPropMap(verification);
            string proto = verificationMap.ContainsKey("Protocol") ? verificationMap["Protocol"] : "tcp";
            string access = verificationMap.ContainsKey("Access") ? verificationMap["Access"] : string.Empty;
            string position = verificationMap.ContainsKey("Position") ? verificationMap["Position"] : "top";
            string addrFamily = verificationMap.ContainsKey("AddressFamily") ? verificationMap["AddressFamily"] : "IPv4";
            string status = verificationMap.ContainsKey("Ensure") ? verificationMap["Ensure"] : "present";
            string state = string.Empty;
            string direction = string.Empty;
            string sHost = string.Empty;
            string sProt = string.Empty;
            string dHost = string.Empty;
            string dPort = string.Empty;

            string protocol = " -i eth0 -p " + proto;
            if (verificationMap["Direction"].ToLower().Equals("output"))
            {
                protocol = " -p " + proto;
            }

            if (access.ToLower().Equals("allow"))
            {
                access = " -j ACCEPT";
            }
            else if (access.ToLower().Equals("block"))
            {
                access = " -j DROP";
            }
            if (verificationMap.ContainsKey("State"))
            {
                state = " -m state --state " + verificationMap["State"];
            }

            //set the direction for different firewall type.
            if (verificationMap.ContainsKey("Direction"))
            {
                direction = " " + verificationMap["Direction"];

                if (firewallType.Equals("ufw"))
                {
                    if (position.ToLower().Equals("top"))
                    {
                        direction = " ufw-before-" + verificationMap["Direction"].ToLower();
                    }
                    else if (position.ToLower().Equals("end"))
                    {
                        direction = " ufw-after-" + verificationMap["Direction"].ToLower();
                    }
                    else
                    {
                        direction = " ufw-user-" + verificationMap["Direction"].ToLower();
                    }
                }


                if (firewallType.Equals("firewalld"))
                {
                    direction = " " + verificationMap["Direction"] + "_direct";
                }

            }

            if (verificationMap.ContainsKey("SourceHost"))
            {
                sHost = " -s " + verificationMap["SourceHost"] + "/32";
                if (addrFamily.ToLower().Equals("ipv6"))
                {
                    sHost = " -s " + verificationMap["SourceHost"] + "::/128";
                }
            }

            if (verificationMap.ContainsKey("SourcePort"))
            {
                sProt = " -m " + proto + " --sport " + verificationMap["SourcePort"];
            }

            if (verificationMap.ContainsKey("DestinationHost"))
            {
                dHost = " -d " + verificationMap["DestinationHost"] + "/32";
                if(addrFamily.ToLower().Equals("ipv6"))
                {
                    dHost = " -d " + verificationMap["DestinationHost"] + "::/128";
                }
            }

            if (verificationMap.ContainsKey("DestinationPort"))
            {
                dPort = " -m " + proto + " --dport " + verificationMap["DestinationPort"];
            }

            string iptCmmd = " -A" + direction + sHost + dHost + protocol + sProt + dPort + state + access;

            try
            {
                sshHelper.Execute(String.Format("{0}-save | grep '^-' > {1};", iptableType, afterRule));
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            string diff = string.Empty;
            if (status.ToLower().Equals("present"))
            {
                sshHelper.Execute(String.Format("diff {0} {1} | grep '^>' | sed 's/<//g'|cut -d '>' -f2 |tr -d '\n'", beforeRule, afterRule), out diff);
                if (!diff.Replace(" ", "").ToLower().Equals(iptCmmd.Replace(" ", "").ToLower()))
                {
                    throw new VarFail(String.Format("Firewall rule : expect - '{0}', actual - '{1}'", iptCmmd, diff));
                }
            }
            else
            {
                sshHelper.Execute(String.Format("diff {0} {1} | grep '^<' | sed 's/<//g'|tr -d '\n'", beforeRule, afterRule), out diff);
                if (!diff.Replace(" ", "").ToLower().Equals(iptCmmd.Replace(" ", "").ToLower()))
                {
                    throw new VarFail(String.Format("beforeRule is : '{0}', afterRule is : '{1}'", beforeRule, afterRule));
                }
            }
        }

        #region Private Methods

        private string GetInitializeCmd()
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("{0}-save |grep '' > {1};", iptableType, rulePath));

            if (iptableType.Equals("firewalld"))
            {
                command.Append(firewalldCmd);
                command.Append(String.Format("{0} -P INPUT ACCEPT; iptables -A INPUT_direct -p tcp -m tcp --dport 22 -j ACCEPT", iptableType));
            }
            else
            {
                command.Append(String.Format("{0} -P INPUT ACCEPT; {0} -A INPUT -p tcp --dport 22 -j ACCEPT;", iptableType));
            }
            if (!string.IsNullOrEmpty(initialSet))
            {
                Dictionary<string, string> initialDict = ConvertStringToPropMap(initialSet);

                string proto = initialDict.ContainsKey("Protocol") ? initialDict["Protocol"] : "tcp";
                string protocol = " -i eth0 -p " + proto;
                string access = initialDict.ContainsKey("Access") ? initialDict["Access"] : string.Empty;
                string direction = string.Empty;
                string state = string.Empty;

                if (access.ToLower().Equals("allow"))
                {
                    access = " -j ACCEPT";
                }
                else if (access.ToLower().Equals("block"))
                {
                    access = " -j DROP";
                }

                if (initialDict.ContainsKey("Direction"))
                {
                    switch (firewallType.ToLower())
                    {
                        case "iptables":
                            direction = " " + initialDict["Direction"];
                            break;
                        case "ufw":
                            direction = " ufw-before-" + initialDict["Direction"].ToLower();
                            break;
                        case "yast":
                            direction = " " + initialDict["Direction"];
                            break;
                        case "susefirewall2":
                            direction = " " + initialDict["Direction"];
                            break;
                        case "firewalld":
                            direction = " " + initialDict["Direction"] + "_direct";
                            break;
                        case "ip6tables":
                            direction = " " + initialDict["Direction"];
                            break;
                    }
                }
                if (initialDict.ContainsKey("State"))
                {
                    state = " -m state --state " + initialDict["State"];
                }

                string initialCmmd = " -A" + direction + protocol + state + access;
                command.Append(String.Format("{0} {1};", iptableType, initialCmmd));
            }
        
            command.Append(String.Format("{0}-save | grep '^-' >{1};", iptableType, beforeRule));

            return command.ToString();
        }

        private string GetFinalizeCmd()
        {
            StringBuilder command = new StringBuilder();

            //restore the original firewall rules
            command.Append(String.Format("cat {0} | {1}-restore; rm -rf {0}", rulePath, iptableType));

            return command.ToString();
        }

        private void CheckfirewallTypeIsValid(IContext ctx)
        {
            string sysinfo = string.Empty;

            try
            {
                sshHelper.Execute("cat /proc/version", out sysinfo);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            if (sysinfo.Contains("Ubuntu") || sysinfo.Contains("Debian"))
            {
                if (firewallType.Equals("yast") || firewallType.Equals("susefirewall2") || firewallType.Equals("firewalld"))
                {
                    throw new VarUnsupported("The firewall type is unsopport on Debian/Ubuntu ");
                }
            }
            else if (sysinfo.Contains("SUSE"))
            {
                if (firewallType.Equals("ufw") || firewallType.Equals("firewalld"))
                {
                    throw new VarUnsupported("The firewall type is unsopport on SUSE.");
                }
            }
            else if (sysinfo.Contains("el7"))
            {
                if (firewallType.Equals("yast") || firewallType.Equals("susefirewall2") || firewallType.Equals("ufw"))
                {
                    throw new VarUnsupported("The firewall type is unsopport on CentOS 7");
                }
            }
            else
            {
                if (firewallType.Equals("yast") || firewallType.Equals("susefirewall2") || firewallType.Equals("ufw") || firewallType.Equals("firewalld"))
                {
                    throw new VarUnsupported("The firewall type is unsopport on other OS.");
                }
            }
        }
        #endregion
    }
}







