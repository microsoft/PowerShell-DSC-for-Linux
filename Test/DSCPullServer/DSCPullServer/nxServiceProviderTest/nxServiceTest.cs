using System.IO;

namespace DSCPullServer
{
    using System;
    using System.Text;
    using Infra.Frmwrk;
    
    class nxServiceTest : ProviderTestBase
    {
        private const string service_tool = "service";
        private const string chkconfig_tool = "/sbin/chkconfig";
        private const string invoke_tool = "/usr/sbin/invoke-rc.d";
        private const string update_tool = "/usr/sbin/update-rc.d";

        private const string service_tool_check_status_command = service_tool + " {0} status | tr -d '\n';";
        private const string chkconfig_tool_enable_command = chkconfig_tool + " {0} on;";
        private const string chkconfig_tool_disable_command = chkconfig_tool + " {0} off;";

        private const string invoke_tool_check_status_command = invoke_tool + " {0} status;";
        private const string update_tool_enable_command = update_tool + " -f {0} enable;";
        private const string update_tool_disable_command = update_tool + " -f {0} disable;";
       
            
            
        public override void Setup(IContext ctx)
        {
            ctx.Alw("nxServiceTest Setup Begin.");

            mofHelper = new ServiceMofHelper();
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
            string nxDomainName = ctx.Records.GetValue("nxDomainName"); 
            int nxPort = Int32.Parse(ctx.Records.GetValue("nxPort"));

            // Open SSH.
            sshHelper = new SshHelper(nxHostName, nxUsername, nxpassword, nxPort);

            string invalidServiceName = ctx.Records.GetValue("invalidServiceName");
            string serviceName = ctx.Records.GetValue("serviceName");
            string controller = ctx.Records.GetValue("controller");
            string state = ctx.Records.GetValue("initialState") ?? "";
            string enable = ctx.Records.GetValue("initialEnabledState") ?? "";
            string orgState = String.Empty;
            string orgEnableState = String.Empty;

            string sysinfo = String.Empty;
            if ( controller.ToLower().Equals("init"))
            {            
                sshHelper.Execute("cat /proc/version", out sysinfo);
                if (sysinfo.ToLower().Contains("ubuntu"))
                {
                    throw new VarUnsupported("init controller is ignored on Ubuntu!");
                }
            }
            
            // Check if the controller is supported on the Linux.
            CheckControllerExist(controller);

            // Check if the service exists in the controller.
            CheckServiceExistOrInvalid(controller, serviceName, invalidServiceName);

            initializeCmd = GetInitializeCmd(serviceName, controller, state, enable, out orgState, out orgEnableState);
            finalizeCmd = GetFinalizeCmd(serviceName, controller, orgState, orgEnableState);

            // Initialize Service State.
            ctx.Alw(String.Format("Initilize Linux state : '{0}'", initializeCmd));
            try
            {
                sshHelper.Execute(initializeCmd);
            }
            catch (Exception ex)
            {
                ctx.Alw(ex.Message);
            }

            // Prepare a configuration MOF file.
            propMap = ConvertStringToPropMap(propString);
            mofHelper.PrepareMofGenerator(propMap, configMofScriptPath, nxHostName, mofPath, nxDomainName);
            ctx.Alw(String.Format("Prepare a MOF generator '{0}'",
                configMofScriptPath));

            // Add the config to the logs
            StreamReader sr = new StreamReader(configMofScriptPath);
            string line = null;
            StringBuilder configFile = new StringBuilder();
            line = sr.ReadLine();
            while (line != null)
            {
                line = line.Replace("{", "{{").Replace("}", "}}");
                configFile.Append(line);
                line = sr.ReadLine();
            }
            ctx.Alw(String.Format(configFile.ToString()));


            ctx.Alw("nxServiceTest Setup End.");
        }

