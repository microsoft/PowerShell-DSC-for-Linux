//----------------------------------------------------------------------
// <copyright file="DNSAddrMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;

namespace DSCPullServer
{
    class DNSAddressMofHelper : MofHelper
    {
        public DNSAddressMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ResourceType", "nxDNSServerAddress").
                    Replace("$ResourceName", "DNSServerAddress");
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
    }
}


