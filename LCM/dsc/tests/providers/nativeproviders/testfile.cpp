/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26018 28301 26006) //this is unit test code don't worry about the warnings.
#endif /* _PREFAST_ */



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <MSFT_FileDirectoryConfiguration.h>
#include <nativeProvider.traps.h>
#include "testfile.h"
#include "TestHelper.cpp"
#include "..\..\common\NitsPriority.h"

using namespace std;

wstring contents = L"1";

#pragma region instances for get operation
MSFT_FileDirectoryConfiguration normalfile = {0};
MSFT_FileDirectoryConfiguration normalDirectory = {0};

MSFT_FileDirectoryConfiguration destinationPathNotExist = {0};
MSFT_FileDirectoryConfiguration invalidEnsure = {0};
MSFT_FileDirectoryConfiguration noDestinationPath = {0};
MSFT_FileDirectoryConfiguration invalidWildCardInDest = {0};
MSFT_FileDirectoryConfiguration destPathRelative = {0};
#pragma endregion instances for get operation

#pragma region instances for test operation
#pragma region ensure=present&file

MSFT_FileDirectoryConfiguration noSourceJustDestFilewithbom = {0};
MSFT_FileDirectoryConfiguration contentAndDestFilewithbom = {0};
MSFT_FileDirectoryConfiguration contentAndDestFilewithoutbom = {0};
MSFT_FileDirectoryConfiguration sourceFileAndDestFilewithbom = {0};
MSFT_FileDirectoryConfiguration sourceFileAndDestDirWithSameFileWithBom = {0};
MSFT_FileDirectoryConfiguration invalidSourceFileWithoutChecksum = {0};


MSFT_FileDirectoryConfiguration AttributesNotMatch= {0};
MSFT_FileDirectoryConfiguration ContentNotMatch = {0};
MSFT_FileDirectoryConfiguration SourceFileNotMatch = {0};


MSFT_FileDirectoryConfiguration sourceFileAndNotExistDestFile = {0};
MSFT_FileDirectoryConfiguration contentAndNotExistDestFile = {0};
MSFT_FileDirectoryConfiguration noSourceAndNotExistDestFile = {0};

MSFT_FileDirectoryConfiguration invalidSourceFileWithSha1Checksum = {0};

MSFT_FileDirectoryConfiguration sourcePathAndContents = {0};
MSFT_FileDirectoryConfiguration invalidChecksumNoSource = {0};
#pragma endregion ensure=present&file

#pragma region ensure=dir and recurse= false
MSFT_FileDirectoryConfiguration sourceDirAndDestDir = {0};
MSFT_FileDirectoryConfiguration sourceDirAndNotExistDest = {0};
MSFT_FileDirectoryConfiguration sourceDirAndDestFile = {0};
MSFT_FileDirectoryConfiguration sourceContent = {0};
MSFT_FileDirectoryConfiguration sourceFileWithoutChecksum = {0};
MSFT_FileDirectoryConfiguration sourceFileWithSha1Checksum = {0};
#pragma endregion ensure=dir

#pragma region ensure=dir and recurse= true
MSFT_FileDirectoryConfiguration RDestdirIdentical = {0};
MSFT_FileDirectoryConfiguration RDestdirMissingFile = {0};
MSFT_FileDirectoryConfiguration RDestdirMoreFile = {0};
MSFT_FileDirectoryConfiguration RDestdirMissingSubdir = {0};
MSFT_FileDirectoryConfiguration RDestdirMoreSubdir = {0};
MSFT_FileDirectoryConfiguration RDestdirFileContentMismatch = {0};
MSFT_FileDirectoryConfiguration RDestDirsubFileAttributeMismatch = {0};
MSFT_FileDirectoryConfiguration RDestDirSubdirAttributeMismatch = {0};
MSFT_FileDirectoryConfiguration RDestDirExpectSubdirButFile = {0};
MSFT_FileDirectoryConfiguration RDestDirExpectFileButSubDir = {0};
#pragma endregion ensure=dir

#pragma region ensure=absent
MSFT_FileDirectoryConfiguration DestDir = {0};
MSFT_FileDirectoryConfiguration DestFile = {0};
MSFT_FileDirectoryConfiguration NotExistDest = {0};
MSFT_FileDirectoryConfiguration DestDirNotEmptyForceTrue = {0};
MSFT_FileDirectoryConfiguration DestDirNotEmptyForceFALSE = {0};
#pragma endregion ensure=absent

#pragma endregion instances for test operation

#pragma region instances for set operation
#pragma region ensure=present&file
MSFT_FileDirectoryConfiguration ContentNotMatchForSet = {0};
MSFT_FileDirectoryConfiguration AttributesNotMatchForSet= {0};
MSFT_FileDirectoryConfiguration SourceFileNotMatchForSet = {0};
MSFT_FileDirectoryConfiguration ContentNotMatchForSetEmptyFile = {0};

MSFT_FileDirectoryConfiguration contentAndNotExistDestFileForSet = {0};
MSFT_FileDirectoryConfiguration sourceFileAndNotExistDestFileForSet = {0};
MSFT_FileDirectoryConfiguration DestDirEnsureFileContentForce = {0};
MSFT_FileDirectoryConfiguration DestFileParentNotExistContent= {0};
#pragma endregion ensure=present&file

#pragma region ensure=dir
MSFT_FileDirectoryConfiguration sourceDirAndDestDirForSet = {0};
MSFT_FileDirectoryConfiguration sourceDirAndNotExistDestForSet = {0};
MSFT_FileDirectoryConfiguration DestFileEnsureDirForce = {0};
MSFT_FileDirectoryConfiguration DestDirParentNotExistForSet= {0};
MSFT_FileDirectoryConfiguration RDestdirForSet= {0};
#pragma endregion ensure=dir

#pragma region ensure=absent
MSFT_FileDirectoryConfiguration DestDirForSet = {0};
MSFT_FileDirectoryConfiguration DestFileForSet = {0};
#pragma endregion ensure=absent


#pragma region invalid
MSFT_FileDirectoryConfiguration DestDirEnsureFileNoSource = {0};
MSFT_FileDirectoryConfiguration DestWildcardEnsureFileNosouce = {0};
MSFT_FileDirectoryConfiguration DestDirEnsureFileContent = {0};
MSFT_FileDirectoryConfiguration DestWildcardEnsureFileContent = {0};
MSFT_FileDirectoryConfiguration SourceProblematic = {0};
MSFT_FileDirectoryConfiguration SourceWildCard = {0};
MSFT_FileDirectoryConfiguration NoSourcePathCheckSumModifiedDate = {0};
#pragma endregion


#pragma endregion instances for set operation

#pragma region instances for credential
MSFT_FileDirectoryConfiguration SingleFileRemoteSourceNotMatchLocalUser = {0};
MSFT_FileDirectoryConfiguration MultipleFileRemoteSourceNotMatchLocalUser = {0};
MSFT_FileDirectoryConfiguration CredentialIsSpecifiedButNoPassword = {0};
MSFT_FileDirectoryConfiguration CredentialIsSpecifiedButNoUserName = {0};
MSFT_FileDirectoryConfiguration LocalSource = {0};
MSFT_FileDirectoryConfiguration NotExistSource = {0};
MSFT_FileDirectoryConfiguration WrongPassword = {0};

MSFT_Credential credential = {0};
MSFT_Credential noPasswordCredential = {0};
MSFT_Credential noUserNameCredential = {0};
MSFT_Credential wrongPasswordCredential = {0};

#pragma endregion

#pragma region instances for recursive get
MSFT_FileDirectoryConfiguration localDirectory = {0};
MSFT_FileDirectoryConfiguration localDirectoryWithBackSlash = {0};
MSFT_FileDirectoryConfiguration sharedDirectory = {0};
MSFT_FileDirectoryConfiguration normalfileWithRecurse = {0};
MSFT_FileDirectoryConfiguration networkShare = {0};
MSFT_FileDirectoryConfiguration rootDir = {0};
#pragma endregion


MI_InstanceFT fakeFT;
wstring singleDestFileFullPath;
wstring singleDestDirFullPath;
wstring destdirname;
wstring destdirnameWithBackSlash;
wstring netShareDirName;

struct Ptr
{
    void *ptr;
};

Ptr PtrVal = {NULL};
//test operation: test utf8, test stream, test content
#pragma region Get
NitsSetup0(SingleFileDirTestOfGetOperation, Ptr)
    //CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestGetOperationSetup.ps1");
        FileUnitTestGetOperationSetup();
    NitsTrapHandle h = NitsOpenTrap("DSCCoreConfProv.dll", NativeProviderTraps);
        NitsAssert(h != NULL, L"Failed to load NativeProviderTraps!");
        NitsContext()->_Ptr->ptr = h;

    InitializeInputInstancesOfGetOperation();
NitsEndSetup


NitsCleanup(SingleFileDirTestOfGetOperation)
    //CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCleanup.ps1");
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

NitsTestSetTimeout(ValidSingleDirAndFileOfGetOperation, 9000)
NitsDRTTest1(ValidSingleDirAndFileOfGetOperation, SingleFileDirTestOfGetOperation, PtrVal)
    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfGetOperation->_Ptr->ptr;

    ValidationOfGetOperation(normalfile, true, true, h);
    ValidationOfGetOperation(normalDirectory, false, true, h);
    SingleNoneExistDestinationGetOperation(destinationPathNotExist, h);
NitsEndTest

