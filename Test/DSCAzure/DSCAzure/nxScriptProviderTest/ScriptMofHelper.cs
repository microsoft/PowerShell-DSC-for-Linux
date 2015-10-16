namespace DSCAzure
{
    using System.Collections.Generic;

    class ScriptMofHelper : MofHelper
    {
        public ScriptMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ModuleName", "nx").
                    Replace("$ResourceType", "nxScript").
                    Replace("$ResourceName", "Script");
        }

        public override Dictionary<string, string> ReturnedPropertiesOfGetDscConfiguration(Dictionary<string, string> propKeyValuePairs)
        {
            Dictionary<string, string> returnKeyValuePairs = new Dictionary<string, string>();

            foreach (var key in propKeyValuePairs.Keys)
            {
                returnKeyValuePairs.Add(key, 
                    propKeyValuePairs[key].Replace("\r", "&#13;").Replace("\n", "&#10;"));
            }

            return returnKeyValuePairs;
        }
    }
}