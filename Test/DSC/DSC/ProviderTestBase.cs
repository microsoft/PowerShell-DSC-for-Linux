//-----------------------------------------------------------------------
// <copyright file="BaseProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A base class about provider test.</description>
//-----------------------------------------------------------------------

using System.IO;
using System.Text;

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
            //the TestConfigurationReturnValude defalut val
            psHelper.TestConfigurationReturnValue = -1;

            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
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

            // Add the config to the logs
            StreamReader sr = new StreamReader(configMofScriptPath);        
            StringBuilder configFile = new StringBuilder();

            //The temp variable line is to read a line from the temp variable sr.It's recycle variable.
            string line = null;
            line = sr.ReadLine();
            while (line != null)
            {
                line = line.Replace("{", "{{").Replace("}","}}");
                configFile.Append(line);
                line = sr.ReadLine();
            }
            ctx.Alw(String.Format(configFile.ToString()));
                
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

                //get the Test-DscConfiguration's returnvalue
                if (psHelper.TestConfigurationReturnValue != -1)
                {
                    
                    
                    string expectedInstallState = ctx.Records.GetValue("expectedInstallState").ToLower();
                    ctx.Alw("The expectedInstallState:" + expectedInstallState + "\n" +"the TestConfigurationReturnValue:" + Convert.ToString(psHelper.TestConfigurationReturnValue) + "\n");

                    if (psHelper.TestConfigurationReturnValue == 0)
                    {
                        if (expectedInstallState != "false")
                        {
                            throw new VarFail(string.Format(
                                "The expectedInstallState: '{0}' \n" +
                                "the TestConfigurationReturnValue:'{1}'\n",
                                expectedInstallState, Convert.ToString(psHelper.TestConfigurationReturnValue)));
                        }
                    }
                    else if (psHelper.TestConfigurationReturnValue == 1)
                    {
                        if (expectedInstallState != "true")
                        {
                            throw new VarFail(string.Format(
                                "The expectedInstallState: '{0}' \n" +
                                "the TestConfigurationReturnValue:'{1}'\n",
                                expectedInstallState, Convert.ToString(psHelper.TestConfigurationReturnValue)));
                        }
                    }
                    ctx.Alw("Verify End.");

                    return;
                }

                // Check the result of GetConfiguration.
                ctx.Alw("The result of Get-DscConfiguration:");

                //Get the value of properties from Linux.
                Dictionary<string, string> linuxMap = GetLinuxValue();            

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

                Dictionary<string, string> varMap = mofHelper.ReturnedPropertiesOfGetDscConfiguration(propMap);
                foreach (string key in list.Keys)
                {

                    if (linuxMap.ContainsKey(key))                  
                    {
                        string actualDescription = linuxMap[key];

                        // Check Linux property value with Get-DscConfiguration
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

                    if (propMap.ContainsKey(key))
                    {
                        string mapProperty = varMap[key];

                        // Check varmap property value with Get-DscConfiguration
                        if (!String.IsNullOrEmpty(mapProperty))
                        {
                            try
                            {
                                psHelper.CheckOutput(key, mapProperty);
                                ctx.Alw(String.Format("Check Get-DscConfiguration: {0} is pass", key));
                            }
                            catch (VarFail ex)
                            {
                                throw new VarFail(ex.Message);
                            }
                        }
                    }
                }

                // Verify Linux machine state.
                VerifyLinuxState(ctx);
                
            }
            else
            {
                psHelper.CheckErrorMessage(psErrorMsg);
                ctx.Alw(String.Format("PowerShell return error message '{0}' as expected!", psErrorMsg));
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
            ctx.Alw(String.Format("Delete MOF generator : '{0}'", mofPath));
            mofHelper.DeleteMof(mofPath);

            // Dispose ps runspace.
            psHelper.Dispose();

            // Dispose ssh connection.
            sshHelper.Dispose();

            ctx.Alw("Cleanup End.");
        }

        protected Dictionary<string, string> ConvertStringToPropMap(string propString)
        {
            string[] properties = propString.Split(';');
            
            return (from property in properties
                    where !String.IsNullOrWhiteSpace(property)
                    select property.Split(':'))
                    .ToDictionary(propertyMap => propertyMap[0], propertyMap => PickStringList(propertyMap,1));
        }

        protected string PickStringList(string[] list, int index)
        {
            string indexString = String.Empty;
            int len = list.Length;
            for (int i = index; i < len; i++)
            {
                indexString = indexString + list[i] + ":";
            }
            return indexString.TrimEnd(':');
        }

        protected virtual void VerifyLinuxState(IContext ctx)
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
        }

        protected virtual Dictionary<string, string> GetLinuxValue()
        {
            Dictionary<string, string> linuxValueMap = new Dictionary<string, string>();
            return linuxValueMap;
        }        
    }
}
