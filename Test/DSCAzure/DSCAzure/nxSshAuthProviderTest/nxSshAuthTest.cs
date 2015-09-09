//-----------------------------------------------------------------------
// <copyright file="nxSshAuthTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Infra.Frmwrk;

namespace DSCAzure
{
    class nxSshAuthTest : ProviderTestBase
    {
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxSshAuthTest Setup Begin.");

            mofHelper = new SshAuthMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            ctx.Alw("nxSshAuthTest Setup End.");
        }

        private string VerifyLogin(string nxUsername, string nxHostName, string userName, string hostName, string password, int port)
        {
            try
            {
                SshHelper tmpHelper = new SshHelper(userName, hostName, password, port);
                tmpHelper.Execute(String.Format("ssh {0}@{1}", userName, hostName));

                string user;
                string host;
                tmpHelper.Execute("whoami", out user);
                tmpHelper.Execute("hostname", out host);
                if (user.ToLower().Equals(nxUsername.ToLower()) && host.ToLower().Equals(nxHostName.ToLower()))
                    return "true";
                else
                    return "false";
            }
            catch (Exception)
            {
                return "false";
            }
        }

        protected override void VerifyLinuxState(IContext ctx)
        {

            if (!string.IsNullOrWhiteSpace(verificationCmd))
            {
                try
                {
                    ctx.Alw(String.Format("Run verification command : '{0}', expect it return '{1}'",
                        verificationCmd, expectedValue));
                    sshHelper.VerifyExecution(verificationCmd, expectedValue);

                    ctx.Alw(successfulyMsg);
                }
                catch (Exception ex)
                {
                    throw new VarFail(failedMsg, ex);
                }
            } 

            string expectedLogin = ctx.Records.GetValue("expectedLogin");
            if (!String.IsNullOrWhiteSpace(expectedLogin))
            {
                string verification = ctx.Records.GetValue("username");
                string userName = ctx.Records.GetValue("username");
                string hostName = ctx.Records.GetValue("hostname");
                string nxHostName = ctx.Records.GetValue("nxHostName");
                string nxUsername = ctx.Records.GetValue("nxUsername");
                string password = ctx.Records.GetValue("password");
                if (String.IsNullOrWhiteSpace(password))
                {
                    password = "OpsMgr2007R2";
                }
                int port = Int32.Parse(ctx.Records.GetValue("port"));
                if (port == 0)
                {
                    port = 23;
                }

                string result = VerifyLogin(nxUsername, nxHostName, userName, hostName, password, port);
                if (!expectedLogin.ToLower().Equals(result))
                {
                    throw new InvalidOperationException(string.Format(
                       "Failed to login {0} with {1} from {2}@{3}",
                       nxHostName,
                       nxUsername,
                       userName,
                       hostName));
                }
               
            }
        }
    }
}