NitsTestSetTimeout(InValidInputOfGetOperation, 9000)
NitsDRTTest1(InValidInputOfGetOperation, SingleFileDirTestOfGetOperation, PtrVal)

    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfGetOperation->_Ptr->ptr;
    InValidObjOfGetOperation(invalidEnsure, MI_RESULT_INVALID_PARAMETER, h);
    InValidObjOfGetOperation(noDestinationPath, MI_RESULT_INVALID_PARAMETER, h);
    InValidObjOfGetOperation(invalidWildCardInDest, MI_RESULT_INVALID_PARAMETER, h);
    InValidObjOfGetOperation(destPathRelative, MI_RESULT_INVALID_PARAMETER, h);
NitsEndTest
#pragma endregion Get

#pragma region TestCredentialSingleFile
NitsSetup0(SingleFileDirTestOfTestOperation, Ptr)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestTestOperationSetup.ps1");
        //FileUnitTestTestOperationSetup();
    NitsTrapHandle h = NitsOpenTrap("DSCCoreConfProv.dll", NativeProviderTraps);
        NitsAssert(h != NULL, L"Failed to load NativeProviderTraps!");
        NitsContext()->_Ptr->ptr = h;

    InitializeInputInstancesOfTestOperation();
    InitializeInputInstancesOfRecursiveTestOperation();
NitsEndSetup

NitsCleanup(SingleFileDirTestOfTestOperation)
    //don't clean up to save some unit test time
    //CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCleanup.ps1");
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup


//for ensure= file and present
NitsTestSetTimeout(SingleDirAndFileOfTestOperationPresentFile, 9000)
NitsDRTTest1(SingleDirAndFileOfTestOperationPresentFile, SingleFileDirTestOfTestOperation, PtrVal)
    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfTestOperation->_Ptr->ptr;
    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$true\"");
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$false\"");
        }
        SingleValidObjOfTestOperation(noSourceJustDestFilewithbom, true, h);

        SingleValidObjOfTestOperation(contentAndDestFilewithbom, true, h);
        //iterate through different checksum for this case, including modified date
        contentAndDestFilewithbom.Checksum.exists= true;
        contentAndDestFilewithbom.Checksum.value = L"sha-1";
        SingleValidObjOfTestOperation(contentAndDestFilewithbom, true, h);
        contentAndDestFilewithbom.Checksum.value = L"sha-256";
        SingleValidObjOfTestOperation(contentAndDestFilewithbom, true, h);
        contentAndDestFilewithbom.Checksum.value = L"sha-512";

        SingleValidObjOfTestOperation(contentAndDestFilewithoutbom, true, h);

        SingleValidObjOfTestOperation(sourceFileAndDestFilewithbom, true, h);

        MSFT_FileDirectoryConfiguration createddatechecksum= sourceFileAndDestFilewithbom;
        createddatechecksum.DestinationPath.value = createddatechecksum.SourcePath.value;
        SingleValidObjOfTestOperation(createddatechecksum, true, h);


                // Test For environment Variable in Path.
                MSFT_FileDirectoryConfiguration environmentVarInPath= sourceFileAndDestFilewithbom;
                environmentVarInPath.Ensure.exists = MI_TRUE;
                environmentVarInPath.Ensure.value = L"Present";
                environmentVarInPath.Type.exists = MI_TRUE;
                environmentVarInPath.Type.value = L"File";
                environmentVarInPath.Attributes.exists = MI_FALSE;
                environmentVarInPath.SourcePath.value = L"%windir%\\System32\\cmd.exe";
                environmentVarInPath.DestinationPath.value = L"%windir%\\System32\\cmd.exe";
                SingleValidObjOfTestOperation(environmentVarInPath, true, h);


        SingleValidObjOfTestOperation(sourceFileAndDestDirWithSameFileWithBom, true, h);
        SingleValidObjOfTestOperation(invalidSourceFileWithoutChecksum, true, h);

        SingleValidObjOfTestOperation(AttributesNotMatch, false, h);
        SingleValidObjOfTestOperation(ContentNotMatch, false, h);
        SingleValidObjOfTestOperation(SourceFileNotMatch, false, h);
        SingleValidObjOfTestOperation(sourceFileAndNotExistDestFile, false, h);
        SingleValidObjOfTestOperation(contentAndNotExistDestFile, false, h);
        SingleValidObjOfTestOperation(noSourceAndNotExistDestFile, false, h);

        SingleInValidObjOfTestOperation(invalidSourceFileWithSha1Checksum, MI_RESULT_INVALID_PARAMETER, h);
        SingleInValidObjOfTestOperation(sourcePathAndContents, MI_RESULT_INVALID_PARAMETER, h);
        SingleInValidObjOfTestOperation(invalidChecksumNoSource, MI_RESULT_INVALID_PARAMETER, h);
    }

    //iterate through different checksum for this case, including modified date
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$false\"");
    sourceFileAndDestFilewithbom.Checksum.exists= true;
    sourceFileAndDestFilewithbom.Checksum.value = L"sha-1";
    SingleValidObjOfTestOperation(sourceFileAndDestFilewithbom, true, h);
    sourceFileAndDestFilewithbom.Checksum.value = L"sha-256";
    SingleValidObjOfTestOperation(sourceFileAndDestFilewithbom, true, h);
    sourceFileAndDestFilewithbom.Checksum.value = L"sha-512";
    SingleValidObjOfTestOperation(sourceFileAndDestFilewithbom, true, h);
    sourceFileAndDestFilewithbom.Checksum.value = L"modifieddate";
    SingleValidObjOfTestOperation(sourceFileAndDestFilewithbom, true, h);
    sourceFileAndDestFilewithbom.Checksum.value = L"invalid";
    SingleInValidObjOfTestOperation(sourceFileAndDestFilewithbom, MI_RESULT_INVALID_PARAMETER, h);
    sourceFileAndDestFilewithbom.Checksum.value = L"none";

NitsEndTest

//for ensure=directory and recurse=true
NitsTestSetTimeout(TestOperationRecurseDirectory, 9000)
NitsDRTTest1(TestOperationRecurseDirectory, SingleFileDirTestOfTestOperation, PtrVal)
    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfTestOperation->_Ptr->ptr;
    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$true\"");
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$false\"");
        }
        SingleValidObjOfTestOperation(RDestdirIdentical, true, h);
        SingleValidObjOfTestOperation(RDestdirMissingFile, false, h);
        SingleValidObjOfTestOperation(RDestdirMoreFile, true, h);
        SingleValidObjOfTestOperation(RDestdirMissingSubdir, false, h);
        SingleValidObjOfTestOperation(RDestdirMoreSubdir, true, h);
        SingleValidObjOfTestOperation(RDestdirFileContentMismatch, false, h);
        SingleValidObjOfTestOperation(RDestDirsubFileAttributeMismatch, false, h);
        SingleValidObjOfTestOperation(RDestDirSubdirAttributeMismatch, false, h);
        SingleValidObjOfTestOperation(RDestDirExpectSubdirButFile, false, h);
        SingleValidObjOfTestOperation(RDestDirExpectFileButSubDir, false, h);
    }
NitsEndTest

//for ensure=directory and recurse = false
NitsTestSetTimeout(SingleDirAndFileOfTestOperationDirectory, 9000)
NitsDRTTest1(SingleDirAndFileOfTestOperationDirectory, SingleFileDirTestOfTestOperation, PtrVal)
    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfTestOperation->_Ptr->ptr;

    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$true\"");
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$false\"");
        }
        SingleValidObjOfTestOperation(sourceDirAndDestDir, true, h);
        SingleValidObjOfTestOperation(sourceDirAndNotExistDest, false, h);
        SingleValidObjOfTestOperation(sourceDirAndDestFile, false, h);
        SingleValidObjOfTestOperation(sourceFileWithoutChecksum, false, h);

        SingleInValidObjOfTestOperation(sourceContent, MI_RESULT_INVALID_PARAMETER, h);
        SingleInValidObjOfTestOperation(sourceFileWithSha1Checksum, MI_RESULT_INVALID_PARAMETER, h);
    }
NitsEndTest

//for ensure=absent
NitsTestSetTimeout(SingleDirAndFileOfTestOperationAbsent, 9000)
NitsDRTTest1(SingleDirAndFileOfTestOperationAbsent, SingleFileDirTestOfTestOperation, PtrVal)
    NitsTrapHandle h = NitsContext()->_SingleFileDirTestOfTestOperation->_Ptr->ptr;

    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$true\"");
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestTestOperationSetup.ps1 -keepcache:$false\"");
        }
        SingleValidObjOfTestOperation(DestDir, false, h);
        SingleValidObjOfTestOperation(DestFile, false, h);
        SingleValidObjOfTestOperation(NotExistDest, true, h);

                MSFT_FileDirectoryConfiguration TypeFileActualDir = DestDir;
                TypeFileActualDir.Ensure.exists = MI_TRUE;
                TypeFileActualDir.Ensure.value = L"absent";
                TypeFileActualDir.Type.exists = MI_TRUE;
                TypeFileActualDir.Type.value = L"File";
                SingleValidObjOfTestOperation(TypeFileActualDir, true, h);
        
                MSFT_FileDirectoryConfiguration TypeDirActualFile = DestFile;
                TypeDirActualFile.Ensure.exists = MI_TRUE;
                TypeDirActualFile.Ensure.value = L"absent";
                TypeDirActualFile.Type.exists = MI_TRUE;
                TypeDirActualFile.Type.value = L"Directory";
                SingleValidObjOfTestOperation(TypeDirActualFile, true, h);
    }
NitsEndTest
#pragma endregion Test

