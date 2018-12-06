/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "MSFT_nxNopResource.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

static MI_CONST MI_QualifierDecl ClassVersion_qual_decl =
{
    MI_T("ClassVersion"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl FriendlyName_qual_decl =
{
    MI_T("FriendlyName"), /* name */
    MI_STRING, /* type */
    MI_FLAG_CLASS, /* scope */
    MI_FLAG_ENABLEOVERRIDE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean InventoryFilter_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl InventoryFilter_qual_decl =
{
    MI_T("InventoryFilter"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE, /* flavor */
    0, /* subscript */
    &InventoryFilter_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Stream_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Stream_qual_decl =
{
    MI_T("Stream"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Stream_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean SupportsInventory_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl SupportsInventory_qual_decl =
{
    MI_T("SupportsInventory"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS, /* scope */
    MI_FLAG_ENABLEOVERRIDE, /* flavor */
    0, /* subscript */
    &SupportsInventory_qual_decl_value, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &ClassVersion_qual_decl,
    &FriendlyName_qual_decl,
    &InventoryFilter_qual_decl,
    &Stream_qual_decl,
    &SupportsInventory_qual_decl,
};

/*
**==============================================================================
**
** OMI_BaseResource
**
**==============================================================================
*/

static MI_CONST MI_Boolean OMI_BaseResource_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_BaseResource_Abstract_qual_value
};

static MI_CONST MI_Char* OMI_BaseResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier OMI_BaseResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_BaseResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* OMI_BaseResource_Description_qual_value = MI_T("1");

static MI_CONST MI_Qualifier OMI_BaseResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_quals[] =
{
    &OMI_BaseResource_Abstract_qual,
    &OMI_BaseResource_ClassVersion_qual,
    &OMI_BaseResource_Description_qual,
};

/* class OMI_BaseResource */
MI_CONST MI_ClassDecl OMI_BaseResource_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006F6510, /* code */
    MI_T("OMI_BaseResource"), /* name */
    OMI_BaseResource_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_quals), /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(OMI_BaseResource), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** MSFT_nxNopResource
**
**==============================================================================
*/

/* property MSFT_nxNopResource.Name */
static MI_CONST MI_PropertyDecl MSFT_nxNopResource_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource, Name), /* offset */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    NULL,
};

/* property MSFT_nxNopResource.Value */
static MI_CONST MI_PropertyDecl MSFT_nxNopResource_Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766505, /* code */
    MI_T("Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource, Value), /* offset */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    NULL,
};

/* property MSFT_nxNopResource.Ensure */
static MI_CONST MI_PropertyDecl MSFT_nxNopResource_Ensure_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656506, /* code */
    MI_T("Ensure"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource, Ensure), /* offset */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_nxNopResource_props[] =
{
    &MSFT_nxNopResource_Name_prop,
    &MSFT_nxNopResource_Value_prop,
    &MSFT_nxNopResource_Ensure_prop,
};

static MI_CONST MI_Char* MSFT_nxNopResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxNopResource");

static MI_CONST MI_Qualifier MSFT_nxNopResource_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &MSFT_nxNopResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxNopResource_GetTargetResource_InputResource_quals[] =
{
    &MSFT_nxNopResource_GetTargetResource_InputResource_EmbeddedInstance_qual,
};

/* parameter MSFT_nxNopResource.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxNopResource_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxNopResource_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxNopResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_GetTargetResource, InputResource), /* offset */
};

/* parameter MSFT_nxNopResource.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Char* MSFT_nxNopResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxNopResource");

static MI_CONST MI_Qualifier MSFT_nxNopResource_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &MSFT_nxNopResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxNopResource_GetTargetResource_OutputResource_quals[] =
{
    &MSFT_nxNopResource_GetTargetResource_OutputResource_EmbeddedInstance_qual,
};

/* parameter MSFT_nxNopResource.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    MSFT_nxNopResource_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxNopResource_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxNopResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_GetTargetResource, OutputResource), /* offset */
};

/* parameter MSFT_nxNopResource.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxNopResource_GetTargetResource_params[] =
{
    &MSFT_nxNopResource_GetTargetResource_MIReturn_param,
    &MSFT_nxNopResource_GetTargetResource_InputResource_param,
    &MSFT_nxNopResource_GetTargetResource_Flags_param,
    &MSFT_nxNopResource_GetTargetResource_OutputResource_param,
};

/* method MSFT_nxNopResource.GetTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxNopResource_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_nxNopResource_GetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxNopResource_GetTargetResource_params), /* numParameters */
    sizeof(MSFT_nxNopResource_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxNopResource_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Char* MSFT_nxNopResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxNopResource");

static MI_CONST MI_Qualifier MSFT_nxNopResource_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &MSFT_nxNopResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxNopResource_TestTargetResource_InputResource_quals[] =
{
    &MSFT_nxNopResource_TestTargetResource_InputResource_EmbeddedInstance_qual,
};

/* parameter MSFT_nxNopResource.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxNopResource_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxNopResource_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxNopResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_TestTargetResource, InputResource), /* offset */
};

/* parameter MSFT_nxNopResource.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_TestTargetResource, Flags), /* offset */
};

/* parameter MSFT_nxNopResource.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_TestTargetResource, Result), /* offset */
};

