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
#include "OMI_nxUserResource.h"

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

static MI_CONST MI_QualifierDecl FriendlyName_qual_decl =
{
    MI_T("FriendlyName"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ANY, /* scope */
    MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
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
    &FriendlyName_qual_decl,
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
** OMI_nxUserResource
**
**==============================================================================
*/

static MI_CONST MI_Boolean OMI_nxUserResource_UserName_Key_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_UserName_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_UserName_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_UserName_quals[] =
{
    &OMI_nxUserResource_UserName_Key_qual,
};

/* property OMI_nxUserResource.UserName */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_UserName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00756508, /* code */
    MI_T("UserName"), /* name */
    OMI_nxUserResource_UserName_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_UserName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, UserName), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_Ensure_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_Ensure_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_Ensure_Write_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_Ensure_ValueMap_qual_data_value[] =
{
    MI_T("Present"),
    MI_T("Absent"),
};

static MI_CONST MI_ConstStringA OMI_nxUserResource_Ensure_ValueMap_qual_value =
{
    OMI_nxUserResource_Ensure_ValueMap_qual_data_value,
    MI_COUNT(OMI_nxUserResource_Ensure_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_nxUserResource_Ensure_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_Ensure_ValueMap_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_Ensure_Values_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
};

static MI_CONST MI_ConstStringA OMI_nxUserResource_Ensure_Values_qual_value =
{
    OMI_nxUserResource_Ensure_Values_qual_data_value,
    MI_COUNT(OMI_nxUserResource_Ensure_Values_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_nxUserResource_Ensure_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_Ensure_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_Ensure_quals[] =
{
    &OMI_nxUserResource_Ensure_Write_qual,
    &OMI_nxUserResource_Ensure_ValueMap_qual,
    &OMI_nxUserResource_Ensure_Values_qual,
};

/* property OMI_nxUserResource.Ensure */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_Ensure_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656506, /* code */
    MI_T("Ensure"), /* name */
    OMI_nxUserResource_Ensure_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_Ensure_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, Ensure), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_FullName_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_FullName_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_FullName_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_FullName_quals[] =
{
    &OMI_nxUserResource_FullName_Write_qual,
};

/* property OMI_nxUserResource.FullName */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_FullName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666508, /* code */
    MI_T("FullName"), /* name */
    OMI_nxUserResource_FullName_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_FullName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, FullName), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_Description_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_Description_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_Description_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_Description_quals[] =
{
    &OMI_nxUserResource_Description_Write_qual,
};

/* property OMI_nxUserResource.Description */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    OMI_nxUserResource_Description_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_Description_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, Description), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_Password_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_Password_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_Password_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_Password_quals[] =
{
    &OMI_nxUserResource_Password_Write_qual,
};

/* property OMI_nxUserResource.Password */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_Password_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706408, /* code */
    MI_T("Password"), /* name */
    OMI_nxUserResource_Password_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_Password_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, Password), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_Disabled_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_Disabled_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_Disabled_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_Disabled_quals[] =
{
    &OMI_nxUserResource_Disabled_Write_qual,
};

/* property OMI_nxUserResource.Disabled */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_Disabled_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646408, /* code */
    MI_T("Disabled"), /* name */
    OMI_nxUserResource_Disabled_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_Disabled_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, Disabled), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_PasswordChangeRequired_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_PasswordChangeRequired_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_PasswordChangeRequired_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_PasswordChangeRequired_quals[] =
{
    &OMI_nxUserResource_PasswordChangeRequired_Write_qual,
};

/* property OMI_nxUserResource.PasswordChangeRequired */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_PasswordChangeRequired_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706416, /* code */
    MI_T("PasswordChangeRequired"), /* name */
    OMI_nxUserResource_PasswordChangeRequired_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_PasswordChangeRequired_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, PasswordChangeRequired), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_HomeDirectory_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_HomeDirectory_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_HomeDirectory_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_HomeDirectory_quals[] =
{
    &OMI_nxUserResource_HomeDirectory_Write_qual,
};

/* property OMI_nxUserResource.HomeDirectory */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_HomeDirectory_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068790D, /* code */
    MI_T("HomeDirectory"), /* name */
    OMI_nxUserResource_HomeDirectory_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_HomeDirectory_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, HomeDirectory), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean OMI_nxUserResource_GroupID_Write_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GroupID_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GroupID_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GroupID_quals[] =
{
    &OMI_nxUserResource_GroupID_Write_qual,
};

/* property OMI_nxUserResource.GroupID */
static MI_CONST MI_PropertyDecl OMI_nxUserResource_GroupID_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00676407, /* code */
    MI_T("GroupID"), /* name */
    OMI_nxUserResource_GroupID_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GroupID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource, GroupID), /* offset */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_nxUserResource_props[] =
{
    &OMI_nxUserResource_UserName_prop,
    &OMI_nxUserResource_Ensure_prop,
    &OMI_nxUserResource_FullName_prop,
    &OMI_nxUserResource_Description_prop,
    &OMI_nxUserResource_Password_prop,
    &OMI_nxUserResource_Disabled_prop,
    &OMI_nxUserResource_PasswordChangeRequired_prop,
    &OMI_nxUserResource_HomeDirectory_prop,
    &OMI_nxUserResource_GroupID_prop,
};

