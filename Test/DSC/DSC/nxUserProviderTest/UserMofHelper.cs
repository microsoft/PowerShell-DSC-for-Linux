//-----------------------------------------------------------------------
// <copyright file="UserMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

namespace DSC
{
    class UserMofHelper : MofHelper
    {
        public UserMofHelper()
        {
            MofTemplate = TemplateFormat.
                    Replace("$ResourceType","MSFT_nxUserResource").
                    Replace("$ResourceName","User");
        }
    }
}