/* parameter MSFT_nxNopResource.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_TestTargetResource, ProviderContext), /* offset */
};

/* parameter MSFT_nxNopResource.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxNopResource_TestTargetResource_params[] =
{
    &MSFT_nxNopResource_TestTargetResource_MIReturn_param,
    &MSFT_nxNopResource_TestTargetResource_InputResource_param,
    &MSFT_nxNopResource_TestTargetResource_Flags_param,
    &MSFT_nxNopResource_TestTargetResource_Result_param,
    &MSFT_nxNopResource_TestTargetResource_ProviderContext_param,
};

/* method MSFT_nxNopResource.TestTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxNopResource_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_nxNopResource_TestTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxNopResource_TestTargetResource_params), /* numParameters */
    sizeof(MSFT_nxNopResource_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxNopResource_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Char* MSFT_nxNopResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxNopResource");

static MI_CONST MI_Qualifier MSFT_nxNopResource_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &MSFT_nxNopResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxNopResource_SetTargetResource_InputResource_quals[] =
{
    &MSFT_nxNopResource_SetTargetResource_InputResource_EmbeddedInstance_qual,
};

/* parameter MSFT_nxNopResource.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxNopResource_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxNopResource_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxNopResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_SetTargetResource, InputResource), /* offset */
};

/* parameter MSFT_nxNopResource.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_SetTargetResource, ProviderContext), /* offset */
};

/* parameter MSFT_nxNopResource.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_SetTargetResource, Flags), /* offset */
};

/* parameter MSFT_nxNopResource.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxNopResource_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxNopResource_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxNopResource_SetTargetResource_params[] =
{
    &MSFT_nxNopResource_SetTargetResource_MIReturn_param,
    &MSFT_nxNopResource_SetTargetResource_InputResource_param,
    &MSFT_nxNopResource_SetTargetResource_ProviderContext_param,
    &MSFT_nxNopResource_SetTargetResource_Flags_param,
};

/* method MSFT_nxNopResource.SetTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxNopResource_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_nxNopResource_SetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxNopResource_SetTargetResource_params), /* numParameters */
    sizeof(MSFT_nxNopResource_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxNopResource"), /* origin */
    MI_T("MSFT_nxNopResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxNopResource_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_nxNopResource_meths[] =
{
    &MSFT_nxNopResource_GetTargetResource_rtti,
    &MSFT_nxNopResource_TestTargetResource_rtti,
    &MSFT_nxNopResource_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT MSFT_nxNopResource_funcs =
{
  (MI_ProviderFT_Load)MSFT_nxNopResource_Load,
  (MI_ProviderFT_Unload)MSFT_nxNopResource_Unload,
  (MI_ProviderFT_GetInstance)MSFT_nxNopResource_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_nxNopResource_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_nxNopResource_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_nxNopResource_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_nxNopResource_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MSFT_nxNopResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_nxNopResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_nxNopResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_nxNopResource_FriendlyName_qual_value = MI_T("nxNop");

static MI_CONST MI_Qualifier MSFT_nxNopResource_FriendlyName_qual =
{
    MI_T("FriendlyName"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE,
    &MSFT_nxNopResource_FriendlyName_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxNopResource_quals[] =
{
    &MSFT_nxNopResource_ClassVersion_qual,
    &MSFT_nxNopResource_FriendlyName_qual,
};

/* class MSFT_nxNopResource */
MI_CONST MI_ClassDecl MSFT_nxNopResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6512, /* code */
    MI_T("MSFT_nxNopResource"), /* name */
    MSFT_nxNopResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxNopResource_quals), /* numQualifiers */
    MSFT_nxNopResource_props, /* properties */
    MI_COUNT(MSFT_nxNopResource_props), /* numProperties */
    sizeof(MSFT_nxNopResource), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    MSFT_nxNopResource_meths, /* methods */
    MI_COUNT(MSFT_nxNopResource_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_nxNopResource_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &MSFT_nxNopResource_rtti,
    &OMI_BaseResource_rtti,
};

MI_SchemaDecl schemaDecl =
{
    qualifierDecls, /* qualifierDecls */
    MI_COUNT(qualifierDecls), /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

/*
**==============================================================================
**
** MI_Server Methods
**
**==============================================================================
*/

MI_Result MI_CALL MI_Server_GetVersion(
    MI_Uint32* version){
    return __mi_server->serverFT->GetVersion(version);
}

MI_Result MI_CALL MI_Server_GetSystemName(
    const MI_Char** systemName)
{
    return __mi_server->serverFT->GetSystemName(systemName);
}

