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

namespace DSC
{
    class nxFirewallTest : ProviderTestBase
    {
        private string initialSet;
        private string cmmdFirewall;
        private const string beforeRule = "/tmp/before.rule";
        private const string afterRule = "/tmp/after.rule";
        
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxFirewallTest Setup Begin.");
            mofHelper = new EnvironmentMofHelper();

            initialSet = ctx.Records.GetValue("initialSet");
            string addrFamily = ctx.Records.GetValue("addrFamily");
            
            if (!String.IsNullOrWhiteSpace(addrFamily) && addrFamily.Equals("6"))
            {
                cmmdFirewall = "ip6tables";
            }
            else 
            {
                cmmdFirewall = "iptables";
            }

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            string sysinfo = string.Empty;
            //bool isUbuntu = false;
            string rulePath = "/tmp/firewall.rules";

            initializeCmd = GetInitializeCmd(initialSet, rulePath);
            finalizeCmd = GetFinalizeCmd(rulePath);

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

            ctx.Alw("nxFirewallTest Setup End.");
        }



        // Check Linux service's state and enabled state.
        protected override void VerifyLinuxState(IContext ctx)
        {
            StringBuilder command = new StringBuilder();
            string verification = ctx.Records.GetValue("verification");
            string proto = string.Empty;
            string access = string.Empty;
            string state = string.Empty;
            string direction = string.Empty;
            string sHost = string.Empty;
            string sProt = string.Empty;
            string dHost = string.Empty;
            string dPort = string.Empty;
            string status = String.Empty;
            var verificationMap = ConvertStringToPropMap(verification);

            if (verificationMap.ContainsKey("Present"))
            {
                status = "Present";
            }
            else
            {
                status = "Absent";
            }

            // Construct the firewall by given values 
            if (verificationMap.ContainsKey("Protocol"))
            {
                proto = " -p " + verificationMap["Protocol"];
            }
            if (verificationMap.ContainsKey("Access"))
            {
                state = " -j " + verificationMap["Access"];   
            }
            if (verificationMap.ContainsKey("State"))
            {
                state = " -m state --state " + verificationMap["State"];
            }
            if (verificationMap.ContainsKey("State1"))
            {
                state = state + "," + verificationMap["State1"];
            }
            if (verificationMap.ContainsKey("State2"))
            {
                state = state + "," + verificationMap["State2"];
            }
            if (verificationMap.ContainsKey("Direction"))
            {
                direction = " " + verificationMap["Direction"];
            }
            if (verificationMap.ContainsKey("SourceHost"))
            {
                sHost = " -s " + verificationMap["SourceHost"];
            }
            if (verificationMap.ContainsKey("SourcePort"))
            {
                sProt = " --sport " + verificationMap["SourcePort"];
            }
            if (verificationMap.ContainsKey("DestinationHost"))
            {
                dHost = " -d " + verificationMap["DestinationHost"];
            }
            if (verificationMap.ContainsKey("DestinationPort"))
            {
                dPort = " --dport " + verificationMap["DestinationPort"];
            }

            try
            {
                string diff = string.Empty;
                string iptCmmd = " -A" + proto + state + direction + sHost + sProt + dHost + dPort + access;
                sshHelper.Execute(String.Format("{0}-save | grep '^-' >{1};", cmmdFirewall, afterRule));

                if (status.Equals("Present"))
                {   
                    sshHelper.Execute(String.Format("diff {0} {1} | grep '^>' | sed 's/<//g' ", beforeRule, afterRule), out diff);
                }
                else
                {
                    sshHelper.Execute(String.Format("diff {0} {1} | grep '^<' | sed 's/<//g'", beforeRule, afterRule), out diff);
                }

                if (!diff.Replace(" ", "").ToLower().Equals(iptCmmd.Replace(" ", "").ToLower()))
                {
                    throw new VarFail(String.Format(
                       "Firewall rule : expect '{0}' item - '{1}', actual - '{2}'",
                       status, diff, iptCmmd));
                }
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }
            
        }

        #region Private Methods

        private string GetInitializeCmd(string initialSet, string rulePath)
        {
            StringBuilder command = new StringBuilder();

            // restore the original firewall rules
            command.Append(String.Format("{0}-save > {1};", cmmdFirewall, rulePath));

            command.Append(String.Format("{0} -P INPUT ACCEPT; {0} -F; {0} -A INPUT -p tcp --dport 22 -j ACCEPT;", cmmdFirewall));
            command.Append(String.Format("{0}-save | grep '^-' >{1};", cmmdFirewall, beforeRule));
            return command.ToString();
        }

        private string GetFinalizeCmd(string rulePath)
        {
            StringBuilder command = new StringBuilder();

            //restore the original firewall rules
            command.Append(String.Format("{0} -F; {0}-restore > {1}; {0} -A INPUT -p tcp --dport 22 -j ACCEPT;", cmmdFirewall, rulePath));
            return command.ToString();
        }

        #endregion
    }
}







