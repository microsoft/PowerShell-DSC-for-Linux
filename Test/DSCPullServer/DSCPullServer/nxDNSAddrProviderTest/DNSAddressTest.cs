//-----------------------------------------------------------------------
// <copyright file="nxDNSAddrProviderTest.cs" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
// <author>v-fridax@microsoft.com</author>
// <description>Inherit from BaseProviderTest, override Setup(IContext ctx). </description>
//-----------------------------------------------------------------------
using System;
using Infra.Frmwrk;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace DSCPullServer
{
    class DNSAddressTest : ProviderTestBase
    {
        private const string debDNSCheck = "cat /etc/network/interfaces | grep -e \"dns-nameservers\\s*{0}\" | wc -l |tr -d '\n'";
        private const string suseDNSCheck = "cat /etc/sysconfig/network/config | grep -e \"NETCONFIG_DNS_STATIC_SEARCHLIST=\\\"{0}\\\"\" | wc -l | tr -d '\n'";
        private const string redDNSCheck = "cat /etc/resolv.conf | grep -e \"nameserver  {0}\" | wc -l | tr -d '\\n'";
        private string sysinfo;
        
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxDNSAddrTest Setup Begin.");
            mofHelper = new DNSAddressMofHelper();

            propString = ctx.Records.GetValue("propString");
            mofPath = ctx.Records.GetValue("mofPath");
            configMofScriptPath = ctx.Records.GetValue("configMofScriptPath");
            psScripts = ctx.Records.GetValues("psScript");
            psErrorMsg = ctx.Records.GetValue("psErrorMsg");
            verificationCmd = ctx.Records.GetValue("verificationCmd");
            expectedValue = ctx.Records.GetValue("expectedValue");
            successfulyMsg = ctx.Records.GetValue("successfulMsg");
            failedMsg = ctx.Records.GetValue("failedMsg");

            string nxHostName = ctx.Records.GetValue("nxHostName");
            string nxUsername = ctx.Records.GetValue("nxUsername");
            string nxpassword = ctx.Records.GetValue("nxpassword");
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);
            try
            {
                string tmpInfo = String.Empty;
                sshHelper.Execute("cat /proc/version", out tmpInfo);
                if (tmpInfo.ToLower().Contains("debian") || tmpInfo.ToLower().Contains("ubuntu"))
                {
                    sysinfo = "debian"; //debian & ubuntu
                    initializeCmd = "cp /etc/network/interfaces /tmp/interfaces_bk";
                    finalizeCmd = "cp /tmp/interfaces_bk /etc/network/interfaces";
                }
                else if (tmpInfo.ToLower().Contains("suse"))
                {
                    sysinfo = "suse";
                    initializeCmd = "cp /etc/sysconfig/network/config /tmp/config_bk";
                    finalizeCmd = "cp /tmp/config_bk /etc/sysconfig/network/config";
                }
                else
                {
                    sysinfo = "redhat"; //redhat & centos
                    initializeCmd = "cp /etc/resolv.conf /tmp/resolv.conf_bk";
                    finalizeCmd = "cp /tmp/resolv.conf_bk /etc/resolv.conf";
                }
            }
            catch (Exception ex)
            {  
                ctx.Alw(ex.Message);
            }
            initializeCmd = initializeCmd + ";sleep 1;" + ctx.Records.GetValue("initialCmd");
            base.Setup(ctx);

            ctx.Alw("nxDNSAddrTest Setup End.");
        }


        protected override void VerifyLinuxState(IContext ctx)
        {
            string verification = ctx.Records.GetValue("verification");
            Dictionary<string, string> verificationMap = new Dictionary<string, string>();
            if (!String.IsNullOrEmpty(verification))
            {
                verificationMap = ConvertStringToPropMap(verification);
            }
            else
            {
                ctx.Alw("No specified property need to be verified in varmap");
            }
            try
            {
                if(verificationMap.ContainsKey("Address"))
                {
                    string[] ipList = verificationMap["Address"].ToString().Split(',');
                    string ipString = String.Empty;
                    string result = String.Empty;
                    ipString = ipList.Aggregate(ipString, (current, item) => current + item + " ");

                    switch (sysinfo)
                    {
                        case "debian":
                            sshHelper.Execute(String.Format(debDNSCheck, ipString), out result);
                            if (result.Equals("0"))
                            {
                                throw new Exception("The DNSServer is not updated successfully");
                            }
                            break;
                        case "suse":
                            sshHelper.Execute(String.Format(suseDNSCheck, ipString), out result);
                            if (result.Equals("0"))
                            {
                                throw new Exception("The DNSServer is not updated successfully");
                            }
                            break;
                        default:
                            foreach (string item in ipList)
                            {
                                string cmd = String.Format(redDNSCheck, item);
                                sshHelper.Execute(cmd, out result);
                                if (result.Equals("0"))
                                {
                                    throw new Exception("The DNSServer is not updated successfully");
                                }
                            }
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }
        }
    }
}