#pragma region Set
NitsSetup0(FileDirTestOfSetOperation, Ptr)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestSetOperationSetup.ps1");
        //FileUnitTestSetOperationSetup(false);
    NitsTrapHandle h = NitsOpenTrap("DSCCoreConfProv.dll", NativeProviderTraps);
        NitsAssert(h != NULL, L"Failed to load NativeProviderTraps!");
        NitsContext()->_Ptr->ptr = h;
    InitializeInputInstancesOfSetOperation();
NitsEndSetup

NitsCleanup(FileDirTestOfSetOperation)
    //CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCleanup.ps1");
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

NitsTestSetTimeout(SetOperation, 9000)
NitsDRTTest1(SetOperation, FileDirTestOfSetOperation, PtrVal)

NitsTrapHandle h = NitsContext()->_FileDirTestOfSetOperation->_Ptr->ptr;
#pragma region file and present
    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestSetOperationSetup.ps1 -keepcache:$true\"");
                        //FileUnitTestSetOperationSetup(true);
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestSetOperationSetup.ps1 -keepcache:$false\"");
                        //FileUnitTestSetOperationSetup(false);
        }
        
        ValidObjOfSetOperation(ContentNotMatchForSet, h);
        ValidObjOfSetOperation(AttributesNotMatchForSet, h);
        ValidObjOfSetOperation(SourceFileNotMatchForSet, h);
        ValidObjOfSetOperation(ContentNotMatchForSetEmptyFile, h);
        ValidObjOfSetOperation(contentAndNotExistDestFileForSet, h);
        ValidObjOfSetOperation(sourceFileAndNotExistDestFileForSet, h);
        ValidObjOfSetOperation(DestDirEnsureFileContentForce, h);
        ValidObjOfSetOperation(DestFileParentNotExistContent, h);

#pragma endregion file and present

#pragma region directory
        sourceDirAndDestDirForSet.Type.exists =MI_TRUE;
        ValidObjOfSetOperation(sourceDirAndDestDirForSet, h);

        //winblue:227549
        ValidObjOfSetOperation(sourceDirAndDestDirForSet, h);
        sourceDirAndDestDirForSet.Type.exists =MI_FALSE;

        ValidObjOfSetOperation(sourceDirAndNotExistDestForSet, h);
        ValidObjOfSetOperation(DestFileEnsureDirForce, h);
        ValidObjOfSetOperation(DestDirParentNotExistForSet, h);
        //the recursive set
        ValidObjOfSetOperation(RDestdirForSet, h);
#pragma endregion directory

#pragma region absent
        ValidObjOfSetOperation(DestDirForSet, h);
        ValidObjOfSetOperation(DestFileForSet, h);
        ValidObjOfSetOperation(DestDirNotEmptyForceTrue, h);

#pragma endregion absent
        CheckOutputOfSetOperation(i);

#pragma region invalid
        InValidObjOfSetOperation(DestDirEnsureFileNoSource, MI_RESULT_INVALID_PARAMETER, h);
        InValidObjOfSetOperation(DestWildcardEnsureFileNosouce, MI_RESULT_NOT_SUPPORTED, h);
        InValidObjOfSetOperation(DestDirEnsureFileContent, MI_RESULT_INVALID_PARAMETER, h);
        InValidObjOfSetOperation(DestWildcardEnsureFileContent, MI_RESULT_NOT_SUPPORTED, h);
        InValidObjOfSetOperation(SourceProblematic, MI_RESULT_INVALID_PARAMETER, h);
        InValidObjOfSetOperation(SourceWildCard, MI_RESULT_NOT_SUPPORTED, h);
        InValidObjOfSetOperation(NoSourcePathCheckSumModifiedDate, MI_RESULT_INVALID_PARAMETER, h);
        InValidObjOfSetOperation(DestDirNotEmptyForceFALSE, MI_RESULT_INVALID_PARAMETER, h);
    }
#pragma endregion
NitsEndTest
#pragma endregion Set

#pragma region Credential
NitsSetup0(CredentialOperation, Ptr)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCredentialSetup.ps1");
    NitsTrapHandle h = NitsOpenTrap("DSCCoreConfProv.dll", NativeProviderTraps);
        NitsAssert(h != NULL, L"Failed to load NativeProviderTraps!");
        NitsContext()->_Ptr->ptr = h;

    InitializeInputInstancesOfCredentialOperation();
NitsEndSetup


NitsCleanup(CredentialOperation)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCredentialCleanup.ps1");
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

//Credential test, only used for ensure = present, and sourcepath is specified
NitsTestSetTimeout(CredentialTest, 9000)
NitsIDXTest1(CredentialTest, CredentialOperation, PtrVal)
NitsTrapHandle h = NitsContext()->_CredentialOperation->_Ptr->ptr;
    //ValidObjOfSetOperation(SingleRemoteSourceFileNotMatchDomainUser, h);
    //create local user;create a dir and grant permission to that local user only; share the folder; 
    int runCount = 2;                  //run every test twice; the first time generate cache, the second time use cache
    for(int i = 0; i < runCount; i++)
    {
        //re-setup the files
        if(i == 1)
        {
            (L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestCredentialSetup.ps1 -keepcache:$true\"");
                        //FileUnitTestCredentialSetup();
        }
        else
        {
            CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command \".\\FileUnitTestCredentialSetup.ps1 -keepcache:$false\"");
                        //FileUnitTestCredentialSetup();
        }
        ValidObjOfSetOperation(SingleFileRemoteSourceNotMatchLocalUser, h);
        ValidObjOfSetOperation(MultipleFileRemoteSourceNotMatchLocalUser, h);
        MSFT_FileDirectoryConfiguration_Set_SourcePath(&MultipleFileRemoteSourceNotMatchLocalUser,  L"\\\\localhost\\credentialshare");
        ValidObjOfSetOperation(MultipleFileRemoteSourceNotMatchLocalUser, h);
        InValidObjOfSetOperation(CredentialIsSpecifiedButNoPassword, MI_RESULT_INVALID_PARAMETER, h);
        InValidObjOfSetOperation(CredentialIsSpecifiedButNoUserName, MI_RESULT_INVALID_PARAMETER, h);
        // commented out, since there is sanity check for share name. - InValidObjOfSetOperation(LocalSource, ERROR_BAD_NET_NAME, h);
        InValidObjOfSetOperation(NotExistSource, ERROR_BAD_NETPATH, h);
        InValidObjOfSetOperation(WrongPassword, ERROR_LOGON_FAILURE, h);
    }
NitsEndTest
#pragma endregion Credential

#pragma region Recursive
NitsSetup0(RecursiveGetOperation, Ptr)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestRecursiveGetOperationSetup.ps1");
    NitsTrapHandle h = NitsOpenTrap("DSCCoreConfProv.dll", NativeProviderTraps);
        NitsAssert(h != NULL, L"Failed to load NativeProviderTraps!");
        NitsContext()->_Ptr->ptr = h;

    InitializeInputInstancesOfRecursiveGetOperation();
NitsEndSetup

NitsCleanup(RecursiveGetOperation)
    //CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestCleanup.ps1");
    NitsTrapHandle h = NitsContext()->_Ptr->ptr;

    if (h != NULL)
        NitsCloseTrap(h);

NitsEndCleanup

NitsTestSetTimeout(RecursiveGetOperationTest, 9000)
NitsDRTTest1(RecursiveGetOperationTest, RecursiveGetOperation, PtrVal)

NitsTrapHandle h = NitsContext()->_RecursiveGetOperation->_Ptr->ptr;
    //get from a local folder
    //get from a local folder with trailing backslash
    //get from a network share folder
    //get from a file with recurse = true (should ignore that recurse)


    /*error cases
        get from a network share 
        get from a root directory(C:)
    */
    ValidationOfGetOperation(localDirectory, false, false, h);
    ValidationOfGetOperation(localDirectoryWithBackSlash, false, false, h);
    ValidationOfGetOperation(sharedDirectory, false, false, h);
    ValidationOfGetOperation(normalfileWithRecurse, true, true, h);

    InValidObjOfGetOperation(networkShare, ERROR_BAD_NET_NAME, h);
    InValidObjOfGetOperation(rootDir, MI_RESULT_INVALID_PARAMETER, h);
    rootDir.DestinationPath.value = L"C:";
    InValidObjOfGetOperation(rootDir, MI_RESULT_INVALID_PARAMETER, h);
NitsEndTest
#pragma endregion Recursive

//TODO: add credential test for recursive cases
//In that case should test dir with backslash and without backslash


#pragma region E2E
NitsTestSetTimeout(FileE2ETest, 9000)
NitsIDXTest(FileE2ETest)
    CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileE2E.ps1");
    CheckOutpuFile();
NitsEndTest

#pragma endregion

void CheckOutpuFile()
{
    bool notExist = false;
    wstring resultfile = FindFilePath(L"result.txt", notExist);
    NitsAssert(notExist, L"something is wrong in the Set operation");
    if(!notExist)
    {
        wifstream resultStream(resultfile, wifstream::in);
        while ( !resultStream.eof() )
        {
            int bufferSize = 64 * 1024;
            vector<WCHAR> buffer(bufferSize);
            resultStream.getline (buffer.data(),bufferSize);
            NitsAssert(false, buffer.data());
        }
        resultStream.close();
    }
}
void CheckOutputOfSetOperation(int i)
{
    if(i == 0)
        CreateProcessHelper(L"powershell.exe -executionpolicy unrestricted -command .\\FileUnitTestSetOperationVerify.ps1");
        else
        FileUnitTestSetOperationVerify();
    CheckOutpuFile();
}



