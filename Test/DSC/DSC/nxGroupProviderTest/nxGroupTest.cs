//-----------------------------------------------------------------------
// <copyright file="nxGroupTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Text;
    using Infra.Frmwrk;

    class nxGroupTest : ProviderTestBase
    {
        private string groupName;
        private string initialState;
        private string initialmembers;

        private int nextAvailableGroupID = 0;

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxGroupTest Setup Begin.");

            mofHelper = new GroupMofHelper();

            groupName = ctx.Records.GetValue("groupName");
            initialState = ctx.Records.GetValue("initialState");

            initialmembers = ctx.Records.GetValue("members");

            initializeCmd = GetInitializeCmd(groupName, initialState);

            finalizeCmd = GetFinalizeCmd(groupName);
            base.Setup(ctx);

            if (!propMap.ContainsKey("Members"))
            {
                propMap["Members"] = "";
            }

            if (!propMap.ContainsKey("Ensure"))
            {
                propMap["Ensure"] = "present";
            }

            ctx.Alw("nxGroupTest Setup End.");
        }

        #region Private Methods

        private string GetInitializeCmd(string groupname, string initState)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("groupdel {0};", groupname));

            if (initState.ToLower().Equals("present"))
            {
                command.Append(String.Format("groupadd {0};", groupname));
                if (!string.IsNullOrEmpty(initialmembers))
                {
                    string[] memberArray = initialmembers.Split(',');
                    foreach(string member in memberArray)
                    {
                        command.Append(String.Format("gpasswd -a {0} {1};", member , groupname));   
                    }
                }
            }

            return command.ToString();
        }

        private string GetFinalizeCmd(string groupname)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("groupdel {0};", groupname));

            return command.ToString();
        }

        #endregion
    }
}
