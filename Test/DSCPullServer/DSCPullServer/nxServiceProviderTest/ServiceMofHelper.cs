using System;
using System.Collections.Generic;
using System.Text;
namespace DSCPullServer
{
    class ServiceMofHelper : MofHelper
    {
        public ServiceMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ModuleName", "nx").
                    Replace("$ResourceType", "nxService").
                    Replace("$ResourceName", "Service");
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