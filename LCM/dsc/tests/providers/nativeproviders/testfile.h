/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <MI.h>
#include <nits.h>
#include <MSFT_FileDirectoryConfiguration.h>

void MatchTime(MI_Datetime * time, DWORD differenceInSeconds);
void InitializeInputInstancesOfGetOperation();
void InitializeInputInstancesOfTestOperation();
void InitializeInputInstancesOfRecursiveTestOperation();
void InitializeInputInstancesOfSetOperation();
void InitializeInputInstancesOfCredentialOperation();
void InitializeInputInstancesOfRecursiveGetOperation();
void CreateProcessHelper(const _In_z_ wchar_t *cmdLine);
void ValidationOfGetOperation(MSFT_FileDirectoryConfiguration &input, bool file, bool single, NitsTrapHandle h);
void SingleNoneExistDestinationGetOperation(MSFT_FileDirectoryConfiguration &input, NitsTrapHandle h);
void InValidObjOfGetOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h);
void SingleValidObjOfTestOperation(MSFT_FileDirectoryConfiguration &input, bool shouldMatch, NitsTrapHandle h);
void SingleInValidObjOfTestOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h);
void InValidObjOfSetOperation(MSFT_FileDirectoryConfiguration &input, int errorCode, NitsTrapHandle h);
void ValidObjOfSetOperation(MSFT_FileDirectoryConfiguration &input, NitsTrapHandle h);
void CheckOutputOfSetOperation(int i);
void CheckOutpuFile();

void Instance_Desctruct(MSFT_FileDirectoryConfiguration *obj);
MI_Result MI_CALL Fake_SetElementAt(
    MI_Instance* self_, 
    MI_Uint32 index,
    const MI_Value* value,
    MI_Type type,
    MI_Uint32 flags);


std::wstring FindFilePath(std::wstring partialName, bool &notExist);

template<class T>
class CDeleteUs
{
protected:
    T *m_p;
public:
    CDeleteUs(_In_ T *p) : m_p(p) {}
    ~CDeleteUs() { delete [] m_p; }
};

