/*============================================================================
 * Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *============================================================================
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

