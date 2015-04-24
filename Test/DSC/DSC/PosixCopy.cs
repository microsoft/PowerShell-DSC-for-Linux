//-----------------------------------------------------------------------
// <copyright file="PosixCopy.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>a-brmill</author>
// <description></description>
// <history>1/20/2009 1:15:59 PM: Created</history>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.Text;
    using sshcomLib; // This is the Microsoft SSL library
    // using Tamir.SharpSsh;  This library is deprecated

    /// <summary>
    /// Description for PosixCopy.
    /// </summary>
    public class PosixCopy : IFileCopyHelper, IDisposable
    {
        #region Private Fields

        /// <summary>
        /// Name of posix host
        /// </summary>
        private string host = string.Empty;

        /// <summary>
        /// SSH port number
        /// </summary>
        private int port = 22;

        /// <summary>
        /// Valid user name on Posix host
        /// </summary>
        private string userName = string.Empty;

        /// <summary>
        /// Password for user name
        /// </summary>
        private string password = string.Empty;

        /// <summary>
        /// Instance of SSH FTP connection
        /// </summary>
        private sshcomLib.scxssh ftp;

        /// <summary>
        /// The status of dispos
        /// </summary>
        private bool alreadyDisposed = false;

        #endregion Private Fields

        #region Constructors

        /// <summary>
        /// Initializes a new instance of the PosixCopy class for MCF usage.
        /// </summary>
        public PosixCopy()
        {
        }

        /// <summary>
        /// Initializes a new instance of the PosixCopy class.
        /// </summary>
        /// <param name="hostName">Name of the Posix host</param>
        /// <param name="userName">Valid user name on Posix host</param>
        /// <param name="password">Valid password for user name</param>
        public PosixCopy(string hostName, string userName, string password)
        {
            if (string.IsNullOrEmpty(hostName))
            {
                throw new ArgumentException("hostName is null or empty");
            }

            if (string.IsNullOrEmpty(userName))
            {
                throw new ArgumentException("userName is null or empty");
            }

            if (string.IsNullOrEmpty(password))
            {
                throw new ArgumentException("password is null or empty");
            }

            this.host = hostName;
            this.userName = userName;
            this.password = password;

            this.NewSshConnection();
        }

        /// <summary>
        /// Finalizes an instance of the PosixCopy class
        /// </summary>
        ~PosixCopy()
        {
            this.Dispose(true);
        }

        #endregion Constructors

        #region Properties

        /// <summary>
        /// Gets or sets the HostName property for the Posix host name
        /// </summary>
        public string HostName
        {
            get { return this.host; }
            set { this.host = value; }
        }

        /// <summary>
        /// Gets or sets the UserName property for the Posix host
        /// </summary>
        public string UserName
        {
            get { return this.userName; }
            set { this.userName = value; }
        }

        /// <summary>
        /// Gets or sets the Password property for the UserName
        /// </summary>
        public string Password
        {
            get { return this.password; }
            set { this.password = value; }
        }

        /// <summary>
        /// Gets or sets the Ftp property for the ssh class
        /// </summary>
        public sshcomLib.scxssh Ftp
        {
            get { return this.ftp; }
            set { this.ftp = value; }
        }

        #endregion Properties

        #region Methods

        #region Public Methods

        /// <summary>
        /// Interface method to copy files from a Posix host
        /// </summary>
        /// <param name="sourcePath">Path for source file(s)</param>
        /// <param name="destPath">Destination path</param>
        public void CopyFrom(string sourcePath, string destPath)
        {
            if (String.IsNullOrEmpty(sourcePath))
            {
                throw new ArgumentException("sourcePath is null or empty");
            }

            if (String.IsNullOrEmpty(destPath))
            {
                throw new ArgumentException("destPath is null or empty");
            }

            this.ftp.SFTPCopyToLocal(sourcePath, destPath);
        }

        /// <summary>
        /// Interface method to copy files to a Posix host
        /// </summary>
        /// <param name="sourcePath">Path for source file(s)</param>
        /// <param name="destPath">Destination path</param>
        public void CopyTo(string sourcePath, string destPath)
        {
            if (String.IsNullOrEmpty(sourcePath))
            {
                throw new ArgumentException("sourcePath is null or empty");
            }

            if (String.IsNullOrEmpty(destPath))
            {
                throw new ArgumentException("destPath is null or empty");
            }

            // Returns uint, but throws exception on error (like source file not found)
            this.ftp.SFTPCopyToRemote(sourcePath, destPath);
        }

        /// <summary>
        /// The function for dispose.
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion Public Methods

        #region protected Methods

        /// <summary>
        /// Initialize a new SSH connection
        /// </summary>
        /// <returns>Whether the error code from the SSL library is zero (indicating success)</returns>
        protected bool NewSshConnection()
        {
            uint connectResult;

            try
            {
                this.ftp = new scxssh();
                /*returns uint*/
                connectResult = this.ftp.ConnectWithPassword(this.host, this.port, this.userName, this.password);
            }
            catch (Exception e)
            {
                throw new Exception("Unable to connect to host", e);
            }

            return connectResult == 0;
        }

        /// <summary>
        /// This function is for disposing the project. 
        /// </summary>
        /// <param name="isDisposing">The bool value to verify if has been disposed</param>
        protected virtual void Dispose(bool isDisposing)
        {
            if (this.alreadyDisposed)
            {
                return;
            }

            if (isDisposing)
            {
                if (this.ftp != null)
                {
                    this.ftp.Shutdown();
                }
            }

            this.alreadyDisposed = true;
        }

        #endregion protected Methods

        #endregion Methods
    }
}