static MI_CONST MI_Boolean OMI_nxUserResource_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_quals[] =
{
    &OMI_nxUserResource_GetTargetResource_Static_qual,
    &OMI_nxUserResource_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean OMI_nxUserResource_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_nxUserResource");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_InputResource_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_InputResource_quals[] =
{
    &OMI_nxUserResource_GetTargetResource_InputResource_In_qual,
    &OMI_nxUserResource_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &OMI_nxUserResource_GetTargetResource_InputResource_Description_qual,
};

/* parameter OMI_nxUserResource.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    OMI_nxUserResource_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_nxUserResource"), /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_Flags_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_Flags_quals[] =
{
    &OMI_nxUserResource_GetTargetResource_Flags_In_qual,
    &OMI_nxUserResource_GetTargetResource_Flags_Description_qual,
};

/* parameter OMI_nxUserResource.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    OMI_nxUserResource_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_nxUserResource");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_OutputResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_OutputResource_quals[] =
{
    &OMI_nxUserResource_GetTargetResource_OutputResource_Out_qual,
    &OMI_nxUserResource_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &OMI_nxUserResource_GetTargetResource_OutputResource_Description_qual,
};

/* parameter OMI_nxUserResource.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    OMI_nxUserResource_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_nxUserResource"), /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_GetTargetResource_MIReturn_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier OMI_nxUserResource_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_MIReturn_quals[] =
{
    &OMI_nxUserResource_GetTargetResource_MIReturn_Static_qual,
    &OMI_nxUserResource_GetTargetResource_MIReturn_Description_qual,
};

/* parameter OMI_nxUserResource.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    OMI_nxUserResource_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST OMI_nxUserResource_GetTargetResource_params[] =
{
    &OMI_nxUserResource_GetTargetResource_MIReturn_param,
    &OMI_nxUserResource_GetTargetResource_InputResource_param,
    &OMI_nxUserResource_GetTargetResource_Flags_param,
    &OMI_nxUserResource_GetTargetResource_OutputResource_param,
};

/* method OMI_nxUserResource.GetTargetResource() */
MI_CONST MI_MethodDecl OMI_nxUserResource_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    OMI_nxUserResource_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_quals), /* numQualifiers */
    OMI_nxUserResource_GetTargetResource_params, /* parameters */
    MI_COUNT(OMI_nxUserResource_GetTargetResource_params), /* numParameters */
    sizeof(OMI_nxUserResource_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)OMI_nxUserResource_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_Static_qual,
    &OMI_nxUserResource_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_nxUserResource");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_InputResource_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_InputResource_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_InputResource_In_qual,
    &OMI_nxUserResource_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &OMI_nxUserResource_TestTargetResource_InputResource_Description_qual,
};

