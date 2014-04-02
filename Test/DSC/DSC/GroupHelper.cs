//-----------------------------------------------------------------------
// <copyright file="GroupHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Test cases group operators: to start DSC omiserver before run and stop DSC omiserver after run.</description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;
    using Infra.Frmwrk;

    public class GroupHelper : ISetup, ICleanup
    {
        private SshHelper sshHelper;

        string getPidCommand;
        string killCommand;
        string startOMIcommand;

        public void Setup(IContext ctx)
        {
            ctx.Alw("GroupHelper Setup Begin");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);

            getPidCommand = ctx.Records.GetValue("getPid");
            killCommand = ctx.Records.GetValue("kill");
            startOMIcommand = ctx.Records.GetValue("startOMI");
            
            // TO-DO: Install DSC Providers.

            // TO-DO: Kill current omiserver process, start omiserver process of DSC.
            string pid;
            sshHelper.Execute(getPidCommand, out pid);

            if (!String.IsNullOrWhiteSpace(pid))
            {
                sshHelper.Execute(String.Format("{0} {1}", killCommand, pid));
                ctx.Alw(String.Format("Kill old omiserver process '{0}'", pid));
            }

            sshHelper.Execute(startOMIcommand);
            ctx.Alw(String.Format("Start DSC omiserver : '{0}'", startOMIcommand));

            ctx.Alw("GroupHelper Setup End");
        }

        public void Cleanup(IContext ctx)
        {
            ctx.Alw("GroupHelper Cleanup Begin");
            
            // TO-DO: Stop omiserver process of DSC.

            // TO-DO: Uninstall DSC Providers.
            string pid;
            sshHelper.Execute(getPidCommand, out pid);

            if (!String.IsNullOrWhiteSpace(pid))
            {
                sshHelper.Execute(String.Format("{0} {1}", killCommand, pid));
                ctx.Alw(String.Format("Kill DSC omiserver process '{0}'", pid));
            }

            sshHelper.Dispose();

            ctx.Alw("GroupHelper Cleanup End");
        }
    }
}