        /// <summary>
        /// Check Linux service's state and enabled state.
        /// </summary>
        /// <param name="ctx">Testing Context.</param>
        protected override void VerifyLinuxState(IContext ctx)
        {
            
            string verification = ctx.Records.GetValue("verification");

            if (String.IsNullOrEmpty(verification))
            {
                return;
            }

            var verificationMap = ConvertStringToPropMap(verification);

            string name = verificationMap["Name"];
            string controller = verificationMap["Controller"];

            string actualState = string.Empty;
            string actualEnable = string.Empty;
            switch (controller.ToLower())
            {
                case "init":
                    actualState = InitGetStatus(name);
                    actualEnable = InitGetEnabledState(name);
                    break;
                case "upstart":
                    actualState = UpstartGetStatus(name);
                    actualEnable = UpstartGetEnabledState(name);
                    break;
                case "systemd":
                    actualState = SystemdGetStatus(name);
                    actualEnable = SystemdGetEnabledState(name);
                    break;
                default:
                    throw new ArgumentException("The controller is invalid!");
            }

            // Check state if needed.
            if (verificationMap.ContainsKey("State"))
            {
                if (!verificationMap["State"].Equals(
                    actualState, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["State"], actualState));
                }
            }
            // Check enabled state if needed.
            if (verificationMap.ContainsKey("Enabled"))
            {
                if (!verificationMap["Enabled"].Equals(
                    actualEnable, StringComparison.InvariantCultureIgnoreCase))
                {
                    throw new VarFail(String.Format(
                        "'{0}' Service Enabled State : expect - '{1}', actual - '{2}'",
                        name, verificationMap["Enabled"], actualEnable));
                }
            }
        }

        #region Private Methods

        private string GetInitializeCmd(string name, string controller, string state, string enable, out string orgState, out string orgEnableState)
        {
            orgState = "";
            orgEnableState = "";

            switch (controller.ToLower())
            {
                case "init":
                    orgState = InitGetStatus(name);
                    orgEnableState = InitGetEnabledState(name);
                    break;
                case "upstart":
                    orgState = UpstartGetStatus(name);
                    orgEnableState = UpstartGetEnabledState(name);
                    break;
                case "systemd":
                    orgState = SystemdGetStatus(name);
                    orgEnableState = SystemdGetEnabledState(name);
                    break;
                default:
                    throw new ArgumentException("The controller is invalid!");
            }

            return GetCmd(name, controller, state, enable);
        }

        private string GetFinalizeCmd(string name, string controller, string state, string enable)
        {
            return GetCmd(name, controller, state, enable);
        }

        private string GetCmd(string name, string controller, string state, string enable)
        {
            StringBuilder command = new StringBuilder();

            switch (controller.ToLower())
            {
                case "init":
                    command.Append(InitCmd(name, state, enable));
                    break;
                case "upstart":
                    command.Append(UpstartCmd(name, state, enable));
                    break;
                case "systemd":
                    command.Append(SystemdCmd(name, state, enable));
                    break;
                default:
                    throw new ArgumentException("The controller is invalid!");
            }

            return command.ToString();
        }

        private void CheckControllerExist(string controller)
        {
            switch (controller.ToLower())
            {
                case "init":
                    if (!InitExist())
                    {
                        throw new VarUnsupported("init controller does not exist!");
                    }
                    break;
                case "upstart":
                    if (!UpstartExist())
                    {
                        throw new VarUnsupported("upstart controller does not exist!");
                    }
                    break;
                case "systemd":
                    if (!SystemdExist())
                    {
                        throw new VarUnsupported("systemd controller does not exist!");
                    }
                    break;
                default:
                    throw new ArgumentException("The controller is invalid!");
            }
        }

        private void CheckServiceExistOrInvalid(string controller, string serviceName, string expectedInvalidService)
        {
            if (serviceName.Equals(expectedInvalidService))
            {
                return;
            }

            switch (controller.ToLower())
            {
                case "init":
                    if (!InitServiceExist(serviceName))
                    {
                        throw new VarUnsupported("service does not exist!");
                    }
                    break;
                case "upstart":
                    if (!UpstartServiceExist(serviceName))
                    {
                        throw new VarUnsupported("service does not exist!");
                    }
                    break;
                case "systemd":
                    if (!SystemdServiceExist(serviceName))
                    {
                        throw new VarUnsupported("service does not exist!");
                    }
                    break;
                default:
                    throw new ArgumentException("The controller is invalid!");
            }
        }