void ValidObjOfSetOperation(MSFT_FileDirectoryConfiguration &input, NitsTrapHandle h)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);

    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_SetFileDirectoryObject)(&input, &application);
    NitsAssert(result == 0, L"error happens when test file!");
    NitsAssert(result == 0, input.DestinationPath.value);
}

void SingleValidObjOfTestOperation(MSFT_FileDirectoryConfiguration &input, bool shouldMatch, NitsTrapHandle h)
{
    bool isMatch;
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);

    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_TestFileDirectoryObject)(&input, &application, isMatch);
    NitsAssert(result == 0, L"error happens when test file!");
    NitsAssert(result == 0, input.DestinationPath.value);
    NitsAssert(isMatch == shouldMatch, L"result doesn't match when test file!");
    NitsAssert(isMatch == shouldMatch, input.DestinationPath.value);
}

void SingleInValidObjOfTestOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h)
{
    bool isMatch;
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);

    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_TestFileDirectoryObject)(&input, &application, isMatch);
    NitsAssert(result == errorCode, L"error doesn't match!");
    NitsAssert(result == errorCode, input.DestinationPath.value);
}

void InValidObjOfSetOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);

    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_SetFileDirectoryObject)(&input, &application);
    NitsAssert(result == errorCode, L"error doesn't match!");
    NitsAssert(result == errorCode, input.DestinationPath.value);
}

void ValidationOfGetObj(MSFT_FileDirectoryConfiguration &input, MI_Instance *outputInstance, bool file, bool single)
{
    //compare the destination path
    //compare the ensure
    //compare the attributes
    //compare the size
    //compare the time (20 seconds)
    MI_Value value;
    MI_Type type;

    MI_Result r  = MI_Instance_GetElement(outputInstance, L"DestinationPath", &value, &type, 0, NULL);
    NitsAssert(r == MI_RESULT_OK, L"DestinationPath doesn't match!");
    NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
    if(r != MI_RESULT_OK)
    {
        return;
    }
    if(wcsstr(value.string, input.DestinationPath.value) == NULL)
    {
        NitsAssert(true, L"DestinationPath doesn't match!");
        NitsAssert(true, value.string);
        return;
    }

    r  = MI_Instance_GetElement(outputInstance, L"Ensure", &value, &type, 0, NULL);
    NitsAssert(r == MI_RESULT_OK, L"ensure doesn't match!");
    NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
    if(r != MI_RESULT_OK)
    {
        return;
    }
    if((file && _wcsicmp(value.string,L"file") != 0 )|| (!file &&_wcsicmp(value.string,L"directory") != 0))
    {
        NitsAssert(true, L"ensure doesn't match!");
        NitsAssert(true, input.DestinationPath.value);
        return;
    }

//    NitsAssert(error.error_code == 0, L"error happens when get file!");
    r  = MI_Instance_GetElement(outputInstance, L"Attributes", &value, &type, 0, NULL);
    NitsAssert(r == MI_RESULT_OK, L"Attributes doesn't match!");
    NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
    if(r != MI_RESULT_OK)
    {
        return;
    }
    bool attributesFound = false;
    for(UINT32 i = 0; i< value.stringa.size; ++i)
    {
        if(_wcsicmp(value.stringa.data[i],L"readonly") == 0)
        {
            attributesFound = true;
        }
    }
    NitsAssert(attributesFound, L"attributes doesn't match!");
    NitsAssert(attributesFound, input.DestinationPath.value);

    r  = MI_Instance_GetElement(outputInstance, L"CreatedDate", &value, &type, 0, NULL);
    if(r != MI_RESULT_OK)
    {
        return;
    }
    NitsAssert(r == MI_RESULT_OK, L"created date  doesn't match!");
    NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
    MatchTime(&(value.datetime), 10);

    r  = MI_Instance_GetElement(outputInstance, L"ModifiedDate", &value, &type, 0, NULL);
    if(r != MI_RESULT_OK)
    {
        return;
    }
    NitsAssert(r == MI_RESULT_OK, L"modified date  doesn't match!");
    NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
    MatchTime(&(value.datetime), 10);

    if(file)
    {
        r  = MI_Instance_GetElement(outputInstance, L"Size", &value, &type, 0, NULL);
        if(r != MI_RESULT_OK)
        {
            return;
        }
        NitsAssert(r == MI_RESULT_OK, L"size doesn't match!");
        NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
        NitsAssert(value.uint64 == 8 , L"size doesn't match!");
        NitsAssert(value.uint64 == 8, input.DestinationPath.value);
    }

    if(!single)
    {
        r  = MI_Instance_GetElement(outputInstance, L"SubItems", &value, &type, 0, NULL);
        if(r != MI_RESULT_OK)
        {
            return;
        }
        NitsAssert(r == MI_RESULT_OK, L"SubItems doesn't match!");
        NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
        NitsAssert(value.instancea.size == 3 , L"SubItems doesn't match!");
        NitsAssert(value.instancea.size == 3, input.DestinationPath.value);
        for(MI_Uint32 i = 0; i < value.instancea.size; i++)
        {
            MI_Value subEnsureValue;
            MI_Type subEnsureType;
            MI_Result r  = MI_Instance_GetElement(outputInstance, L"Ensure", &subEnsureValue, &subEnsureType, 0, NULL);
            if(r != MI_RESULT_OK)
            {
                return;
            }
            NitsAssert(r == MI_RESULT_OK, L"sub ensure doesn't match!");
            NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
            bool subFile = false;
            if( _wcsicmp(value.string,L"file") == 0)
            {
                subFile = true;
            }
            ValidationOfGetObj(input, value.instancea.data[i], subFile, true);
        }
    }
    else
    {
        r  = MI_Instance_GetElement(outputInstance, L"SubItems", &value, &type, 0, NULL);
        NitsAssert(r == MI_RESULT_OK, L"SubItems doesn't match!");
        NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
        NitsAssert(value.instancea.size == 0, L"SubItems doesn't match!");
        NitsAssert(value.instancea.size == 0, input.DestinationPath.value);
    }
}

void ValidationOfGetOperation(MSFT_FileDirectoryConfiguration &input, bool file, bool single, NitsTrapHandle h)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);
    MI_Instance *outputInstance;

    //MSFT_FileDirectoryConfiguration outputInstance = {0};
    //fakeFT.SetElementAt = &Fake_SetElementAt;
    //outputInstance.__instance.ft = &fakeFT;
    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_GetFileDirectoryObject)(&input,&application, &outputInstance);
    NitsAssert(result == 0, L"error happens when get file!");
    NitsAssert(result == 0, input.DestinationPath.value);

    if(result == 0)
    {
        ValidationOfGetObj(input, outputInstance, file, single);
        MI_Instance_Delete(outputInstance);
    }

    MI_Application_Close(&application);
}


void SingleNoneExistDestinationGetOperation(MSFT_FileDirectoryConfiguration &input, NitsTrapHandle h)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);
    MI_Instance *outputInstance;

    //MSFT_FileDirectoryConfiguration outputInstance = {0};
    //fakeFT.SetElementAt = &Fake_SetElementAt;
    //outputInstance.__instance.ft = &fakeFT;

    //the single file
    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_GetFileDirectoryObject)(&input,&application, &outputInstance);
    NitsAssert(result == 0, L"error happens when get file!");
    NitsAssert(result == 0, input.DestinationPath.value);
    
    if(result == 0)
    {
        //compare the ensure
        MI_Value value;
        MI_Type type;
        MI_Result r  = MI_Instance_GetElement(outputInstance, L"Ensure", &value, &type, 0, NULL);
        NitsAssert(r == MI_RESULT_OK, L"ensure doesn't match!");
        NitsAssert(r == MI_RESULT_OK, input.DestinationPath.value);
        if(_wcsicmp(value.string, L"absent"))
        {
            NitsAssert(true, L"ensure doesn't match!");
        }

        MSFT_FileDirectoryConfiguration * output = (MSFT_FileDirectoryConfiguration * )outputInstance;
        NitsAssert(output->Attributes.exists == MI_FALSE, L"attributes doesn't match!");
        NitsAssert(output->CreatedDate.exists == MI_FALSE, L"CreatedDate doesn't match!");
        NitsAssert(output->ModifiedDate.exists == MI_FALSE, L"ModifiedDate doesn't match!");

        NitsAssert(output->Size.exists == MI_FALSE, L"Size doesn't match!");
        MI_Instance_Delete(outputInstance);
    }
    MI_Application_Close(&application);
}

void InValidObjOfGetOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Application_Initialize(0, NULL, NULL, &application);
    MI_Instance *outputInstance;

    int result = NitsGetTrap(h, NativeProviderTraps, _NativeProvider_GetFileDirectoryObject)(&input, &application, &outputInstance);
    NitsAssert(
        result == errorCode  , 
        L"Didn't get the expected error!");

    NitsAssert(
        result == errorCode  , 
        input.DestinationPath.value);

    MI_Application_Close(&application);

}

