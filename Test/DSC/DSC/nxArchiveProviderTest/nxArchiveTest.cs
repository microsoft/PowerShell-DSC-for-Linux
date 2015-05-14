using System;
using Infra.Frmwrk;
using System.Collections.Generic;
using System.Linq;

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

            if (!propMap.ContainsKey("Force")) 
            {
                propMap["Force"] = "False";
            }

            if (!propMap.ContainsKey("Ensure")) 
            {
                propMap["Ensure"] = "present";
            }

            if (!propMap.ContainsKey("Checksum")) 
            {
                propMap["Checksum"] = "md5";
            }
            ctx.Alw("nxArchiveTest Setup End.");
        }

    }
}
