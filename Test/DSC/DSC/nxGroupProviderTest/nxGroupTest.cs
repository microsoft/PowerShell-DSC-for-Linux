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
    using System.Collections.Generic;

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


        protected override Dictionary<string, string> GetLinuxValue()
        {
            Dictionary<string, string> linuxValueMap = new Dictionary<string, string>();
            string groupName = propMap["GroupName"];
            string members = propMap.ContainsKey("Members") ? propMap["Members"] : string.Empty;
            string membersToInclude = propMap.ContainsKey("MembersToInclude") ? propMap["MembersToInclude"] : string.Empty;
            string membersToExclude = propMap.ContainsKey("MembersToExclude") ? propMap["MembersToExclude"] : string.Empty;
            string ensureVal = propMap.ContainsKey("Ensure") ? propMap["Ensure"] : "present";
            string preferredGroupID = string.Empty;

            if (ensureVal.ToLower() == "present")
            {
                try
                {
                    const string cmd = "cat /etc/group |grep -i {0} |cut -d ':' -f3 |tr -d '\n'";
                    string getGroupCmd = cmd.Replace("{0}", groupName);

                    sshHelper.Execute(getGroupCmd, out preferredGroupID);
                }
                catch (Exception)
                {
                    throw new VarFail(String.Format("Fail to get GroupID of user: {0}", groupName));
                }

                // If 'Members' exist, membersToInclude and membersToExclude are invalid.
                if (!string.IsNullOrEmpty(members))
                {
                    linuxValueMap["Members"] = members;
                }

                if (!string.IsNullOrEmpty(membersToInclude))
                {
                    linuxValueMap["Members"] = membersToInclude;
                }

                if (!string.IsNullOrEmpty(membersToExclude))
                {
                    linuxValueMap["Members"] = "";
                }
                
                linuxValueMap["MembersToInclude"] = membersToInclude;
                linuxValueMap["MembersToExclude"] = membersToExclude;
                linuxValueMap["PreferredGroupID"] = preferredGroupID;
            }
            else
            {
                //if Ensure is 'absent', the value is null.
                linuxValueMap["MembersToInclude"] = "";
                linuxValueMap["MembersToExclude"] = "";
                linuxValueMap["PreferredGroupID"] = "";
                linuxValueMap["Members"] = "";
            }

            return linuxValueMap;
        } 
        #endregion
    }
}
