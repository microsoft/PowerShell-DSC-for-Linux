//-----------------------------------------------------------------------
// <copyright file="PsHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A helper class about PowerShell, to handle to initialize powershell runspace, execute powershell script, and check output and error/exception msg</description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Linq;
    using System.Management.Automation;
    using System.Management.Automation.Runspaces;
    using System.Globalization;
    using Infra.Frmwrk;

    public class PsHelper : IDisposable
    {
        private const int DefaultWinRMPort = 5985;

        private PowerShell powershell;

        #region Properties

        public string ExceptionMsg
        {
            get;
            set;
        }

        public string ErrorMsg
        {
            get;
            set;
        }

        public PSInvocationStateInfo LastPipelineStateInfo
        {
            get;
            set;
        }

        public List<Dictionary<string, string>> LastPowerShellReturnValues
        {
            get;
            set;
        }

        #endregion

        #region Construct Methods

        public PsHelper() : this(null, null, null, 0, true) { }
        
        public PsHelper(string hostName) : this(hostName, null, null, 0 ,true) { }
        
        public PsHelper(
            string hostName,
            string username,
            string password)
            : this(hostName, username, password, 0, true) { }
        
        public PsHelper(
            string hostName,
            string username,
            string password,
            int port,
            bool useSsl)
        {
            NewConnection(hostName, username, password, port, useSsl);
        }

        #endregion

        #region Public Methods

        public void Run(string[] scripts)
        {
            foreach (var script in scripts)
            {
                powershell.AddScript(script);
            }

            try
            {
                Collection<PSObject> objs = powershell.Invoke();

                var errors = powershell.Streams.Error;

                foreach (var error in errors)
                {
                    ErrorMsg += error.ToString();
                }

                LastPipelineStateInfo = powershell.InvocationStateInfo;

                LastPowerShellReturnValues = ConvertPowerShellObjects(objs);
            }
            catch (RuntimeException ex)
            {
                ExceptionMsg = ex.ToString();
            }
            finally
            {
                powershell.Streams.ClearStreams();
                powershell.Commands.Clear();
            }
        }

        public void CheckOutput(string key, string value)
        {
            if (LastPowerShellReturnValues == null || LastPowerShellReturnValues.Count <= 0)
            {
                throw new VarFail(string.Format(
                    CultureInfo.InvariantCulture,
                    "Last PowerShell return null object!"));
            }

            bool flag = LastPowerShellReturnValues.Where(
                obj => obj.ContainsKey(key)).Any(
                obj => obj[key].Equals(value, StringComparison.InvariantCultureIgnoreCase));

            if (!flag)
            {
                throw new VarFail(string.Format(
                    CultureInfo.InvariantCulture,
                    "Key-Value '{0}'-'{1}' does not exist in the result",
                    key, value));
            }
        }

        public void CheckOutput(Dictionary<string, string> keyValuePairs)
        {
            foreach (var key in keyValuePairs.Keys)
            {
                CheckOutput(key, keyValuePairs[key]);
            }
        }

        public void CheckExceptionMsg(string expectedMsg)
        {
            if (!ExceptionMsg.Contains(expectedMsg))
            {
                throw new VarFail(string.Format(
                       CultureInfo.InvariantCulture,
                       "Actual exception not include expected: actual='{0}' expect='{1}'",
                       ExceptionMsg, expectedMsg));
            }
        }

        public void CheckErrorMessage(string expectedMsg)
        {
            string[] errors = expectedMsg.Split(';');

            bool flag = errors.Any(error => ErrorMsg.Contains(error));

            if (!flag)
            {
                throw new VarFail(string.Format(
                       CultureInfo.InvariantCulture,
                       "Actual error not include expected: actual='{0}' expect='{1}'",
                       ErrorMsg, expectedMsg));
            }
        }

        public void Dispose()
        {
            if (powershell != null)
            {
                powershell.Runspace.Close();
                powershell.Dispose();
            }
        }
    
        #endregion

        #region Private Methods

        private static List<Dictionary<string, string>> ConvertPowerShellObjects(IEnumerable<PSObject> psObjects)
        {
            var data = new List<Dictionary<string, string>>();

            if (psObjects == null)
                return data;

            foreach (PSObject obj in psObjects)
            {
                var dict = new Dictionary<string, string>();

                foreach (PSPropertyInfo prop in obj.Properties)
                {
                    try
                    {
                        if (prop.Value != null)
                        {
                            dict[prop.Name] = prop.Value.ToString();
                        }
                    }
                    catch (GetValueException e)
                    {
                        // Impossible to get the value.  Just store the Key.
                        dict[prop.Name] = e.Message;
                    }
                }

                data.Add(dict);
            }

            return data;
        }

        private void NewConnection(
            string hostName,
            string username,
            string password,
            int port,
            bool useSsl)
        {
            powershell = PowerShell.Create();
            
            Runspace runspace;

            if (hostName == null)
            {
                runspace = RunspaceFactory.CreateRunspace();
            }
            else
            {
                using (var securePwd = new System.Security.SecureString())
                {
                    RunspaceConnectionInfo connInfo = null;

                    foreach (var c in password)
                    {
                        securePwd.AppendChar(c);
                    }

                    if (port <= 0)
                    {
                        connInfo = new WSManConnectionInfo(new Uri(String.Format(
                            CultureInfo.InvariantCulture,
                            "http://{0}:{1}/wsman",
                            hostName,
                            DefaultWinRMPort)),
                            "http://schemas.microsoft.com/powershell/Microsoft.PowerShell",
                            new PSCredential(username, securePwd));
                    }
                    else
                    {
                        connInfo = new WSManConnectionInfo(
                            useSsl,
                            hostName,
                            port,
                            "wsman",
                            "http://schemas.microsoft.com/powershell/Microsoft.PowerShell",
                            new PSCredential(username, securePwd));
                    }

                    connInfo.AuthenticationMechanism = AuthenticationMechanism.Default;

                    runspace = RunspaceFactory.CreateRunspace(connInfo);
                }
            }

            runspace.Open();

            powershell.Runspace = runspace;
        }

        #endregion
    }
}
