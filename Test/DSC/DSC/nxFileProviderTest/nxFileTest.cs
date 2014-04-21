//-----------------------------------------------------------------------
// <copyright file="nxFileTest.cs" company="Microsoft">
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

    public class nxFileTest : ProviderTestBase
    {
        private string path;

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxFileTest Setup Begin.");

            mofHelper = new FileMofHelper();

            path = ctx.Records.GetValue("path");

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            ctx.Alw("nxFileTest Setup End.");
        }

        #region Private Methods

        private string GetInitializeCmd(string path, string initType, string initState)
        {
            StringBuilder command = new StringBuilder();
            command.Append(String.Format("rm -rf {0};", path));

            if (initState.ToLower().Equals("present"))
            {
                switch (initType.ToLower())
                {
                    case "file":
                        command.Append(String.Format("touch {0}", path));
                        break;
                    case "directory":
                        command.Append(String.Format("mkdir {0}", path));
                        break;
                    default:
                        throw new ArgumentException("The specific type is invalid! Should be 'file' or 'directory'");
                }
            }

            return command.ToString();
        }

        private string GetFinalizeCmd(string path)
        {
            StringBuilder command = new StringBuilder();

            command.Append(String.Format("rm -rf {0};", path));

            return command.ToString();
        }

        #endregion
    }
}
