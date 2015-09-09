//-----------------------------------------------------------------------
// <copyright file="IFileCopyHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>a-brmill</author>
// <description></description>
// <history>1/20/2009 9:26:34 AM: Created</history>
//-----------------------------------------------------------------------

// Microsoft.VisualBasic.FileIO.FileSystem.CopyFile
namespace DSCAzure
{

    // using Tamir.SharpSsh; This is deprecated.

    /// <summary>
    /// Description for IFileCopyHelper.
    /// </summary>
    public interface IFileCopyHelper
    {
        #region Private Fields

        #endregion Private Fields

        #region Constructors

        #endregion Constructors

        #region Properties

        /// <summary>
        /// Gets or sets HostName
        /// </summary>
        string HostName { get; set; }

        /// <summary>
        /// Gets or sets UserName
        /// </summary>
        string UserName { get; set; }

        /// <summary>
        /// Gets or sets Password
        /// </summary>
        string Password { get; set; }

        #endregion Properties

        #region Methods

        #region Private Methods

        #endregion Private Methods

        #region Public Methods

        /// <summary>
        /// Copy from with source and destination
        /// </summary>
        /// <param name="sourcePath">Source path</param>
        /// <param name="destPath">Destination path</param>
        void CopyFrom(string sourcePath, string destPath);

        /// <summary>
        /// Copy to with source and destination
        /// </summary>
        /// <param name="sourcePath">Source path</param>
        /// <param name="destPath">Destination path</param>
        void CopyTo(string sourcePath, string destPath);

        #endregion Public Methods

        #endregion Methods
    }
}
