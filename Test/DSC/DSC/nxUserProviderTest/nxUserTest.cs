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

                string expectedPasswordChangeRequired = ctx.Records.GetValue("expectedPasswordChangeRequired");
                Dictionary<string, string> verificationMap = propMap;
                if (!String.IsNullOrEmpty(expectedPasswordChangeRequired))
                {
                    if (verificationMap.ContainsKey("PasswordChangeRequired"))
                    {
                        verificationMap["PasswordChangeRequired"] = expectedPasswordChangeRequired;
                    }
                }
                else
                {
                    ctx.Alw("No specified property need to be verified in varmap");
                }

                //Return from Get-DscConfiguration
                Dictionary<string, string> list = psHelper.LastPowerShellReturnValues[0];
                list.Remove("CimClass");
                list.Remove("CimInstanceProperties");
                list.Remove("CimSystemProperties");
                list.Remove("PSShowComputerName");
                list.Remove("PSComputerName");
                string rltGetDSC = "The result of Get-DscConfiguration:\n\n************************************************";
                foreach (string key in list.Keys)
                {
                    rltGetDSC = rltGetDSC + String.Format("\n{0,-20}:{1}", key, list[key]);
                }
                ctx.Alw(rltGetDSC + "\n************************************************\n");
                //Get property value from Linux
                //TBD
                //Dictionary<string, string> linuxMap = new Dictionary<string, string>();
                //linuxMap = GetLinuxValue(name, propMap);

                ///////////////////////
                foreach (string key in list.Keys)
                {
                    if (!verificationMap.ContainsKey(key))
                    { continue; }
                    string actualDescription = verificationMap[key];

                    // Check property value with Get-DscConfiguration
                    if (!String.IsNullOrEmpty(actualDescription))
                    {
                        try
                        {
                            psHelper.CheckOutput(key, actualDescription);
                            ctx.Alw(String.Format("Check Get-DscConfiguration: {0} is pass", key));
                        }
                        catch (VarFail ex)
                        {
                            throw new VarFail(ex.Message);
                        }
                    }
                }
            }
            else
            {
                psHelper.CheckErrorMessage(psErrorMsg);
                ctx.Alw(String.Format("PowerShell return error message '{0}' as expected!", psErrorMsg));
            }

            ctx.Alw("Verify End.");
        }
        #endregion 
    }
}
