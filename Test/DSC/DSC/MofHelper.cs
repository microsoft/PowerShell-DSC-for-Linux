//-----------------------------------------------------------------------
// <copyright file="MofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>A helper class about MOF file, to handle MOF creation and deletion. </description>
//-----------------------------------------------------------------------

namespace DSC
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Text;
    
    public class MofHelper
    {
        #region Generator

        public string GeneratorFormat =
            "Configuration MyTestConfig{Node \"$agentName\"{\n$ResourceType $ResourceName{$Properties}\n#DependdeResourceType #DependedResourceName{#DependedProperties}\n}};MyTestConfig -outputpath:$mofPath";

        public string MofGenerator
        {
            get;
            set;
        }

        #endregion

        public void DeleteMof(string path) // Out of date.
        {
            try
            {
                File.Delete(path);
            }
            catch
            {
                Directory.Delete(path, true);
            }
        }

        public void PrepareMofGenerator(Dictionary<string, string> propString, string generatorPath, string agentName, string mofPath)
        {
            string content = this.ConvertStringToMofProperty(propString)
                .Replace("$agentName", agentName)
                .Replace("$mofPath", mofPath);

            File.Delete(generatorPath);

            FileStream fs = File.OpenWrite(generatorPath);

            Encoding encoder = new UTF8Encoding();
            byte[] bytes = encoder.GetBytes(content);

            fs.Write(bytes, 0, bytes.Length);

            fs.Close();
        }

        protected virtual string ConvertStringToMofProperty(Dictionary<string, string> propString)
        {
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

            return this.MofGenerator.Replace("$Properties", text.ToString());
        }

        public virtual Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            return propKeyValuePairs;
        }
    }
}
