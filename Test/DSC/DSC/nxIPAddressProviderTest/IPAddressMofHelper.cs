//-----------------------------------------------------------------------
// <copyright file="IPAddressMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DSC
{
    class IPAddressMofHelper : MofHelper
    {
        public IPAddressMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ResourceType", "nxIPAddress").
                    Replace("$ResourceName", "IPAddress");
        }

        protected override string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
            StringBuilder text = new StringBuilder();

            List<String> booleanProp = new List<String> { "Enabled" };

            foreach (string property in propString.Keys)
            {
                if (!String.IsNullOrWhiteSpace(property))
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

            return this.MofGenerator.Replace("$Properties", text.ToString());
        }
    }
}