        #region Upstart Controller
        private string UpstartCmd(string name, string state, string enable)
        {
            StringBuilder command = new StringBuilder();

            if (state.ToLower() == "running")
            {
                // Start Service.
                command.Append("/sbin/start " + name + ";");
            }
            else if (state.ToLower() == "stopped")
            {
                // Stop Service.
                command.Append("/sbin/stop " + name + ";");
            }

            // Change /etc/init/{service}.conf file to enable/disable service.
            if (enable.ToLower() == "true")
            {
                // Enable Service.
                string enableCommand = String.Format(
                    "ls /etc/init/{0}.conf;if [ $? -eq 0 ];then sed 's/start on runlevel .*/start on runlevel [2345]/g' /etc/init/{0}.conf  > /tmp/{0}.conf.tmp; cat /tmp/{0}.conf.tmp > /etc/init/{0}.conf;sed 's/stop on runlevel .*/stop on runlevel [!2345]/g' /etc/init/{0}.conf > /tmp/{0}.conf.tmp; cat /tmp/{0}.conf.tmp> /etc/init/{0}.conf;fi",
                    name);
                command.Append(enableCommand);
            }
            else if (enable.ToLower() == "false")
            {
                // Disable Service.
                string disableCommand = String.Format(
                    "ls /etc/init/{0}.conf;if [ $? -eq 0 ];then sed 's/start on runlevel .*//g' /etc/init/{0}.conf  > /tmp/{0}.conf.tmp; cat /tmp/{0}.conf.tmp > /etc/init/{0}.conf;sed 's/stop on runlevel .*/stop on runlevel [0123456]/g' /etc/init/{0}.conf > /tmp/{0}.conf.tmp; cat /tmp/{0}.conf.tmp> /etc/init/{0}.conf;fi",
                    name);
                command.Append(disableCommand);
            }
            return command.ToString();
        }

        private string UpstartGetStatus(string name)
        {
            try
            {
                string retval = "";
                sshHelper.Execute("/sbin/status " + name + " | tr -d '\n'", out retval);

                if (retval.Contains("start"))
                {
                    return "Running";
                }
                else
                {
                    return "Stopped";
                }
            }
            catch { }

            return "Stopped";
        }

        private string UpstartGetEnabledState(string name)
        {
            try
            {
                string startRetval = "";
                string stopRetval = "";
                sshHelper.Execute("cat /etc/init/" + name + ".conf | grep -i 'start on runlevel ' | awk '{print $4}' | tr -d '\n'", out startRetval);
                sshHelper.Execute("cat /etc/init/" + name + ".conf | grep -i 'stop on runlevel ' | awk '{print $4}' | tr -d '\n'", out stopRetval);

                if (startRetval == "[2345]" && stopRetval == "[!2345]")
                {
                    return "true";
                }

                if (stopRetval == "[0123456]")
                {
                    return "false";
                }
            }
            catch { }

            return "false";
        }

