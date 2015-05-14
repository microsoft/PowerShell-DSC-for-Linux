//-----------------------------------------------------------------------
// <copyright file="nxEnvironmentTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-mifu@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------

using System;
using System.Text;
using Infra.Frmwrk;

namespace DSC
{
    class nxEnvironmentTest : ProviderTestBase
    {

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxEnvironmentTest Setup Begin.");

            mofHelper = new EnvironmentMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            if (!propMap.ContainsKey("Path"))
            {
                propMap["Path"] = "False";
            }

            if (!propMap.ContainsKey("Ensure"))
            {
                propMap["Ensure"] = "present";
            }

            ctx.Alw("nxEnvironmentTest Setup End.");
        }


    }
}
