using System;
using Infra.Frmwrk;

namespace DSCPullServer
{
    class nxArchiveTest : ProviderTestBase
    {
        const string getMtimeCmd = "stat {0} |grep -i 'Modify'|awk '{print $3}'|cut -d '.' -f1 |tr -d '\n'";
        const string getCtimeCmd = "stat {0} |grep -i 'Change'|awk '{print $3}'|cut -d '.' -f1 |tr -d '\n'";
        private string time;
        private string getTimeCmd;
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxArchiveTest Setup Begin.");

            mofHelper = new ArchiveMofHelper(ctx);

            initializeCmd = ctx.Records.GetValue("initialCmd");
            finalizeCmd = ctx.Records.GetValue("finalCmd");

            base.Setup(ctx);

            if (verificationCmd.ToLower().Equals("ctime"))
            {
                getTimeCmd = getCtimeCmd.Replace("{0}", propMap["DestinationPath"]);
            }
            else if (verificationCmd.ToLower().Equals("mtime"))
            {
                getTimeCmd = getMtimeCmd.Replace("{0}", propMap["DestinationPath"]);
            }

            ctx.Alw("nxArchiveTest Setup End.");
        }


        public override void Verify(IContext ctx)
        {
            ctx.Alw("Verify Begin.");

            if (String.IsNullOrWhiteSpace(psErrorMsg))
            {
                try
                {
                    sshHelper.Execute(forcePullpullServerCmd);
                }
                catch (Exception ex)
                {
                    ctx.Alw(ex.Message);
                }

                if (verificationCmd.ToLower().Equals("ctime") || verificationCmd.ToLower().Equals("mtime"))
                {
                    try
                    {
                        sshHelper.Execute(getTimeCmd, out time);

                    }
                    catch (Exception)
                    {
                        throw new VarFail(String.Format("Fail to get ctime or mtime of {0}", propMap["DestinationPath"]));
                    }

                    //Run the second time to verify if the destination path will be updated when the source has no change.
                    try
                    {
                        sshHelper.Execute(forcePullpullServerCmd);
                    }
                    catch (Exception ex)
                    {
                        ctx.Alw(ex.Message);
                    }
                }
                
                // Verify Linux machine state.
                VerifyLinuxState(ctx);

            }
            else
            {
                //Fail to execute force pull server command when it should send error message.
                try
                {
                    sshHelper.Execute(forcePullpullServerCmd);
                }
                catch (Exception)
                {
                    ctx.Alw(String.Format("Send the error message"));
                }
            }
            ctx.Alw("Verify End.");
        }

        protected override void VerifyLinuxState(IContext ctx)
        {
            
            if (!string.IsNullOrWhiteSpace(verificationCmd))
            {
                if (verificationCmd.ToLower().Equals("ctime") || verificationCmd.ToLower().Equals("mtime"))
                {
                    try
                    {
                        string newTime = string.Empty;

                        //get the new ctime or mtime.
                        sshHelper.Execute(getTimeCmd, out newTime);

                        //the old time and new time should be same.
                        if (!newTime.Equals(time))
                        {
                            throw new VarFail(failedMsg);
                        }
                    }
                    catch (Exception ex)
                    {
                        throw new VarFail(failedMsg, ex);
                    }
                }
                else
                {
                    try
                    {
                        ctx.Alw(String.Format("Run verification command : '{0}', expect it return '{1}'",
                            verificationCmd, expectedValue));
                        sshHelper.VerifyExecution(verificationCmd, expectedValue);

                        ctx.Alw(successfulyMsg);
                    }
                    catch (Exception ex)
                    {
                        throw new VarFail(failedMsg, ex);
                    }
                }
            }
        }
    }
}
