//-----------------------------------------------------------------------
// <copyright file="nxFileTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

namespace DSCPullServer
{
    using System;
    using System.Text;
    using Infra.Frmwrk;
    using System.Collections.Generic;

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

        protected override Dictionary<string, string> GetLinuxValue()
        {
            Dictionary<string, string> linuxValueMap = new Dictionary<string, string>();
            string desPath = propMap["DestinationPath"];
            string type = propMap.ContainsKey("Type") ? propMap["Type"] : "File";
            string ensureVal = propMap.ContainsKey("Ensure") ? propMap["Ensure"] : "present";
            string contents = string.Empty;
            

            if (ensureVal.ToLower() == "present")
            {
                string mode = string.Empty;
                string owner = string.Empty;
                string group = string.Empty;

                try
                {                    
                    string cmd = "stat {0} |grep -i 'Access'|grep -i 'Uid'| awk '{print $10}' |cut -d ')' -f1 |tr -d '\n'";
                    string getGroupCmd = cmd.Replace("{0}", desPath);

                    cmd = "stat {0} |grep -i 'Access'|grep -i 'Uid'| awk '{print $6}' |cut -d ')' -f1 |tr -d '\n'";
                    string getOwnerCmd = cmd.Replace("{0}", desPath);

                    cmd = "stat {0} |grep -i 'Access'|grep -i 'Uid'| awk '{print $2}' |cut -d '/' -f1 |cut -d '0' -f2|tr -d '\n'";
                    string getModeCmd = cmd.Replace("{0}", desPath);

                    if (type.ToLower() == "directory")
                    {
                        cmd = "ls -l {0} | awk '{print $9}'";
                        string getContentsCmd = cmd.Replace("{0}", desPath);
                        sshHelper.Execute(getContentsCmd, out contents);
                    }

                    sshHelper.Execute(getOwnerCmd, out owner);
                    sshHelper.Execute(getGroupCmd, out group);
                    sshHelper.Execute(getModeCmd, out mode);
                }
                catch (Exception)
                {
                    throw new VarFail(String.Format("Fail to get Owner,Mode,Group,Contents from {0}", desPath));
                }

                // Get the contents under the directory in required order, like this ['file1', 'dir1'].
                if (type.ToLower() == "directory")
                {
                    string[] contentsArray = contents.Split('\n');
                    contents = "[";

                    for (int i = contentsArray.Length - 1; i >= 0; i--)
                    {
                        if (string.IsNullOrEmpty(contentsArray[i]))
                        {
                            continue;
                        }
                        contents += "'" + contentsArray[i] + "', ";
                    }
                    if (contents.Length > 2)
                    {
                        contents = contents.Substring(0, contents.Length - 2) + "]";
                    }
                    else
                    {
                        contents = string.Empty;
                    }
                }

                linuxValueMap["Mode"] = mode;
                linuxValueMap["Owner"] = owner;
                linuxValueMap["Group"] = group;  
                linuxValueMap["Contents"] = contents;
            }
            else
            {
                //if Ensure is 'absent', the value is null.
                linuxValueMap["Mode"] = "";
                linuxValueMap["Owner"] = "";
                linuxValueMap["Group"] = "";
                linuxValueMap["Contents"] = "";
            }
           
            return linuxValueMap;
        } 

        #endregion
    }
}
