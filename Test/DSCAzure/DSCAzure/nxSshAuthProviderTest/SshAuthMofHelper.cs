﻿//-----------------------------------------------------------------------
// <copyright file="SshAuthMofHelper.cs" company="Microsoft">
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
    class SshAuthMofHelper : MofHelper
    {
        public SshAuthMofHelper()
        {
            MofGenerator = base.GeneratorFormat.
                Replace("$ModuleName", "nx").
                Replace("$ResourceType","nxSshAuthorizedKeys").
                Replace("$ResourceName","SshAuthorizedKeys");
        }

    }
}
