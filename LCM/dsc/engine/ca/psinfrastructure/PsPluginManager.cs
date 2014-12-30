using System.Diagnostics;
using System.Linq;
using System.Text;
using Microsoft.Management.Infrastructure;
using Microsoft.Management.Infrastructure.Native;
using System.Security.Cryptography;
using System.Security.Cryptography.X509Certificates;
using System;
using System.Security;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Globalization;
using System.IO;
// ReSharper disable RedundantUsingDirective
using System.IO.Compression;
// ReSharper restore RedundantUsingDirective
using System.Management.Automation;
using System.Management.Automation.Runspaces;
using Microsoft.PowerShell.Commands;

namespace Microsoft.PowerShell.DesiredStateConfiguration.Internal
{
    /// <summary>
    /// DownloadManagerBase handles the interaction between CA and the Powershell download managers.
    /// </summary>
    public static class DownloadManagerBase
    {
        #region PLUGIN_CONSTANTS

        // Cmdlets
        private const string DownloadManagerGetConfiguration = "Get-DscDocument";
        private const string DownloadManagerGetModules = "Get-DscModule";
        private const string DownloadManagerGetAction = "Get-DscAction";
        private const string WebDownloadManagerName = "WebDownloadManager";
        private const string WebDownloadManagerLoadPath = "PSDesiredStateConfiguration\\WebDownloadManager";
        private const string FileDownloadManagerName = "DSCFileDownloadManager";
        private const string FileDownloadManagerLoadPath = "PSDesiredStateConfiguration\\DownloadManager\\DSCFileDownloadManager";
        private static readonly Dictionary<string, string> DownloadManagerMap;

        // PS DSC module cmdlets
        private const string PsDscCmdletGet = "Get-TargetResource";
        private const string PsDscCmdletSet = "Set-TargetResource";
        private const string PsDscCmdletTest = "Test-TargetResource";
        private const string BaseResourceClass = "OMI_BaseResource";

        // Parameters
        private const string ParamCredential = "Credential";
        private const string ParamCredentialUserName = "UserName";
        private const string ParamCredentialPassword = "Password";
        private const string ParamCredentialDomain = "Domain";
        private const string ParamConfigurationId = "ConfigurationID";
        private const string ParamDestinationPath = "DestinationPath";
        private const string ParamModules = "Module";
        private const string ParamFileHash = "FileHash";
        private const string ParamStatusCode = "StatusCode";
        private const string ParamNotCompliant = "NotCompliant";

        //Meta Config
        private const string MetaConfigConfigurationId = "ConfigurationID";
        private const string UseSystemUUIDValue = "UseSystemUUID";
        private const string MetaConfigDownloadManagerName = "DownloadManagerName";
        private const string MetaConfigDownloadManagerCustomData = "DownloadManagerCustomData"; //This is array of MSFT_KeyValuePair.
        //static readonly string MetaConfig_Credential = "Credential";
        private const string MetaConfigAllowModuleOverwrite = "AllowModuleOverwrite";

        // Infrastructure defaults
        private const int SchemaValidationOption = 4; //Ignore
        //static readonly string BASE_RESOURCE_CLASSNAME = "OMI_BaseResource";
        private const string BaseDocumentClassname = "OMI_ConfigurationDocument";
        static readonly string[] NativeModules = { "MSFT_FileDirectoryConfiguration" };
        // status result
        private const string StatusOk = "OK";
        private const string StatusGetMof = "GETCONFIGURATION";
        private const string StatusRetry = "RETRY";

        private const string WriteQualifier = "write";

        #endregion PLUGIN_CONSTANTS
        #region PLUGIN_STATE
        //This is initialized only once and cached until process is unloaded.
        // ReSharper disable FieldCanBeMadeReadOnly.Local
        static private Runspace _pluginRunspace;
        static private Runspace _validationRunspace;
        // ReSharper restore FieldCanBeMadeReadOnly.Local
        static private readonly bool PluginRunspaceInitialized;
        static private string _pluginModuleName;

        /// <summary>
        /// Enumeration for Get Action Status Code
        /// </summary>
        internal enum GetActionStatusCodeTypes
        {
            Success = 0,
            DownloadManagerInitializationFailure = 1,
            GetConfigurationCommandFailure = 2,
            UnexpectedGetConfigurationResponseFromServer = 3,
            ConfigurationChecksumFileReadFailure = 4,
            ConfigurationChecksumValidationFailure = 5,
            InvalidConfigurationFile = 6,
            AvailableModulesCheckFailure = 7,
            InvalidConfigurationIdInMetaConfig = 8,
            InvalidDownloadManagerCustomDataInMetaConfig = 9,
            GetDscModuleCommandFailure = 10,
            GetDscModuleInvalidOutput = 11,
            ModuleChecksumFileNotFound = 12,
            InvalidModuleFile = 13,
            ModuleChecksumValidationFailure = 14,
            ModuleExtractionFailure = 15,
            ModuleValidationFailure = 16,
            InvalidDownloadedModule = 17,
            ConfigurationFileNotFound = 18,
            MultipleConfigurationFilesFound = 19,
            ConfigurationChecksumFileNotFound = 20,
            ModuleNotFound = 21,
            InvalidModuleVersionFormat = 22,
            InvalidConfigurationIdFormat = 23,
            GetDscActionCommandFailure = 24,
            InvalidChecksumAlgorithm = 25,
        };

        #endregion PLUGIN_STATE
        #region PLUGIN_CONSTRUCTORS
        static DownloadManagerBase()
        {
            DownloadManagerMap = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
            DownloadManagerMap.Add(WebDownloadManagerName, WebDownloadManagerLoadPath);
            DownloadManagerMap.Add(FileDownloadManagerName, FileDownloadManagerLoadPath);
            _pluginRunspace = RunspaceFactory.CreateRunspace(InitialSessionState.CreateDefault2());
            _pluginRunspace.Open();
            _validationRunspace = RunspaceFactory.CreateRunspace(InitialSessionState.CreateDefault2());
            _validationRunspace.Open();
            PluginRunspaceInitialized = false;
        }

