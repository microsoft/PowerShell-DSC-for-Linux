//-----------------------------------------------------------------------
// <copyright file="BaseProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A base class about provider test.</description>
//-----------------------------------------------------------------------

using System.IO;
using System.Text;

namespace DSCPullServer
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
        protected PosixCopy posixCopy;
        protected string initializeCmd;
        protected string forcePullpullServerCmd;
        protected string metaPath;
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
        protected string mofFileName;
        protected string metaFileName;
        protected string pullServerDirectory;

        protected string tmpMofFileFullName;
        protected string newMofFileFullName;
        protected string checkSumPSCommand = "New-DSCChecksum '$1'";
        public const string NEW_GUID_PS_COMMAND = "[guid]::NewGuid()";
        

        public virtual void Setup(IContext ctx)
        {
            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
            configMofScriptPath = ctx.Records.GetValue("configMofScriptPath");        
            
            pullServerDirectory = ctx.Records.GetValue("pullServerDirectory");
            psScripts = ctx.Records.GetValues("psScript");
            psErrorMsg = ctx.Records.GetValue("psErrorMsg");
            verificationCmd = ctx.Records.GetValue("verificationCmd");
            expectedValue = ctx.Records.GetValue("expectedValue");
            successfulyMsg = ctx.Records.GetValue("successfulMsg");
            failedMsg = ctx.Records.GetValue("failedMsg");
            forcePullpullServerCmd = ctx.Records.GetValue("forcePullpullServerCmd");
            metaPath = ctx.Records.GetValue("metaPath");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            string nxDomainName = ctx.Records.GetValue("nxDomainName"); 
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            mofFileName = nxHostName + "." + nxDomainName + ".mof";
            metaFileName = nxHostName + "." + nxDomainName + ".meta.mof";
            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            posixCopy = new PosixCopy(nxHostName, nxUsername, nxpassword);


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
            mofHelper.PrepareMofGenerator(propMap, configMofScriptPath, nxHostName, mofPath, nxDomainName);
            ctx.Alw(String.Format("Prepare a MOF generator '{0}'",
                configMofScriptPath));

            // Add the config to the logs
            StreamReader sr = new StreamReader(configMofScriptPath);        
            StringBuilder configFile = new StringBuilder();

            //The temp variable line is to read a line from the temp variable sr.It's recycle variable.
            string line = sr.ReadLine();
            while (line != null)
            {
                line = line.Replace("{", "{{").Replace("}","}}");
                configFile.Append(line);
                line = sr.ReadLine();
            }
            ctx.Alw(String.Format(configFile.ToString()));

            ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));
            
        }

        public virtual void Run(IContext ctx)
        {
            ctx.Alw("Run Begin.");

            //Generate Mof
            ctx.Alw(String.Format("Run PowerShell : '{0}'", configMofScriptPath));
            string[] generateMofScript = { configMofScriptPath };
            psHelper.Run(generateMofScript);
            
            //Get GUID
            ctx.Alw(String.Format("Run PowerShell : '{0}'", NEW_GUID_PS_COMMAND));
            string[] newGUIDPSCommand = { NEW_GUID_PS_COMMAND };
            psHelper.Run(newGUIDPSCommand);
            string newGUID = psHelper.LastPowerShellReturnString;

            //Rename Mof file with GUID and copy to the directory on the DSC Pull Server.
            tmpMofFileFullName = mofPath + "\\" + mofFileName;
            newMofFileFullName = pullServerDirectory + "\\" + newGUID + ".mof";
            if (File.Exists(tmpMofFileFullName))
            {
                File.Copy(tmpMofFileFullName, newMofFileFullName , true);
            }
            else 
            {
                throw new VarFail("Failed fo create MOF file");
            }

            //Create Checksum file for mof file
            checkSumPSCommand = checkSumPSCommand.Replace("$1", newMofFileFullName);
            string[] checkSumPSCommandArray = { checkSumPSCommand };
            psHelper.Run(checkSumPSCommandArray);
            
            // Run PowerShell script to get/send configuration MOF.
            for (int i = 0; i < psScripts.Length;i++ )
            {
                psScripts[i] = psScripts[i].Replace("$GUID", newGUID);
            }
            ctx.Alw(String.Format("Run PowerShell : '{0}'", psScripts));
            psHelper.Run(psScripts);
            ctx.Alw("Run End.");
        }

        public virtual void Verify(IContext ctx)
        {
            ctx.Alw("Verify Begin.");

            if (String.IsNullOrWhiteSpace(psErrorMsg))
            {
                try
                {
                    sshHelper.Execute(forcePullpullServerCmd);
                }
                catch (Exception ex)
                {
                    ctx.Alw(ex.Message);
                }                    
         
                // Verify Linux machine state.
                VerifyLinuxState(ctx);
                
            }
            else
            {
                //Fail to execute force pull server command when it should send error message.
                try
                {
                    sshHelper.Execute(forcePullpullServerCmd);
                }
                catch (Exception)
                {
                    ctx.Alw(String.Format("Send the error message"));
                }           
            }
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
            mofHelper.DeleteMof(newMofFileFullName);
            mofHelper.DeleteMof(newMofFileFullName + ".checksum");

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
