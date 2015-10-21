//-----------------------------------------------------------------------
// <copyright file="BaseProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A base class about provider test.</description>
//-----------------------------------------------------------------------

using System.IO;
using System.Text;

namespace DSCAzure
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using Infra.Frmwrk;
    using System.Threading;

    public class ProviderTestBase : ISetup, IRun, IVerify, ICleanup
    {
        protected MofHelper mofHelper;

        protected PsHelper psHelper = new PsHelper();

        protected SshHelper sshHelper;
        protected PosixCopy posixCopy;
        protected string initializeCmd;
        protected string forcePullpullServerCmd;
        protected string azureMofFileName;
        protected string finalizeCmd;

        protected string propString;
        protected string mofPath;
        protected string configFilePath;
        protected string configMofScriptPath;

        protected string[] psScripts;
        protected string[] configAzure;
        protected string[] getNodeIdCmd;
        protected string[] importConfigToAzure;
        protected string[] setAzureAutomation;
        protected string[] getNodeStatus;
        protected string[] removeNode;
        protected string psErrorMsg;

        protected string verificationCmd;
        protected string expectedValue;
        protected string successfulyMsg;
        protected string failedMsg;

        protected Dictionary<string, string> propMap;
        protected string metaFileName;
        protected string pullServerDirectory;

        protected string tmpMofFileFullName;
        protected string newMofFileFullName;
        protected string varID;
        protected int setID;
        protected string caseID;
        protected string nodeID;
        protected string isNeedCompile;
        protected string isReport;
        protected string status;
       
        

        public virtual void Setup(IContext ctx)
        {
            caseID = ((IVarContext)ctx).VarID.ToString();
            setID = ((IVarContext)ctx).Set;

            isReport = ctx.Records.GetValue("isReport");
            status = ctx.Records.GetValue("status");

            isNeedCompile = ctx.Records.GetValue("isNeedCompile");
            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
            configFilePath = ctx.Records.GetValue("configFilePath");
            configMofScriptPath = ctx.Records.GetValue("configMofScriptPath");        
            
            pullServerDirectory = ctx.Records.GetValue("pullServerDirectory");
            psScripts = ctx.Records.GetValues("psScript");
            configAzure = ctx.Records.GetValues("configAzure");
            getNodeIdCmd = ctx.Records.GetValues("getNodeIdCmd");
            importConfigToAzure = ctx.Records.GetValues("importConfigToAzure");
            setAzureAutomation = ctx.Records.GetValues("setAzureAutomation");
            getNodeStatus = ctx.Records.GetValues("getNodeStatus");
            removeNode = ctx.Records.GetValues("removeNode");
            psErrorMsg = ctx.Records.GetValue("psErrorMsg");
            verificationCmd = ctx.Records.GetValue("verificationCmd");
            expectedValue = ctx.Records.GetValue("expectedValue");
            successfulyMsg = ctx.Records.GetValue("successfulMsg");
            failedMsg = ctx.Records.GetValue("failedMsg");
            forcePullpullServerCmd = ctx.Records.GetValue("forcePullpullServerCmd");
            azureMofFileName = ctx.Records.GetValue("azureMofFileName");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            string nxDomainName = ctx.Records.GetValue("nxDomainName");
            string configurationName = ctx.Records.GetValue("configurationName");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            varID = "Node" + caseID;
            if (setID == 14)
            {
                varID = nxHostName + "." + caseID;
            }

            metaFileName = nxHostName + "." + nxDomainName + ".meta.mof";
            tmpMofFileFullName = configFilePath + "\\" + azureMofFileName;
            newMofFileFullName = configFilePath + "\\" + metaFileName;
            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            posixCopy = new PosixCopy(nxHostName, nxUsername, nxpassword);

            //connect to Azure.
            ctx.Alw(String.Format("Run PowerShell : '{0}'", configAzure));
            psHelper.Run(configAzure);

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
            mofHelper.PrepareMofGenerator(propMap, configMofScriptPath, mofPath, varID, configurationName);
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

            //Rename and modify the MOF file under '..\DscMetaConfigs\'
            if (File.Exists(tmpMofFileFullName))
            {
                string metaFileContents = File.ReadAllText(tmpMofFileFullName);
                metaFileContents = metaFileContents.Replace("ApplyAndMonitor", "ApplyAndAutocorrect");
                FileStream fs = null; ;
                StreamWriter sw = null;
                try
                {
                    fs = File.Create(newMofFileFullName);
                    sw = new StreamWriter(fs);
                    sw.Write(metaFileContents);
                    sw.Flush();
                }
                catch (Exception ex)
                {
                    throw new VarFail(ex.Message);
                }
                finally
                {
                    sw.Close();
                    fs.Close();
                }
            }
            else
            {
                throw new VarFail("Failed fo rename and modify the MOF file");
            }

            //push the config to the DSC agent
            ctx.Alw(String.Format("Run PowerShell : '{0}'", psScripts));
            psHelper.Run(psScripts);

            //Get Node Id
            ctx.Alw(String.Format("Get the node Id"));
            ctx.Alw(String.Format("Run PowerShell : '{0}'", getNodeIdCmd));
            psHelper.Run(getNodeIdCmd);
            nodeID = psHelper.LastPowerShellReturnString;

            if (isNeedCompile.ToLower().Equals("yes"))
            {
                // Import the config into Azure, compile the config and assign the compiled config to the node.
                ctx.Alw(String.Format("Run PowerShell : '{0}'", importConfigToAzure));
                psHelper.Run(importConfigToAzure);
                string status = psHelper.LastPowerShellReturnString;
                if (status.ToLower().Equals("completed"))
                {
                    ctx.Alw(String.Format("The status was Completed."));
                }
                else
                {
                    throw new VarFail(String.Format("The status was still {0}...", status));
                }
            }
            //set Azure Automation
            for (int i = 0; i < setAzureAutomation.Length; i++)
            {
                setAzureAutomation[i] = setAzureAutomation[i].Replace("$nodeID", nodeID);
                setAzureAutomation[i] = setAzureAutomation[i].Replace("$varID", varID);
            }
            ctx.Alw(String.Format("Run PowerShell : '{0}'", setAzureAutomation));
            psHelper.Run(setAzureAutomation);

            //Get DSC Node Status Command
            for (int i = 0; i < getNodeStatus.Length; i++)
            {
                getNodeStatus[i] = getNodeStatus[i].Replace("$nodeID", nodeID);
            }
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
                    if (isReport.ToLower().Equals("true"))
                    {
                        ctx.Alw(String.Format("Run PowerShell : '{0}'", getNodeStatus));
                        psHelper.Run(getNodeStatus);
                        string nodeStatus = psHelper.LastPowerShellReturnString;
                        if (!(nodeStatus.Equals(status)))
                        {
                            throw new VarFail(String.Format("expected Status is: {0}, but Actual is: {1}", status, nodeStatus));
                        }
                    }
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
                string errorTag = null;
                try
                {
                    //Fail to execute force pull server command when it should send error message.
                    sshHelper.Execute(forcePullpullServerCmd);

                }
                catch (Exception)
                {
                    errorTag = "yes";
                }
                finally
                {
                    if (isReport.ToLower().Equals("true"))
                    {
                        ctx.Alw(String.Format("Run PowerShell : '{0}'", getNodeStatus));
                        psHelper.Run(getNodeStatus);
                        string nodeStatus = psHelper.LastPowerShellReturnString;
                        if (!(nodeStatus.Equals(status)))
                        {
                            throw new VarFail(String.Format("expected Status is: {0}, but Actual is: {1}", status, nodeStatus));
                        }
                    }
                }

                if (!(errorTag.Equals("yes")))
                {
                    throw new VarFail(failedMsg);
                }
       
            }
            ctx.Alw("Verify End.");
        }

        public virtual void Cleanup(IContext ctx)
        {
            ctx.Alw("Cleanup Begin.");
            ctx.Alw(String.Format("Finalize Linux state : '{0}'", finalizeCmd));
            try
            {
                sshHelper.Execute(finalizeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            //remove node
            for (int i = 0; i < removeNode.Length; i++)
            {
                removeNode[i] = removeNode[i].Replace("$nodeID", nodeID);
            }
            ctx.Alw(String.Format("Run PowerShell : '{0}'", removeNode));
            psHelper.Run(removeNode);

            // Delete MOF file.
            ctx.Alw(String.Format("Delete MOF generator : '{0}'", configMofScriptPath));
            mofHelper.DeleteMof(configMofScriptPath);

            //Delete Meta mof file.
            ctx.Alw(String.Format("Delete MOF generator : '{0}'", configMofScriptPath));
            mofHelper.DeleteMof(newMofFileFullName);

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
