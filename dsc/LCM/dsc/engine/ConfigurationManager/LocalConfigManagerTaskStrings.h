/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _LOCALCONFIGMANAGERTASKSTRINGS_H_

#define LocalConfigManagerTaskXMLFormatString\
    L"<?xml version=\"1.0\" encoding=\"UTF-16\"?>"\
    L"<Task version=\"1.2\" xmlns=\"http://schemas.microsoft.com/windows/2004/02/mit/task\">"\
    L"  <RegistrationInfo>"\
    L"    <Author>SYSTEM</Author>"\
    L"  </RegistrationInfo>"\
    L"  <Triggers>"\
    L"    <TimeTrigger>"\
    L"      <Repetition>"\
    L"        <Interval>PT%dS</Interval>"\
    L"        <StopAtDurationEnd>false</StopAtDurationEnd>"\
    L"      </Repetition>"\
    L"      <StartBoundary>%s</StartBoundary>"\
    L"      <RandomDelay>PT5M</RandomDelay>"\
    L"      <Enabled>true</Enabled>"\
    L"    </TimeTrigger>"\
    L"  </Triggers>"\
    L"  <Settings>"\
    L"    <MultipleInstancesPolicy>IgnoreNew</MultipleInstancesPolicy>"\
    L"    <DisallowStartIfOnBatteries>true</DisallowStartIfOnBatteries>"\
    L"    <StopIfGoingOnBatteries>true</StopIfGoingOnBatteries>"\
    L"    <AllowHardTerminate>true</AllowHardTerminate>"\
    L"    <StartWhenAvailable>false</StartWhenAvailable>"\
    L"    <RunOnlyIfNetworkAvailable>false</RunOnlyIfNetworkAvailable>"\
    L"    <IdleSettings>"\
    L"      <Duration>PT10M</Duration>"\
    L"      <WaitTimeout>PT1H</WaitTimeout>"\
    L"      <StopOnIdleEnd>true</StopOnIdleEnd>"\
    L"      <RestartOnIdle>false</RestartOnIdle>"\
    L"    </IdleSettings>"\
    L"    <AllowStartOnDemand>true</AllowStartOnDemand>"\
    L"    <Enabled>true</Enabled>"\
    L"    <Hidden>false</Hidden>"\
    L"    <RunOnlyIfIdle>false</RunOnlyIfIdle>"\
    L"    <WakeToRun>false</WakeToRun>"\
    L"    <ExecutionTimeLimit>PT72H</ExecutionTimeLimit>"\
    L"    <Priority>7</Priority>"\
    L"  </Settings>"\
    L"  <Actions Context=\"Author\">"\
    L"    <Exec>"\
    L"      <Command>PowerShell.exe</Command>"\
    L"      <Arguments>-NonInt -Window Hidden -Command &quot;Invoke-CimMethod -Namespace root/Microsoft/Windows/DesiredStateConfiguration"\
                L" -Cl MSFT_DSCLocalConfigurationManager -Method PerformRequiredConfigurationChecks -Arguments @{Flags = [System.UInt32]%d}&quot;</Arguments>"\
    L"    </Exec>"\
    L"  </Actions>"\
    L"</Task>"

#define LocalConfigManagerTaskXMLConsistencyStringEnd LocalConfigManagerTaskXMLFormatStringMiddle2 L"2" LocalConfigManagerTaskXMLFormatStringEnd
#define LocalConfigManagerTaskXMLPullServerEnd LocalConfigManagerTaskXMLFormatStringMiddle2  L"3" LocalConfigManagerTaskXMLFormatStringEnd

#define LocalConfigManagerTaskCommandBase L" /Create /RU System /F /XML %s /TN "
#define LocalConfigManagerTaskCommandDoubleQuote L"\""
#define LocalConfigManagerTaskConsistencyCommand LocalConfigManagerTaskCommandBase LocalConfigManagerTaskCommandDoubleQuote CONSISTENCY_TASKSCHEDULE_NAME LocalConfigManagerTaskCommandDoubleQuote

#endif //_LOCALCONFIGMANAGERTASKSTRINGS_H_
