using System;
using System.Text;
using Infra.Frmwrk;
using System.IO;

namespace DSC
{
    class nxExecTest : ProviderTestBase
    {

        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxExecTest Setup Begin.");

            mofHelper = new ExecMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);
            ctx.Alw("nxExecTest Setup End.");
        }

    }
}
