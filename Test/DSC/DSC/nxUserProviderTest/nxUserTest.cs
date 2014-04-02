//-----------------------------------------------------------------------
// <copyright file="nxUserTest.cs" company="Microsoft">
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
    
    class nxUserTest : ProviderTestBase
    {
        private string username;
        private string initialState;

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxUserTest Setup Begin.");

            mofHelper = new UserMofHelper();

            username = ctx.Records.GetValue("username");
            initialState = ctx.Records.GetValue("initialState");

            initializeCmd = GetInitializeCmd(username, initialState);

            base.Setup(ctx);

            ctx.Alw("nxUserTest Setup End."); 
        }

        #region Private Methods

        private string GetInitializeCmd(string username, string initState)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("userdel -f -r {0};", username));

            if (initState.ToLower().Equals("present"))
            {
                command.Append(String.Format("useradd {0};", username));
            }

            return command.ToString();
        }

        private string GetFinalizeCmd(string username)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("userdel -f -r {0};", username));

            return command.ToString();
        }

        #endregion 
    }
}