void CreateProcessHelper(const _In_z_ wchar_t *cmdLine)
{
    PROCESS_INFORMATION processInformation;
    STARTUPINFO startupInfo;

    ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));
    processInformation.hProcess = INVALID_HANDLE_VALUE;
    processInformation.hThread = INVALID_HANDLE_VALUE;

    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);

    //The second parameter of CreateProcess is _in_out_, so we need to allocate a new buffer
    DWORD cmdLineSize = wcslen(cmdLine);
    WCHAR * cmdLineBuf = new WCHAR[cmdLineSize + 1];
    ZeroMemory(cmdLineBuf, (cmdLineSize + 1) * sizeof(WCHAR));

    CDeleteUs<WCHAR> _1(cmdLineBuf);  
    errno_t error = wcscpy_s(cmdLineBuf, cmdLineSize + 1, cmdLine);
    NitsAssert(error == 0, L"Failed to copy the cmdline!");

    if(!CreateProcess(
        NULL,           // No module name (use command line)
        cmdLineBuf,                // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // creation flags
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory 
        &startupInfo,           // Pointer to STARTUPINFO structure
        &processInformation))   // Pointer to PROCESS_INFORMATION structure
    {
        NitsAssert(false, L"Failed to create process!");
    } 

    // Wait for process to exit and check the exit code, if necessary
    DWORD ttl = INFINITE;
    DWORD waitResult;

    // Successfully created the process.  Wait for it to finish.
    waitResult = WaitForSingleObject(processInformation.hProcess, ttl );
    if (waitResult == WAIT_FAILED)
    {
        NitsAssert(false, L"Failed to wait the process!");
    }

    DWORD processExitCode;
    // Get the exit code.
    if (!GetExitCodeProcess(processInformation.hProcess, &processExitCode))
    {
        NitsAssert(false, L"process failed!");
    }
    if(0 != processExitCode)
    {
        NitsAssert(false, L"process failed!!");
    }
    CloseHandle( processInformation.hProcess);    
    CloseHandle(processInformation.hThread);    
}

wstring FindFilePath(wstring partialName, bool &notExist)
{
    notExist = false;
    WCHAR currentDirBuf[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirBuf);
    wstring fileName = currentDirBuf;
    fileName += L"\\fileunitestdata\\";
    fileName += partialName;

    //get the attribute block
    fileName = currentDirBuf;
    fileName += L"\\fileunitestdata\\";

    //we will concatenate the original name if it's not found
    WIN32_FIND_DATA findFileData;
    HANDLE hfind = FindFirstFile((fileName + partialName).c_str(), &findFileData);
    if (hfind != INVALID_HANDLE_VALUE) 
    {
        FindClose(hfind);
        fileName += findFileData.cFileName;
    }
    else
    {
        fileName += partialName;
        notExist = true;
    }


    return fileName;
}

wstring FindFilePath(wstring partialName)
{
    bool notExist;
    return FindFilePath(partialName, notExist);
}



void InitializeInputInstancesOfGetOperation()
{
    singleDestFileFullPath = FindFilePath(L"singledestfilename*");
    singleDestDirFullPath = FindFilePath(L"singledestdirname*");

    MSFT_FileDirectoryConfiguration templateInstance = {0};

    templateInstance.DestinationPath.exists = MI_TRUE;
    templateInstance.DestinationPath.value= singleDestFileFullPath.c_str();
    templateInstance.DestinationPath.flags |= MI_FLAG_BORROW;

    templateInstance.SourcePath.exists = MI_TRUE;
    templateInstance.SourcePath.value= singleDestFileFullPath.c_str();

    templateInstance.Checksum.exists = MI_TRUE;
    templateInstance.Checksum.value = L"sha-1";

    templateInstance.Ensure.exists= MI_TRUE;
    templateInstance.Ensure.value = L"Present";

    normalfile = templateInstance;

    normalDirectory = templateInstance;
    normalDirectory.DestinationPath.value = singleDestDirFullPath.c_str();

    destinationPathNotExist = templateInstance;
    destinationPathNotExist.DestinationPath.value = L"C:\\windows\\system32\\notexistfileC2AFCAF0-2BA7-4cbb-9F14-E11B36E79FD7";

    invalidEnsure = templateInstance;
    invalidEnsure.Ensure.value = L"invalid";

    noDestinationPath = templateInstance;
    noDestinationPath.DestinationPath.exists = MI_FALSE;

    invalidWildCardInDest = templateInstance;
    invalidWildCardInDest.DestinationPath.value  = L"C:\\*\\1";

    destPathRelative = templateInstance;
    destPathRelative.DestinationPath.value = L"File.txt";

}

vector<wstring> GetAttributes(wstring attributesLine)
{
    vector<wstring> attributes;
    std::wstringstream linestream(attributesLine);
    wstring attribute;
    while(std::getline(linestream, attribute, L' '))
    {
        //attribute.erase(attribute.begin(), std::find_if(attribute.begin(), attribute.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        attributes.push_back(attribute);
    }
    return attributes;
}

void SetAttributesProperty(MSFT_FileDirectoryConfiguration &config ,vector<wstring> attributes)
{
    vector<const MI_Char *> attributeList;
    for(UINT32 i = 0 ; i < attributes.size(); ++i)
    {
        attributeList.push_back(attributes[i].c_str());
    }
    MSFT_FileDirectoryConfiguration_Set_Attributes(&config, attributeList.data(), (MI_Uint32)attributeList.size());

}

void InitializeInputInstancesOfTestOperation()
{
    //note we cannot use a fixed name because of the File System Tunneling feature, where the creation time will be cached
    wstring singledestfilewithbom = FindFilePath(L"singledestfilewithbom*");
    wstring singledestfilewithoutbom = FindFilePath(L"singledestfilewithoutbom*");
    wstring singlesourcewithbom = FindFilePath(L"singlesourcewithbom*");
    wstring singlesourcewithoutbom = FindFilePath(L"singlesourcewithoutbom*");
    wstring singledestdirname = FindFilePath(L"singledestdirname*");
    wstring singlesourcedirname = FindFilePath(L"singlesourcedirname*");

    //the setup script put the properties in this file already; now we just need to read them out
    wifstream propertyStream(FindFilePath(L"properties.txt"), wifstream::in);
    int bufferSize = 64 * 1024;
    vector<WCHAR> buffer(bufferSize);
    propertyStream.getline (buffer.data(),bufferSize);
    vector<wstring> attributesFileWithBom = GetAttributes(buffer.data());

    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    wstring sdFileWithBom = buffer.data();

    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    vector<wstring> attributesFileWithoutBom = GetAttributes(buffer.data());

    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    wstring sdFileWithoutBom = buffer.data();

    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    vector<wstring> attributesDir = GetAttributes(buffer.data());

    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    wstring sdDir = buffer.data();

    propertyStream.close();

#pragma region ensure=present&file
    fakeFT.SetElementAt = &Fake_SetElementAt;
    noSourceJustDestFilewithbom.__instance.ft = &fakeFT;            
    noSourceJustDestFilewithbom.Checksum.exists = MI_TRUE;
        noSourceJustDestFilewithbom.Checksum.value = L"None";


    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&noSourceJustDestFilewithbom, singledestfilewithbom.c_str());
    SetAttributesProperty(noSourceJustDestFilewithbom, attributesFileWithBom);

    contentAndDestFilewithbom = noSourceJustDestFilewithbom;
    contentAndDestFilewithbom.Contents.exists = MI_TRUE;
    contentAndDestFilewithbom.Contents.value = contents.c_str();

    contentAndDestFilewithoutbom = contentAndDestFilewithbom;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&contentAndDestFilewithoutbom, singledestfilewithoutbom.c_str());
    SetAttributesProperty(contentAndDestFilewithoutbom, attributesFileWithoutBom);

    
    sourceFileAndDestFilewithbom = noSourceJustDestFilewithbom;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&sourceFileAndDestFilewithbom, singlesourcewithbom.c_str());

    sourceFileAndDestDirWithSameFileWithBom = sourceFileAndDestFilewithbom;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceFileAndDestDirWithSameFileWithBom, singledestdirname.c_str());

    invalidSourceFileWithoutChecksum = sourceFileAndDestFilewithbom;
    invalidSourceFileWithoutChecksum.SourcePath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";

    AttributesNotMatch = noSourceJustDestFilewithbom;
    auto noMatchAttributes = attributesFileWithBom;
    noMatchAttributes.push_back(L"hidden");
    SetAttributesProperty(AttributesNotMatch, noMatchAttributes);

    ContentNotMatch = contentAndDestFilewithbom;
    ContentNotMatch.Contents.value = L"Doesn't match";
    ContentNotMatch.Checksum.exists = MI_TRUE;
    ContentNotMatch.Checksum.value = L"sha-1";

    SourceFileNotMatch = sourceFileAndDestFilewithbom;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&SourceFileNotMatch, singlesourcewithoutbom.c_str());
    SourceFileNotMatch.Checksum.exists = MI_TRUE;
    SourceFileNotMatch.Checksum.value = L"sha-1";

    sourceFileAndNotExistDestFile = sourceFileAndDestFilewithbom;
    sourceFileAndNotExistDestFile.DestinationPath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";

    contentAndNotExistDestFile = contentAndDestFilewithbom;
    contentAndNotExistDestFile.DestinationPath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";

    noSourceAndNotExistDestFile = noSourceJustDestFilewithbom;
    noSourceAndNotExistDestFile.DestinationPath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";

    invalidSourceFileWithSha1Checksum = sourceFileAndDestFilewithbom;
    invalidSourceFileWithSha1Checksum.SourcePath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";
    invalidSourceFileWithSha1Checksum.Checksum.value = L"sha1";
    invalidSourceFileWithSha1Checksum.Checksum.exists = MI_TRUE;

    sourcePathAndContents = sourceFileAndDestFilewithbom;
    sourcePathAndContents.Contents.exists = MI_TRUE;
    sourcePathAndContents.Contents.value = contents.c_str();

    invalidChecksumNoSource = noSourceJustDestFilewithbom;
    invalidChecksumNoSource.Checksum.value = L"sha-1";
    invalidChecksumNoSource.Checksum.exists = MI_TRUE;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&invalidChecksumNoSource, singledestfilewithbom.c_str());

