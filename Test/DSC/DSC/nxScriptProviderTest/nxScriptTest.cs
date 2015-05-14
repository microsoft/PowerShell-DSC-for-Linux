namespace DSC
{
    using Infra.Frmwrk;
    
    class nxScriptTest : ProviderTestBase
    {
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxScriptTest Setup Begin.");

            mofHelper = new ScriptMofHelper();

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            if (!propMap.ContainsKey("User"))
            {
                propMap["User"] = "";
            }

            if (!propMap.ContainsKey("Group"))
            {
                propMap["Group"] = "";
            }

            ctx.Alw("nxScriptTest Setup End."); 
        }
    }
}
