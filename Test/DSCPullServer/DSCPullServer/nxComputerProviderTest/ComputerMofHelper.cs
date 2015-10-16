//-----------------------------------------------------------------------
// <copyright file="ComputerMofHelper.cs" company="Microsoft">
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
    class ComputerMofHelper : MofHelper
    {
        public ComputerMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ModuleName", "nxComputermanagement").
                    Replace("$ResourceType", "nxComputer").
                    Replace("$ResourceName", "Computer");
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