#pragma region ensure=present&file

#pragma region  ensure=directory
    sourceDirAndDestDir.__instance.ft = &fakeFT;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceDirAndDestDir, singledestdirname.c_str());
    SetAttributesProperty(sourceDirAndDestDir, attributesDir);
    sourceDirAndDestDir.Ensure.exists = MI_TRUE;
    sourceDirAndDestDir.Ensure.value = L"Present";
        sourceDirAndDestDir.Type.exists = MI_TRUE;
        sourceDirAndDestDir.Type.value = L"Directory";

    sourceDirAndNotExistDest = sourceDirAndDestDir;
    sourceDirAndNotExistDest.DestinationPath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";

    sourceDirAndDestFile = sourceDirAndDestDir;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceDirAndDestFile, singledestfilewithbom.c_str());

    sourceContent = sourceDirAndDestDir;
    sourceContent.SourcePath.exists = false;
    sourceContent.Contents.exists = MI_TRUE;
    sourceContent.Contents.value = contents.c_str();

    sourceFileWithoutChecksum = sourceDirAndDestDir;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&sourceFileWithoutChecksum, singledestfilewithbom.c_str());

    sourceFileWithSha1Checksum = sourceDirAndDestDir;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&sourceFileWithSha1Checksum, singledestfilewithbom.c_str());
    sourceFileWithSha1Checksum.Checksum.value = L"sha1";
    sourceFileWithSha1Checksum.Checksum.exists = MI_TRUE;
#pragma endregion

#pragma region ensure=absent
    DestDir.__instance.ft = &fakeFT;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDir, singledestdirname.c_str());
    DestDir.Ensure.exists = MI_TRUE;
    DestDir.Ensure.value = L"absent";
        DestDir.Type.exists = MI_TRUE;
        DestDir.Type.value = L"Directory";

    DestFile = DestDir;
        DestFile.Type.exists = MI_TRUE;
        DestFile.Type.value = L"File";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestFile, singledestfilewithbom.c_str());

    NotExistDest = DestDir;
    NotExistDest.DestinationPath.exists = MI_TRUE;
    NotExistDest.DestinationPath.value = L"C:\\doesntexist11bd9629-10c3-4aca-9247-d67cff7f212e.txt";
#pragma endregion
}

void InitializeInputInstancesOfRecursiveTestOperation()
{
    wstring RsourcedirPath = FindFilePath(L"Rsourcedir");
    wstring RDestdirIdenticalPath = FindFilePath(L"RDestdirIdentical");
    wstring RDestdirMissingFilePath = FindFilePath(L"RDestdirMissingFile");
    wstring RDestdirMoreFilePath = FindFilePath(L"RDestdirMoreFile");
    wstring RDestdirMissingSubdirPath = FindFilePath(L"RDestdirMissingSubdir");
    wstring RDestdirMoreSubdirPath = FindFilePath(L"RDestdirMoreSubdir");
    wstring RDestdirFileContentMismatchPath = FindFilePath(L"RDestdirFileContentMismatch");
    wstring RDestDirsubFileAttributeMismatchPath = FindFilePath(L"RDestDirsubFileAttributeMismatch");
    wstring RDestDirSubdirAttributeMismatchPath = FindFilePath(L"RDestDirSubdirAttributeMismatch");
    wstring RDestDirExpectSubdirButFilePath = FindFilePath(L"RDestDirExpectSubdirButFile");
    wstring RDestDirExpectFileButSubDirPath = FindFilePath(L"RDestDirExpectFileButSubDir");

    vector<wstring> desiredAttributes;
    desiredAttributes.push_back(L"ReadOnly");
    desiredAttributes.push_back(L"System");
    desiredAttributes.push_back(L"hidden");

#pragma region ensure=present&file
    fakeFT.SetElementAt = &Fake_SetElementAt;
    RDestdirIdentical.__instance.ft = &fakeFT;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirIdentical, RDestdirIdenticalPath.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&RDestdirIdentical, RsourcedirPath.c_str());
    SetAttributesProperty(RDestdirIdentical, desiredAttributes);
    RDestdirIdentical.Ensure.value= L"Present";
        RDestdirIdentical.Type.value= L"Directory";
    RDestdirIdentical.Ensure.exists = MI_TRUE;
        RDestdirIdentical.Type.exists = MI_TRUE;
    RDestdirIdentical.Force.value= MI_TRUE;
    RDestdirIdentical.Force.exists = MI_TRUE;
    RDestdirIdentical.Recurse.value= MI_TRUE;
    RDestdirIdentical.Recurse.exists = MI_TRUE;
    RDestdirIdentical.Checksum.value= L"sha-1";
    RDestdirIdentical.Checksum.exists = MI_TRUE;

    RDestdirMissingFile = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirMissingFile, RDestdirMissingFilePath.c_str());

    RDestdirMoreFile = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirMoreFile, RDestdirMoreFilePath.c_str());

    RDestdirMissingSubdir = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirMissingSubdir, RDestdirMissingSubdirPath.c_str());

    RDestdirMoreSubdir = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirMoreSubdir, RDestdirMoreSubdirPath.c_str());

    RDestdirFileContentMismatch = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirFileContentMismatch, RDestdirFileContentMismatchPath.c_str());

    RDestDirsubFileAttributeMismatch = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestDirsubFileAttributeMismatch, RDestDirsubFileAttributeMismatchPath.c_str());

    RDestDirSubdirAttributeMismatch = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestDirSubdirAttributeMismatch, RDestDirSubdirAttributeMismatchPath.c_str());

    RDestDirExpectSubdirButFile = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestDirExpectSubdirButFile, RDestDirExpectSubdirButFilePath.c_str());

    RDestDirExpectFileButSubDir = RDestdirIdentical;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestDirExpectFileButSubDir, RDestDirExpectFileButSubDirPath.c_str());

#pragma endregion
}

void InitializeInputInstancesOfSetOperation()
{
    //We are using fixed name for set.
    wstring singledestfilecontentmismatch = FindFilePath(L"singledestfilecontentmismatch.txt");
    wstring singledestfileattributesmismatch= FindFilePath(L"singledestfileattributesmismatch.txt");
    wstring singledestfileSourcemismatch=FindFilePath(L"singledestfileSourcemismatch.txt");
    wstring emptyFile=FindFilePath(L"emptyFile.txt");

    wstring singledestfileoriginallynotexistcontent= FindFilePath(L"singledestfileoriginallynotexistcontent.txt");
    wstring singledestfileoriginallynotexistsource= FindFilePath(L"test\\test\\test\\test\\test\\singledestfileoriginallynotexistsource.txt");
    wstring singledestdirname=FindFilePath(L"singledestdirname");
    wstring singledestdiroriginallynotexist=FindFilePath(L"singledestdiroriginallynotexist");

    wstring singlesource = FindFilePath(L"singlesource.txt");
    wstring singlesourcedirname = FindFilePath(L"singlesourcedirname");

    wstring DestDirForAbsent=FindFilePath(L"DestDirForAbsent");
    wstring DestFileForAbsent=FindFilePath(L"DestFileForAbsent.txt");

    wstring DestDirNotEmptyForceTruePath=FindFilePath(L"DestDirNotEmptyForceTrue");
    wstring DestDirNotEmptyForceFALSEPath=FindFilePath(L"DestDirNotEmptyForceFALSE");

    wstring DestDirEnsureFileContentForcePath = FindFilePath(L"DestDirEnsureFileContentForce");
    wstring DestFileParentNotExistContentPath = FindFilePath(L"notexist\\notexst2\\..\\DestFileParentNotExistContent");
    wstring DestFileEnsureDirForcePath = FindFilePath(L"DestFileEnsureDirForce");
    wstring DestDirParentNotExistForSetPath= FindFilePath(L"notexist\\notexst2\\..\\DestDirParentNotExistForSet");

    wstring RDestdirForSetPath = FindFilePath(L"RDestdirForSet");
    wstring RsourcedirPath = FindFilePath(L"Rsourcedir");

    //the setup script put the properties in this file already; now we just need to read them out
    wifstream propertyStream(FindFilePath(L"properties.txt"), wifstream::in);
    int bufferSize = 64 * 1024;
    vector<WCHAR> buffer(bufferSize);
    buffer.resize(bufferSize, 0);
    propertyStream.getline (buffer.data(),bufferSize);
    wstring targetSD = buffer.data();
    propertyStream.close();


#pragma region ensure=present&file
    fakeFT.SetElementAt = &Fake_SetElementAt;
    MSFT_FileDirectoryConfiguration templateInstance = {0};
    templateInstance.__instance.ft = &fakeFT;
    SetAttributesProperty(templateInstance, GetAttributes(L"readonly"));

    ContentNotMatchForSet = templateInstance;
    ContentNotMatchForSet.Ensure.exists =MI_TRUE;
    ContentNotMatchForSet.Ensure.value = L"Present";
        ContentNotMatchForSet.Type.exists =MI_TRUE;
        ContentNotMatchForSet.Type.value = L"file";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&ContentNotMatchForSet, singledestfilecontentmismatch.c_str());
    ContentNotMatchForSet.Contents.exists = MI_TRUE;
    ContentNotMatchForSet.Contents.value = contents.c_str();
    ContentNotMatchForSet.Checksum.exists = MI_TRUE;
    ContentNotMatchForSet.Checksum.value = L"sha-1";

    contentAndNotExistDestFileForSet = ContentNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&contentAndNotExistDestFileForSet, singledestfileoriginallynotexistcontent.c_str());

    ContentNotMatchForSetEmptyFile = ContentNotMatchForSet;
    ContentNotMatchForSetEmptyFile.Contents.value = L"";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&ContentNotMatchForSetEmptyFile, emptyFile.c_str());

    AttributesNotMatchForSet = ContentNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&AttributesNotMatchForSet, singledestfileattributesmismatch.c_str());

    SourceFileNotMatchForSet = templateInstance;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&SourceFileNotMatchForSet, singledestfileSourcemismatch.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&SourceFileNotMatchForSet, singlesource.c_str());
    SourceFileNotMatchForSet.Checksum.exists = MI_TRUE;
    SourceFileNotMatchForSet.Checksum.value = L"sha-1";

    sourceFileAndNotExistDestFileForSet = SourceFileNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceFileAndNotExistDestFileForSet, singledestfileoriginallynotexistsource.c_str());

    DestDirEnsureFileContentForce = ContentNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDirEnsureFileContentForce, DestDirEnsureFileContentForcePath.c_str());
    DestDirEnsureFileContentForce.Force.exists = MI_TRUE;
    DestDirEnsureFileContentForce.Force.value= MI_TRUE;

    DestFileParentNotExistContent  = ContentNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestFileParentNotExistContent , DestFileParentNotExistContentPath.c_str());


