/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "CAValidate.h"

MI_Boolean IsSameMiValue(
    _In_ MI_Value* value0,
    _In_ MI_Value* value1,
    _In_ MI_Type type)
{
    switch (type)
    {
        case MI_BOOLEAN:
            return value0->boolean == value1->boolean;

        case MI_UINT8:
            return value0->uint8 == value1->uint8;

        case MI_SINT8:
            return value0->sint8 == value1->sint8;

        case MI_UINT16:
            return value0->uint16 == value1->uint16;

        case MI_SINT16:
            return value0->sint16 == value1->sint16;

        case MI_UINT32:
            return value0->uint32 == value1->uint32;

        case MI_SINT32:
            return value0->sint32 == value1->sint32;

        case MI_UINT64:
            return value0->uint64 == value1->uint64;

        case MI_SINT64:
            return value0->sint64 == value1->sint64;

        case MI_REAL32:
            return value0->real32 == value1->real32;

        case MI_REAL64:
            return value0->real64 == value1->real64;

        case MI_CHAR16:
            return value0->char16 == value1->char16;

        case MI_DATETIME:
            return memcmp((const void *)&value0->datetime, (const void*)&value1->datetime, sizeof(value0->datetime)) == 0;

        case MI_STRING:
            return Tcscmp(value0->string, value1->string) == 0;

        default:
            return MI_FALSE;
    }

}

MI_Result CreateMemoryError(
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.	

    return GetCimMIError(MI_RESULT_SERVER_LIMITS_EXCEEDED, extendedError, ID_ENGINEHELPER_MEMORY_ERROR);
}

MI_Boolean IsMatchedKeyProperties(
    _In_ MI_Instance* instance0,
    _In_ MI_Instance* instance1,
    _Outptr_result_maybenull_z_ MI_Char** keywords,
    _Out_ MI_Result* miResult,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Uint32 i, j;
    MI_Result result0, result1;
    MI_Value value0, value1;
    MI_Type type0, type1;
    Intlstr intlstr = Intlstr_Null;
    MI_Char* tempKeywords = NULL;
    MI_Char* tempKeywordsBackup = NULL;
    size_t length;
    MI_PropertyDecl** properties;

    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.	

    *miResult = MI_RESULT_OK;
    *keywords = NULL;
    properties = (MI_PropertyDecl**)instance0->classDecl->properties;
    for (i = 0; i < instance0->classDecl->numProperties; i++)
    {
        for (j = 0; j < properties[i]->numQualifiers; j++)
        {
            if (Tcscasecmp(properties[i]->qualifiers[j]->name, MI_T("Key")) == 0)
            {
                result0 = DSC_MI_Instance_GetElement(instance0, properties[i]->name, &value0, &type0, NULL, NULL);
                result1 = DSC_MI_Instance_GetElement(instance1, properties[i]->name, &value1, &type1, NULL, NULL);
                if (result0 == MI_RESULT_OK
                    && result1 == MI_RESULT_OK
                    && type0 == type1
                    && IsSameMiValue(&value0, &value1, type0))
                {
                    // key is the same, building keywords list.
                    length = Tcslen(properties[i]->name) + 1;
                    if (tempKeywords == NULL)
                    {
                        // the first keyword.
                        tempKeywords = (MI_Char*)DSC_malloc(length * sizeof (MI_Char), NitsHere());
                        if (tempKeywords == NULL)
                        {
                            *miResult = CreateMemoryError(extendedError);
                            return MI_TRUE;
                        }

                        memcpy(tempKeywords, properties[i]->name, length * sizeof(MI_Char) );
                    }
                    else
                    {
                        // the second or more keywords.
                        if (intlstr.str == NULL)
                        {
                            // create separator string once.
                            GetResourceString(ID_CA_COMMA_SEPARATOR, &intlstr);
                            if (intlstr.str == NULL)
                            {
                                *miResult = CreateMemoryError(extendedError);
                                DSC_free(tempKeywords);
                                return MI_TRUE;
                            }
                        }

                        length += Tcslen(tempKeywords) + Tcslen(intlstr.str);
                        tempKeywordsBackup = tempKeywords;
                        tempKeywords = (MI_Char*)DSC_realloc(tempKeywordsBackup, length * sizeof (MI_Char), NitsHere());
                        if (tempKeywords == NULL)
                        {
                            *miResult = CreateMemoryError(extendedError);
                            DSC_free(tempKeywordsBackup);
                            Intlstr_Free(intlstr);
                            return MI_TRUE;
                        }
                        Stprintf(tempKeywords, length, MI_T("%T%T"), intlstr.str, properties[i]->name);
                    }
                }
                else
                {
                    if (tempKeywords)
                    {
                        DSC_free(tempKeywords);
                    }
                    
                    if (intlstr.str)
                    {
                        Intlstr_Free(intlstr);
                    }
                    
                    if(result0 != MI_RESULT_OK)
                    {
                        *miResult = result0;
                    }
                    else if(result1 != MI_RESULT_OK)
                    {
                        *miResult = result1;
                    }

                    return MI_FALSE;
                }

                break;
            }
        }
    }

    if (intlstr.str)
    {
        Intlstr_Free(intlstr);
    }

    // at least one key was found, and all matched.
    if (tempKeywords)
    {
        *keywords = tempKeywords;
        return MI_TRUE;
    }

    return MI_FALSE;
}

MI_Result ValidateIfDuplicatedInstances(
    _In_ MI_InstanceA *instanceA,
    _Outptr_result_maybenull_ MI_Instance **extendedError)
{
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance* instance0;
    MI_Instance* instance1;
    MI_Char* keywords;
    const MI_Char* resourceId0;
    const MI_Char* resourceId1;
    MI_Uint32 i, j;
    
    if (extendedError == NULL)
    {        
        return MI_RESULT_INVALID_PARAMETER; 
    }
    *extendedError = NULL;	// Explicitly set *extendedError to NULL as _Outptr_ requires setting this at least once.	

    for (i = 0; i < instanceA->size; i++)
    {
        instance0 = instanceA->data[i];
        if (instance0->classDecl->superClass != NULL &&Tcscasecmp(instance0->classDecl->superClass, BASE_RESOURCE_CLASSNAME) == 0)
        {
            for (j = i + 1; j < instanceA->size; j++)
            {
                instance1 = instanceA->data[j];
                if (Tcscasecmp(instance0->classDecl->name, instance1->classDecl->name) == 0
                    && IsMatchedKeyProperties(instance0, instance1, &keywords, &miResult, extendedError))
                {
                    if (miResult != MI_RESULT_OK && *extendedError)
                    {
                        return miResult;
                    }

                    resourceId0 = GetResourceId(instance0);
                    resourceId1 = GetResourceId(instance1);
                    if (resourceId0 == NULL || resourceId1 == NULL)
                    {
                        miResult = CreateMemoryError(extendedError);
                        DSC_free(keywords);
                        return miResult;
                    }

                    miResult = GetCimMIError4Params(MI_RESULT_ALREADY_EXISTS, extendedError, ID_CA_DUPLICATE_KEYS, instance0->classDecl->name, resourceId0, resourceId1, keywords);
                    if (keywords)
                    {
                        DSC_free(keywords);
                    }

                    return miResult;
                }
                else if (miResult != MI_RESULT_OK)
                {
                    return miResult;
                }
            }
        }
    }

    return MI_RESULT_OK;
}

