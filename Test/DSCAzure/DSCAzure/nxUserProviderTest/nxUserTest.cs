//-----------------------------------------------------------------------
// <copyright file="nxUserTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

namespace DSCAzure
{
    using System;
    using System.Text;
    using Infra.Frmwrk;
    using System.Collections.Generic;
    using System.IO;
    using System.Text.RegularExpressions;
    
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

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);
      
            ctx.Alw("nxUserTest Setup End."); 
        }

        #region Private Methods

        private string GetInitializeCmd(string userName, string initState)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("userdel -f -r {0};", userName));

            if (initState.ToLower().Equals("present"))
            {
                command.Append(String.Format("useradd {0};", userName));
            }

            return command.ToString();
        }

        private string GetFinalizeCmd(string userName)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("userdel -f -r {0};", userName));

            return command.ToString();
        }

        /*
        public override void Verify(IContext ctx)
        {
            ctx.Alw("Verify Begin.");

            if (String.IsNullOrWhiteSpace(psErrorMsg))
            {
                // Verify if the PowerShell cmdlets were executed without error.
                if (String.IsNullOrWhiteSpace(psHelper.ErrorMsg))
                {
                    ctx.Alw("PowerShell return 0.");
                }
                else
                {
                    throw new VarFail(psHelper.ErrorMsg);
                }

                //string expectedPasswordChangeRequired = ctx.Records.GetValue("expectedPasswordChangeRequired");
                //Dictionary<string, string> verificationMap = propMap;
                //if (!String.IsNullOrEmpty(expectedPasswordChangeRequired))
                //{
                //    if (verificationMap.ContainsKey("PasswordChangeRequired"))
                //    {
                //        verificationMap["PasswordChangeRequired"] = expectedPasswordChangeRequired;
                //    }
                //}
                //else
                //{
                //    ctx.Alw("No specified property need to be verified in varmap");
                //}

                //get the Test-DscConfiguration's returnvalue
                if (psHelper.TestConfigurationReturnValue != -1)
                {
                    string expectedInstallState = ctx.Records.GetValue("expectedInstallState").ToLower();
                    ctx.Alw("The expectedInstallState:" + expectedInstallState + "\n" + "the testConfigurationReturnValude:" + Convert.ToString(psHelper.TestConfigurationReturnValue) + "\n");

                    if (psHelper.TestConfigurationReturnValue == 0)
                    {
                        if (expectedInstallState != "false")
                        {
                            throw new VarFail(string.Format(
                                "The expectedInstallState: '{0}' \n" +
                                "the testConfigurationReturnValude:'{1}'\n",
                                expectedInstallState, Convert.ToString(psHelper.TestConfigurationReturnValue)));
                        }
                    }
                    else if (psHelper.TestConfigurationReturnValue == 1)
                    {
                        if (expectedInstallState != "true")
                        {
                            throw new VarFail(string.Format(
                                "The expectedInstallState: '{0}' \n" +
                                "the testConfigurationReturnValude:'{1}'\n",
                                expectedInstallState, Convert.ToString(psHelper.TestConfigurationReturnValue)));
                        }
                    }
                    ctx.Alw("Verify End.");

                    return;
                } 
            }
            else
            {
                psHelper.CheckErrorMessage(psErrorMsg);
                ctx.Alw(String.Format("PowerShell return error message '{0}' as expected!", psErrorMsg));
            }

            ctx.Alw("Verify End.");
        }
        */
  
        #endregion 
    }
}