#pragma region ensure=present&file

#pragma region  ensure=directory
    sourceDirAndDestDirForSet = templateInstance;
    sourceDirAndDestDirForSet.Ensure.exists =MI_TRUE;
    sourceDirAndDestDirForSet.Ensure.value = L"Present";
        sourceDirAndDestDirForSet.Type.exists =MI_TRUE;
        sourceDirAndDestDirForSet.Type.value = L"directory";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceDirAndDestDirForSet, singledestdirname.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&sourceDirAndDestDirForSet, singlesourcedirname.c_str());

    sourceDirAndNotExistDestForSet = sourceDirAndDestDirForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&sourceDirAndNotExistDestForSet, singledestdiroriginallynotexist.c_str());

    DestFileEnsureDirForce  = sourceDirAndDestDirForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestFileEnsureDirForce , DestFileEnsureDirForcePath.c_str());
    DestFileEnsureDirForce.Force.exists = MI_TRUE;
    DestFileEnsureDirForce.Force.value= MI_TRUE;

    DestDirParentNotExistForSet = sourceDirAndDestDirForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDirParentNotExistForSet , DestDirParentNotExistForSetPath.c_str());

    RDestdirForSet = sourceDirAndDestDirForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&RDestdirForSet , RDestdirForSetPath.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&RDestdirForSet , RsourcedirPath.c_str());
    RDestdirForSet.Recurse.exists = MI_TRUE;
    RDestdirForSet.Recurse.value = MI_TRUE;
    RDestdirForSet.Force.exists = MI_TRUE;
    RDestdirForSet.Force.value = MI_TRUE;
    RDestdirForSet.Checksum.value = L"sha-1";
    RDestdirForSet.Checksum.exists = MI_TRUE;
#pragma endregion

#pragma region ensure=absent
    DestDirForSet.__instance.ft = &fakeFT;
    DestDirForSet.Ensure.exists =MI_TRUE;
    DestDirForSet.Ensure.value = L"absent";
    DestDirForSet.Type.exists = MI_TRUE;
    DestDirForSet.Type.value = L"Directory";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDirForSet, DestDirForAbsent.c_str());

    DestFileForSet = DestDirForSet;
        DestFileForSet.Type.exists = MI_TRUE;
    DestFileForSet.Type.value = L"File";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestFileForSet, DestFileForAbsent.c_str());

    DestDirNotEmptyForceTrue = DestDirForSet;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDirNotEmptyForceTrue, DestDirNotEmptyForceTruePath.c_str());
    DestDirNotEmptyForceTrue.Force.exists = MI_TRUE;
    DestDirNotEmptyForceTrue.Force.value = MI_TRUE;

    DestDirNotEmptyForceFALSE = DestDirForSet;
        DestDirNotEmptyForceFALSE.Type.exists = MI_TRUE;
    DestDirNotEmptyForceFALSE.Type.value = L"Directory";

    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestDirNotEmptyForceFALSE, DestDirNotEmptyForceFALSEPath.c_str());

#pragma endregion

#pragma region invalid
    DestDirEnsureFileNoSource = sourceDirAndDestDirForSet;
    DestDirEnsureFileNoSource.Ensure.value = L"Present";
        DestDirEnsureFileNoSource.Type.exists = MI_TRUE;
        DestDirEnsureFileNoSource.Type.value = L"file";
    DestDirEnsureFileNoSource.SourcePath.exists = MI_FALSE;
    DestWildcardEnsureFileNosouce = DestDirEnsureFileNoSource;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&DestWildcardEnsureFileNosouce, L"C:\\*.txt");

    DestDirEnsureFileContent = DestDirEnsureFileNoSource;
    DestDirEnsureFileContent.Contents.exists = MI_TRUE;
    DestDirEnsureFileContent.Contents.value = L"";

    DestWildcardEnsureFileContent = DestWildcardEnsureFileNosouce;
    DestWildcardEnsureFileContent.Contents.exists = MI_TRUE;
    DestWildcardEnsureFileContent.Contents.value = L"";

    SourceProblematic = SourceFileNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&SourceProblematic, L"D:\\notexistingfile");
    SourceWildCard = SourceFileNotMatchForSet;
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&SourceWildCard, L"D:\\*.txt");

    NoSourcePathCheckSumModifiedDate = SourceFileNotMatchForSet;
    NoSourcePathCheckSumModifiedDate.SourcePath.exists = MI_FALSE;
    NoSourcePathCheckSumModifiedDate.Attributes.exists = MI_FALSE;
    NoSourcePathCheckSumModifiedDate.Checksum.exists = MI_TRUE;
    NoSourcePathCheckSumModifiedDate.Checksum.value = L"modifieddate";
    NoSourcePathCheckSumModifiedDate.Contents.exists = MI_TRUE;
    NoSourcePathCheckSumModifiedDate.Contents.value = L"";

#pragma endregion

}

void InitializeInputInstancesOfCredentialOperation()
{
    wstring SingleFileRemoteSource = L"\\\\localhost\\credentialshare\\1.txt";
    wstring singlefileDest= FindFilePath(L"singlefileDest.txt");
    wstring dirDest = FindFilePath(L"singlefileDest");
    wstring dirSource = L"\\\\localhost\\credentialshare\\";

#pragma region ensure=present&file
    fakeFT.SetElementAt = &Fake_SetElementAt;
    SingleFileRemoteSourceNotMatchLocalUser.__instance.ft = &fakeFT;

    SingleFileRemoteSourceNotMatchLocalUser.Ensure.exists =MI_TRUE;
    SingleFileRemoteSourceNotMatchLocalUser.Ensure.value = L"Present";
        SingleFileRemoteSourceNotMatchLocalUser.Type.exists =MI_TRUE;
        SingleFileRemoteSourceNotMatchLocalUser.Type.value = L"file";
    credential.UserName.exists = MI_TRUE;
    credential.UserName.value = L"localhost\\paxnj";
    credential.Password.exists = MI_TRUE;
    credential.Password.value = L"123456Q((";
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&SingleFileRemoteSourceNotMatchLocalUser, singlefileDest.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&SingleFileRemoteSourceNotMatchLocalUser, SingleFileRemoteSource.c_str());
    SingleFileRemoteSourceNotMatchLocalUser.Credential.exists = MI_TRUE;
    SingleFileRemoteSourceNotMatchLocalUser.Credential.value = &credential;

    MultipleFileRemoteSourceNotMatchLocalUser = SingleFileRemoteSourceNotMatchLocalUser;
    MSFT_FileDirectoryConfiguration_Set_DestinationPath(&MultipleFileRemoteSourceNotMatchLocalUser, dirDest.c_str());
    MSFT_FileDirectoryConfiguration_Set_SourcePath(&MultipleFileRemoteSourceNotMatchLocalUser, dirSource.c_str());
    MultipleFileRemoteSourceNotMatchLocalUser.Recurse.exists = MI_TRUE;
    MultipleFileRemoteSourceNotMatchLocalUser.Recurse.value = MI_TRUE;
    MultipleFileRemoteSourceNotMatchLocalUser.Ensure.value = L"Present";
        MultipleFileRemoteSourceNotMatchLocalUser.Type.exists =MI_TRUE;
        MultipleFileRemoteSourceNotMatchLocalUser.Type.value = L"Directory";

    CredentialIsSpecifiedButNoPassword = SingleFileRemoteSourceNotMatchLocalUser;
    noPasswordCredential.UserName.exists = MI_TRUE;
    noPasswordCredential.UserName.value = L"paxnj";
    CredentialIsSpecifiedButNoPassword.Credential.value = &noPasswordCredential;

    CredentialIsSpecifiedButNoUserName = SingleFileRemoteSourceNotMatchLocalUser;
    noUserNameCredential.UserName.exists = MI_TRUE;
    noUserNameCredential.UserName.value = L"paxnj";
    CredentialIsSpecifiedButNoUserName.Credential.value = &noUserNameCredential;

    LocalSource = SingleFileRemoteSourceNotMatchLocalUser;
    LocalSource.SourcePath.value = L"C:\\windows\\system32\\dsccoreconfprov.dll";

    NotExistSource = SingleFileRemoteSourceNotMatchLocalUser;
    NotExistSource.SourcePath.value = L"\\\\notexistcomputer\\abcdefg\\1.txt";

    WrongPassword = SingleFileRemoteSourceNotMatchLocalUser;
    wrongPasswordCredential.UserName.exists = MI_TRUE;
    wrongPasswordCredential.UserName.value = L"paxnj";
    wrongPasswordCredential.Password.exists = MI_TRUE;
    wrongPasswordCredential.Password.value = L"11111";
    WrongPassword.Credential.value = &wrongPasswordCredential;

}

