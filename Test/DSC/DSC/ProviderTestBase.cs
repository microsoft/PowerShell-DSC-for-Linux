//-----------------------------------------------------------------------
// <copyright file="BaseProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A base class about provider test.</description>
//-----------------------------------------------------------------------
namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using Infra.Frmwrk;
    
    public class ProviderTestBase : ISetup, IRun, IVerify, ICleanup
    {
        protected MofHelper mofHelper;

        protected PsHelper psHelper = new PsHelper();

        protected SshHelper sshHelper;
        protected string initializeCmd;
        protected string finalizeCmd;

        protected string propString;
        protected string mofPath;
        protected string configMofScriptPath;

        protected string[] psScripts;
        protected string psErrorMsg;

        protected string verificationCmd;
        protected string expectedValue;
        protected string successfulyMsg;
        protected string failedMsg;

        protected Dictionary<string, string> propMap;

        public virtual void Setup(IContext ctx)
        {
            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("scriptLocation");
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

            // Create/Delete the specific file/folder.
            ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));
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
        }

        public virtual void Run(IContext ctx)
        {
            ctx.Alw("Run Begin.");
            
            // Run PowerShell script to get/send configuration MOF.
            ctx.Alw(String.Format("Run PowerShell : '{0}'", psScripts));
            psHelper.Run(psScripts);

            ctx.Alw("Run End.");
        }

        public virtual void Verify(IContext ctx)
        {
            ctx.Alw("Verify Begin.");

            #region Check PowerShell Result

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

                // Check the result of GetConfiguration.
                ctx.Alw("The result of Get-DscConfiguration:");
                foreach (var key in propMap.Keys)
                {
                    try
                    {
                        psHelper.CheckOutput(key, propMap[key]);
                        ctx.Alw(String.Format("\t{0} : {1}", key, propMap[key]));
                    }
                    catch (VarFail ex)
                    {
                        throw new VarFail(ex.Message);
                    }
                }
            }
            else
            {
                psHelper.CheckErrorMessage(psErrorMsg);
                ctx.Alw(String.Format("PowerShell return error message '{0}' as expected!", psErrorMsg));
            }

            #endregion

            #region Check Linux State

            // Verify Linux machine state.
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

            #endregion
            
            ctx.Alw("Verify End.");
        }

        public virtual void Cleanup(IContext ctx)
        {
            ctx.Alw("Cleanup Begin.");
            
            // Delete created file/folder.
            ctx.Alw(String.Format("Finalize Linux state : '{0}'", finalizeCmd));
            try
            {
                sshHelper.Execute(finalizeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }
            
            // Delete MOF file.
            ctx.Alw(String.Format("Delete MOF generator : '{0}'", configMofScriptPath));
            mofHelper.DeleteMof(configMofScriptPath);

            // Dispose ps runspace.
            psHelper.Dispose();

            // Dispose ssh connection.
            sshHelper.Dispose();

            ctx.Alw("Cleanup End.");
        }

        private Dictionary<string, string> ConvertStringToPropMap(string propString)
        {
            string[] properties = propString.Split(';');

            return (from property in properties
                    where !String.IsNullOrWhiteSpace(property)
                    select property.Split(':'))
                    .ToDictionary(propertyMap => propertyMap[0], propertyMap => propertyMap[1]);
        } 
    }
}
