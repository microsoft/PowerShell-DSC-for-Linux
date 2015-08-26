using System;
using Infra.Frmwrk;

namespace DSCPullServer
{
    class nxFileLineTest : ProviderTestBase
    {

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxFileLineTest Setup Begin.");

            mofHelper = new FileLineMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            ctx.Alw("nxFileLineTest Setup End.");
        }

    }
}
