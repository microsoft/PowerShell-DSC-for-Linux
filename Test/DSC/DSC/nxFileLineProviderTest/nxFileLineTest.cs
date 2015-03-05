using System;
using Infra.Frmwrk;

namespace DSC
{
    class nxFileLineTest : ProviderTestBase
    {

        protected SshHelper sshHelper;
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
