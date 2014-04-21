//-----------------------------------------------------------------------
// <copyright file="FileMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.Text;
    using System.Linq;
    
    public class FileMofHelper : MofHelper
    {
        public FileMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                Replace("$ResourceType","nxFile").
                Replace("$ResourceName","File");
        }

        protected override string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
            string content = string.Empty;

            StringBuilder text = new StringBuilder();

            foreach (string property in propString.Keys)
            {
                if (!String.IsNullOrWhiteSpace(property))
                {
                    text.Append(String.Format("{0} = \"{1}\"\n",
                        property,
                        propString[property]));
                }
            }

            content = this.MofGenerator.Replace("$Properties", text.ToString());

            if (propString.ContainsKey("DependsOn") && !propString["DependsOn"].EndsWith("#"))
            {
                StringBuilder dependedProp = new StringBuilder();
                string[] values = propString["DependsOn"].Replace("[", "").Split(']');
                string dependedType = values[0];
                string dependedName = values[1];
                if (dependedType.Equals("nxUser", StringComparison.InvariantCultureIgnoreCase))
                {
                    const string keyProp = "UserName";
                    string username = propString.ContainsKey("Owner") ? propString["Owner"] : "temp_test";

                    dependedProp.Append(String.Format("{0} = \"{1}\"\n",
                        keyProp,
                        username));

                    dependedProp.Append("Ensure = \"Present\"");
                }

                content = content.Replace("#DependdeResourceType", dependedType);
                content = content.Replace("#DependedResourceName", dependedName);
                content = content.Replace("#DependedProperties", dependedProp.ToString());
            }

            return content; ;
        }

        public override Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            string[] forbiddenProp = { "Contents", "Checksum", "Force", "Recurse", "Links", "DependsOn" };

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
