//-----------------------------------------------------------------------
// <copyright file="nxLogTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------


using Infra.Frmwrk;

namespace DSC
{
    class nxLogTest : ProviderTestBase
    {
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxLogTest Setup Begin.");

            mofHelper = new ScriptMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            ctx.Alw("nxLogTest Setup End.");
        }
    }
}
