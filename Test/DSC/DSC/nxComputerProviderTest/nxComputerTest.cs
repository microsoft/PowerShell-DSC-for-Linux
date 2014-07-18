//-----------------------------------------------------------------------
// <copyright file="nxComputerTest.cs" company="Microsoft">
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
    class nxComputerTest : ProviderTestBase
    {
        private string orgHostName;
        private const string orgTimeZone = "/etc/localtime-old";

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxComputerTest Setup Begin.");

            mofHelper = new EnvironmentMofHelper();

            string hostName = ctx.Records.GetValue("computerName");
            string timeZone = ctx.Records.GetValue("timeZone");
            string initalHostName = ctx.Records.GetValue("initalHostName");
            if (String.IsNullOrWhiteSpace(initalHostName))
            {
                initalHostName = "initalHostName";
            }
            string initalTimeZone = ctx.Records.GetValue("initalTimeZone");
            if (String.IsNullOrWhiteSpace(initalTimeZone))
            {
                initalTimeZone = "America/Los_Angeles";
            }

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            try
            {
                // Store the orignal hostname.
                sshHelper.Execute("hostname", out orgHostName);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            initializeCmd = GetInitializeCmd(initalHostName, initalTimeZone, orgTimeZone);
            finalizeCmd = GetFinalizeCmd(orgHostName, orgTimeZone);

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

            ctx.Alw("nxComputerTest Setup End.");
        }

        #region Private Methods

        private string GetInitializeCmd(string hostName, string timeZone, string orgLocalTime)
        {
            StringBuilder command = new StringBuilder();
            
            //configure the intial environment(hostname and timezone) as required
            command.Append(String.Format("hostname {0};mv /etc/localtime {1};ln -sf /usr/share/zoneinfo/{2} /etc/localtime;", hostName, timeZone, orgLocalTime));
            return command.ToString();
        }

        private string GetFinalizeCmd(string hostName, string timeZone)
        {
            StringBuilder command = new StringBuilder();

            //reset to the original hostname and timezone
            command.Append(String.Format("hostname {0}; mv {1} /etc/localtime ", hostName, timeZone));
            return command.ToString();
        }

        #endregion
    }
}