        #endregion PLUGIN_CONSTRUCTORS
        #region PLUGIN_GETCONFIGURATION
        /*If this succeeds, the first object in the collection is a valid object.*/
        private static MiResult ValidateGetConfigurationResult(System.Management.Automation.PowerShell powershell, Collection<PSObject> providerImportResult,
                                                                  string downloadManagerName, out string importModuleResult, out ErrorRecord errorRecord,
                                                                  out UInt32 getActionStatusCode)
        {
            var result = ValidateGetResult(powershell, providerImportResult, downloadManagerName, out importModuleResult,
                                                out errorRecord, out getActionStatusCode);

            if (result != MiResult.OK)
            {
                return result;
            }
            if (!(string.Compare(importModuleResult, StatusOk, StringComparison.OrdinalIgnoreCase) == 0 ||
                string.Compare(importModuleResult, StatusRetry, StringComparison.OrdinalIgnoreCase) == 0))
            {
                errorRecord = GetErrorRecord("PsPluginManagerGetConfUnexpectedResult", ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.PsPluginManagerGetConfUnexpectedResult, importModuleResult, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.UnexpectedGetConfigurationResponseFromServer;
                return MiResult.FAILED;
            }
            return result;
        }
        /*If this succeeds, the first object in the collection is a valid object.*/
        private static MiResult ValidateGetResult(System.Management.Automation.PowerShell powershell, Collection<PSObject> providerImportResult,
                                                                  string downloadManagerName, out string importModuleResult, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            importModuleResult = null;
            HandleNonTerminatingErrors(powershell, downloadManagerName, DownloadManagerGetConfiguration, out errorRecord);
            if (errorRecord != null)
            {
                getActionStatusCode = (int) GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                return MiResult.FAILED;
            }

            if (providerImportResult == null || providerImportResult.Count != 1)
            {
                errorRecord = GetErrorRecord("GetConfigurationResultNotExpected", ErrorCategory.ObjectNotFound,
                                                    PSinfrastructureStrings.GetConfigurationResultCountUnexpected, downloadManagerName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                return MiResult.NOT_FOUND;
            }
            try
            {
                importModuleResult = LanguagePrimitives.ConvertTo<string>(providerImportResult[0]);
            }
            catch (PSInvalidCastException ex)
            {
                errorRecord = GetErrorRecord("GetConfigurationResultNotExpected", ex, ErrorCategory.InvalidType,
                                                    PSinfrastructureStrings.GetConfigurationResultCountUnexpected, downloadManagerName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                return MiResult.NOT_FOUND;
            }

            if (importModuleResult == null || string.IsNullOrEmpty(importModuleResult))
            {
                errorRecord = GetErrorRecord("GetConfigurationResultNotExpected", ErrorCategory.ObjectNotFound,
                                                                   PSinfrastructureStrings.GetConfigurationResultCountUnexpected, downloadManagerName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                return MiResult.NOT_FOUND;
            }
            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }
        /*If this succeeds, the first object in the collection is a valid object.*/
        private static MiResult ValidateGetActionResult(System.Management.Automation.PowerShell powershell, Collection<PSObject> providerImportResult,
                                                                  string downloadManagerName, out string importModuleResult, out ErrorRecord errorRecord,
                                                                  out UInt32 getActionStatusCode)
        {
            var result = ValidateGetResult(powershell, providerImportResult, downloadManagerName, out importModuleResult,
                                                out errorRecord, out getActionStatusCode);
            if (result != MiResult.OK)
            {
                return result;
            }
            if (!(string.Compare(importModuleResult, StatusOk, StringComparison.OrdinalIgnoreCase) == 0 ||
                string.Compare(importModuleResult, StatusGetMof, StringComparison.OrdinalIgnoreCase) == 0))
            {
                errorRecord = GetErrorRecord("PluginGetActionUnsuccessful", ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.PluginGetActionUnsuccessful, importModuleResult, _pluginModuleName);
                return MiResult.FAILED;
            }
            return result;
        }
        #endregion PLUGIN_GETCONFIGURATION
        #region PLUGIN_GETMODULE

        /*If this succeeds, the first object in the collection is a valid object.*/
        private static MiResult ValidateModuleForVersion(System.Management.Automation.PowerShell powershell,
                                            IEnumerable<PSModuleInfo> availableModules,
                                            string downloadManagerName,
                                            string moduleVersion,
                                            out bool isModuleAvailable,
                                            out ErrorRecord errorRecord)
        {
            isModuleAvailable = false;

            HandleNonTerminatingErrors(powershell, downloadManagerName, "Import-Module", out errorRecord);
            if (errorRecord != null)
            {
                return MiResult.FAILED;
            }

            if (availableModules == null)
            {
                return MiResult.OK; // cached module not available.
            }
            // ReSharper disable LoopCanBeConvertedToQuery
            foreach (PSModuleInfo localModule in availableModules)
            // ReSharper restore LoopCanBeConvertedToQuery
            {
                if (string.IsNullOrEmpty(moduleVersion) ||
                    string.Compare(moduleVersion, localModule.Version.ToString(), StringComparison.OrdinalIgnoreCase) == 0)
                {
                    // Module is a default module available in system cache.
                    S_DscCoreR.EventWriteLCMPullModuleSkippedAsModuleIsAvailable(S_DscCoreR.JobGuidString, localModule.Name, localModule.Version.ToString(), localModule.Path);
                    isModuleAvailable = true;
                    return MiResult.OK;
                }
            }

            return MiResult.OK;
        }

        private static ModuleSpecification[] GetModuleSpecification(Dictionary<string, Tuple<string, List<string>>> moduleVersionTable)
        {
            List<ModuleSpecification> moduleSpecifications = new List<ModuleSpecification>();
            foreach (var entry in moduleVersionTable)
            {
                if (string.IsNullOrEmpty(entry.Value.Item1))
                {
                    moduleSpecifications.Add(new ModuleSpecification(entry.Key));
                }
                else
                {
                    Hashtable h = new Hashtable(StringComparer.OrdinalIgnoreCase);
                    h.Add("ModuleName", entry.Key);
                    h.Add("ModuleVersion", entry.Value.Item1);
                    moduleSpecifications.Add(new ModuleSpecification(h));
                }

            }

            return moduleSpecifications.ToArray();
        }

        private static MiResult GetGetModuleParams(IntPtr metaConfigHandle, out PSCredential pscredential,
                                                       Hashtable arguments, out string configurationId,
                                                        out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            //Get info from MetaConfig
            MiResult statusCode = GetMetaConfigParams(metaConfigHandle, out pscredential, arguments, out configurationId, out errorRecord, out getActionStatusCode);
            return statusCode;
        }

        private static MiResult GetModuleNameVersionTable(string mofFileLocation, Dictionary<string, Tuple<string, List<string>>> moduleNameTable, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            Debug.Assert(moduleNameTable != null, "moduleNameTable can not be null");
            //Load the mof file.
            errorRecord = null;
            List<CimInstance> cimInstances;
            try
            {
                CimClassCache.InitializeInfraStructureMof();
                cimInstances = CimClassCache.ImportInstances(mofFileLocation, SchemaValidationOption);
            }
            catch (CimException exception)
            {
                errorRecord = GetErrorRecord("ConfigurationFileInvalid", ErrorCategory.InvalidResult,
                                                                        PSinfrastructureStrings.ConfigurationFileInvalid, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidConfigurationFile;
                return (MiResult)exception.StatusCode;
            }

            foreach (var inst in cimInstances)
            {
                string moduleName = inst.CimSystemProperties.ClassName;
                string moduleVersion = "";
                string providerClassName = inst.CimSystemProperties.ClassName;
                // check for resource class and get module Name and Version
                if (string.Compare(inst.CimSystemProperties.ClassName, BaseDocumentClassname, StringComparison.OrdinalIgnoreCase) != 0)
                {
                    if (inst.CimInstanceProperties["ModuleName"] != null && inst.CimInstanceProperties["ModuleName"].Value != null)
                    {
                        moduleName = inst.CimInstanceProperties["ModuleName"].Value.ToString();
                    }
                    if (inst.CimInstanceProperties["ModuleVersion"] != null && inst.CimInstanceProperties["ModuleVersion"].Value != null)
                    {
                        moduleVersion = inst.CimInstanceProperties["ModuleVersion"].Value.ToString();
                    }

                    if (!string.IsNullOrEmpty(moduleName) && (string.IsNullOrEmpty(moduleVersion) || IsModuleVersionValidFormat(moduleVersion)))
                    {
                        Tuple<string, List<string>> moduleEntry;
                        if (moduleNameTable.ContainsKey(moduleName))
                        {
                            moduleEntry = moduleNameTable[moduleName];
                            if (!moduleEntry.Item2.Contains(providerClassName))
                            {
                                moduleEntry.Item2.Add(providerClassName);
                            }
                        }
                        else
                        {
                            moduleEntry = new Tuple<string, List<string>>(moduleVersion, new List<string>());
                            moduleEntry.Item2.Add(providerClassName);
                            moduleNameTable[moduleName] = moduleEntry;
                        }
                    }
                    else
                    {
                        getActionStatusCode = (int) GetActionStatusCodeTypes.InvalidModuleVersionFormat;
                        S_DscCoreR.EventWriteLCMPullModuleInvalidVersionFormat(S_DscCoreR.JobGuidString, moduleName, moduleVersion);
                        errorRecord = GetErrorRecord("InvalidModuleVersionFormat", null, ErrorCategory.InvalidArgument, PSinfrastructureStrings.InvalidModuleVersionFormat, moduleVersion, moduleName);
                        return MiResult.INVALID_PARAMETER;
                    }
                }
            }
            // check with cached modules and remove them from the list.

            return FilterUsingCachedModules(moduleNameTable, out errorRecord, out getActionStatusCode);
        }

        private static bool IsModuleVersionValidFormat(string moduleVersion)
        {
            Version throwAwayVersion;
            return Version.TryParse(moduleVersion, out throwAwayVersion);
        }

        private static MiResult FilterUsingCachedModules(Dictionary<string, Tuple<string, List<string>>> moduleNameTable, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            errorRecord = null;
            // if it is known Native Module, remove it from the list.
            foreach (string nativeModule in NativeModules)
            {
                if (moduleNameTable.ContainsKey(nativeModule))
                {
                    //remove it
                    moduleNameTable.Remove(nativeModule);
                }
            }
            // Find if modules are present locally
            var cachedModules = new List<string>();
            foreach (var entry in moduleNameTable)
            {
                // Find if modules are present as internal DSC module
                var corePsProvidersModuleRelativePath = Path.Combine(Constants.CorePsProvidersRelativePath, entry.Key);
                var corePsProvidersModulePath = Path.Combine(Environment.SystemDirectory, corePsProvidersModuleRelativePath);
                if (Directory.Exists(corePsProvidersModulePath))
                {
                    S_DscCoreR.EventWriteLCMPullModuleSkippedAsModuleIsAvailable(S_DscCoreR.JobGuidString, entry.Key, entry.Value.Item1, corePsProvidersModulePath);
                    cachedModules.Add(entry.Key);
                    continue;
                }

                System.Management.Automation.PowerShell powershell = System.Management.Automation.PowerShell.Create();
                powershell.Runspace = _pluginRunspace;
                Collection<PSModuleInfo> availableModules;
                try
                {
                    // check if the module exists.
                    powershell.AddCommand("Get-Module").AddParameter("Name", entry.Key).AddParameter("ListAvailable");
                    powershell.Streams.Error.Clear();
                    availableModules = powershell.Invoke<PSModuleInfo>();
                    if (powershell.Streams.Error.Count > 0)
                    {
                        errorRecord = GetErrorRecord("GetModuleListAvailableError", ErrorCategory.InvalidResult,
                                                                               PSinfrastructureStrings.GetModuleListAvailableError, entry.Key);
                        powershell.Dispose();
                        getActionStatusCode = (int)GetActionStatusCodeTypes.AvailableModulesCheckFailure;
                        return MiResult.FAILED;
                    }
                }
                catch (Exception ex)
                {
                    errorRecord = GetErrorRecord("GetModuleListAvailableError", ex, ErrorCategory.InvalidResult,
                                                                            PSinfrastructureStrings.GetModuleListAvailableError, entry.Key);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.AvailableModulesCheckFailure;
                    return MiResult.FAILED;
                }
                bool isModuleAvailable;
                var statusCode = ValidateModuleForVersion(powershell, availableModules, entry.Key, entry.Value.Item1, out isModuleAvailable, out errorRecord);
                powershell.Dispose();
                if (statusCode != MiResult.OK)
                {
                    getActionStatusCode = (int)GetActionStatusCodeTypes.AvailableModulesCheckFailure;
                    return statusCode;
                }

                if (isModuleAvailable)
                {
                    cachedModules.Add(entry.Key);
                }
            }
            // Remove the cached item from the list so we don't need to pull those
            foreach (var cachedModule in cachedModules)
            {
                moduleNameTable.Remove(cachedModule);
            }
            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }
        private static MiResult ValidatePsdscModule(string moduleName, string schemaFileName, out UInt32 getActionStatusCode, out ErrorRecord errorRecord)
        {
            errorRecord = null;
            CimClassCache.InitializeInfraStructureMof();
            List<CimClass> newCimClasses;
            PSModuleInfo moduleInfo;

            if (!File.Exists(schemaFileName))
            {
                getActionStatusCode = (int) GetActionStatusCodeTypes.ModuleValidationFailure;

                errorRecord = Utility.CreateErrorRecord(
                        "ProviderSchemaFileNotFound",
                        ErrorCategory.ObjectNotFound,
                        null,
                        PSinfrastructureStrings.SchemaFileNotFound,
                        new object[] { moduleName, schemaFileName });

                return MiResult.NOT_FOUND;
            }

            try
            {
                newCimClasses = CimClassCache.ImportClasses(schemaFileName);

                // Get Module Info by importing module.
                using (System.Management.Automation.PowerShell ps = System.Management.Automation.PowerShell.Create())
                {
                    ps.Runspace = _validationRunspace;
                    moduleInfo = ps.AddCommand("Import-Module").AddParameter("Name", moduleName).AddParameter("Force", true).AddParameter("PassThru", true).Invoke<PSModuleInfo>().FirstOrDefault();
                    _validationRunspace.ResetRunspaceState();
                }
            }
            catch (Exception e)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                errorRecord = GetErrorRecord(
                    "InvalidModuleOrSchema", 
                    e, 
                    ErrorCategory.InvalidOperation, 
                    PSinfrastructureStrings.InvalidModuleFileOrMOF, moduleName, schemaFileName);
                return MiResult.NOT_FOUND;
            }

            if (moduleInfo == null)
            {
                errorRecord = GetErrorRecord(
                    "CannotLoadModuleFileForValidation",
                    null,
                    ErrorCategory.InvalidOperation,
                    PSinfrastructureStrings.MissingModuleFileForValidation, moduleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                return MiResult.NO_SUCH_PROPERTY;
            }

            // Validate schema.
            var resourceClass = newCimClasses.FirstOrDefault(
                        cimClass => cimClass.CimSuperClassName != null &&
                        string.Compare(cimClass.CimSuperClassName, BaseResourceClass, StringComparison.OrdinalIgnoreCase) == 0);
            if (resourceClass == null)
            {
                errorRecord = GetErrorRecord(
                    "InvalidModuleMissingSchemaClass",
                    null,
                    ErrorCategory.InvalidOperation,
                    PSinfrastructureStrings.InvalidModuleMissingSchemaClass, moduleName, schemaFileName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                return MiResult.NOT_FOUND;
            }

            // Validate required exported commands.
            CommandInfo exportedCommand;
            if (!moduleInfo.ExportedCommands.TryGetValue(PsDscCmdletGet, out exportedCommand))
            {
                errorRecord = GetErrorRecord(
                   "InvalidModuleMissingCommand",
                   null,
                   ErrorCategory.InvalidOperation,
                   PSinfrastructureStrings.InvalidModuleMissingCommand, moduleName, PsDscCmdletGet);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                return MiResult.NO_SUCH_PROPERTY;
            }
            if (!moduleInfo.ExportedCommands.TryGetValue(PsDscCmdletSet, out exportedCommand))
            {
                errorRecord = GetErrorRecord(
                   "InvalidModuleMissingCommand",
                   null,
                   ErrorCategory.InvalidOperation,
                   PSinfrastructureStrings.InvalidModuleMissingCommand, moduleName, PsDscCmdletSet);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                return MiResult.NO_SUCH_PROPERTY;
            }
            if (!moduleInfo.ExportedCommands.TryGetValue(PsDscCmdletTest, out exportedCommand))
            {
                errorRecord = GetErrorRecord(
                   "InvalidModuleMissingCommand",
                   null,
                   ErrorCategory.InvalidOperation,
                   PSinfrastructureStrings.InvalidModuleMissingCommand, moduleName, PsDscCmdletTest);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleValidationFailure;
                return MiResult.NO_SUCH_PROPERTY;
            }

            // Validate required exported command parameters.
            return ValidateExportedCommandParameters(resourceClass, moduleInfo, out getActionStatusCode, out errorRecord);
        }

        private static MiResult ValidateExportedCommandParameters(
            CimClass resourceClass,
            PSModuleInfo moduleInfo,
            out UInt32 getActionStatusCode,
            out ErrorRecord errorRecord)
        {
            // Get key and write parameter data from MOF schema.
            List<CimPropertyDeclaration> keyProperties;
            List<CimPropertyDeclaration> writeProperties;
            List<CimPropertyDeclaration> requiredProperties;
            Utility.GetKeyWriteRequiredProperties(resourceClass, out keyProperties, out writeProperties, out requiredProperties);

            // Validate Get command against key parameters.
            string moduleName = moduleInfo.Name;
            CommandInfo cmdInfo = moduleInfo.ExportedCommands[PsDscCmdletGet];
            MiResult result = ValidateCommandParameters(cmdInfo, keyProperties, moduleName, out getActionStatusCode, out errorRecord);
            if (result != MiResult.OK) { return result; }

            // Validate Set command against key and write parameters.
            cmdInfo = moduleInfo.ExportedCommands[PsDscCmdletSet];
            result = ValidateCommandParameters(cmdInfo, keyProperties, moduleName, out getActionStatusCode, out errorRecord);
            if (result != MiResult.OK) { return result; }
            result = ValidateCommandParameters(cmdInfo, writeProperties, moduleName, out getActionStatusCode, out errorRecord);
            if (result != MiResult.OK) { return result; }

            // Validate Test command against key and write parameters.
            cmdInfo = moduleInfo.ExportedCommands[PsDscCmdletTest];
            result = ValidateCommandParameters(cmdInfo, keyProperties, moduleName, out getActionStatusCode, out errorRecord);
            if (result != MiResult.OK) { return result; }
            return ValidateCommandParameters(cmdInfo, writeProperties, moduleName, out getActionStatusCode, out errorRecord);
        }

        private static MiResult ValidateCommandParameters(
            CommandInfo cmdInfo,
            List<CimPropertyDeclaration> keyOrWriteProperties,
            string moduleName,
            out UInt32 getActionStatusCode,
            out ErrorRecord errorRecord)
        {
            errorRecord = null;

            foreach (var currentKeyOrWriteProperty in keyOrWriteProperties)
            {
                if (!cmdInfo.Parameters.ContainsKey(currentKeyOrWriteProperty.Name))
                {
                    errorRecord = GetErrorRecord(
                        "KeyParameterNotImplemented",
                        null,
                        ErrorCategory.InvalidOperation,
                        PSinfrastructureStrings.MismatchedPsModuleCommandParameterWithSchema, moduleName, cmdInfo.Name, currentKeyOrWriteProperty.Name);
                        getActionStatusCode = (uint) GetActionStatusCodeTypes.ModuleValidationFailure;
                    return MiResult.INVALID_PARAMETER;
                }
            }

            getActionStatusCode = (uint) GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        private static MiResult ValidateModuleWithChecksum(string moduleFileName, string checksumFileName,
                                                        out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            errorRecord = null;
            // Read mof file content and get the checksum.
            byte[] moduleContent;
            byte[] checkSumContent;
            try
            {
                using (var fs = File.OpenRead(moduleFileName))
                {
                    moduleContent = new byte[fs.Length];
                    fs.Read(moduleContent, 0, Convert.ToInt32(fs.Length));
                    fs.Close();
                }
                using (var fs = File.OpenRead(checksumFileName))
                {
                    checkSumContent = new byte[fs.Length];
                    fs.Read(checkSumContent, 0, Convert.ToInt32(fs.Length));
                    fs.Close();
                }
            }
            catch (Exception exception)
            {
                errorRecord = GetErrorRecord("ModuleFileInvalid", exception, ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.ModuleFileInvalid, moduleFileName, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidModuleFile;
                return MiResult.FAILED;
            }
            //Compute checksum of mof file.
            var sha = new SHA256Managed();
            byte[] computedHash = sha.ComputeHash(moduleContent);
            var hashStringFromMof = BitConverter.ToString(computedHash).Replace("-", "");
            var hashStringFromChecksum = System.Text.Encoding.Default.GetString(checkSumContent);
            if (string.Compare(hashStringFromMof, hashStringFromChecksum, StringComparison.OrdinalIgnoreCase) != 0)
            {
                errorRecord = GetErrorRecord("ChecksumValidationModuleFailed", ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.ChecksumValidationModuleFailed, moduleFileName, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleChecksumValidationFailure;
                return MiResult.FAILED;
            }

            getActionStatusCode = (int) GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }
        
        private static MiResult ValidateMofWithChecksum(string mofFileName, string checksumFileName,
                                                        out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            errorRecord = null;
            // Read mof file content and get the checksum.
            byte[] mofContent;
            byte[] checkSumContent;
            try
            {
                using (var fs = File.OpenRead(mofFileName))
                {
                    mofContent = new byte[fs.Length];
                    fs.Read(mofContent, 0, Convert.ToInt32(fs.Length));
                    fs.Close();
                }
                using (var fs = File.OpenRead(checksumFileName))
                {
                    checkSumContent = new byte[fs.Length];
                    fs.Read(checkSumContent, 0, Convert.ToInt32(fs.Length));
                    fs.Close();
                }
            }
            catch (Exception exception)
            {
                errorRecord = GetErrorRecord("ConfigurationFileInvalid", exception, ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.ConfigurationFileInvalid, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ConfigurationChecksumFileReadFailure;
                return MiResult.FAILED;
            }
            //Compute checksum of mof file.
            var sha = new SHA256Managed();
            byte[] computedHash = sha.ComputeHash(mofContent);
            var hashStringFromMof = BitConverter.ToString(computedHash).Replace("-", "");
            var hashStringFromChecksum = System.Text.Encoding.Default.GetString(checkSumContent);
            if (string.Compare(hashStringFromMof, hashStringFromChecksum, StringComparison.OrdinalIgnoreCase) != 0)
            {
                errorRecord = GetErrorRecord("ChecksumValidationConfigurationFailed", ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.ChecksumValidationConfigurationFailed, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.ConfigurationChecksumValidationFailure;
                return MiResult.FAILED;
            }

            getActionStatusCode = (int) GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        private static MiResult ValidateConfigurationChecksum(string downloadLocation,
                                                              out string mofFileName, out ErrorRecord errorRecord,
                                                              out UInt32 getActionStatusCode)
        {
            mofFileName = null;
            // DownloadLocation contain .mof file and .mof.checksum file.
            // We will fail if both the files are not available.
            string mofFileLocation = null;
            try
            {
                string[] mofFiles = Directory.GetFiles(downloadLocation, "*.mof");
                if (mofFiles.Length == 0)
                {
                    errorRecord = GetErrorRecord("ConfigurationFileNotExist", ErrorCategory.InvalidResult,
                                                                            PSinfrastructureStrings.ConfigurationFileNotExist, _pluginModuleName);
                    getActionStatusCode = (int) GetActionStatusCodeTypes.ConfigurationFileNotFound;
                    return MiResult.NOT_FOUND;
                }
                if (mofFiles.Length > 1)
                {
                    errorRecord = GetErrorRecord("ConfigurationFileMultipleExist", ErrorCategory.InvalidResult,
                                                                            PSinfrastructureStrings.ConfigurationFileMultipleExist, _pluginModuleName);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.MultipleConfigurationFilesFound;
                    return MiResult.FAILED;
                }
                mofFileLocation = mofFiles[0];
                //get the checksum now.
                if (!File.Exists(mofFiles[0] + ".checksum"))
                {
                    errorRecord = GetErrorRecord("ConfigurationChecksumFileNotExist", ErrorCategory.InvalidResult,
                                                                            PSinfrastructureStrings.ConfigurationChecksumFileNotExist, _pluginModuleName, mofFileLocation);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.ConfigurationChecksumFileNotFound;
                    return MiResult.NOT_FOUND;
                }
                //compute checksum
                MiResult statusCode = ValidateMofWithChecksum(mofFileLocation, mofFiles[0] + ".checksum", out errorRecord, out getActionStatusCode);
                S_DscCoreR.EventWriteLCMPullConfigurationChecksumValidationResult(S_DscCoreR.JobGuidString, mofFileLocation, (uint)statusCode);
                if (statusCode != MiResult.OK)
                {
                    return statusCode;
                }
            }
            catch (Exception ex)
            {
                errorRecord = GetErrorRecord("ConfigurationFileGenericFailure", ex, ErrorCategory.InvalidResult,
                                                                    PSinfrastructureStrings.ConfigurationFileGenericFailure, _pluginModuleName);
                getActionStatusCode = (int) GetActionStatusCodeTypes.ConfigurationChecksumValidationFailure;
                return MiResult.FAILED;
            }
            mofFileName = mofFileLocation;
            return MiResult.OK;
        }

        private static MiResult InstallModules(IntPtr metaConfigHandle, string downloadLocation, string mofFileName, bool allowModuleOverwrite, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            // Get module Names with Version and required resource names
            var moduleNameVersionTable = new Dictionary<string, Tuple<string, List<string>>>();
            MiResult statusCode = GetModuleNameVersionTable(mofFileName, moduleNameVersionTable, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                return statusCode;
            }
            if (moduleNameVersionTable.Count == 0)
            {
                S_DscCoreR.EventWriteLCMPullModuleSkippedAsAllModulesAreAvailable(S_DscCoreR.JobGuidString, mofFileName);
                return MiResult.OK;
            }

            string configurationId;
            // This holds the download manager specific properties - ServerUrl, SourcePath, etc. 
            Hashtable arguments;
            // We use this collection to hold the PSObjects that we create from arguments. We pass this down to the download manager cmdlets (The parameters have ValueFromPipelineByPropertyName specified) 
            Collection<PSObject> argumentParameters;
            
            ModuleSpecification[] moduleSpecifications;

            using (System.Management.Automation.PowerShell powershell = System.Management.Automation.PowerShell.Create(InitialSessionState.CreateDefault2()))
            {
                PSCommand powershellCommand;
                statusCode = DoInitializationForGetModule(metaConfigHandle, moduleNameVersionTable, downloadLocation,
                                                          out configurationId, out moduleSpecifications, powershell, 
                                                          out powershellCommand, out arguments, out argumentParameters,
                                                          out errorRecord, out getActionStatusCode);

                if (statusCode != MiResult.OK)
                {
                    return statusCode;
                }


                for (int i = 0; i < moduleNameVersionTable.Count; i++)
                {
                    string downloadedModule;
                    Collection<PSObject> pullOneModuleResult;
                    powershell.Commands.Clear();
                    powershell.Commands = powershellCommand;
                    powershell.Streams.Error.Clear();
                    statusCode = PullOneModule(powershell, moduleSpecifications[i], configurationId, downloadLocation,
                                               arguments, argumentParameters, out downloadedModule,
                                               out pullOneModuleResult, out errorRecord, out getActionStatusCode);
                    if (statusCode != MiResult.OK)
                    {
                        return statusCode;
                    }

                    // This validation is maybe not necessary.
                    // This validation checks if the module that we got from the Pull Server is what we asked for
                    // This used to make sense when we were downloading a bunch of modules. 
                    // TODO : Remove this
                    statusCode = ValidateForExpectedModule(powershell, pullOneModuleResult, moduleNameVersionTable,
                                                           out errorRecord, out getActionStatusCode);
                    if (statusCode != MiResult.OK)
                    {
                        return statusCode;
                    }

                    var moduleSpecification = moduleSpecifications[i];
                    statusCode = ValidateAndInstallOneModule(downloadLocation, moduleSpecification, 
                                                  moduleNameVersionTable[moduleSpecification.Name].Item2, allowModuleOverwrite,
                                                  out errorRecord, out getActionStatusCode);
                    if (statusCode != (UInt32)MiResult.OK)
                    {
                        return statusCode;
                    }
                }
            }

            // Log to ETW Channel:Microsoft-Windows-DSC/Operational
            S_DscCoreR.EventWriteLCMPullGetModuleSuccess(S_DscCoreR.JobGuidString, _pluginModuleName);
            return MiResult.OK;
        }

        // Does the initialization for Get-DscModule. This initialization needs to only happen once for all the modules.  
        // As part of this initialization, the following is done
        // 1) Download manager is imported
        // 2) Configuration is parsed to get the list of modules and the download-manager specific properties
        // 3) For the download manager specific properties, we create PSObjects so we can pass those down to the download manager cmdlets.
        // 4) We construct a PowerShell that has all the parameters added (except for the Module parameter. This parameter gets added for each module)
        private static MiResult DoInitializationForGetModule(IntPtr metaConfigHandle, Dictionary<string, Tuple<string, List<string>>> moduleNameVersionTable, 
                                                            string downloadLocation, out string configurationId, out ModuleSpecification[] moduleSpecifications,
                                                            System.Management.Automation.PowerShell powershell, out PSCommand powershellCommand, out Hashtable arguments, out Collection<PSObject> argumentParameters,
                                                            out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            configurationId = null;
            powershellCommand = null;
            moduleSpecifications = null;
            argumentParameters = null;
            arguments = new Hashtable();
            // Initialize DownloadManager
            MiResult statusCode = InitializePlugin(metaConfigHandle, out errorRecord);
            if (statusCode != MiResult.OK)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.DownloadManagerInitializationFailure;
                return statusCode;
            }

            //Get parameters for Get-Module cmdlet
            PSCredential pscredential;
            statusCode = GetGetModuleParams(metaConfigHandle, out pscredential, arguments, out configurationId, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                return statusCode;
            }

            moduleSpecifications = GetModuleSpecification(moduleNameVersionTable);

            powershell.Runspace = _pluginRunspace;
            if (arguments.Count > 0)
            {
                argumentParameters = powershell.AddCommand("New-Object").AddParameter("Type", "psobject").AddParameter("Property", arguments).Invoke();
                powershell.Commands.Clear();
            }
            powershellCommand = new PSCommand();
            powershellCommand.AddCommand(_pluginModuleName + "\\" + DownloadManagerGetModules);
            powershellCommand.AddParameter(ParamConfigurationId, configurationId);
            powershellCommand.AddParameter(ParamDestinationPath, downloadLocation);
            if (pscredential != null)
            {
                powershellCommand.AddParameter(ParamCredential, pscredential);
            }

            return MiResult.OK;
        }

        // Powershell object passed here will be disposed off by the caller
        private static MiResult PullOneModule(System.Management.Automation.PowerShell powershell, ModuleSpecification moduleSpecification, string configurationId, string downloadLocation,
                                              Hashtable arguments, Collection<PSObject> argumentParameters, out string downloadedModule, out Collection<PSObject> pullOneModuleResult,
                                              out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            pullOneModuleResult = null;
            downloadedModule = null;
            string moduleVersionString = GetModuleVersionStringFromModuleSpecification(moduleSpecification);
            try
            {
                powershell.AddParameter(ParamModules, moduleSpecification);

                // Log to ETW Channel:Microsoft-Windows-DSC/Operational
                S_DscCoreR.EventWriteLCMPullGetModuleAttempt(S_DscCoreR.JobGuidString, _pluginModuleName, configurationId, moduleVersionString);

                powershell.Streams.Error.Clear();
                pullOneModuleResult = arguments.Count > 0 ? powershell.Invoke(argumentParameters) : powershell.Invoke();
                if (powershell.Streams.Error.Count > 0)
                {
                    errorRecord = powershell.Streams.Error[0];
                    powershell.Dispose();
                    if( string.Compare(errorRecord.FullyQualifiedErrorId, "WebDownloadManagerUnknownChecksumAlgorithm", StringComparison.OrdinalIgnoreCase) == 0 )
                    {
                        getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidChecksumAlgorithm;
                    }
                    else
                    {
                        getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                    }
                    return MiResult.FAILED;
                }
            }
            catch (Exception ex)
            {
                errorRecord = GetErrorRecord("GetModuleExecutionFailure", ex, ErrorCategory.InvalidType,
                                                    PSinfrastructureStrings.GetModuleExecutionFailure, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                return MiResult.FAILED;
            }
            S_DscCoreR.EventWriteLCMPullModuleDownloadLocation(S_DscCoreR.JobGuidString, moduleVersionString, downloadLocation);
            errorRecord = null;
            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        // Validates that the module we have is the module we asked for from the Pull Server
        // This validation is maybe not necessary.
        // This used to make sense when we were downloading a bunch of modules. 
        // TODO : Remove this
        private static MiResult ValidateForExpectedModule(System.Management.Automation.PowerShell powershell, Collection<PSObject> pullOneModuleResult, 
                                                  Dictionary<string, Tuple<string, List<string>>> moduleNameVersionTable,
                                                  out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            ModuleSpecification[] pullOneModuleInternalResult;
            HandleNonTerminatingErrors(powershell, _pluginModuleName, DownloadManagerGetConfiguration, out errorRecord);
            if (errorRecord != null)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                return MiResult.FAILED;
            }

            if (pullOneModuleResult == null || pullOneModuleResult.Count == 0)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                errorRecord = GetErrorRecord("GetModuleResultNotExpected", ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetModuleResultCountUnexpected, _pluginModuleName);
                return MiResult.NOT_FOUND;
            }
            try
            {
                pullOneModuleInternalResult = LanguagePrimitives.ConvertTo<ModuleSpecification[]>(pullOneModuleResult);
            }
            catch (PSInvalidCastException ex)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleInvalidOutput;
                errorRecord = GetErrorRecord("GetModuleResultNotExpected", ex, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetModuleResultCountUnexpected, _pluginModuleName);
                return MiResult.NOT_FOUND;
            }

            // We are always downloading only one module at at a time
            if (pullOneModuleInternalResult == null || pullOneModuleInternalResult.Count() > 1)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleInvalidOutput;
                errorRecord = GetErrorRecord("GetModuleResultNotExpected", ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetModuleResultCountUnexpected, _pluginModuleName);
                return MiResult.NOT_FOUND;
            }

            if (!moduleNameVersionTable.ContainsKey(pullOneModuleInternalResult[0].Name))
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleInvalidOutput;
                errorRecord = GetErrorRecord("GetModuleResultNotExpected", ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetModuleResultCountUnexpected, _pluginModuleName);
                return MiResult.NO_SUCH_PROPERTY;
            }
            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        // Installs one module
        // This includes the following steps
        // 1. Unzip the file
        // 2. Validate checksum
        // 3. Validate that the module is a proper DSC module
        // 4. Install the module
        private static MiResult ValidateAndInstallOneModule(string downloadLocation, ModuleSpecification moduleSpecification, 
                                                            IEnumerable<string> requiredResources,
                                                            bool allowModuleOverwrite, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            Debug.Assert(((requiredResources != null) && requiredResources.Any()), "requiredResources can not be null and should contain one or more required resources");
            // DownloadLocation contain .zip file 
            try
            {
                string zipFileToSearchFor;
                if (moduleSpecification.Version == null)
                {
                    zipFileToSearchFor = moduleSpecification.Name + ".zip";
                }
                else
                {
                    zipFileToSearchFor = moduleSpecification.Name + "_" + moduleSpecification.Version + ".zip";
                }
                var zipFiles = Directory.GetFiles(downloadLocation, zipFileToSearchFor);
                if (zipFiles.Length < 1)
                {
                    errorRecord = GetErrorRecord("DownloadedModulesNotFound", ErrorCategory.InvalidResult,
                                                                            PSinfrastructureStrings.DownloadedModulesNotFound, _pluginModuleName);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleNotFound;
                    return MiResult.NOT_FOUND;
                }
                var dirPath = GetPsProgramFilesModulePath();
                var moduleName = String.Empty;
                var zipFilePath = String.Empty;
                string moduleToMatch;
                if (moduleSpecification.Version != null && !string.IsNullOrEmpty(moduleSpecification.Version.ToString()))
                {
                    moduleToMatch = string.Format(CultureInfo.InvariantCulture, "{0}_{1}.zip", moduleSpecification.Name, moduleSpecification.Version);
                }
                else
                {
                    moduleToMatch = string.Format(CultureInfo.InvariantCulture, "{0}.zip", moduleSpecification.Name);
                }

                string zipFile = zipFiles[0];
                //extract it in $pshome.
                var localPath = zipFile.Substring(zipFile.LastIndexOf('\\') + 1);
                if (string.Compare(localPath, moduleToMatch, StringComparison.OrdinalIgnoreCase) != 0)
                {
                    getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                    errorRecord = GetErrorRecord("DownloadedModulesNotFound", ErrorCategory.InvalidResult,
                                                                                PSinfrastructureStrings.DownloadedModulesNotFound, _pluginModuleName);
                    return MiResult.NOT_FOUND;
                }

                moduleName = moduleSpecification.Name;
                zipFilePath = zipFile;

                if (string.IsNullOrEmpty(moduleName))
                {
                    getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscModuleCommandFailure;
                    errorRecord = GetErrorRecord("DownloadedModulesNotFound", ErrorCategory.InvalidResult,
                                                                                PSinfrastructureStrings.DownloadedModulesNotFound, _pluginModuleName);
                    return MiResult.NOT_FOUND;
                }

                if (!File.Exists(zipFilePath + ".checksum"))
                {
                    getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleChecksumFileNotFound;
                    errorRecord = GetErrorRecord("ModuleChecksumFileNotExist", ErrorCategory.InvalidResult,
                                                                                PSinfrastructureStrings.ModuleChecksumFileNotExist, _pluginModuleName, zipFilePath);
                    return MiResult.NOT_FOUND;
                }

                //compute checksum
                var statusCode = ValidateModuleWithChecksum(zipFilePath, zipFilePath + ".checksum", out errorRecord, out getActionStatusCode);
                S_DscCoreR.EventWriteLCMPullModuleChecksumValidationResult(S_DscCoreR.JobGuidString, moduleName, (uint)statusCode);
                if (statusCode != MiResult.OK)
                {
                    return statusCode;
                }
                var modulePath = dirPath + moduleName;
                if (Directory.Exists(modulePath) && allowModuleOverwrite == false)
                {
                    S_DscCoreR.EventWriteLCMPullModuleDirectoryAlreadyExists(S_DscCoreR.JobGuidString, moduleName, modulePath);
                    errorRecord = GetErrorRecord("ModuleDirectoryAlreadyExists", ErrorCategory.ResourceExists,
                                                        PSinfrastructureStrings.ModuleDirectoryAlreadyExists, moduleName, modulePath);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleExtractionFailure;
                    statusCode = MiResult.FAILED;
                    return statusCode;
                }
                if (Directory.Exists(modulePath) && allowModuleOverwrite)
                {
                    S_DscCoreR.EventWriteLCMPullModuleDirectoryOverwrite(S_DscCoreR.JobGuidString, moduleName, GetModuleVersionStringFromModuleSpecification(moduleSpecification));
                    Directory.Move(modulePath, modulePath + "_tmp");
                }
                Directory.CreateDirectory(modulePath);

                //Validate if module is a valid module. 
                //It is expected that we will get a valid module from the server
                //hence optimizing for that.

                try
                {
                    using (var archive = ZipFile.OpenRead(zipFilePath))
                    {
                        // Zip file can be in two format. 
                        // 1) zip was created at root level and zip content starts with Module folder
                        // 2) zip was created inside the module and top level directly contain the file. It may contain
                        // sub directories and one of them could be same as module name. hence we need to first determine
                        // whether it is type(1) or type(2).
                        var bZipTypeRoot = archive.Entries.All(entry => entry.FullName.StartsWith(moduleName, StringComparison.OrdinalIgnoreCase));
                        foreach (var entry in archive.Entries)
                        {
                            string fullPath = Path.Combine(bZipTypeRoot ? dirPath : modulePath, entry.FullName);
                            var dirTempIndex = fullPath.LastIndexOf('/');

                            // This is a directory so we'll create it if necessary.
                            if (dirTempIndex == fullPath.Length - 1) // file is a directory.
                            {
                                if (!Directory.Exists(fullPath))
                                {
                                    Directory.CreateDirectory(fullPath);
                                }
                            }
                            else
                            {
                                entry.ExtractToFile(fullPath, true);
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    Directory.Delete(modulePath, true);
                    errorRecord = GetErrorRecord("ModuleExtractionFailed", ex, ErrorCategory.InvalidResult,
                                                 PSinfrastructureStrings.ModuleExtractionFailed, zipFilePath, _pluginModuleName);
                    getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleExtractionFailure;
                    return MiResult.FAILED;
                }
                finally
                {
                    // The modulePath would have been deleted if there had been any exception. 
                    // In that case, restore the old module if any
                    if (!Directory.Exists(modulePath) && Directory.Exists(modulePath + "_tmp"))
                    {
                        Directory.Move(modulePath + "_tmp", modulePath);
                    }
                    // In case of no exception , delete the tmp path
                    else if (Directory.Exists(modulePath + "_tmp"))
                    {
                        Directory.Delete(modulePath + "_tmp");
                    }
                }

                var allResourcesAreValid = MiResult.OK;
                if ((requiredResources != null) && requiredResources.Any())
                {
                    foreach (var resourceName in requiredResources)
                    {
                        //Validate the module
                        var resourceModulePath = Path.Combine(Path.Combine(modulePath, Constants.DscResources), resourceName);
                        var schemaFileName = Path.Combine(resourceModulePath, resourceName + Constants.CimSchemaMofFileExtension);
                        var result = ValidatePsdscModule(resourceModulePath, schemaFileName, out getActionStatusCode, out errorRecord);

                        if (result != MiResult.OK)
                        {
                            allResourcesAreValid = result;
                            break;
                        }
                    }
                }

                S_DscCoreR.EventWriteLCMPullModuleContentValidationResult(S_DscCoreR.JobGuidString, moduleName, (uint)allResourcesAreValid);

                if (allResourcesAreValid == MiResult.OK)
                {
                    try
                    {
                        if (Directory.Exists(modulePath + "_tmp"))
                            Directory.Delete(modulePath + "_tmp", true);
                    }
                    catch (IOException) { }
                    catch (UnauthorizedAccessException) { }
                    catch (ArgumentException) { }

                    S_DscCoreR.EventWriteLCMPullModuleInstallLocation(S_DscCoreR.JobGuidString, moduleName, modulePath);
                }
                else
                {
                    try
                    {
                        Directory.Delete(modulePath, true);
                    }
                    catch (IOException) { }
                    catch (UnauthorizedAccessException) { }
                    catch (ArgumentException) { }

                    //Move back old module if any
                    if (Directory.Exists(modulePath + "_tmp"))
                    {
                        Directory.Move(modulePath + "_tmp", modulePath);
                    }

                    if (errorRecord == null)
                    {
                        errorRecord = GetErrorRecord("DownloadedModuleInvalid", ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.DownloadedModuleInvalid, zipFilePath,
                                                        _pluginModuleName);
                    }
                    getActionStatusCode = (int) GetActionStatusCodeTypes.InvalidDownloadedModule;
                    return MiResult.FAILED;
                }
            }
            catch (Exception ex)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.ModuleExtractionFailure;
                errorRecord = GetErrorRecord("ModuleExtractionGenericFailure", ex, ErrorCategory.InvalidResult,
                                                                PSinfrastructureStrings.ModuleExtractionGenericFailure, _pluginModuleName);
                return MiResult.FAILED;
            }

            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        #endregion PLUGIN_GETMODULE
        #region PLUGIN_COMMONHELPERS

        private static string GetModuleVersionStringFromModuleSpecification(ModuleSpecification moduleSpecification)
        {
            StringBuilder result = new StringBuilder();
            result.Append("(").Append(moduleSpecification.Name);
            if (moduleSpecification.Version != null)
            {
                result.Append(",").Append(moduleSpecification.Version).Append(")");
            }
            else
            {
                result.Append(")");
            }

            return result.ToString();
        }

        internal static ErrorRecord GetErrorRecord(string errorId, ErrorCategory errorCategory, string errorResourceId, params object[] errorResourceIdParams)
        {
            return Utility.CreateErrorRecord(errorId, errorCategory, null, errorResourceId, errorResourceIdParams);
        }

        internal static ErrorRecord GetErrorRecord(string errorId, Exception exception, ErrorCategory errorCategory, string errorResourceId, params object[] errorResourceIdParams)
        {
            return Utility.CreateErrorRecord(errorId, errorCategory, exception, errorResourceId, errorResourceIdParams);
        }

        // ReSharper disable UnusedMember.Local
        private static string GetPsProgramFilesModulePath()
        // ReSharper restore UnusedMember.Local
        {
            //return @"c:\Program Files\Microsoft\Windows\Powershell\Modules\";
            return Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles) + @"\WindowsPowerShell\Modules\";
        }

        private static void HandleNonTerminatingErrors(System.Management.Automation.PowerShell powerShell,
                                                                    string providerName,
                                                                    string operationCmd,
                                                                    out ErrorRecord errorRecord)
        {
            errorRecord = null;
            if (powerShell != null &&
                powerShell.Streams != null &&
                powerShell.Streams.Error != null &&
                powerShell.Streams.Error.Count > 0 &&
                !string.IsNullOrEmpty(providerName) &&
                !string.IsNullOrEmpty(operationCmd))
            {
                string errorMessage = string.Format(
                    CultureInfo.CurrentCulture,
                    PSinfrastructureStrings.NonTerminatingErrorFromProvider,
                    providerName,
                    operationCmd);

                InvalidOperationException invalidOperationException;

                // If there is only one non-terminting error then the surface it's inner execetion (if it exists) to the commandline.
                if (powerShell.Streams.Error.Count == 1 && powerShell.Streams.Error[0].Exception != null)
                {
                    invalidOperationException = new InvalidOperationException(errorMessage, powerShell.Streams.Error[0].Exception);
                }
                else
                {
                    invalidOperationException = new InvalidOperationException(errorMessage);
                }

                errorRecord = new ErrorRecord(
                   invalidOperationException,
                   "NonTerminatingErrorFromProvider",
                   ErrorCategory.InvalidOperation,
                   null);
            }
        }

        private static string GetSystemUuid()
        {
            var cimSession = CimSession.Create("localhost");
            var cimInstance = cimSession.EnumerateInstances(@"root/cimv2", "Win32_ComputerSystemProduct").First();
            if (cimInstance.CimInstanceProperties["UUID"] != null)
            {
                return cimInstance.CimInstanceProperties["UUID"].Value.ToString();
            }
            return String.Empty;
        }

        private static MiResult GetAllowModuleOverwriteFromMetaConfig(IntPtr metaConfigHandle, out Boolean allowModuleOverwrite, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            errorRecord = null;
            allowModuleOverwrite = false;
            var metaConfigInstance = new CimInstance(new InstanceHandle(metaConfigHandle, false), null);
            if (metaConfigInstance.CimInstanceProperties[MetaConfigAllowModuleOverwrite] != null &&
                    metaConfigInstance.CimInstanceProperties[MetaConfigAllowModuleOverwrite].Value != null)
            {
                LanguagePrimitives.TryConvertTo(metaConfigInstance.CimInstanceProperties[MetaConfigAllowModuleOverwrite].Value, out allowModuleOverwrite);
            }
            getActionStatusCode = (int)GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        private static MiResult GetMetaConfigParams(IntPtr metaConfigHandle, out PSCredential pscredential, Hashtable arguments, out string configurationId, out ErrorRecord errorRecord, out UInt32 getActionStatusCode)
        {
            configurationId = null;
            errorRecord = null;
            pscredential = null;
            var metaConfigInstance = new CimInstance(new InstanceHandle(metaConfigHandle, false), null);

            // Get ConfigurationID.
            try
            {
                if (metaConfigInstance.CimInstanceProperties[MetaConfigConfigurationId] != null &&
                    metaConfigInstance.CimInstanceProperties[MetaConfigConfigurationId].Value != null)
                {
                    string tempConfigurationId = metaConfigInstance.CimInstanceProperties[MetaConfigConfigurationId].Value.ToString();
                    /* We will use System UUID only if user has explicitly asked for.*/
                    if (string.Compare(tempConfigurationId, UseSystemUUIDValue, StringComparison.OrdinalIgnoreCase) == 0)
                    {
                        tempConfigurationId = GetSystemUuid();

                    }
                    Guid throwAwayGuid = Guid.Empty;
                    if (Guid.TryParse(tempConfigurationId, out throwAwayGuid))
                    {
                        configurationId = tempConfigurationId;
                    }
                    else
                    {
                        getActionStatusCode = (int) GetActionStatusCodeTypes.InvalidConfigurationIdFormat;
                        errorRecord = GetErrorRecord("InvalidConfigurationIdFormat", null, ErrorCategory.InvalidArgument, PSinfrastructureStrings.InvalidConfigurationIdFormat, tempConfigurationId);
                        return MiResult.INVALID_PARAMETER;
                    }
                }
                else
                {
                    getActionStatusCode = (int) GetActionStatusCodeTypes.InvalidConfigurationIdFormat;
                    errorRecord = GetErrorRecord("ConfigurationIdNotSpecified", null, ErrorCategory.InvalidArgument, PSinfrastructureStrings.ConfigurationIdNotSpecified);
                    return MiResult.INVALID_PARAMETER;                        
                }
            }
            catch (CimException exception)
            {
                errorRecord = GetErrorRecord("MetaConfigConfigurationIdInvalid", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.MetaConfigConfigurationIdInvalid,
                                                    _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidConfigurationIdInMetaConfig;
                return (MiResult)exception.StatusCode;
            }

            //Get PS Credential
            if (metaConfigInstance.CimInstanceProperties[ParamCredential] != null &&
                metaConfigInstance.CimInstanceProperties[ParamCredential].Value != null)
            {
                string userName = null;
                string password = null;
                string domain = null;
                var cimCredentialInstance = metaConfigInstance.CimInstanceProperties[ParamCredential].Value as CimInstance;
                if (cimCredentialInstance != null)
                {
                    if (cimCredentialInstance.CimInstanceProperties[ParamCredentialUserName] != null &&
                        cimCredentialInstance.CimInstanceProperties[ParamCredentialUserName].Value != null)
                    {
                        userName = cimCredentialInstance.CimInstanceProperties[ParamCredentialUserName].Value.ToString();
                    }
                    if (cimCredentialInstance.CimInstanceProperties[ParamCredentialPassword] != null &&
                        cimCredentialInstance.CimInstanceProperties[ParamCredentialPassword].Value != null)
                    {
                        password = cimCredentialInstance.CimInstanceProperties[ParamCredentialPassword].Value.ToString();
                    }
                    if (cimCredentialInstance.CimInstanceProperties[ParamCredentialDomain] != null &&
                        cimCredentialInstance.CimInstanceProperties[ParamCredentialDomain].Value != null)
                    {
                        domain = cimCredentialInstance.CimInstanceProperties[ParamCredentialDomain].Value.ToString();
                    }
                    if (userName != null &&
                        password != null)
                    {
                        // Extract the password into a SecureString.
                        var securePassword = new SecureString();
                        foreach (var t in password)
                        {
                            securePassword.AppendChar(t);
                        }
                        securePassword.MakeReadOnly();

                        if (!string.IsNullOrEmpty(domain))
                        {
                            userName = Path.Combine(domain, userName);
                        }

                        pscredential = new PSCredential(userName, securePassword);
                    }
                }
            }

            // Get cmdlet arguments as hashtable.
            try
            {
                if (metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerCustomData] != null &&
                    metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerCustomData].Value != null)
                {
                    var cimInstances = metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerCustomData].Value as CimInstance[];
                    if (cimInstances != null)
                    {
                        foreach (var inst in cimInstances)
                        {
                            arguments.Add(inst.CimInstanceProperties["Key"].Value.ToString(), inst.CimInstanceProperties["Value"].Value.ToString());
                        }
                    }


                }
            }
            catch (CimException exception)
            {
                errorRecord = GetErrorRecord("MetaConfigCustomDataInvalid", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.MetaConfigCustomDataInvalid,
                                                    _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidDownloadManagerCustomDataInMetaConfig;
                return (MiResult)exception.StatusCode;
            }

            getActionStatusCode = (int) GetActionStatusCodeTypes.Success;
            return MiResult.OK;
        }

        private static MiResult InitializePlugin(IntPtr metaConfigHandle, out ErrorRecord errorRecord)
        {
            errorRecord = null;
            if (PluginRunspaceInitialized == false)
            {
                MiResult statusCode = ImportDownloadManager(metaConfigHandle, out errorRecord);
                if (statusCode != MiResult.OK)
                {
                    return statusCode;
                }
            }
            return MiResult.OK;
        }

        private static MiResult ImportDownloadManager(IntPtr metaConfigHandle, out ErrorRecord errorRecord)
        {
            string downloadManagerName;
            // Get Module Name
            MiResult statusCode = GetDownloadManagerModuleName(metaConfigHandle, out downloadManagerName, out errorRecord);
            if (statusCode != MiResult.OK)
            {
                return statusCode;
            }

            // if it is webDownloadManager, it is implemented inside PSDesiredStateConfiguration\WebDownloadManager.
            // if it is FileDownloadManager, it is implemented inside PSDesiredStateConfiguration\DownloadManager\DSCFileDownloadManager.
            string downloadManagerPath = GetDownloadManagerModuleLoadPath(downloadManagerName);

            try
            {
                using (System.Management.Automation.PowerShell powershell = System.Management.Automation.PowerShell.Create())
                {
                    powershell.Runspace = _pluginRunspace;
                    // Load the module
                    powershell.Streams.Error.Clear();
                    powershell.AddCommand("Import-Module")
                                  .AddParameter("Name", downloadManagerPath)
                                  .AddParameter("PassThru", true)
                                  .Invoke<PSModuleInfo>()
                                  .FirstOrDefault();
                    if (powershell.Streams.Error.Count > 0)
                    {
                        errorRecord = GetErrorRecord("ImportDownloadManagerException", powershell.Streams.Error[0].Exception, ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.ImportDownloadManagerException, _pluginModuleName);
                        return MiResult.FAILED;
                    }
                }
            }
            catch (Exception exception)
            {
                errorRecord = GetErrorRecord("ImportDownloadManagerException", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.ImportDownloadManagerException, _pluginModuleName);
                return MiResult.FAILED;
            }
            if (statusCode != MiResult.OK)
            {
                return statusCode;
            }
            _pluginModuleName = downloadManagerName;
            return MiResult.OK;

        }

        private static string GetDownloadManagerModuleLoadPath(string downloadManagerName)
        {
            string downloadManagerLoadPath;
            if (!DownloadManagerMap.TryGetValue(downloadManagerName, out downloadManagerLoadPath))
            {
                downloadManagerLoadPath = downloadManagerName;
            }
            return downloadManagerLoadPath;
        }

        private static MiResult GetDownloadManagerModuleName(IntPtr metaConfigHandle, out string downloadManagerName,
                                                            out ErrorRecord errorRecord)
        {
            downloadManagerName = null;
            errorRecord = null;
            var metaConfigInstance = new CimInstance(new InstanceHandle(metaConfigHandle, false), null);
            try
            {
                if (metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerName] != null &&
                    metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerName].Value != null)
                {
                    downloadManagerName = metaConfigInstance.CimInstanceProperties[MetaConfigDownloadManagerName].Value.ToString();
                }
                else
                {
                    errorRecord = GetErrorRecord("MetaConfigDownloadManagerInvalid", ErrorCategory.InvalidResult,
                                                        PSinfrastructureStrings.MetaConfigDownloadManagerInvalid);
                    return MiResult.NOT_FOUND;
                }
            }
            catch (CimException exception)
            {
                errorRecord = GetErrorRecord("MetaConfigDownloadManagerInvalid", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.MetaConfigDownloadManagerInvalid);
                return (MiResult)exception.StatusCode;
            }
            return MiResult.OK;
        }
        #endregion PLUGIN_COMMONHELPERS
        #region PLUGIN_PUBLICMETHODS

        /// <summary>
        /// Install API used to install the modules as necessary from the mof file.. 
        /// </summary>
        /// <param name="metaConfigHandle"></param>
        /// <param name="downloadLocation"></param>
        /// <param name="mofFileName"></param>
        /// <param name="allowModuleOverwrite"></param>
        /// <param name="errorInstanceHandle"></param>
        /// <param name="getActionStatusCode"></param>
        /// <returns>If InstallModules operation is successful, 0 is returned or else a status code indicating the error is returned.</returns>        

        public static UInt32 GetDscModule(IntPtr metaConfigHandle, string downloadLocation, string mofFileName, bool allowModuleOverwrite, out IntPtr errorInstanceHandle, out UInt32 getActionStatusCode)   
        {
            ErrorRecord errorRecord;
            errorInstanceHandle = IntPtr.Zero;
            MiResult statusCode =  InstallModules(metaConfigHandle, downloadLocation, mofFileName, allowModuleOverwrite, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;                
            }
            return (uint)MiResult.OK;
        }
        /// <summary>
        /// Get Api facilitates to execute Get-Configuration functionality on the provider mentioned in the meta configuration.. 
        /// </summary>
        /// <param name="metaConfigHandle"></param>
        /// <param name="fileHash"></param>
        /// <param name="complianceStatus"></param>
        /// <param name="lastGetActionStatusCode"></param>
        /// <param name="errorInstanceHandle"></param>
        /// <param name="outputResult"></param>
        /// <param name="getActionStatusCode"></param>
        /// <returns>If GetDscAction operation is successful, 0 is returned or else a status code indicating the error is returned.</returns>
        public static UInt32 GetDscAction(IntPtr metaConfigHandle, string fileHash, bool complianceStatus, UInt32 lastGetActionStatusCode, out IntPtr errorInstanceHandle, out string outputResult, out UInt32 getActionStatusCode)
        {
            ErrorRecord errorRecord;
            errorInstanceHandle = IntPtr.Zero;
            MiResult statusCode = InitializePlugin(metaConfigHandle, out errorRecord);
            outputResult = null;
            if (statusCode != MiResult.OK)
            {
                getActionStatusCode = (int) GetActionStatusCodeTypes.DownloadManagerInitializationFailure;
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            //Get parameters for Get-Status cmdlet
            PSCredential pscredential;
            var arguments = new Hashtable();
            string configurationId;
            statusCode = GetMetaConfigParams(metaConfigHandle, out pscredential, arguments, out configurationId, out errorRecord, out getActionStatusCode);
            if (getActionStatusCode != (uint)GetActionStatusCodeTypes.Success)
            {
                lastGetActionStatusCode = getActionStatusCode;
            }

            if (statusCode != MiResult.OK)
            {
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            System.Management.Automation.PowerShell powershell;
            Collection<PSObject> providerResult;
            //Create PowerShell object and invoke the command.
            try
            {
                powershell = System.Management.Automation.PowerShell.Create();
                powershell.Runspace = _pluginRunspace;
                Collection<PSObject> argumentParameters = null;
                if (arguments.Count > 0)
                {
                    argumentParameters = powershell.AddCommand("New-Object").AddParameter("Type", "psobject").AddParameter("Property", arguments).Invoke();
                    powershell.Commands.Clear();
                }
                powershell.Commands.AddCommand(_pluginModuleName + "\\" + DownloadManagerGetAction);
                powershell.AddParameter(ParamConfigurationId, configurationId);
                powershell.AddParameter(ParamNotCompliant, !complianceStatus);
                powershell.AddParameter(ParamFileHash, fileHash);
                powershell.AddParameter(ParamStatusCode, lastGetActionStatusCode);
                if (pscredential != null)
                {
                    powershell.AddParameter(ParamCredential, pscredential);
                }
                // Log to ETW Channel:Microsoft-Windows-DSC/Operational
                S_DscCoreR.EventWriteLCMPullGetActionAttempt(S_DscCoreR.JobGuidString,
                    _pluginModuleName, configurationId, fileHash, complianceStatus);

                powershell.Streams.Error.Clear();
                providerResult = arguments.Count > 0 ? powershell.Invoke(argumentParameters) : powershell.Invoke();
                if (powershell.Streams.Error.Count > 0)
                {
                    errorRecord = powershell.Streams.Error[0];
                    errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)MiResult.FAILED, errorRecord);
                    powershell.Dispose();
                    getActionStatusCode = (int) GetActionStatusCodeTypes.GetDscActionCommandFailure;
                    return (UInt32)MiResult.FAILED;
                }
            }
            catch (Exception exception)
            {
                errorRecord = GetErrorRecord("GetActionException", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetActionException, _pluginModuleName);
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)MiResult.FAILED, errorRecord);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetDscActionCommandFailure;
                return (UInt32)MiResult.FAILED;
            }
            statusCode = ValidateGetActionResult(powershell, providerResult, _pluginModuleName, out outputResult, out errorRecord, out getActionStatusCode);
            powershell.Dispose();
            if (statusCode != MiResult.OK)
            {
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }
            // Log to ETW Channel:Microsoft-Windows-DSC/Operational
            S_DscCoreR.EventWriteLCMPullGetActionSuccess(S_DscCoreR.JobGuidString,
                outputResult,
                _pluginModuleName);
            return (uint)MiResult.OK;
        }

        /// <summary>
        /// Get Api facilitates to execute Get-Configuration functionality on the provider mentioned in the meta configuration.. 
        /// </summary>
        /// <param name="metaConfigHandle"></param>
        /// <param name="errorInstanceHandle"></param>
        /// <param name="mofFileName"></param>
        /// <param name="outputResult"></param>
        /// <param name="getActionStatusCode"></param>
        /// <returns>If GetDscDocument operation is successful, 0 is returned or else a status code indicating the error is returned.</returns>
        public static UInt32 GetDscDocument(IntPtr metaConfigHandle, out IntPtr errorInstanceHandle, out string mofFileName, out string outputResult, out UInt32 getActionStatusCode)
        {
            ErrorRecord errorRecord;
            errorInstanceHandle = IntPtr.Zero;
            string destinationPath = Path.GetTempPath() + "\\" + DateTime.Now.Ticks;
            MiResult statusCode = InitializePlugin(metaConfigHandle, out errorRecord);
            outputResult = null;
            mofFileName = null;
            if (statusCode != MiResult.OK)
            {
                getActionStatusCode = (int)GetActionStatusCodeTypes.DownloadManagerInitializationFailure;
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }
            if (Directory.Exists(destinationPath))
            {
                errorRecord = GetErrorRecord("DownloadLocationDirectoryExists", ErrorCategory.InvalidResult,
                                                                    PSinfrastructureStrings.DownloadLocationDirectoryExists);
                getActionStatusCode = (int)GetActionStatusCodeTypes.DownloadManagerInitializationFailure;
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((UInt32)MiResult.ALREADY_EXISTS, errorRecord);
                return (uint)MiResult.ALREADY_EXISTS;
            }
            Directory.CreateDirectory(destinationPath);

            //Get parameters for Get-Configuration cmdlet
            PSCredential pscredential;
            var arguments = new Hashtable(StringComparer.OrdinalIgnoreCase);
            string configurationId;
            statusCode = GetMetaConfigParams(metaConfigHandle, out pscredential, arguments, out configurationId, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            bool allowModuleOverwrite;
            statusCode = GetAllowModuleOverwriteFromMetaConfig(metaConfigHandle, out allowModuleOverwrite, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            System.Management.Automation.PowerShell powershell;
            Collection<PSObject> providerResult;
            //Create PowerShell object and invoke the command.
            try
            {
                powershell = System.Management.Automation.PowerShell.Create();
                powershell.Runspace = _pluginRunspace;
                Collection<PSObject> argumentParameters = null;
                if (arguments.Count > 0)
                {
                    argumentParameters = powershell.AddCommand("New-Object").AddParameter("Type", "psobject").AddParameter("Property", arguments).Invoke();
                    powershell.Commands.Clear();
                }
                powershell.Commands.AddCommand(_pluginModuleName + "\\" + DownloadManagerGetConfiguration);
                powershell.AddParameter(ParamConfigurationId, configurationId);
                powershell.AddParameter(ParamDestinationPath, destinationPath);
                if (pscredential != null)
                {
                    powershell.AddParameter(ParamCredential, pscredential);
                }
                // Log to ETW Channel:Microsoft-Windows-DSC/Operational
                S_DscCoreR.EventWriteLCMPullGetConfigAttempt(S_DscCoreR.JobGuidString,
                    _pluginModuleName, configurationId);

                powershell.Streams.Error.Clear();
                providerResult = arguments.Count > 0 ? powershell.Invoke(argumentParameters) : powershell.Invoke();
                if (powershell.Streams.Error.Count > 0)
                {
                    Directory.Delete(destinationPath, true);
                    errorRecord = powershell.Streams.Error[0];
                    errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)MiResult.FAILED, errorRecord);
                    powershell.Dispose();
                    if( string.Compare(errorRecord.FullyQualifiedErrorId, "WebDownloadManagerUnknownChecksumAlgorithm", StringComparison.OrdinalIgnoreCase) == 0 )
                    {
                        getActionStatusCode = (int)GetActionStatusCodeTypes.InvalidChecksumAlgorithm;
                    }
                    else
                    {
                        getActionStatusCode = (int)GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                    }
                    return (uint)MiResult.FAILED;
                }
            }
            catch (Exception exception)
            {
                Directory.Delete(destinationPath, true);
                errorRecord = GetErrorRecord("GetConfigurationException", exception, ErrorCategory.InvalidResult,
                                                    PSinfrastructureStrings.GetConfigurationException, _pluginModuleName);
                getActionStatusCode = (int)GetActionStatusCodeTypes.GetConfigurationCommandFailure;
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)MiResult.FAILED, errorRecord);
                return (uint)MiResult.FAILED;
            }
            statusCode = ValidateGetConfigurationResult(powershell, providerResult, _pluginModuleName, out outputResult, out errorRecord, out getActionStatusCode);
            S_DscCoreR.EventWriteLCMPullConfigurationChecksumValidationResult(S_DscCoreR.JobGuidString, configurationId, (uint)statusCode);
            powershell.Dispose();
            if (statusCode != MiResult.OK)
            {
                Directory.Delete(destinationPath, true);
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            // if it is ok, we will validate checksum here.
            if (string.Compare(outputResult, StatusOk, StringComparison.OrdinalIgnoreCase) == 0)
            {
                statusCode = ValidateConfigurationChecksum(destinationPath, out mofFileName, out errorRecord, out getActionStatusCode);
            }
            if (statusCode != MiResult.OK)
            {
                Directory.Delete(destinationPath, true);
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            // If checksum validation passes, we go on to pull the module
            statusCode = InstallModules(metaConfigHandle, destinationPath, mofFileName, allowModuleOverwrite, out errorRecord, out getActionStatusCode);
            if (statusCode != MiResult.OK)
            {
                Directory.Delete(destinationPath, true);
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)statusCode, errorRecord);
                return (uint)statusCode;
            }

            // Log to ETW Channel:Microsoft-Windows-DSC/Operational
            S_DscCoreR.EventWriteLCMPullGetConfigSuccess(S_DscCoreR.JobGuidString,
                _pluginModuleName);
            return (uint)MiResult.OK;
        }

        /// <summary>
        /// This API installs a private certificate (.pfx). 
        /// </summary>
        /// <param name="certificatePath"></param>
        /// <param name="password"></param>
        /// <param name="certificateThumbprint"></param>
        /// <param name="errorInstanceHandle"></param>
        /// <returns>If successfully installed return 0 and certificateThumbprint or else a status code indicating the error is returned.</returns>
        public static uint InstallCertificate(string certificatePath, SecureString password,
                                                   out string certificateThumbprint, out IntPtr errorInstanceHandle)
        {
            certificateThumbprint = null;
            errorInstanceHandle = IntPtr.Zero;
            X509Store store = null;
            try
            {
                var cert = new X509Certificate2(certificatePath, password);
                // open certificate store
                store = new X509Store(StoreName.My, StoreLocation.LocalMachine);
                store.Open(OpenFlags.ReadWrite);
                // install certificate.
                if (!store.Certificates.Contains(cert))
                {
                    store.Add(cert);
                }
                certificateThumbprint = cert.Thumbprint;
            }
            catch (Exception ex)
            {
                var errorRecord = GetErrorRecord("InstallCertificateException", ex, ErrorCategory.InvalidType,
                                                         PSinfrastructureStrings.InstallCertificateException, certificatePath);
                errorInstanceHandle = Utility.ConvertErrorRecordToMiInstance((uint)MiResult.FAILED, errorRecord);
                return (uint)MiResult.FAILED;
            }
            finally
            {
                if (store != null)
                {
                    store.Close();
                }
            }
            return (uint)MiResult.OK;
        }

        #endregion PLUGIN_PUBLICMETHODS
    }
}


