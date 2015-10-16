//-----------------------------------------------------------------------
// <copyright file="FirewallMofHelper.cs" company="Microsoft">
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
    class FirewallMofHelper : MofHelper
    {
        
        public FirewallMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ModuleName", "nxNetworking").
                    Replace("$ResourceType", "nxFirewall").
                    Replace("$ResourceName", "Firewall");
        }

        protected override string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
            StringBuilder text = new StringBuilder();

            List<String> booleanProp = new List<String> { "SourceHost", "DestinationHost" };

            foreach (string property in propString.Keys)
            {
                if (!String.IsNullOrWhiteSpace(property))
                {
                    if (booleanProp.Contains(property))
                    {
                        string addrFamily = propString.ContainsKey("AddressFamily") ? propString["AddressFamily"] : "IPv4";
                        text.Append(addrFamily.ToLower().Equals("ipv6")
                            ? String.Format("{0} = \"{1}::\"\n", property, propString[property])
                            : String.Format("{0} = \"{1}\"\n", property, propString[property]));
                    }
                    else 
                    {
                        text.Append(String.Format("{0} = \"{1}\"\n", property, propString[property]));
                    }                 
                }
            }
            return this.MofGenerator.Replace("$Properties", text.ToString());
        }

        
        public override Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            List<string> forbiddenProp = new List<string> { "SourceHost", "DestinationHost" };

            foreach (var prop in forbiddenProp)
            {
                string addrFamily = propKeyValuePairs.ContainsKey("AddressFamily") ? propKeyValuePairs["AddressFamily"] : "IPv4";
                
                if (propKeyValuePairs.ContainsKey(prop))
                {
                    if (addrFamily.ToLower().Equals("ipv6"))
                    {
                        propKeyValuePairs[prop] = propKeyValuePairs[prop] + "::";
                    }
                }
            }

            return propKeyValuePairs;
        }
        
    }
}

