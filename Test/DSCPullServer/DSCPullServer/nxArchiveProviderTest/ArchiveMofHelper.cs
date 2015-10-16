//-----------------------------------------------------------------------
// <copyright file="FileLineMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-tilin@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Infra.Frmwrk;

namespace DSCPullServer
{
    class ArchiveMofHelper : MofHelper
    {
        private IContext ctx;
        public ArchiveMofHelper(IContext ctx)
        {
            MofGenerator = base.GeneratorFormat.
                Replace("$ModuleName", "nx").
                Replace("$ResourceType", "nxArchive").
                Replace("$ResourceName", "Archive");
            this.ctx = ctx;
        }      

        protected override string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
            StringBuilder text = new StringBuilder();

            List<String> booleanProp = new List<String> { "Force" };

            foreach (string property in propString.Keys)
            {
                if (!String.IsNullOrWhiteSpace(property) && !property.ToString().Equals("Password"))
                {
                    if (!booleanProp.Contains(property))
                    {
                        text.Append(String.Format("{0} = \"{1}\"\n",
                            property,
                            propString[property].Replace("$", "`$")));
                    }
                    else
                    {
                        text.Append(String.Format("{0} = ${1}\n",
                            property,
                            propString[property]));
                    }
                }
            }

            string content = this.MofGenerator.Replace("$Properties", text.ToString());

            if (propString.ContainsKey("DependsOn") && !propString["DependsOn"].EndsWith("#"))
            {
                StringBuilder dependedProp = new StringBuilder();
                string[] values = propString["DependsOn"].Replace("[", "").Split(']');
                string dependedType = values[0];
                string dependedName = values[1];
                if (dependedType.Equals("nxFile", StringComparison.InvariantCultureIgnoreCase))
                {
                    const string keyProp = "DestinationPath";
                    string destinationPath = propString.ContainsKey("SourcePath") ? propString["SourcePath"] : "/tmp/source.tar";

                    dependedProp.Append(String.Format("{0} = \"{1}\"\n",
                        keyProp,
                        destinationPath));

                    string sourcePath = ctx.Records.GetValue("remoteTarFilePath");                 
                    dependedProp.Append(String.Format("{0} = \"{1}\"\n",
                        "SourcePath",
                        sourcePath));

                    dependedProp.Append("Type = \"File\"\n");
                    dependedProp.Append("Ensure = \"Present\"");
                }

                content = content.Replace("#DependdeResourceType", dependedType);
                content = content.Replace("#DependedResourceName", dependedName);
                content = content.Replace("#DependedProperties", dependedProp.ToString());

            }

            return content;
        }

        public override Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            List<string> forbiddenProp =
                new List<string>() { "DependsOn" };

            foreach (var prop in forbiddenProp)
            {
                if (propKeyValuePairs.ContainsKey(prop))
                {
                    propKeyValuePairs.Remove(prop);
                }
            }

            return propKeyValuePairs;
        }
    }
}