        private bool UpstartExist()
        {
            try
            {
                sshHelper.Execute("ls /sbin/start");
                sshHelper.Execute("ls /sbin/stop");
                sshHelper.Execute("ls /sbin/status");
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        private bool UpstartServiceExist(string service)
        {
            try
            {
                sshHelper.Execute(String.Format("ls /etc/init/{0}.conf", service));
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        #endregion

        #region Systemd Controller
        private string SystemdCmd(string name, string state, string enable)
        {
            StringBuilder command = new StringBuilder();

            if (state.ToLower() == "running")
            {
                // Start Service.
                command.Append("/bin/systemctl start " + name + ";");
            }
            else if (state.ToLower() == "stopped")
            {
                // Stop Service.
                command.Append("/bin/systemctl stop " + name + ";");
            }

            if (enable.ToLower() == "true")
            {
                // Enable Service.
                command.Append("/bin/systemctl enable " + name + ";");
            }
            else if (enable.ToLower() == "false")
            {
                // Disable Service.
                command.Append("/bin/systemctl disable " + name + ";");
            }

            return command.ToString();
        }

        private string SystemdGetStatus(string name)
        {
            try
            {
                string rlt = String.Empty;
                sshHelper.Execute("/bin/systemctl status " + name, out rlt);
                if (rlt.ToLower().Contains("running"))
                    return "Running";
                else
                    return "Stopped";
            }
            catch (InvalidOperationException)
            {
                return "Stopped";
            }
        }

        private string SystemdGetEnabledState(string name)
        {
            try
            {
                sshHelper.Execute("/bin/systemctl is-enabled " + name);

                return "true";
            }
            catch (InvalidOperationException)
            {
                return "false";
            }
        }

        private bool SystemdExist()
        {
            try
            {
                sshHelper.Execute("ls /bin/systemctl");
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        private bool SystemdServiceExist(string service)
        {
            try
            {
                sshHelper.Execute(String.Format("ls /usr/lib/systemd/system/{0}.service", service));
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        #endregion

        #region Init Controller

        private string InitCmd(string name, string state, string enable)
        {
            StringBuilder command = new StringBuilder();

            string change_state_command = "";
            string enable_command = "";
            string disable_command = "";

            
            try
            {
                sshHelper.Execute("ls /sbin/service");
                sshHelper.Execute("ls /sbin/chkconfig");
                change_state_command = service_tool;
                enable_command = chkconfig_tool_enable_command;
                disable_command = chkconfig_tool_disable_command;
            }
            catch (InvalidOperationException)
            {
                change_state_command = invoke_tool;
                enable_command = update_tool_enable_command;
                disable_command = update_tool_disable_command;

                command.Append(String.Format(disable_command, name));
                command.Append(String.Format(enable_command, name)); 
       
            }

            
            if (state.ToLower() == "running")
            {
                // Start Service.
                command.Append(change_state_command + " " + name + " start;");
            }
            else if (state.ToLower() == "stopped")
            {
                command.Append(change_state_command + " " + name + " start;");
                // Stop Service.
                command.Append(change_state_command + " " + name + " stop;");
            }

            if (enable.ToLower() == "true")
            {
                // Enable Service.
                command.Append(String.Format(enable_command, name));
            }
            else if (enable.ToLower() == "false")
            {
                // Disable Service.
                command.Append(String.Format(disable_command, name));

            }

            return command.ToString();
        }

        private string InitGetStatus(string name)
        {
            string retval = "";
            try
            {
                sshHelper.Execute(String.Format(service_tool_check_status_command, name), out retval);
            }
            catch (InvalidOperationException)
            {
                sshHelper.Execute(String.Format(invoke_tool_check_status_command, name), out retval);
            }
             
            if (retval.Contains("running") && !retval.Contains("failed"))
            {
                return "Running";
            }
            else if (retval.Trim().Equals("Running"))
            {
                return "Running";
            }
            else
            {
                return "Stopped";
            }
            
            
        }

        private string InitGetEnabledState(string name)
        {
            bool service_tool_exist = false;
            try
            {
                sshHelper.Execute("ls /sbin/service");
                sshHelper.Execute("ls /sbin/chkconfig");
                service_tool_exist = true;
            }
            catch (InvalidOperationException)
            {
                service_tool_exist = false;
            }

            if (service_tool_exist)
            {
                try
                {
                    string retval = "";
                    sshHelper.Execute("/sbin/chkconfig --list " + name + " | awk '{print $4$5$6$7}' | tr -d '\n'", out retval);

                    if (retval.Contains("2:on3:on4:on5:on") || retval.Contains("2:on3:on4:off5:on"))
                    {
                        return "true";
                    }
                    else if (retval.Contains("off"))
                    {
                        return "false";
                    }
                }
                catch (InvalidOperationException) { return "false"; }
            }
            else
            { 
                try
                {
                    string retval = "";
                    string command = "start=`ls -l /etc/rc[2-5].d/S*{0} | wc -l`;stop=`ls -l /etc/rc[016].d/K*{0} | wc -l`;echo $start$stop | tr -d '\n'";
                    sshHelper.Execute(String.Format(command, name), out retval);

                    if (retval.Equals("43"))
                    {
                        return "true";
                    }
                }
                catch (InvalidOperationException) { return "false"; }
            }

            return "false";
        }

        private bool InitExist()
        {
            try
            {
                sshHelper.Execute("ls /sbin/init");
                return true;
            }
            catch(InvalidOperationException)
            {
                return false;
            }
        }

        private bool InitServiceExist(string service)
        {
            try
            {
                sshHelper.Execute(String.Format("ls /etc/init.d/{0}", service));
                return true;
            }
            catch (InvalidOperationException)
            {
                return false;
            }
        }

        #endregion

        #endregion
    }
}
