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
            MofTemplate = TemplateFormat.
                Replace("$ResourceType","MSFT_nxFileResource").
                Replace("$ResourceName","File");
        }
    }
}
