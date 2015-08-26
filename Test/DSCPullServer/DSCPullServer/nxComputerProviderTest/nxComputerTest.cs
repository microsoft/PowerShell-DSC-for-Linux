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

namespace DSCPullServer
{
    class nxComputerTest : ProviderTestBase
    {

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxComputerTest Setup Begin.");

            mofHelper = new ComputerMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

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