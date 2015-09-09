//-----------------------------------------------------------------------
// <copyright file="LogMofHelper.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from MofHelper, extend MofTemplate property. </description>
//-----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DSCAzure
{
    class LogMofHelper : MofHelper
    {
        public LogMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                    Replace("$ResourceType", "nxLog").
                    Replace("$ResourceName", "Log");
        }
    }

}
