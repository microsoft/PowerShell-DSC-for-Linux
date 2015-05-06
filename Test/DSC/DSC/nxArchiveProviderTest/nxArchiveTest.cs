using System;
using Infra.Frmwrk;

namespace DSC
{
    class nxArchiveTest : ProviderTestBase
    {

        protected SshHelper sshHelper;
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxArchiveTest Setup Begin.");

            mofHelper = new ArchiveMofHelper(ctx);

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            ctx.Alw("nxArchiveTest Setup End.");
        }

    }
}