/* parameter OMI_nxUserResource.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    OMI_nxUserResource_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_nxUserResource"), /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_Flags_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_Flags_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_Flags_In_qual,
    &OMI_nxUserResource_TestTargetResource_Flags_Description_qual,
};

/* parameter OMI_nxUserResource.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    OMI_nxUserResource_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_Result_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_Result_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_Result_Out_qual,
    &OMI_nxUserResource_TestTargetResource_Result_Description_qual,
};

/* parameter OMI_nxUserResource.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    OMI_nxUserResource_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_ProviderContext_Description_qual_value = MI_T("12");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_ProviderContext_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_ProviderContext_Out_qual,
    &OMI_nxUserResource_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter OMI_nxUserResource.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    OMI_nxUserResource_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_TestTargetResource_MIReturn_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier OMI_nxUserResource_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_MIReturn_quals[] =
{
    &OMI_nxUserResource_TestTargetResource_MIReturn_Static_qual,
    &OMI_nxUserResource_TestTargetResource_MIReturn_Description_qual,
};

/* parameter OMI_nxUserResource.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    OMI_nxUserResource_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST OMI_nxUserResource_TestTargetResource_params[] =
{
    &OMI_nxUserResource_TestTargetResource_MIReturn_param,
    &OMI_nxUserResource_TestTargetResource_InputResource_param,
    &OMI_nxUserResource_TestTargetResource_Flags_param,
    &OMI_nxUserResource_TestTargetResource_Result_param,
    &OMI_nxUserResource_TestTargetResource_ProviderContext_param,
};

/* method OMI_nxUserResource.TestTargetResource() */
MI_CONST MI_MethodDecl OMI_nxUserResource_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    OMI_nxUserResource_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_quals), /* numQualifiers */
    OMI_nxUserResource_TestTargetResource_params, /* parameters */
    MI_COUNT(OMI_nxUserResource_TestTargetResource_params), /* numParameters */
    sizeof(OMI_nxUserResource_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)OMI_nxUserResource_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean OMI_nxUserResource_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_Description_qual_value = MI_T("13");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_quals[] =
{
    &OMI_nxUserResource_SetTargetResource_Static_qual,
    &OMI_nxUserResource_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean OMI_nxUserResource_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_nxUserResource");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_InputResource_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_InputResource_quals[] =
{
    &OMI_nxUserResource_SetTargetResource_InputResource_In_qual,
    &OMI_nxUserResource_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &OMI_nxUserResource_SetTargetResource_InputResource_Description_qual,
};

/* parameter OMI_nxUserResource.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    OMI_nxUserResource_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_nxUserResource"), /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_ProviderContext_Description_qual_value = MI_T("14");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_ProviderContext_quals[] =
{
    &OMI_nxUserResource_SetTargetResource_ProviderContext_In_qual,
    &OMI_nxUserResource_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter OMI_nxUserResource.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    OMI_nxUserResource_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_Flags_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_Flags_quals[] =
{
    &OMI_nxUserResource_SetTargetResource_Flags_In_qual,
    &OMI_nxUserResource_SetTargetResource_Flags_Description_qual,
};

/* parameter OMI_nxUserResource.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    OMI_nxUserResource_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean OMI_nxUserResource_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_nxUserResource_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_SetTargetResource_MIReturn_Description_qual_value = MI_T("13");

static MI_CONST MI_Qualifier OMI_nxUserResource_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_MIReturn_quals[] =
{
    &OMI_nxUserResource_SetTargetResource_MIReturn_Static_qual,
    &OMI_nxUserResource_SetTargetResource_MIReturn_Description_qual,
};

/* parameter OMI_nxUserResource.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl OMI_nxUserResource_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    OMI_nxUserResource_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_nxUserResource_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST OMI_nxUserResource_SetTargetResource_params[] =
{
    &OMI_nxUserResource_SetTargetResource_MIReturn_param,
    &OMI_nxUserResource_SetTargetResource_InputResource_param,
    &OMI_nxUserResource_SetTargetResource_ProviderContext_param,
    &OMI_nxUserResource_SetTargetResource_Flags_param,
};

/* method OMI_nxUserResource.SetTargetResource() */
MI_CONST MI_MethodDecl OMI_nxUserResource_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    OMI_nxUserResource_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_quals), /* numQualifiers */
    OMI_nxUserResource_SetTargetResource_params, /* parameters */
    MI_COUNT(OMI_nxUserResource_SetTargetResource_params), /* numParameters */
    sizeof(OMI_nxUserResource_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("OMI_nxUserResource"), /* origin */
    MI_T("OMI_nxUserResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)OMI_nxUserResource_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST OMI_nxUserResource_meths[] =
{
    &OMI_nxUserResource_GetTargetResource_rtti,
    &OMI_nxUserResource_TestTargetResource_rtti,
    &OMI_nxUserResource_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT OMI_nxUserResource_funcs =
{
  (MI_ProviderFT_Load)OMI_nxUserResource_Load,
  (MI_ProviderFT_Unload)OMI_nxUserResource_Unload,
  (MI_ProviderFT_GetInstance)OMI_nxUserResource_GetInstance,
  (MI_ProviderFT_EnumerateInstances)OMI_nxUserResource_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)OMI_nxUserResource_CreateInstance,
  (MI_ProviderFT_ModifyInstance)OMI_nxUserResource_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)OMI_nxUserResource_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* OMI_nxUserResource_Description_qual_value = MI_T("1");

static MI_CONST MI_Qualifier OMI_nxUserResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_nxUserResource_Description_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier OMI_nxUserResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &OMI_nxUserResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* OMI_nxUserResource_FriendlyName_qual_value = MI_T("nxUser");

static MI_CONST MI_Qualifier OMI_nxUserResource_FriendlyName_qual =
{
    MI_T("FriendlyName"),
    MI_STRING,
    MI_FLAG_RESTRICTED,
    &OMI_nxUserResource_FriendlyName_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_nxUserResource_quals[] =
{
    &OMI_nxUserResource_Description_qual,
    &OMI_nxUserResource_ClassVersion_qual,
    &OMI_nxUserResource_FriendlyName_qual,
};

/* class OMI_nxUserResource */
MI_CONST MI_ClassDecl OMI_nxUserResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F6512, /* code */
    MI_T("OMI_nxUserResource"), /* name */
    OMI_nxUserResource_quals, /* qualifiers */
    MI_COUNT(OMI_nxUserResource_quals), /* numQualifiers */
    OMI_nxUserResource_props, /* properties */
    MI_COUNT(OMI_nxUserResource_props), /* numProperties */
    sizeof(OMI_nxUserResource), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    OMI_nxUserResource_meths, /* methods */
    MI_COUNT(OMI_nxUserResource_meths), /* numMethods */
    &schemaDecl, /* schema */
    &OMI_nxUserResource_funcs, /* functions */
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
    &OMI_BaseResource_rtti,
    &OMI_nxUserResource_rtti,
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

