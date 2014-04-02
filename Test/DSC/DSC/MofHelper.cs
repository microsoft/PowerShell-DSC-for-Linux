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
    using System.IO;
    using System.Text;
    
    public class MofHelper
    {
        #region Template

        public static string TemplateFormat =
            "instance of $ResourceType{$Properties\nResourceId = \"[$ResourceType]$ResourceName\";ModuleName = \"PSDesiredStateConfiguration\";ModuleVersion = \"1.0\";};instance of OMI_ConfigurationDocument{Version=\"1.0.0\";};";

        public string MofTemplate
        {
            get;
            set;
        }

        #endregion

        public void PrepareMof(string propString, string path)
        {
            string content = ConvertStringToMofProperty(propString);

            File.Delete(path);

            FileStream fs = File.OpenWrite(path);

            Encoding encoder = new UTF8Encoding();
            byte[] bytes = encoder.GetBytes(content);

            fs.Write(bytes, 0, bytes.Length);

            fs.Close();
        }

        public void DeleteMof(string path)
        {
            File.Delete(path);
        }

        private string ConvertStringToMofProperty(string propString)
        {
            StringBuilder text = new StringBuilder();

            string[] properties = propString.Split(';');

            foreach (string property in properties)
            {
                if (!String.IsNullOrWhiteSpace(property))
                {
                    string[] propertyMap = property.Split(':');

                    text.Append(String.Format("{0} = \"{1}\";",
                        propertyMap[0],
                        propertyMap[1]));
                }
            }

            return MofTemplate.Replace("$Properties", text.ToString());
        }
    }
}
