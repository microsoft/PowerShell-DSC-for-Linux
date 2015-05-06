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
#include "omi_msft_dsclocalconfigurationmanager.h"
#include "MSFT_DSCMetaConfiguration.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

MI_EXTERN_C MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

static MI_CONST MI_Boolean Abstract_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Abstract_qual_decl =
{
    MI_T("Abstract"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    &Abstract_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Aggregate_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Aggregate_qual_decl =
{
    MI_T("Aggregate"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Aggregate_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Aggregation_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Aggregation_qual_decl =
{
    MI_T("Aggregation"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Aggregation_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Alias_qual_decl =
{
    MI_T("Alias"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Char* ArrayType_qual_decl_value = MI_T("Bag");

static MI_CONST MI_QualifierDecl ArrayType_qual_decl =
{
    MI_T("ArrayType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &ArrayType_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Association_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Association_qual_decl =
{
    MI_T("Association"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Association_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl BitMap_qual_decl =
{
    MI_T("BitMap"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl BitValues_qual_decl =
{
    MI_T("BitValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ClassConstraint_qual_decl =
{
    MI_T("ClassConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ClassVersion_qual_decl =
{
    MI_T("ClassVersion"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Composition_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Composition_qual_decl =
{
    MI_T("Composition"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Composition_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Correlatable_qual_decl =
{
    MI_T("Correlatable"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Counter_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Counter_qual_decl =
{
    MI_T("Counter"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Counter_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Delete_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Delete_qual_decl =
{
    MI_T("Delete"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Delete_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Deprecated_qual_decl =
{
    MI_T("Deprecated"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Description_qual_decl =
{
    MI_T("Description"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl DisplayDescription_qual_decl =
{
    MI_T("DisplayDescription"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl DisplayName_qual_decl =
{
    MI_T("DisplayName"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean DN_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl DN_qual_decl =
{
    MI_T("DN"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &DN_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl EmbeddedInstance_qual_decl =
{
    MI_T("EmbeddedInstance"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean EmbeddedObject_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl EmbeddedObject_qual_decl =
{
    MI_T("EmbeddedObject"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &EmbeddedObject_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Exception_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Exception_qual_decl =
{
    MI_T("Exception"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Exception_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Expensive_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Expensive_qual_decl =
{
    MI_T("Expensive"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Expensive_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Experimental_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Experimental_qual_decl =
{
    MI_T("Experimental"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    &Experimental_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Gauge_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Gauge_qual_decl =
{
    MI_T("Gauge"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Gauge_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Ifdeleted_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Ifdeleted_qual_decl =
{
    MI_T("Ifdeleted"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Ifdeleted_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean In_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl In_qual_decl =
{
    MI_T("In"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &In_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Indication_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Indication_qual_decl =
{
    MI_T("Indication"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Indication_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Invisible_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Invisible_qual_decl =
{
    MI_T("Invisible"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Invisible_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean IsPUnit_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl IsPUnit_qual_decl =
{
    MI_T("IsPUnit"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &IsPUnit_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Key_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Key_qual_decl =
{
    MI_T("Key"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Key_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Large_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Large_qual_decl =
{
    MI_T("Large"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_CLASS|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Large_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MappingStrings_qual_decl =
{
    MI_T("MappingStrings"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Max_qual_decl =
{
    MI_T("Max"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxLen_qual_decl =
{
    MI_T("MaxLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MaxValue_qual_decl =
{
    MI_T("MaxValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl MethodConstraint_qual_decl =
{
    MI_T("MethodConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Uint32 Min_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl Min_qual_decl =
{
    MI_T("Min"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Min_qual_decl_value, /* value */
};

static MI_CONST MI_Uint32 MinLen_qual_decl_value = 0U;

static MI_CONST MI_QualifierDecl MinLen_qual_decl =
{
    MI_T("MinLen"), /* name */
    MI_UINT32, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &MinLen_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl MinValue_qual_decl =
{
    MI_T("MinValue"), /* name */
    MI_SINT64, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ModelCorrespondence_qual_decl =
{
    MI_T("ModelCorrespondence"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Nonlocal_qual_decl =
{
    MI_T("Nonlocal"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl NonlocalType_qual_decl =
{
    MI_T("NonlocalType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl NullValue_qual_decl =
{
    MI_T("NullValue"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Octetstring_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Octetstring_qual_decl =
{
    MI_T("Octetstring"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Octetstring_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Out_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Out_qual_decl =
{
    MI_T("Out"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PARAMETER, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Out_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Override_qual_decl =
{
    MI_T("Override"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Propagated_qual_decl =
{
    MI_T("Propagated"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl PropertyConstraint_qual_decl =
{
    MI_T("PropertyConstraint"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Char* PropertyUsage_qual_decl_value = MI_T("CurrentContext");

static MI_CONST MI_QualifierDecl PropertyUsage_qual_decl =
{
    MI_T("PropertyUsage"), /* name */
    MI_STRING, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &PropertyUsage_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Provider_qual_decl =
{
    MI_T("Provider"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl PUnit_qual_decl =
{
    MI_T("PUnit"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Read_qual_decl_value = 1;

static MI_CONST MI_QualifierDecl Read_qual_decl =
{
    MI_T("Read"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Read_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Required_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Required_qual_decl =
{
    MI_T("Required"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Required_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl Revision_qual_decl =
{
    MI_T("Revision"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Schema_qual_decl =
{
    MI_T("Schema"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Source_qual_decl =
{
    MI_T("Source"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SourceType_qual_decl =
{
    MI_T("SourceType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Static_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Static_qual_decl =
{
    MI_T("Static"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_METHOD|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Static_qual_decl_value, /* value */
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

static MI_CONST MI_QualifierDecl Syntax_qual_decl =
{
    MI_T("Syntax"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl SyntaxType_qual_decl =
{
    MI_T("SyntaxType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Terminal_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Terminal_qual_decl =
{
    MI_T("Terminal"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Terminal_qual_decl_value, /* value */
};

static MI_CONST MI_QualifierDecl TriggerType_qual_decl =
{
    MI_T("TriggerType"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_METHOD|MI_FLAG_PROPERTY|MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UMLPackagePath_qual_decl =
{
    MI_T("UMLPackagePath"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Units_qual_decl =
{
    MI_T("Units"), /* name */
    MI_STRING, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UnknownValues_qual_decl =
{
    MI_T("UnknownValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl UnsupportedValues_qual_decl =
{
    MI_T("UnsupportedValues"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl ValueMap_qual_decl =
{
    MI_T("ValueMap"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Values_qual_decl =
{
    MI_T("Values"), /* name */
    MI_STRINGA, /* type */
    MI_FLAG_METHOD|MI_FLAG_PARAMETER|MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_QualifierDecl Version_qual_decl =
{
    MI_T("Version"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_CONST MI_Boolean Weak_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Weak_qual_decl =
{
    MI_T("Weak"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_REFERENCE, /* scope */
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Weak_qual_decl_value, /* value */
};

static MI_CONST MI_Boolean Write_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Write_qual_decl =
{
    MI_T("Write"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PROPERTY, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS, /* flavor */
    0, /* subscript */
    &Write_qual_decl_value, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &Abstract_qual_decl,
    &Aggregate_qual_decl,
    &Aggregation_qual_decl,
    &Alias_qual_decl,
    &ArrayType_qual_decl,
    &Association_qual_decl,
    &BitMap_qual_decl,
    &BitValues_qual_decl,
    &ClassConstraint_qual_decl,
    &ClassVersion_qual_decl,
    &Composition_qual_decl,
    &Correlatable_qual_decl,
    &Counter_qual_decl,
    &Delete_qual_decl,
    &Deprecated_qual_decl,
    &Description_qual_decl,
    &DisplayDescription_qual_decl,
    &DisplayName_qual_decl,
    &DN_qual_decl,
    &EmbeddedInstance_qual_decl,
    &EmbeddedObject_qual_decl,
    &Exception_qual_decl,
    &Expensive_qual_decl,
    &Experimental_qual_decl,
    &Gauge_qual_decl,
    &Ifdeleted_qual_decl,
    &In_qual_decl,
    &Indication_qual_decl,
    &Invisible_qual_decl,
    &IsPUnit_qual_decl,
    &Key_qual_decl,
    &Large_qual_decl,
    &MappingStrings_qual_decl,
    &Max_qual_decl,
    &MaxLen_qual_decl,
    &MaxValue_qual_decl,
    &MethodConstraint_qual_decl,
    &Min_qual_decl,
    &MinLen_qual_decl,
    &MinValue_qual_decl,
    &ModelCorrespondence_qual_decl,
    &Nonlocal_qual_decl,
    &NonlocalType_qual_decl,
    &NullValue_qual_decl,
    &Octetstring_qual_decl,
    &Out_qual_decl,
    &Override_qual_decl,
    &Propagated_qual_decl,
    &PropertyConstraint_qual_decl,
    &PropertyUsage_qual_decl,
    &Provider_qual_decl,
    &PUnit_qual_decl,
    &Read_qual_decl,
    &Required_qual_decl,
    &Revision_qual_decl,
    &Schema_qual_decl,
    &Source_qual_decl,
    &SourceType_qual_decl,
    &Static_qual_decl,
    &Stream_qual_decl,
    &Syntax_qual_decl,
    &SyntaxType_qual_decl,
    &Terminal_qual_decl,
    &TriggerType_qual_decl,
    &UMLPackagePath_qual_decl,
    &Units_qual_decl,
    &UnknownValues_qual_decl,
    &UnsupportedValues_qual_decl,
    &ValueMap_qual_decl,
    &Values_qual_decl,
    &Version_qual_decl,
    &Weak_qual_decl,
    &Write_qual_decl,
};

/*
**==============================================================================
**
** OMI_BaseResource
**
**==============================================================================
*/

static MI_CONST MI_Char* OMI_BaseResource_ResourceId_Description_qual_value = MI_T("533");

static MI_CONST MI_Qualifier OMI_BaseResource_ResourceId_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_ResourceId_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_ResourceId_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_ResourceId_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_ResourceId_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_ResourceId_quals[] =
{
    &OMI_BaseResource_ResourceId_Description_qual,
    &OMI_BaseResource_ResourceId_Required_qual,
};

/* property OMI_BaseResource.ResourceId */
static MI_CONST MI_PropertyDecl OMI_BaseResource_ResourceId_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x0072640A, /* code */
    MI_T("ResourceId"), /* name */
    OMI_BaseResource_ResourceId_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_ResourceId_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, ResourceId), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_BaseResource_SourceInfo_Description_qual_value = MI_T("534");

static MI_CONST MI_Qualifier OMI_BaseResource_SourceInfo_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_SourceInfo_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_SourceInfo_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_SourceInfo_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_SourceInfo_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_SourceInfo_quals[] =
{
    &OMI_BaseResource_SourceInfo_Description_qual,
    &OMI_BaseResource_SourceInfo_Write_qual,
};

/* property OMI_BaseResource.SourceInfo */
static MI_CONST MI_PropertyDecl OMI_BaseResource_SourceInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736F0A, /* code */
    MI_T("SourceInfo"), /* name */
    OMI_BaseResource_SourceInfo_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_SourceInfo_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, SourceInfo), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_BaseResource_DependsOn_Description_qual_value = MI_T("535");

static MI_CONST MI_Qualifier OMI_BaseResource_DependsOn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_DependsOn_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_DependsOn_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_DependsOn_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_DependsOn_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_DependsOn_quals[] =
{
    &OMI_BaseResource_DependsOn_Description_qual,
    &OMI_BaseResource_DependsOn_Write_qual,
};

/* property OMI_BaseResource.DependsOn */
static MI_CONST MI_PropertyDecl OMI_BaseResource_DependsOn_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E09, /* code */
    MI_T("DependsOn"), /* name */
    OMI_BaseResource_DependsOn_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_DependsOn_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, DependsOn), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_BaseResource_ModuleName_Description_qual_value = MI_T("536");

static MI_CONST MI_Qualifier OMI_BaseResource_ModuleName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_ModuleName_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_ModuleName_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_ModuleName_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_ModuleName_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_ModuleName_quals[] =
{
    &OMI_BaseResource_ModuleName_Description_qual,
    &OMI_BaseResource_ModuleName_Required_qual,
};

/* property OMI_BaseResource.ModuleName */
static MI_CONST MI_PropertyDecl OMI_BaseResource_ModuleName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D650A, /* code */
    MI_T("ModuleName"), /* name */
    OMI_BaseResource_ModuleName_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_ModuleName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, ModuleName), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_BaseResource_ModuleVersion_Description_qual_value = MI_T("537");

static MI_CONST MI_Qualifier OMI_BaseResource_ModuleVersion_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_ModuleVersion_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_ModuleVersion_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_ModuleVersion_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_ModuleVersion_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_ModuleVersion_quals[] =
{
    &OMI_BaseResource_ModuleVersion_Description_qual,
    &OMI_BaseResource_ModuleVersion_Required_qual,
};

/* property OMI_BaseResource.ModuleVersion */
static MI_CONST MI_PropertyDecl OMI_BaseResource_ModuleVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D6E0D, /* code */
    MI_T("ModuleVersion"), /* name */
    OMI_BaseResource_ModuleVersion_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_ModuleVersion_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, ModuleVersion), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_BaseResource_ConfigurationName_Description_qual_value = MI_T("538");

static MI_CONST MI_Qualifier OMI_BaseResource_ConfigurationName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_ConfigurationName_Description_qual_value
};

static MI_CONST MI_Boolean OMI_BaseResource_ConfigurationName_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_BaseResource_ConfigurationName_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_ConfigurationName_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_ConfigurationName_quals[] =
{
    &OMI_BaseResource_ConfigurationName_Description_qual,
    &OMI_BaseResource_ConfigurationName_Write_qual,
};

/* property OMI_BaseResource.ConfigurationName */
static MI_CONST MI_PropertyDecl OMI_BaseResource_ConfigurationName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636511, /* code */
    MI_T("ConfigurationName"), /* name */
    OMI_BaseResource_ConfigurationName_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_ConfigurationName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, ConfigurationName), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("OMI_BaseResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_BaseResource_props[] =
{
    &OMI_BaseResource_ResourceId_prop,
    &OMI_BaseResource_SourceInfo_prop,
    &OMI_BaseResource_DependsOn_prop,
    &OMI_BaseResource_ModuleName_prop,
    &OMI_BaseResource_ModuleVersion_prop,
    &OMI_BaseResource_ConfigurationName_prop,
};

static MI_CONST MI_Char* OMI_BaseResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier OMI_BaseResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_BaseResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* OMI_BaseResource_Description_qual_value = MI_T("19");

static MI_CONST MI_Qualifier OMI_BaseResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_quals[] =
{
    &OMI_BaseResource_ClassVersion_qual,
    &OMI_BaseResource_Description_qual,
};

/* class OMI_BaseResource */
MI_CONST MI_ClassDecl OMI_BaseResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F6510, /* code */
    MI_T("OMI_BaseResource"), /* name */
    OMI_BaseResource_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_quals), /* numQualifiers */
    OMI_BaseResource_props, /* properties */
    MI_COUNT(OMI_BaseResource_props), /* numProperties */
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
** MSFT_Credential
**
**==============================================================================
*/

static MI_CONST MI_Char* MSFT_Credential_UserName_Description_qual_value = MI_T("351");

static MI_CONST MI_Qualifier MSFT_Credential_UserName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_Credential_UserName_Description_qual_value
};

static MI_CONST MI_Uint32 MSFT_Credential_UserName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier MSFT_Credential_UserName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_Credential_UserName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_Credential_UserName_quals[] =
{
    &MSFT_Credential_UserName_Description_qual,
    &MSFT_Credential_UserName_MaxLen_qual,
};

/* property MSFT_Credential.UserName */
static MI_CONST MI_PropertyDecl MSFT_Credential_UserName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00756508, /* code */
    MI_T("UserName"), /* name */
    MSFT_Credential_UserName_quals, /* qualifiers */
    MI_COUNT(MSFT_Credential_UserName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Credential, UserName), /* offset */
    MI_T("MSFT_Credential"), /* origin */
    MI_T("MSFT_Credential"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_Credential_Password_Description_qual_value = MI_T("352");

static MI_CONST MI_Qualifier MSFT_Credential_Password_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_Credential_Password_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_Credential_Password_quals[] =
{
    &MSFT_Credential_Password_Description_qual,
};

/* property MSFT_Credential.Password */
static MI_CONST MI_PropertyDecl MSFT_Credential_Password_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00706408, /* code */
    MI_T("Password"), /* name */
    MSFT_Credential_Password_quals, /* qualifiers */
    MI_COUNT(MSFT_Credential_Password_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Credential, Password), /* offset */
    MI_T("MSFT_Credential"), /* origin */
    MI_T("MSFT_Credential"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Credential_props[] =
{
    &MSFT_Credential_UserName_prop,
    &MSFT_Credential_Password_prop,
};

static MI_CONST MI_Boolean MSFT_Credential_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_Credential_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_Credential_Abstract_qual_value
};

static MI_CONST MI_Char* MSFT_Credential_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_Credential_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_Credential_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_Credential_Description_qual_value = MI_T("353");

static MI_CONST MI_Qualifier MSFT_Credential_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_Credential_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_Credential_quals[] =
{
    &MSFT_Credential_Abstract_qual,
    &MSFT_Credential_ClassVersion_qual,
    &MSFT_Credential_Description_qual,
};

/* class MSFT_Credential */
MI_CONST MI_ClassDecl MSFT_Credential_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006D6C0F, /* code */
    MI_T("MSFT_Credential"), /* name */
    MSFT_Credential_quals, /* qualifiers */
    MI_COUNT(MSFT_Credential_quals), /* numQualifiers */
    MSFT_Credential_props, /* properties */
    MI_COUNT(MSFT_Credential_props), /* numProperties */
    sizeof(MSFT_Credential), /* size */
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
** MSFT_KeyValuePair
**
**==============================================================================
*/

static MI_CONST MI_Boolean MSFT_KeyValuePair_Key_Key_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_KeyValuePair_Key_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_KeyValuePair_Key_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_KeyValuePair_Key_quals[] =
{
    &MSFT_KeyValuePair_Key_Key_qual,
};

/* property MSFT_KeyValuePair.Key */
static MI_CONST MI_PropertyDecl MSFT_KeyValuePair_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    MSFT_KeyValuePair_Key_quals, /* qualifiers */
    MI_COUNT(MSFT_KeyValuePair_Key_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_KeyValuePair, Key), /* offset */
    MI_T("MSFT_KeyValuePair"), /* origin */
    MI_T("MSFT_KeyValuePair"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_KeyValuePair_Value_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_KeyValuePair_Value_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_KeyValuePair_Value_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_KeyValuePair_Value_quals[] =
{
    &MSFT_KeyValuePair_Value_Write_qual,
};

/* property MSFT_KeyValuePair.Value */
static MI_CONST MI_PropertyDecl MSFT_KeyValuePair_Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766505, /* code */
    MI_T("Value"), /* name */
    MSFT_KeyValuePair_Value_quals, /* qualifiers */
    MI_COUNT(MSFT_KeyValuePair_Value_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_KeyValuePair, Value), /* offset */
    MI_T("MSFT_KeyValuePair"), /* origin */
    MI_T("MSFT_KeyValuePair"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_KeyValuePair_props[] =
{
    &MSFT_KeyValuePair_Key_prop,
    &MSFT_KeyValuePair_Value_prop,
};

static MI_CONST MI_Boolean MSFT_KeyValuePair_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_KeyValuePair_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_KeyValuePair_Abstract_qual_value
};

static MI_CONST MI_Char* MSFT_KeyValuePair_Description_qual_value = MI_T("265");

static MI_CONST MI_Qualifier MSFT_KeyValuePair_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_KeyValuePair_Description_qual_value
};

static MI_CONST MI_Char* MSFT_KeyValuePair_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_KeyValuePair_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_KeyValuePair_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_KeyValuePair_quals[] =
{
    &MSFT_KeyValuePair_Abstract_qual,
    &MSFT_KeyValuePair_Description_qual,
    &MSFT_KeyValuePair_ClassVersion_qual,
};

/* class MSFT_KeyValuePair */
MI_CONST MI_ClassDecl MSFT_KeyValuePair_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006D7211, /* code */
    MI_T("MSFT_KeyValuePair"), /* name */
    MSFT_KeyValuePair_quals, /* qualifiers */
    MI_COUNT(MSFT_KeyValuePair_quals), /* numQualifiers */
    MSFT_KeyValuePair_props, /* properties */
    MI_COUNT(MSFT_KeyValuePair_props), /* numProperties */
    sizeof(MSFT_KeyValuePair), /* size */
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
** OMI_ConfigurationDownloadManager
**
**==============================================================================
*/

/* property OMI_ConfigurationDownloadManager.Name */
static MI_CONST MI_PropertyDecl OMI_ConfigurationDownloadManager_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_ConfigurationDownloadManager, Name), /* offset */
    MI_T("OMI_ConfigurationDownloadManager"), /* origin */
    MI_T("OMI_ConfigurationDownloadManager"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_ConfigurationDownloadManager_props[] =
{
    &OMI_ConfigurationDownloadManager_Name_prop,
};

static MI_CONST MI_Boolean OMI_ConfigurationDownloadManager_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier OMI_ConfigurationDownloadManager_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_ConfigurationDownloadManager_Abstract_qual_value
};

static MI_CONST MI_Char* OMI_ConfigurationDownloadManager_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier OMI_ConfigurationDownloadManager_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_ConfigurationDownloadManager_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_ConfigurationDownloadManager_quals[] =
{
    &OMI_ConfigurationDownloadManager_Abstract_qual,
    &OMI_ConfigurationDownloadManager_ClassVersion_qual,
};

/* class OMI_ConfigurationDownloadManager */
MI_CONST MI_ClassDecl OMI_ConfigurationDownloadManager_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006F7220, /* code */
    MI_T("OMI_ConfigurationDownloadManager"), /* name */
    OMI_ConfigurationDownloadManager_quals, /* qualifiers */
    MI_COUNT(OMI_ConfigurationDownloadManager_quals), /* numQualifiers */
    OMI_ConfigurationDownloadManager_props, /* properties */
    MI_COUNT(OMI_ConfigurationDownloadManager_props), /* numProperties */
    sizeof(OMI_ConfigurationDownloadManager), /* size */
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
** OMI_MetaConfigurationResource
**
**==============================================================================
*/

static MI_CONST MI_Boolean OMI_MetaConfigurationResource_ResourceId_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_ResourceId_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_MetaConfigurationResource_ResourceId_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_MetaConfigurationResource_ResourceId_quals[] =
{
    &OMI_MetaConfigurationResource_ResourceId_Required_qual,
};

/* property OMI_MetaConfigurationResource.ResourceId */
static MI_CONST MI_PropertyDecl OMI_MetaConfigurationResource_ResourceId_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x0072640A, /* code */
    MI_T("ResourceId"), /* name */
    OMI_MetaConfigurationResource_ResourceId_quals, /* qualifiers */
    MI_COUNT(OMI_MetaConfigurationResource_ResourceId_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_MetaConfigurationResource, ResourceId), /* offset */
    MI_T("OMI_MetaConfigurationResource"), /* origin */
    MI_T("OMI_MetaConfigurationResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_MetaConfigurationResource_SourceInfo_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_SourceInfo_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_MetaConfigurationResource_SourceInfo_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_MetaConfigurationResource_SourceInfo_quals[] =
{
    &OMI_MetaConfigurationResource_SourceInfo_Write_qual,
};

/* property OMI_MetaConfigurationResource.SourceInfo */
static MI_CONST MI_PropertyDecl OMI_MetaConfigurationResource_SourceInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736F0A, /* code */
    MI_T("SourceInfo"), /* name */
    OMI_MetaConfigurationResource_SourceInfo_quals, /* qualifiers */
    MI_COUNT(OMI_MetaConfigurationResource_SourceInfo_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_MetaConfigurationResource, SourceInfo), /* offset */
    MI_T("OMI_MetaConfigurationResource"), /* origin */
    MI_T("OMI_MetaConfigurationResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_MetaConfigurationResource_ModuleName_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_ModuleName_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_MetaConfigurationResource_ModuleName_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_MetaConfigurationResource_ModuleName_quals[] =
{
    &OMI_MetaConfigurationResource_ModuleName_Required_qual,
};

/* property OMI_MetaConfigurationResource.ModuleName */
static MI_CONST MI_PropertyDecl OMI_MetaConfigurationResource_ModuleName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D650A, /* code */
    MI_T("ModuleName"), /* name */
    OMI_MetaConfigurationResource_ModuleName_quals, /* qualifiers */
    MI_COUNT(OMI_MetaConfigurationResource_ModuleName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_MetaConfigurationResource, ModuleName), /* offset */
    MI_T("OMI_MetaConfigurationResource"), /* origin */
    MI_T("OMI_MetaConfigurationResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_MetaConfigurationResource_ModuleVersion_Required_qual_value = 1;

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_ModuleVersion_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_MetaConfigurationResource_ModuleVersion_Required_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_MetaConfigurationResource_ModuleVersion_quals[] =
{
    &OMI_MetaConfigurationResource_ModuleVersion_Required_qual,
};

/* property OMI_MetaConfigurationResource.ModuleVersion */
static MI_CONST MI_PropertyDecl OMI_MetaConfigurationResource_ModuleVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D6E0D, /* code */
    MI_T("ModuleVersion"), /* name */
    OMI_MetaConfigurationResource_ModuleVersion_quals, /* qualifiers */
    MI_COUNT(OMI_MetaConfigurationResource_ModuleVersion_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_MetaConfigurationResource, ModuleVersion), /* offset */
    MI_T("OMI_MetaConfigurationResource"), /* origin */
    MI_T("OMI_MetaConfigurationResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_MetaConfigurationResource_props[] =
{
    &OMI_MetaConfigurationResource_ResourceId_prop,
    &OMI_MetaConfigurationResource_SourceInfo_prop,
    &OMI_MetaConfigurationResource_ModuleName_prop,
    &OMI_MetaConfigurationResource_ModuleVersion_prop,
};

static MI_CONST MI_Boolean OMI_MetaConfigurationResource_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_MetaConfigurationResource_Abstract_qual_value
};

static MI_CONST MI_Char* OMI_MetaConfigurationResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_MetaConfigurationResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* OMI_MetaConfigurationResource_Description_qual_value = MI_T("539");

static MI_CONST MI_Qualifier OMI_MetaConfigurationResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_MetaConfigurationResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_MetaConfigurationResource_quals[] =
{
    &OMI_MetaConfigurationResource_Abstract_qual,
    &OMI_MetaConfigurationResource_ClassVersion_qual,
    &OMI_MetaConfigurationResource_Description_qual,
};

/* class OMI_MetaConfigurationResource */
MI_CONST MI_ClassDecl OMI_MetaConfigurationResource_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006F651D, /* code */
    MI_T("OMI_MetaConfigurationResource"), /* name */
    OMI_MetaConfigurationResource_quals, /* qualifiers */
    MI_COUNT(OMI_MetaConfigurationResource_quals), /* numQualifiers */
    OMI_MetaConfigurationResource_props, /* properties */
    MI_COUNT(OMI_MetaConfigurationResource_props), /* numProperties */
    sizeof(OMI_MetaConfigurationResource), /* size */
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
** MSFT_PartialConfiguration
**
**==============================================================================
*/

static MI_CONST MI_Char* MSFT_PartialConfiguration_Description_Description_qual_value = MI_T("517");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_Description_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_PartialConfiguration_Description_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_PartialConfiguration_Description_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_Description_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_PartialConfiguration_Description_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_PartialConfiguration_Description_quals[] =
{
    &MSFT_PartialConfiguration_Description_Description_qual,
    &MSFT_PartialConfiguration_Description_Write_qual,
};

/* property MSFT_PartialConfiguration.Description */
static MI_CONST MI_PropertyDecl MSFT_PartialConfiguration_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    MSFT_PartialConfiguration_Description_quals, /* qualifiers */
    MI_COUNT(MSFT_PartialConfiguration_Description_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_PartialConfiguration, Description), /* offset */
    MI_T("MSFT_PartialConfiguration"), /* origin */
    MI_T("MSFT_PartialConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_PartialConfiguration_ExclusiveResources_Description_qual_value = MI_T("518");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_ExclusiveResources_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_PartialConfiguration_ExclusiveResources_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_PartialConfiguration_ExclusiveResources_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_ExclusiveResources_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_PartialConfiguration_ExclusiveResources_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_PartialConfiguration_ExclusiveResources_quals[] =
{
    &MSFT_PartialConfiguration_ExclusiveResources_Description_qual,
    &MSFT_PartialConfiguration_ExclusiveResources_Write_qual,
};

/* property MSFT_PartialConfiguration.ExclusiveResources */
static MI_CONST MI_PropertyDecl MSFT_PartialConfiguration_ExclusiveResources_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657312, /* code */
    MI_T("ExclusiveResources"), /* name */
    MSFT_PartialConfiguration_ExclusiveResources_quals, /* qualifiers */
    MI_COUNT(MSFT_PartialConfiguration_ExclusiveResources_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_PartialConfiguration, ExclusiveResources), /* offset */
    MI_T("MSFT_PartialConfiguration"), /* origin */
    MI_T("MSFT_PartialConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_PartialConfiguration_ConfigurationSource_Description_qual_value = MI_T("519");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_ConfigurationSource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_PartialConfiguration_ConfigurationSource_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_PartialConfiguration_ConfigurationSource_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_ConfigurationSource_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_PartialConfiguration_ConfigurationSource_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_PartialConfiguration_ConfigurationSource_quals[] =
{
    &MSFT_PartialConfiguration_ConfigurationSource_Description_qual,
    &MSFT_PartialConfiguration_ConfigurationSource_Write_qual,
};

/* property MSFT_PartialConfiguration.ConfigurationSource */
static MI_CONST MI_PropertyDecl MSFT_PartialConfiguration_ConfigurationSource_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636513, /* code */
    MI_T("ConfigurationSource"), /* name */
    MSFT_PartialConfiguration_ConfigurationSource_quals, /* qualifiers */
    MI_COUNT(MSFT_PartialConfiguration_ConfigurationSource_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_PartialConfiguration, ConfigurationSource), /* offset */
    MI_T("MSFT_PartialConfiguration"), /* origin */
    MI_T("MSFT_PartialConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_PartialConfiguration_DependsOn_Description_qual_value = MI_T("521");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_DependsOn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_PartialConfiguration_DependsOn_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_PartialConfiguration_DependsOn_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_DependsOn_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_PartialConfiguration_DependsOn_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_PartialConfiguration_DependsOn_quals[] =
{
    &MSFT_PartialConfiguration_DependsOn_Description_qual,
    &MSFT_PartialConfiguration_DependsOn_Write_qual,
};

/* property MSFT_PartialConfiguration.DependsOn */
static MI_CONST MI_PropertyDecl MSFT_PartialConfiguration_DependsOn_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E09, /* code */
    MI_T("DependsOn"), /* name */
    MSFT_PartialConfiguration_DependsOn_quals, /* qualifiers */
    MI_COUNT(MSFT_PartialConfiguration_DependsOn_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_PartialConfiguration, DependsOn), /* offset */
    MI_T("MSFT_PartialConfiguration"), /* origin */
    MI_T("MSFT_PartialConfiguration"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_PartialConfiguration_props[] =
{
    &OMI_MetaConfigurationResource_ResourceId_prop,
    &OMI_MetaConfigurationResource_SourceInfo_prop,
    &OMI_MetaConfigurationResource_ModuleName_prop,
    &OMI_MetaConfigurationResource_ModuleVersion_prop,
    &MSFT_PartialConfiguration_Description_prop,
    &MSFT_PartialConfiguration_ExclusiveResources_prop,
    &MSFT_PartialConfiguration_ConfigurationSource_prop,
    &MSFT_PartialConfiguration_DependsOn_prop,
};

static MI_CONST MI_Char* MSFT_PartialConfiguration_Description_qual_value = MI_T("522");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_PartialConfiguration_Description_qual_value
};

static MI_CONST MI_Char* MSFT_PartialConfiguration_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_PartialConfiguration_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_PartialConfiguration_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_PartialConfiguration_quals[] =
{
    &MSFT_PartialConfiguration_Description_qual,
    &MSFT_PartialConfiguration_ClassVersion_qual,
};

/* class MSFT_PartialConfiguration */
MI_CONST MI_ClassDecl MSFT_PartialConfiguration_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6E19, /* code */
    MI_T("MSFT_PartialConfiguration"), /* name */
    MSFT_PartialConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_PartialConfiguration_quals), /* numQualifiers */
    MSFT_PartialConfiguration_props, /* properties */
    MI_COUNT(MSFT_PartialConfiguration_props), /* numProperties */
    sizeof(MSFT_PartialConfiguration), /* size */
    MI_T("OMI_MetaConfigurationResource"), /* superClass */
    &OMI_MetaConfigurationResource_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** MSFT_DSCMetaConfiguration
**
**==============================================================================
*/

/* property MSFT_DSCMetaConfiguration.ConfigurationModeFrequencyMins */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063731E, /* code */
    MI_T("ConfigurationModeFrequencyMins"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationModeFrequencyMins), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_value = 0;

/* property MSFT_DSCMetaConfiguration.RebootNodeIfNeeded */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00726412, /* code */
    MI_T("RebootNodeIfNeeded"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, RebootNodeIfNeeded), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    &MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_value,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_data_value[] =
{
    MI_T("ApplyOnly"),
    MI_T("ApplyAndMonitor"),
    MI_T("ApplyAndAutoCorrect"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_value =
{
    MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual_data_value[] =
{
    MI_T("358"),
    MI_T("359"),
    MI_T("360"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual_value =
{
    MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_ConfigurationMode_quals[] =
{
    &MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual,
    &MSFT_DSCMetaConfiguration_ConfigurationMode_Values_qual,
};

/* property MSFT_DSCMetaConfiguration.ConfigurationMode */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationMode_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00636511, /* code */
    MI_T("ConfigurationMode"), /* name */
    MSFT_DSCMetaConfiguration_ConfigurationMode_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationMode_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationMode), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_Credential_EmbeddedInstance_qual_value = MI_T("MSFT_Credential");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_Credential_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_Credential_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_Credential_quals[] =
{
    &MSFT_DSCMetaConfiguration_Credential_EmbeddedInstance_qual,
};

/* property MSFT_DSCMetaConfiguration.Credential */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_Credential_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00636C0A, /* code */
    MI_T("Credential"), /* name */
    MSFT_DSCMetaConfiguration_Credential_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_Credential_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Credential"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, Credential), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual_data_value[] =
{
    MI_T("Push"),
    MI_T("Pull"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual_value =
{
    MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_RefreshMode_Values_qual_data_value[] =
{
    MI_T("411"),
    MI_T("412"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_RefreshMode_Values_qual_value =
{
    MSFT_DSCMetaConfiguration_RefreshMode_Values_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_RefreshMode_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_RefreshMode_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_RefreshMode_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_RefreshMode_quals[] =
{
    &MSFT_DSCMetaConfiguration_RefreshMode_ValueMap_qual,
    &MSFT_DSCMetaConfiguration_RefreshMode_Values_qual,
};

/* property MSFT_DSCMetaConfiguration.RefreshMode */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_RefreshMode_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0072650B, /* code */
    MI_T("RefreshMode"), /* name */
    MSFT_DSCMetaConfiguration_RefreshMode_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_RefreshMode_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, RefreshMode), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

/* property MSFT_DSCMetaConfiguration.CertificateID */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_CertificateID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063640D, /* code */
    MI_T("CertificateID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, CertificateID), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

/* property MSFT_DSCMetaConfiguration.ConfigurationID */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063640F, /* code */
    MI_T("ConfigurationID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationID), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

/* property MSFT_DSCMetaConfiguration.DownloadManagerName */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_DownloadManagerName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00646513, /* code */
    MI_T("DownloadManagerName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, DownloadManagerName), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_DownloadManagerCustomData_EmbeddedInstance_qual_value = MI_T("MSFT_KeyValuePair");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_DownloadManagerCustomData_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_DownloadManagerCustomData_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_DownloadManagerCustomData_quals[] =
{
    &MSFT_DSCMetaConfiguration_DownloadManagerCustomData_EmbeddedInstance_qual,
};

/* property MSFT_DSCMetaConfiguration.DownloadManagerCustomData */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_DownloadManagerCustomData_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00646119, /* code */
    MI_T("DownloadManagerCustomData"), /* name */
    MSFT_DSCMetaConfiguration_DownloadManagerCustomData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_DownloadManagerCustomData_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_KeyValuePair"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, DownloadManagerCustomData), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

/* property MSFT_DSCMetaConfiguration.RefreshFrequencyMins */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_RefreshFrequencyMins_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00727314, /* code */
    MI_T("RefreshFrequencyMins"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, RefreshFrequencyMins), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

/* property MSFT_DSCMetaConfiguration.AllowModuleOverwrite */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_AllowModuleOverwrite_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00616514, /* code */
    MI_T("AllowModuleOverwrite"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, AllowModuleOverwrite), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_Description_qual_value = MI_T("492");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_Description_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_EmbeddedInstance_qual_value = MI_T("OMI_ConfigurationDownloadManager");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_quals[] =
{
    &MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_Description_qual,
    &MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_EmbeddedInstance_qual,
};

/* property MSFT_DSCMetaConfiguration.ConfigurationDownloadManagers */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063731D, /* code */
    MI_T("ConfigurationDownloadManagers"), /* name */
    MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("OMI_ConfigurationDownloadManager"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationDownloadManagers), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual_data_value[] =
{
    MI_T("Ready"),
    MI_T("Busy"),
    MI_T("PendingReboot"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual_value =
{
    MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual_data_value[] =
{
    MI_T("856"),
    MI_T("422"),
    MI_T("425"),
};

static MI_CONST MI_ConstStringA MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual_value =
{
    MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual_data_value,
    MI_COUNT(MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_quals[] =
{
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Read_qual,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_ValueMap_qual,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Values_qual,
};

/* property MSFT_DSCMetaConfiguration.LocalConfigurationManagerState */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006C651E, /* code */
    MI_T("LocalConfigurationManagerState"), /* name */
    MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, LocalConfigurationManagerState), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_PartialConfigurations_EmbeddedInstance_qual_value = MI_T("MSFT_PartialConfiguration");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_PartialConfigurations_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCMetaConfiguration_PartialConfigurations_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_PartialConfigurations_quals[] =
{
    &MSFT_DSCMetaConfiguration_PartialConfigurations_EmbeddedInstance_qual,
};

/* property MSFT_DSCMetaConfiguration.PartialConfigurations */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_PartialConfigurations_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00707315, /* code */
    MI_T("PartialConfigurations"), /* name */
    MSFT_DSCMetaConfiguration_PartialConfigurations_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_PartialConfigurations_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_PartialConfiguration"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, PartialConfigurations), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_props[] =
{
    &MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_prop,
    &MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_prop,
    &MSFT_DSCMetaConfiguration_ConfigurationMode_prop,
    &MSFT_DSCMetaConfiguration_Credential_prop,
    &MSFT_DSCMetaConfiguration_RefreshMode_prop,
    &MSFT_DSCMetaConfiguration_CertificateID_prop,
    &MSFT_DSCMetaConfiguration_ConfigurationID_prop,
    &MSFT_DSCMetaConfiguration_DownloadManagerName_prop,
    &MSFT_DSCMetaConfiguration_DownloadManagerCustomData_prop,
    &MSFT_DSCMetaConfiguration_RefreshFrequencyMins_prop,
    &MSFT_DSCMetaConfiguration_AllowModuleOverwrite_prop,
    &MSFT_DSCMetaConfiguration_ConfigurationDownloadManagers_prop,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_prop,
    &MSFT_DSCMetaConfiguration_PartialConfigurations_prop,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCMetaConfiguration_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_quals[] =
{
    &MSFT_DSCMetaConfiguration_ClassVersion_qual,
};

/* class MSFT_DSCMetaConfiguration */
MI_CONST MI_ClassDecl MSFT_DSCMetaConfiguration_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6E19, /* code */
    MI_T("MSFT_DSCMetaConfiguration"), /* name */
    MSFT_DSCMetaConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_quals), /* numQualifiers */
    MSFT_DSCMetaConfiguration_props, /* properties */
    MI_COUNT(MSFT_DSCMetaConfiguration_props), /* numProperties */
    sizeof(MSFT_DSCMetaConfiguration), /* size */
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
** MSFT_DSCLocalConfigurationManager
**
**==============================================================================
*/


static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendConfiguration_Description_qual_value = MI_T("308");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_In_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_In_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_Octetstring_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfiguration(): ConfigurationData */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636111, /* code */
    MI_T("ConfigurationData"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfiguration, ConfigurationData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfiguration_force_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_force_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_force_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfiguration_force_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_force_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfiguration(): force */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfiguration_force_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666505, /* code */
    MI_T("force"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfiguration_force_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfiguration_force_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfiguration, force), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Description_qual_value = MI_T("308");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_ConfigurationData_param,
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_force_param,
};

/* method MSFT_DSCLocalConfigurationManager.SendConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736E11, /* code */
    MI_T("SendConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_SendConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_SendConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_SendConfiguration, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Description_qual_value = MI_T("309");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfigurationApply_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_In_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_In_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_Octetstring_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfigurationApply(): ConfigurationData */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636111, /* code */
    MI_T("ConfigurationData"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfigurationApply, ConfigurationData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfigurationApply(): force */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666505, /* code */
    MI_T("force"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfigurationApply, force), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Description_qual_value = MI_T("309");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendConfigurationApply(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendConfigurationApply, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendConfigurationApply_params[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_ConfigurationData_param,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_force_param,
};

/* method MSFT_DSCLocalConfigurationManager.SendConfigurationApply() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendConfigurationApply_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00737916, /* code */
    MI_T("SendConfigurationApply"), /* name */
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfigurationApply_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_SendConfigurationApply_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendConfigurationApply_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_SendConfigurationApply), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_SendConfigurationApply, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetConfiguration_Description_qual_value = MI_T("312");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_In_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_In_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_Octetstring_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetConfiguration(): configurationData */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636111, /* code */
    MI_T("configurationData"), /* name */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_GetConfiguration, configurationData), /* offset */
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_EmbeddedInstance_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_EmbeddedInstance_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Out_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetConfiguration(): configurations */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0063730E, /* code */
    MI_T("configurations"), /* name */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_GetConfiguration, configurations), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Description_qual_value = MI_T("312");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_GetConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurationData_param,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_param,
};

/* method MSFT_DSCLocalConfigurationManager.GetConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676E10, /* code */
    MI_T("GetConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_GetConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_GetConfiguration, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_TestConfiguration_Description_qual_value = MI_T("314");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_In_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_In_qual,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_Octetstring_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.TestConfiguration(): configurationData */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636111, /* code */
    MI_T("configurationData"), /* name */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_TestConfiguration, configurationData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_Out_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.TestConfiguration(): InDesiredState */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0069650E, /* code */
    MI_T("InDesiredState"), /* name */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_TestConfiguration, InDesiredState), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_Out_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.TestConfiguration(): ResourceId */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0072640A, /* code */
    MI_T("ResourceId"), /* name */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_TestConfiguration, ResourceId), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Description_qual_value = MI_T("314");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.TestConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_TestConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_TestConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_configurationData_param,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_InDesiredState_param,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_ResourceId_param,
};

/* method MSFT_DSCLocalConfigurationManager.TestConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_TestConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746E11, /* code */
    MI_T("TestConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_TestConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_TestConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_TestConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_TestConfiguration, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Description_qual_value = MI_T("430");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_ApplyConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.ApplyConfiguration(): force */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666505, /* code */
    MI_T("force"), /* name */
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_ApplyConfiguration, force), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Description_qual_value = MI_T("430");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.ApplyConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_ApplyConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_ApplyConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_force_param,
};

/* method MSFT_DSCLocalConfigurationManager.ApplyConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_ApplyConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00616E12, /* code */
    MI_T("ApplyConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_ApplyConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_ApplyConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_ApplyConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_ApplyConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_ApplyConfiguration, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Description_qual_value = MI_T("317");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_In_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_In_qual,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_Octetstring_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendMetaConfigurationApply(): ConfigurationData */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636111, /* code */
    MI_T("ConfigurationData"), /* name */
    MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply, ConfigurationData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Description_qual_value = MI_T("317");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.SendMetaConfigurationApply(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_params[] =
{
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_ConfigurationData_param,
};

/* method MSFT_DSCLocalConfigurationManager.SendMetaConfigurationApply() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0073791A, /* code */
    MI_T("SendMetaConfigurationApply"), /* name */
    MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_SendMetaConfigurationApply, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Description_qual_value = MI_T("318");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_Out_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_EmbeddedInstance_qual_value = MI_T("MSFT_DSCMetaConfiguration");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_Out_qual,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetMetaConfiguration(): MetaConfiguration */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E11, /* code */
    MI_T("MetaConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_DSCMetaConfiguration"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration, MetaConfiguration), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Description_qual_value = MI_T("318");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetMetaConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_MetaConfiguration_param,
};

/* method MSFT_DSCLocalConfigurationManager.GetMetaConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676E14, /* code */
    MI_T("GetMetaConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_GetMetaConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_GetMetaConfiguration, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_RollBack_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_RollBack_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_RollBack_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_RollBack_Description_qual_value = MI_T("30");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_RollBack_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_RollBack_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_RollBack_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_RollBack_Static_qual,
    &MSFT_DSCLocalConfigurationManager_RollBack_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.RollBack(): configurationNumber */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00637213, /* code */
    MI_T("configurationNumber"), /* name */
    MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_RollBack, configurationNumber), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Description_qual_value = MI_T("30");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.RollBack(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_RollBack, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_RollBack_params[] =
{
    &MSFT_DSCLocalConfigurationManager_RollBack_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_RollBack_configurationNumber_param,
};

/* method MSFT_DSCLocalConfigurationManager.RollBack() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_RollBack_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00726B08, /* code */
    MI_T("RollBack"), /* name */
    MSFT_DSCLocalConfigurationManager_RollBack_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_RollBack_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_RollBack_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_RollBack_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_RollBack), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_RollBack, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Description_qual_value = MI_T("857");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Static_qual,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.PerformRequiredConfigurationChecks(): Flags */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Description_qual_value = MI_T("857");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.PerformRequiredConfigurationChecks(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_params[] =
{
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Flags_param,
};

/* method MSFT_DSCLocalConfigurationManager.PerformRequiredConfigurationChecks() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00707322, /* code */
    MI_T("PerformRequiredConfigurationChecks"), /* name */
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_PerformRequiredConfigurationChecks, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_StopConfiguration_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_StopConfiguration_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_StopConfiguration_Description_qual_value = MI_T("319");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_StopConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_StopConfiguration_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_Static_qual,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_StopConfiguration_force_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_StopConfiguration_force_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_force_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_StopConfiguration_force_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_force_In_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.StopConfiguration(): force */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_StopConfiguration_force_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666505, /* code */
    MI_T("force"), /* name */
    MSFT_DSCLocalConfigurationManager_StopConfiguration_force_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_StopConfiguration_force_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_StopConfiguration, force), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Description_qual_value = MI_T("319");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Static_qual,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_Description_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.StopConfiguration(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCLocalConfigurationManager_StopConfiguration, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_StopConfiguration_params[] =
{
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_MIReturn_param,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_force_param,
};

/* method MSFT_DSCLocalConfigurationManager.StopConfiguration() */
MI_CONST MI_MethodDecl MSFT_DSCLocalConfigurationManager_StopConfiguration_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736E11, /* code */
    MI_T("StopConfiguration"), /* name */
    MSFT_DSCLocalConfigurationManager_StopConfiguration_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_StopConfiguration_quals), /* numQualifiers */
    MSFT_DSCLocalConfigurationManager_StopConfiguration_params, /* parameters */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_StopConfiguration_params), /* numParameters */
    sizeof(MSFT_DSCLocalConfigurationManager_StopConfiguration), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* origin */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCLocalConfigurationManager_Invoke_StopConfiguration, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_meths[] =
{
    &MSFT_DSCLocalConfigurationManager_SendConfiguration_rtti,
    &MSFT_DSCLocalConfigurationManager_SendConfigurationApply_rtti,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_rtti,
    &MSFT_DSCLocalConfigurationManager_TestConfiguration_rtti,
    &MSFT_DSCLocalConfigurationManager_ApplyConfiguration_rtti,
    &MSFT_DSCLocalConfigurationManager_SendMetaConfigurationApply_rtti,
    &MSFT_DSCLocalConfigurationManager_GetMetaConfiguration_rtti,
    &MSFT_DSCLocalConfigurationManager_RollBack_rtti,
    &MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_rtti,
    &MSFT_DSCLocalConfigurationManager_StopConfiguration_rtti,
};

static MI_CONST MI_ProviderFT MSFT_DSCLocalConfigurationManager_funcs =
{
  (MI_ProviderFT_Load)MSFT_DSCLocalConfigurationManager_Load,
  (MI_ProviderFT_Unload)MSFT_DSCLocalConfigurationManager_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCLocalConfigurationManager_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_Description_qual_value = MI_T("320");

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCLocalConfigurationManager_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCLocalConfigurationManager_quals[] =
{
    &MSFT_DSCLocalConfigurationManager_ClassVersion_qual,
    &MSFT_DSCLocalConfigurationManager_Description_qual,
};

/* class MSFT_DSCLocalConfigurationManager */
MI_CONST MI_ClassDecl MSFT_DSCLocalConfigurationManager_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7221, /* code */
    MI_T("MSFT_DSCLocalConfigurationManager"), /* name */
    MSFT_DSCLocalConfigurationManager_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_quals), /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MSFT_DSCLocalConfigurationManager), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MSFT_DSCLocalConfigurationManager_meths, /* methods */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_DSCLocalConfigurationManager_funcs, /* functions */
    NULL /* owningClass */
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
    &MSFT_Credential_rtti,
    &MSFT_DSCLocalConfigurationManager_rtti,
    &MSFT_DSCMetaConfiguration_rtti,
    &MSFT_KeyValuePair_rtti,
    &MSFT_PartialConfiguration_rtti,
    &OMI_BaseResource_rtti,
    &OMI_ConfigurationDownloadManager_rtti,
    &OMI_MetaConfigurationResource_rtti,
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

