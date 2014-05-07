//-----------------------------------------------------------------------
// <copyright file="SshHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A helper class about Ssh, to handle SSH task. </description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using sshcomLib;
    
    public class SshHelper : IDisposable
    {
        private scxssh ssh;
        private string _hostName;
        private string _username;
        private string _password;
        private int _port;

        public SshHelper(string hostName, string username, string password, int port)
        {
            this._hostName = hostName;
            this._username = username;
            this._password = password;
            this._port = port;

            NewSshConnection();
        }

        public void VerifyExecution(string command, string expected)
        {
            string actual = string.Empty;

            Execute(command, out actual);

            if (!expected.Equals(actual, StringComparison.InvariantCultureIgnoreCase))
            {
                throw new Exception(String.Format(
                    "The result of command '{0}' is unexpected: expected - '{1}', actual - '{2}'",
                    command,
                    expected,
                    actual));
            }
        }

        public void Execute(string command, out string returnValue)
        {
            returnValue = string.Empty;
            if (ssh != null && !string.IsNullOrEmpty(command))
            {
                uint status = 0;

                try
                {
                    status = this.ssh.ExecuteCommand2(command, out returnValue);
                }
                catch (Exception e)
                {
                    throw new Exception(string.Format("Failed to execute command {0}.", command), e);
                }

                if (status != 0)
                {
                    throw new InvalidOperationException(string.Format(
                        "Failed to execute command {0} : return code = {1}; error message = {2}.",
                        command,
                        status,
                        returnValue));
                }
            }
        }

        public void Execute(string command)
        {
            if (ssh != null && !string.IsNullOrEmpty(command))
            {
                uint status = 0;

                try
                {
                    status = this.ssh.ExecuteCommand(command);
                }
                catch (Exception e)
                {
                    throw new Exception(string.Format("Failed to execute command {0}.", command), e);
                }

                if (status != 0)
                {
                    throw new InvalidOperationException(string.Format(
                        "Failed to execute command {0} : return code = {1}.",
                        command,
                        status));
                }
            }
        }

        private void NewSshConnection()
        {
            ssh = new scxssh();

            try
            {
                uint connStatus = ssh.ConnectWithPassword(this._hostName, this._port, this._username, this._password);

                if (connStatus != 0)
                {
                    throw new Exception("Connection failed!");
                }
            }
            catch (Exception e)
            {
                throw new Exception("Connection failed!", e);
            }
        }

        public void Dispose()
        {
            if (ssh != null)
            {
                try
                {
                    uint disconnStatus = ssh.Shutdown();
                    ssh = null;

                    if (disconnStatus != 0)
                    {
                        throw new Exception("Disconnection failed!");
                    }
                }
                catch (Exception e)
                {
                    throw new Exception("Disconnection failed!", e); 
                }
            }
        }
    }
}
