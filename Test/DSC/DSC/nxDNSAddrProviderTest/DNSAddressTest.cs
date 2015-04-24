//-----------------------------------------------------------------------
// <copyright file="nxDNSAddrProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------
using System;
using System.Text;
using Infra.Frmwrk;
using System.IO;

namespace DSC
{
    class DNSAddressTest : ProviderTestBase
    {
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxDNSAddrTest Setup Begin.");

            mofHelper = new FileMofHelper();

            string dnsBKPath = "/tmp/resolv_bk.conf";

            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
            configMofScriptPath = ctx.Records.GetValue("configMofScriptPath");
            psScripts = ctx.Records.GetValues("psScript");
            psErrorMsg = ctx.Records.GetValue("psErrorMsg");
            verificationCmd = ctx.Records.GetValue("verificationCmd");
            expectedValue = ctx.Records.GetValue("expectedValue");
            successfulyMsg = ctx.Records.GetValue("successfulMsg");
            failedMsg = ctx.Records.GetValue("failedMsg");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);

            initializeCmd = GetInitializeCmd(dnsBKPath);
            finalizeCmd = GetFinalizeCmd(dnsBKPath);

            // Initialize Service State.
            ctx.Alw(String.Format("Initilize Linux state: '{0}'", initializeCmd));
            try
            {
                sshHelper.Execute(initializeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            // Prepare a configuration MOF file.

            propMap = ConvertStringToPropMap(propString);
            mofHelper.PrepareMofGenerator(propMap, configMofScriptPath, nxHostName, mofPath);
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

            ctx.Alw("nxDNSAddrTest Setup End.");
        }
   
        // Check Linux service's state and enabled state.
        protected override void VerifyLinuxState(IContext ctx)
        {
            string addrs = ctx.Records.GetValue("verification");
            try
            {
                if (!string.IsNullOrEmpty(addrs))
                {
                    string[] addrArray = addrs.Split(',');
                    string retval = string.Empty;
                    foreach (string addr in addrArray)
                    {
                        retval = "-1";
                        sshHelper.Execute(String.Format("cat /etc/resolv.conf | grep 'nameserver {0}'|echo $?",addr), out retval);
                        if (!retval.Equals("0"))
                        {
                            throw new VarFail(String.Format("DNS Service Address : expect - {0}", addr));
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }
        }

        #region Private Methods

        private string GetInitializeCmd(string dnsPath)
        {
            StringBuilder command = new StringBuilder();

            // keep a backup for the original DNS setting
            command.Append(String.Format("cp /etc/resolv.conf {0}", dnsPath));
            return command.ToString();
        }
        private string GetFinalizeCmd(string dnsPath)
        {
            StringBuilder command = new StringBuilder();

            //restore the original firewall rules
            command.Append(String.Format("mv {0} /etc/resolv.conf", dnsPath));
            return command.ToString();
        }

        #endregion
    }
}
