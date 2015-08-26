//-----------------------------------------------------------------------
// <copyright file="GroupMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace DSCPullServer
{
    class GroupMofHelper : MofHelper
    {
        public const string KEY_MEMBERSTOINCLUDE = "MembersToInclude";

        public const string KEY_MEMBERSTOEXCLUDE = "MembersToExclude";

        public const string KEY_MEMBERS = "Members";


        public GroupMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ResourceType", "nxGroup").
                    Replace("$ResourceName", "Group");
        }

        protected override string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
            StringBuilder text = new StringBuilder();

            foreach (string property in propString.Keys)
            {
                if (!String.IsNullOrWhiteSpace(property))
                {
                    string propertyValue = propString[property];
                    if (propertyValue.Contains(","))
                    {
                        string[] propertyValueArray = propertyValue.Split(',');
                        text.Append(property + "= @(\"" + propertyValueArray[0] + "\"");
                        for (int i = 1; i < propertyValueArray.Length; i++)
                        {
                            text.Append(String.Format(",\"{0}\"",
                             propertyValueArray[i])); 
                        }
                        text.Append(")\n");
                    }
                    else
                    {
                        text.Append(String.Format("{0} = \"{1}\"\n",
                            property,
                            propString[property]));
                    }
                }
            }

            return this.MofGenerator.Replace("$Properties", text.ToString());
        }

        public override Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            Dictionary<string, string> returnKeyValuePairs = new Dictionary<string, string>();

            foreach (string key in propKeyValuePairs.Keys)
            {                
                string value = propKeyValuePairs[key];
                if (key.Equals(KEY_MEMBERSTOINCLUDE))
                {
                    returnKeyValuePairs.Add(KEY_MEMBERS, value);
                }
                else if (key.Equals(KEY_MEMBERSTOEXCLUDE))
                {
                    // returnKeyValuePairs.Add(KEY_MEMBERS, "");
                }
                else
                {
                    returnKeyValuePairs.Add(key, value);
                }

            }
            return returnKeyValuePairs;
        }
    }
}
