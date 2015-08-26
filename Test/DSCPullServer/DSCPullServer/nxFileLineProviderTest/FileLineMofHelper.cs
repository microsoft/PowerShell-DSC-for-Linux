//-----------------------------------------------------------------------
// <copyright file="FileLineMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-tilin@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DSCPullServer
{
    class FileLineMofHelper : MofHelper
    {
        public FileLineMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                Replace("$ResourceType", "nxFileLine").
                Replace("$ResourceName", "FileLine");
        }

    }
}