void InitializeInputInstancesOfRecursiveGetOperation()
{
    singleDestFileFullPath = FindFilePath(L"singledestfilename*");
    destdirname = FindFilePath(L"destdirname*");
    destdirnameWithBackSlash = destdirname;
    destdirnameWithBackSlash.append(L"\\");

    localDirectory.DestinationPath.exists = MI_TRUE;
    localDirectory.DestinationPath.value= destdirname.c_str();
    localDirectory.DestinationPath.flags |= MI_FLAG_BORROW;

    localDirectory.Ensure.exists= MI_TRUE;
    localDirectory.Ensure.value = L"Present";

    localDirectory.Recurse.exists= MI_TRUE;
    localDirectory.Recurse.value = MI_TRUE;


    localDirectoryWithBackSlash = localDirectory;
    localDirectoryWithBackSlash.DestinationPath.value = destdirnameWithBackSlash.c_str();

    WCHAR driveTemp[_MAX_DRIVE] = {'\0'};
    WCHAR dirTemp[_MAX_DIR] = {'\0'};
    WCHAR fileNameTemp[_MAX_FNAME] = {'\0'};
    WCHAR extTemp[_MAX_EXT] = {'\0'}; 
    _wsplitpath_s(destdirname.c_str(), driveTemp, _MAX_DRIVE, dirTemp, _MAX_DIR, fileNameTemp, _MAX_FNAME, extTemp,_MAX_EXT);
    netShareDirName = L"\\\\localhost\\recursivegetshare\\";
    netShareDirName.append(dirTemp);
    sharedDirectory = localDirectory;
    sharedDirectory.DestinationPath.value = netShareDirName.c_str();

    normalfileWithRecurse = localDirectory;
    sharedDirectory.DestinationPath.value = singleDestFileFullPath.c_str();

    networkShare = localDirectory;
    networkShare.DestinationPath.value = L"\\\\localhost\\recursivegetshare";

    rootDir = localDirectory;
    rootDir.DestinationPath.value = L"C:\\";

}

void MatchTime(MI_Datetime * time, DWORD differenceInSeconds)
{
    NitsAssert(time != NULL, L"time is null!");
    NitsAssert(time->isTimestamp, L"time is not time stamp!");
    NitsAssert(time->isTimestamp, L"time is not time stamp!");

    SYSTEMTIME currentTime;
    FILETIME currentFileTime;
    GetSystemTime(&currentTime);
    SystemTimeToFileTime(&currentTime, &currentFileTime);

    SYSTEMTIME instanceTime;
    FILETIME instanceFileTime;
    instanceTime.wYear = (WORD)time->u.timestamp.year;
    instanceTime.wMonth = (WORD)time->u.timestamp.month;
    instanceTime.wDay = (WORD)time->u.timestamp.day;
    instanceTime.wHour = (WORD)time->u.timestamp.hour;
    instanceTime.wMinute = (WORD)time->u.timestamp.minute;
    instanceTime.wSecond = (WORD)time->u.timestamp.second;
    instanceTime.wMilliseconds = (WORD)time->u.timestamp.microseconds / 1000;
    SystemTimeToFileTime(&instanceTime, &instanceFileTime);

    //high part should be the same
    NitsAssert(currentFileTime.dwHighDateTime == instanceFileTime.dwHighDateTime, L"time mismatch!");

    //low part could have a certain difference
    NitsAssert((currentFileTime.dwLowDateTime - instanceFileTime.dwLowDateTime ) < (DWORD)(differenceInSeconds * 10000000), L"time mismatch!");
}

//Warning: this is deeply coupled to the definition of MSFT_FileDirectoryConfiguration; but it's test code...
MI_Result GetFieldPointer( _In_ MI_Instance* self_, MI_Uint32 index, _Outptr_  char**field)
{
    *field = 0;
    /* Get pointer to field */
    switch (index)
    {
    case 0:                                 //destinationpath
        *field = (char *)self_ + sizeof(MI_Instance);
        break;
    case 1:                                 //ensure
        *field = (char *)self_ + sizeof(MI_Instance)+ sizeof(MI_ConstStringField);
        break;
    case 2:                                 //type
        *field = (char *)self_ + sizeof(MI_Instance)+ sizeof(MI_ConstStringField) * 2;
        break;
    case 3:                                 //sourcepath
        *field = (char *)self_ + sizeof(MI_Instance)+ sizeof(MI_ConstStringField) * 3;
        break;
    case 4:                                 //contents
        *field = (char *)self_ + sizeof(MI_Instance)+ sizeof(MI_ConstStringField) * 4;
        break;
    case 11:                                //attributes
        *field = (char *)self_ + sizeof(MI_Instance) + sizeof(MI_ConstStringField) * 6 
            + sizeof(MI_ConstBooleanField) * 2 + 2 //need 1 extra bytes for alignment
            + sizeof(MSFT_Credential_ConstRef) + sizeof(MI_ConstDatetimeField) * 2;
        break;
    default:
        return MI_RESULT_NOT_SUPPORTED;
    }
    return MI_RESULT_OK;
}

//We cannot invoke the provider directly because we want fault injection
//So we will use this fake set funciton to set the elements
MI_Result MI_CALL Fake_SetElementAt(
    MI_Instance* self_, 
    MI_Uint32 index,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags)
{
    char* field;
    MI_Result r = GetFieldPointer(self_, index, &field);
    if(r != MI_RESULT_OK)
    {
        return r;
    }

    /* Set the value */
    switch (type)
    {
    case MI_UINT8:
    case MI_SINT8:
    case MI_BOOLEAN:
        {
            MI_Uint8Field* f = (MI_Uint8Field*)field;

            f->value = value->uint8;
            f->exists = MI_TRUE;
            break;
        }
    case MI_UINT16:
    case MI_SINT16:
    case MI_CHAR16:
        {
            MI_Uint16Field* f = (MI_Uint16Field*)field;

            f->value = value->uint16;
            f->exists = MI_TRUE;
            break;
        }
    case MI_UINT32:
    case MI_SINT32:
    case MI_REAL32:
        {
            MI_Uint32Field* f = (MI_Uint32Field*)field;

            f->value = value->uint32;
            f->exists = MI_TRUE;

            break;
        }
    case MI_UINT64:
    case MI_SINT64:
    case MI_REAL64:
        {
            MI_Uint64Field* f = (MI_Uint64Field*)field;

            f->value = value->uint64;
            f->exists = MI_TRUE;

            break;
        }
    case MI_DATETIME:
        {
            MI_DatetimeField* f = (MI_DatetimeField*)field;

            f->value = value->datetime;
            f->exists = MI_TRUE;

            break;
        }
    case MI_STRING:
        {
            MI_StringField* f = (MI_StringField*)field;
            MI_Char* oldValue = f->value;
            MI_Uint32 oldFlags = f->flags;

            size_t size = wcslen(value->string) + 1;
            MI_Char* tmpStr = new MI_Char[size];
            tmpStr[size - 1] = 0;
            wcscpy_s(tmpStr, size, value->string);

            f->value = tmpStr;
            f->exists = MI_TRUE;
            f->flags = 0;

            if(!(oldFlags & MI_FLAG_BORROW) && oldValue)
            {
                //delete []oldValue;
            }
            break;
        }

    case MI_STRINGA:
        {
            MI_StringAField* f = (MI_StringAField*)field;
            MI_Char** oldValue = f->value.data;
            MI_Uint32 oldFlags = f->flags;
            MI_Uint32 oldSize = f->value.size;

            f->value.data =  new MI_Char*[value->stringa.size];
            for(MI_Uint32 i = 0; i < value->stringa.size; ++i)
            {
                size_t size = wcslen(value->stringa.data[i]) + 1;
                MI_Char* tmpStr = new MI_Char[size];
                tmpStr[size - 1] = 0;
                wcscpy_s(tmpStr, size, value->stringa.data[i]);
                f->value.data[i] = tmpStr;
            }

            f->value.size = value->stringa.size;
            f->exists = MI_TRUE;
            f->flags = 0;
            /* Release old instances and array */
            if (!(oldFlags & MI_FLAG_BORROW) && oldValue)
            {
                for(MI_Uint32 i = 0; i < oldSize; ++i)
                {
                    //delete oldValue[i];
                }
                //delete []oldValue;
            }
        }
        break;
    default:
        return MI_RESULT_NOT_SUPPORTED;
    }
    return(MI_RESULT_OK);
}

//particular fields need to be destructed
void Instance_Desctruct(MSFT_FileDirectoryConfiguration *obj)
{
    if(obj->DestinationPath.exists && !(obj->DestinationPath.flags& MI_FLAG_BORROW))
    {
        delete []obj->DestinationPath.value;
    }
    if(obj->Attributes.exists && !(obj->Attributes.flags& MI_FLAG_BORROW))
    {
        for(MI_Uint32 i = 0; i < obj->Attributes.value.size; ++i)
        {
            delete obj->Attributes.value.data[i];
        }
        delete []obj->Attributes.value.data;
    }

}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */


