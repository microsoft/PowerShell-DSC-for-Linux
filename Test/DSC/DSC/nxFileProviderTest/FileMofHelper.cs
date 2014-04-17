//-----------------------------------------------------------------------
// <copyright file="FileMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

namespace DSC
{
    public class FileMofHelper : MofHelper
    {
        public FileMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                Replace("$ResourceType","nxFile").
                Replace("$ResourceName","File");
        }
    }
}
