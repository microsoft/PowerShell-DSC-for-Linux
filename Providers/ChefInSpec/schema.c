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
#include "MSFT_ChefInSpecResource.h"
#include "OMI_Error.h"
#include "MSFT_DSCResource.h"

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
** MSFT_Credential
**
**==============================================================================
*/

static MI_CONST MI_Char* MSFT_Credential_UserName_Description_qual_value = MI_T("1");

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

static MI_CONST MI_Char* MSFT_Credential_Password_Description_qual_value = MI_T("2");

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

static MI_CONST MI_Char* MSFT_Credential_Description_qual_value = MI_T("3");

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
** OMI_BaseResource
**
**==============================================================================
*/

static MI_CONST MI_Char* OMI_BaseResource_ResourceId_Description_qual_value = MI_T("4");

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

static MI_CONST MI_Char* OMI_BaseResource_SourceInfo_Description_qual_value = MI_T("5");

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

static MI_CONST MI_Char* OMI_BaseResource_DependsOn_Description_qual_value = MI_T("6");

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

static MI_CONST MI_Char* OMI_BaseResource_ModuleName_Description_qual_value = MI_T("7");

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

static MI_CONST MI_Char* OMI_BaseResource_ModuleVersion_Description_qual_value = MI_T("8");

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

static MI_CONST MI_Char* OMI_BaseResource_ConfigurationName_Description_qual_value = MI_T("9");

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

static MI_CONST MI_Char* OMI_BaseResource_PsDscRunAsCredential_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier OMI_BaseResource_PsDscRunAsCredential_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_BaseResource_PsDscRunAsCredential_Description_qual_value
};

static MI_CONST MI_Char* OMI_BaseResource_PsDscRunAsCredential_EmbeddedInstance_qual_value = MI_T("MSFT_Credential");

static MI_CONST MI_Qualifier OMI_BaseResource_PsDscRunAsCredential_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_BaseResource_PsDscRunAsCredential_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_BaseResource_PsDscRunAsCredential_quals[] =
{
    &OMI_BaseResource_PsDscRunAsCredential_Description_qual,
    &OMI_BaseResource_PsDscRunAsCredential_EmbeddedInstance_qual,
};

/* property OMI_BaseResource.PsDscRunAsCredential */
static MI_CONST MI_PropertyDecl OMI_BaseResource_PsDscRunAsCredential_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00706C14, /* code */
    MI_T("PsDscRunAsCredential"), /* name */
    OMI_BaseResource_PsDscRunAsCredential_quals, /* qualifiers */
    MI_COUNT(OMI_BaseResource_PsDscRunAsCredential_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Credential"), /* className */
    0, /* subscript */
    offsetof(OMI_BaseResource, PsDscRunAsCredential), /* offset */
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
    &OMI_BaseResource_PsDscRunAsCredential_prop,
};

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

static MI_CONST MI_Char* OMI_BaseResource_Description_qual_value = MI_T("11");

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
** InSpec_Controls
**
**==============================================================================
*/

static MI_CONST MI_Boolean InSpec_Controls_id_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_id_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_id_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_id_quals[] =
{
    &InSpec_Controls_id_Write_qual,
};

/* property InSpec_Controls.id */
static MI_CONST MI_PropertyDecl InSpec_Controls_id_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    InSpec_Controls_id_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_id_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, id), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Controls_profile_id_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_profile_id_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_profile_id_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_profile_id_quals[] =
{
    &InSpec_Controls_profile_id_Write_qual,
};

/* property InSpec_Controls.profile_id */
static MI_CONST MI_PropertyDecl InSpec_Controls_profile_id_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070640A, /* code */
    MI_T("profile_id"), /* name */
    InSpec_Controls_profile_id_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_profile_id_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, profile_id), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Controls_profile_sha256_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_profile_sha256_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_profile_sha256_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_profile_sha256_quals[] =
{
    &InSpec_Controls_profile_sha256_Write_qual,
};

/* property InSpec_Controls.profile_sha256 */
static MI_CONST MI_PropertyDecl InSpec_Controls_profile_sha256_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070360E, /* code */
    MI_T("profile_sha256"), /* name */
    InSpec_Controls_profile_sha256_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_profile_sha256_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, profile_sha256), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Controls_status_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_status_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_status_Write_qual_value
};

static MI_CONST MI_Char* InSpec_Controls_status_ValueMap_qual_data_value[] =
{
    MI_T("passed"),
    MI_T("failed"),
};

static MI_CONST MI_ConstStringA InSpec_Controls_status_ValueMap_qual_value =
{
    InSpec_Controls_status_ValueMap_qual_data_value,
    MI_COUNT(InSpec_Controls_status_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier InSpec_Controls_status_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_status_ValueMap_qual_value
};

static MI_CONST MI_Char* InSpec_Controls_status_Values_qual_data_value[] =
{
    MI_T("12"),
    MI_T("13"),
};

static MI_CONST MI_ConstStringA InSpec_Controls_status_Values_qual_value =
{
    InSpec_Controls_status_Values_qual_data_value,
    MI_COUNT(InSpec_Controls_status_Values_qual_data_value),
};

static MI_CONST MI_Qualifier InSpec_Controls_status_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &InSpec_Controls_status_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_status_quals[] =
{
    &InSpec_Controls_status_Write_qual,
    &InSpec_Controls_status_ValueMap_qual,
    &InSpec_Controls_status_Values_qual,
};

/* property InSpec_Controls.status */
static MI_CONST MI_PropertyDecl InSpec_Controls_status_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737306, /* code */
    MI_T("status"), /* name */
    InSpec_Controls_status_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_status_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, status), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Controls_codec_desc_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_codec_desc_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_codec_desc_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_codec_desc_quals[] =
{
    &InSpec_Controls_codec_desc_Write_qual,
};

/* property InSpec_Controls.codec_desc */
static MI_CONST MI_PropertyDecl InSpec_Controls_codec_desc_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063630A, /* code */
    MI_T("codec_desc"), /* name */
    InSpec_Controls_codec_desc_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_codec_desc_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, codec_desc), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Controls_message_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Controls_message_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Controls_message_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_message_quals[] =
{
    &InSpec_Controls_message_Write_qual,
};

/* property InSpec_Controls.message */
static MI_CONST MI_PropertyDecl InSpec_Controls_message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("message"), /* name */
    InSpec_Controls_message_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_message_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Controls, message), /* offset */
    MI_T("InSpec_Controls"), /* origin */
    MI_T("InSpec_Controls"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST InSpec_Controls_props[] =
{
    &InSpec_Controls_id_prop,
    &InSpec_Controls_profile_id_prop,
    &InSpec_Controls_profile_sha256_prop,
    &InSpec_Controls_status_prop,
    &InSpec_Controls_codec_desc_prop,
    &InSpec_Controls_message_prop,
};

static MI_CONST MI_Char* InSpec_Controls_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier InSpec_Controls_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &InSpec_Controls_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Controls_quals[] =
{
    &InSpec_Controls_ClassVersion_qual,
};

/* class InSpec_Controls */
MI_CONST MI_ClassDecl InSpec_Controls_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0069730F, /* code */
    MI_T("InSpec_Controls"), /* name */
    InSpec_Controls_quals, /* qualifiers */
    MI_COUNT(InSpec_Controls_quals), /* numQualifiers */
    InSpec_Controls_props, /* properties */
    MI_COUNT(InSpec_Controls_props), /* numProperties */
    sizeof(InSpec_Controls), /* size */
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
** InSpec_Statistics
**
**==============================================================================
*/

static MI_CONST MI_Boolean InSpec_Statistics_duration_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Statistics_duration_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Statistics_duration_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Statistics_duration_quals[] =
{
    &InSpec_Statistics_duration_Write_qual,
};

/* property InSpec_Statistics.duration */
static MI_CONST MI_PropertyDecl InSpec_Statistics_duration_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E08, /* code */
    MI_T("duration"), /* name */
    InSpec_Statistics_duration_quals, /* qualifiers */
    MI_COUNT(InSpec_Statistics_duration_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Statistics, duration), /* offset */
    MI_T("InSpec_Statistics"), /* origin */
    MI_T("InSpec_Statistics"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST InSpec_Statistics_props[] =
{
    &InSpec_Statistics_duration_prop,
};

static MI_CONST MI_Char* InSpec_Statistics_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier InSpec_Statistics_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &InSpec_Statistics_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Statistics_quals[] =
{
    &InSpec_Statistics_ClassVersion_qual,
};

/* class InSpec_Statistics */
MI_CONST MI_ClassDecl InSpec_Statistics_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00697311, /* code */
    MI_T("InSpec_Statistics"), /* name */
    InSpec_Statistics_quals, /* qualifiers */
    MI_COUNT(InSpec_Statistics_quals), /* numQualifiers */
    InSpec_Statistics_props, /* properties */
    MI_COUNT(InSpec_Statistics_props), /* numProperties */
    sizeof(InSpec_Statistics), /* size */
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
** InSpec_Results
**
**==============================================================================
*/

static MI_CONST MI_Boolean InSpec_Results_controls_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Results_controls_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_controls_Write_qual_value
};

static MI_CONST MI_Char* InSpec_Results_controls_EmbeddedInstance_qual_value = MI_T("InSpec_Controls");

static MI_CONST MI_Qualifier InSpec_Results_controls_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_controls_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Results_controls_quals[] =
{
    &InSpec_Results_controls_Write_qual,
    &InSpec_Results_controls_EmbeddedInstance_qual,
};

/* property InSpec_Results.controls */
static MI_CONST MI_PropertyDecl InSpec_Results_controls_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637308, /* code */
    MI_T("controls"), /* name */
    InSpec_Results_controls_quals, /* qualifiers */
    MI_COUNT(InSpec_Results_controls_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("InSpec_Controls"), /* className */
    0, /* subscript */
    offsetof(InSpec_Results, controls), /* offset */
    MI_T("InSpec_Results"), /* origin */
    MI_T("InSpec_Results"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Results_version_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Results_version_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_version_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Results_version_quals[] =
{
    &InSpec_Results_version_Write_qual,
};

/* property InSpec_Results.version */
static MI_CONST MI_PropertyDecl InSpec_Results_version_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766E07, /* code */
    MI_T("version"), /* name */
    InSpec_Results_version_quals, /* qualifiers */
    MI_COUNT(InSpec_Results_version_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Results, version), /* offset */
    MI_T("InSpec_Results"), /* origin */
    MI_T("InSpec_Results"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Results_statistics_Write_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Results_statistics_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_statistics_Write_qual_value
};

static MI_CONST MI_Char* InSpec_Results_statistics_EmbeddedInstance_qual_value = MI_T("InSpec_Statistics");

static MI_CONST MI_Qualifier InSpec_Results_statistics_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_statistics_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Results_statistics_quals[] =
{
    &InSpec_Results_statistics_Write_qual,
    &InSpec_Results_statistics_EmbeddedInstance_qual,
};

/* property InSpec_Results.statistics */
static MI_CONST MI_PropertyDecl InSpec_Results_statistics_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073730A, /* code */
    MI_T("statistics"), /* name */
    InSpec_Results_statistics_quals, /* qualifiers */
    MI_COUNT(InSpec_Results_statistics_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("InSpec_Statistics"), /* className */
    0, /* subscript */
    offsetof(InSpec_Results, statistics), /* offset */
    MI_T("InSpec_Results"), /* origin */
    MI_T("InSpec_Results"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean InSpec_Results_status_Read_qual_value = 1;

static MI_CONST MI_Qualifier InSpec_Results_status_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_status_Read_qual_value
};

static MI_CONST MI_Char* InSpec_Results_status_ValueMap_qual_data_value[] =
{
    MI_T("Compliant"),
    MI_T("Non-Compliant"),
};

static MI_CONST MI_ConstStringA InSpec_Results_status_ValueMap_qual_value =
{
    InSpec_Results_status_ValueMap_qual_data_value,
    MI_COUNT(InSpec_Results_status_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier InSpec_Results_status_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &InSpec_Results_status_ValueMap_qual_value
};

static MI_CONST MI_Char* InSpec_Results_status_Values_qual_data_value[] =
{
    MI_T("14"),
    MI_T("15"),
};

static MI_CONST MI_ConstStringA InSpec_Results_status_Values_qual_value =
{
    InSpec_Results_status_Values_qual_data_value,
    MI_COUNT(InSpec_Results_status_Values_qual_data_value),
};

static MI_CONST MI_Qualifier InSpec_Results_status_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &InSpec_Results_status_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST InSpec_Results_status_quals[] =
{
    &InSpec_Results_status_Read_qual,
    &InSpec_Results_status_ValueMap_qual,
    &InSpec_Results_status_Values_qual,
};

/* property InSpec_Results.status */
static MI_CONST MI_PropertyDecl InSpec_Results_status_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00737306, /* code */
    MI_T("status"), /* name */
    InSpec_Results_status_quals, /* qualifiers */
    MI_COUNT(InSpec_Results_status_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(InSpec_Results, status), /* offset */
    MI_T("InSpec_Results"), /* origin */
    MI_T("InSpec_Results"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST InSpec_Results_props[] =
{
    &InSpec_Results_controls_prop,
    &InSpec_Results_version_prop,
    &InSpec_Results_statistics_prop,
    &InSpec_Results_status_prop,
};

/* class InSpec_Results */
MI_CONST MI_ClassDecl InSpec_Results_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0069730E, /* code */
    MI_T("InSpec_Results"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    InSpec_Results_props, /* properties */
    MI_COUNT(InSpec_Results_props), /* numProperties */
    sizeof(InSpec_Results), /* size */
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
** MSFT_ChefInSpecResource
**
**==============================================================================
*/

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_Name_Key_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_Name_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_Name_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_Name_quals[] =
{
    &MSFT_ChefInSpecResource_Name_Key_qual,
};

/* property MSFT_ChefInSpecResource.Name */
static MI_CONST MI_PropertyDecl MSFT_ChefInSpecResource_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    MSFT_ChefInSpecResource_Name_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource, Name), /* offset */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GithubPath_Key_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GithubPath_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GithubPath_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GithubPath_quals[] =
{
    &MSFT_ChefInSpecResource_GithubPath_Key_qual,
};

/* property MSFT_ChefInSpecResource.GithubPath */
static MI_CONST MI_PropertyDecl MSFT_ChefInSpecResource_GithubPath_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x0067680A, /* code */
    MI_T("GithubPath"), /* name */
    MSFT_ChefInSpecResource_GithubPath_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GithubPath_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource, GithubPath), /* offset */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_Result_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_Result_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_Result_Read_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_Result_EmbeddedInstance_qual_value = MI_T("InSpec_Results");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_Result_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_Result_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_Result_quals[] =
{
    &MSFT_ChefInSpecResource_Result_Read_qual,
    &MSFT_ChefInSpecResource_Result_EmbeddedInstance_qual,
};

/* property MSFT_ChefInSpecResource.Result */
static MI_CONST MI_PropertyDecl MSFT_ChefInSpecResource_Result_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_ChefInSpecResource_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_Result_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("InSpec_Results"), /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource, Result), /* offset */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_ChefInSpecResource_props[] =
{
    &OMI_BaseResource_ResourceId_prop,
    &OMI_BaseResource_SourceInfo_prop,
    &OMI_BaseResource_DependsOn_prop,
    &OMI_BaseResource_ModuleName_prop,
    &OMI_BaseResource_ModuleVersion_prop,
    &OMI_BaseResource_ConfigurationName_prop,
    &OMI_BaseResource_PsDscRunAsCredential_prop,
    &MSFT_ChefInSpecResource_Name_prop,
    &MSFT_ChefInSpecResource_GithubPath_prop,
    &MSFT_ChefInSpecResource_Result_prop,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_Description_qual_value = MI_T("16");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_quals[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_Static_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_ChefInSpecResource");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_InputResource_Description_qual_value = MI_T("17");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_InputResource_quals[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_In_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_ChefInSpecResource_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_ChefInSpecResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_Flags_Description_qual_value = MI_T("18");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_Flags_quals[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_Flags_In_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_Flags_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_ChefInSpecResource_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("MSFT_ChefInSpecResource");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Description_qual_value = MI_T("19");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_OutputResource_quals[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Out_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    MSFT_ChefInSpecResource_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_ChefInSpecResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Description_qual_value = MI_T("16");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_MIReturn_quals[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Static_qual,
    &MSFT_ChefInSpecResource_GetTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_ChefInSpecResource_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_ChefInSpecResource_GetTargetResource_params[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_MIReturn_param,
    &MSFT_ChefInSpecResource_GetTargetResource_InputResource_param,
    &MSFT_ChefInSpecResource_GetTargetResource_Flags_param,
    &MSFT_ChefInSpecResource_GetTargetResource_OutputResource_param,
};

/* method MSFT_ChefInSpecResource.GetTargetResource() */
MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    MSFT_ChefInSpecResource_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_quals), /* numQualifiers */
    MSFT_ChefInSpecResource_GetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_ChefInSpecResource_GetTargetResource_params), /* numParameters */
    sizeof(MSFT_ChefInSpecResource_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_ChefInSpecResource_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_Description_qual_value = MI_T("20");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_Static_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_ChefInSpecResource");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_InputResource_Description_qual_value = MI_T("21");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_InputResource_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_In_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_ChefInSpecResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_Flags_Description_qual_value = MI_T("22");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_Flags_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_Flags_In_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_Flags_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_Result_Description_qual_value = MI_T("23");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_Result_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_Result_Out_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_Result_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Description_qual_value = MI_T("24");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Out_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Description_qual_value = MI_T("20");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_MIReturn_quals[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Static_qual,
    &MSFT_ChefInSpecResource_TestTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_ChefInSpecResource_TestTargetResource_params[] =
{
    &MSFT_ChefInSpecResource_TestTargetResource_MIReturn_param,
    &MSFT_ChefInSpecResource_TestTargetResource_InputResource_param,
    &MSFT_ChefInSpecResource_TestTargetResource_Flags_param,
    &MSFT_ChefInSpecResource_TestTargetResource_Result_param,
    &MSFT_ChefInSpecResource_TestTargetResource_ProviderContext_param,
};

/* method MSFT_ChefInSpecResource.TestTargetResource() */
MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    MSFT_ChefInSpecResource_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_quals), /* numQualifiers */
    MSFT_ChefInSpecResource_TestTargetResource_params, /* parameters */
    MI_COUNT(MSFT_ChefInSpecResource_TestTargetResource_params), /* numParameters */
    sizeof(MSFT_ChefInSpecResource_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_ChefInSpecResource_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_Description_qual_value = MI_T("25");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_quals[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_Static_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_ChefInSpecResource");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_InputResource_Description_qual_value = MI_T("21");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_InputResource_quals[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_In_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_ChefInSpecResource_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_ChefInSpecResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_Description_qual_value = MI_T("26");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_quals[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_In_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_Flags_Description_qual_value = MI_T("22");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_Flags_quals[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_Flags_In_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_Flags_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_ChefInSpecResource_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Description_qual_value = MI_T("25");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_MIReturn_quals[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Static_qual,
    &MSFT_ChefInSpecResource_SetTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_ChefInSpecResource.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_ChefInSpecResource_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_ChefInSpecResource_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ChefInSpecResource_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_ChefInSpecResource_SetTargetResource_params[] =
{
    &MSFT_ChefInSpecResource_SetTargetResource_MIReturn_param,
    &MSFT_ChefInSpecResource_SetTargetResource_InputResource_param,
    &MSFT_ChefInSpecResource_SetTargetResource_ProviderContext_param,
    &MSFT_ChefInSpecResource_SetTargetResource_Flags_param,
};

/* method MSFT_ChefInSpecResource.SetTargetResource() */
MI_CONST MI_MethodDecl MSFT_ChefInSpecResource_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    MSFT_ChefInSpecResource_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_quals), /* numQualifiers */
    MSFT_ChefInSpecResource_SetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_ChefInSpecResource_SetTargetResource_params), /* numParameters */
    sizeof(MSFT_ChefInSpecResource_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_ChefInSpecResource"), /* origin */
    MI_T("MSFT_ChefInSpecResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_ChefInSpecResource_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_ChefInSpecResource_meths[] =
{
    &MSFT_ChefInSpecResource_GetTargetResource_rtti,
    &MSFT_ChefInSpecResource_TestTargetResource_rtti,
    &MSFT_ChefInSpecResource_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT MSFT_ChefInSpecResource_funcs =
{
  (MI_ProviderFT_Load)MSFT_ChefInSpecResource_Load,
  (MI_ProviderFT_Unload)MSFT_ChefInSpecResource_Unload,
  (MI_ProviderFT_GetInstance)MSFT_ChefInSpecResource_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_ChefInSpecResource_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_ChefInSpecResource_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_ChefInSpecResource_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_ChefInSpecResource_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ChefInSpecResource_Description_qual_value
};

static MI_CONST MI_Char* MSFT_ChefInSpecResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_ChefInSpecResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_ChefInSpecResource_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ChefInSpecResource_quals[] =
{
    &MSFT_ChefInSpecResource_Description_qual,
    &MSFT_ChefInSpecResource_ClassVersion_qual,
};

/* class MSFT_ChefInSpecResource */
MI_CONST MI_ClassDecl MSFT_ChefInSpecResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6517, /* code */
    MI_T("MSFT_ChefInSpecResource"), /* name */
    MSFT_ChefInSpecResource_quals, /* qualifiers */
    MI_COUNT(MSFT_ChefInSpecResource_quals), /* numQualifiers */
    MSFT_ChefInSpecResource_props, /* properties */
    MI_COUNT(MSFT_ChefInSpecResource_props), /* numProperties */
    sizeof(MSFT_ChefInSpecResource), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    MSFT_ChefInSpecResource_meths, /* methods */
    MI_COUNT(MSFT_ChefInSpecResource_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_ChefInSpecResource_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Error_ErrorType_Description_qual_value = MI_T("27");

static MI_CONST MI_Qualifier CIM_Error_ErrorType_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorType_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_ValueMap_qual_value =
{
    CIM_Error_ErrorType_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorType_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_Values_qual_data_value[] =
{
    MI_T("28"),
    MI_T("29"),
    MI_T("30"),
    MI_T("31"),
    MI_T("32"),
    MI_T("33"),
    MI_T("34"),
    MI_T("35"),
    MI_T("36"),
    MI_T("37"),
    MI_T("38"),
    MI_T("39"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_Values_qual_value =
{
    CIM_Error_ErrorType_Values_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorType_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.OtherErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorType_quals[] =
{
    &CIM_Error_ErrorType_Description_qual,
    &CIM_Error_ErrorType_ValueMap_qual,
    &CIM_Error_ErrorType_Values_qual,
    &CIM_Error_ErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorType_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorType"), /* name */
    CIM_Error_ErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorType_Description_qual_value = MI_T("40");

static MI_CONST MI_Qualifier CIM_Error_OtherErrorType_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OtherErrorType_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorType_quals[] =
{
    &CIM_Error_OtherErrorType_Description_qual,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorType_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F650E, /* code */
    MI_T("OtherErrorType"), /* name */
    CIM_Error_OtherErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_OwningEntity_Description_qual_value = MI_T("41");

static MI_CONST MI_Qualifier CIM_Error_OwningEntity_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OwningEntity_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OwningEntity_quals[] =
{
    &CIM_Error_OwningEntity_Description_qual,
};

/* property CIM_Error.OwningEntity */
static MI_CONST MI_PropertyDecl CIM_Error_OwningEntity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F790C, /* code */
    MI_T("OwningEntity"), /* name */
    CIM_Error_OwningEntity_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OwningEntity_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OwningEntity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean CIM_Error_MessageID_Required_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_MessageID_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageID_Required_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageID_Description_qual_value = MI_T("42");

static MI_CONST MI_Qualifier CIM_Error_MessageID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_MessageID_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageID_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.Message"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageID_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageID_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageID_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageID_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageID_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageID_quals[] =
{
    &CIM_Error_MessageID_Required_qual,
    &CIM_Error_MessageID_Description_qual,
    &CIM_Error_MessageID_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageID */
static MI_CONST MI_PropertyDecl CIM_Error_MessageID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D6409, /* code */
    MI_T("MessageID"), /* name */
    CIM_Error_MessageID_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageID), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_Message_Description_qual_value = MI_T("43");

static MI_CONST MI_Qualifier CIM_Error_Message_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_Message_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_Message_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_Message_ModelCorrespondence_qual_value =
{
    CIM_Error_Message_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_Message_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_Message_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Message_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_Message_quals[] =
{
    &CIM_Error_Message_Description_qual,
    &CIM_Error_Message_ModelCorrespondence_qual,
};

/* property CIM_Error.Message */
static MI_CONST MI_PropertyDecl CIM_Error_Message_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D6507, /* code */
    MI_T("Message"), /* name */
    CIM_Error_Message_quals, /* qualifiers */
    MI_COUNT(CIM_Error_Message_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, Message), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_MessageArguments_Description_qual_value = MI_T("44");

static MI_CONST MI_Qualifier CIM_Error_MessageArguments_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_MessageArguments_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.Message"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageArguments_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageArguments_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageArguments_quals[] =
{
    &CIM_Error_MessageArguments_Description_qual,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageArguments */
static MI_CONST MI_PropertyDecl CIM_Error_MessageArguments_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D7310, /* code */
    MI_T("MessageArguments"), /* name */
    CIM_Error_MessageArguments_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageArguments_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageArguments), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Description_qual_value = MI_T("45");

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_PerceivedSeverity_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_PerceivedSeverity_ValueMap_qual_value =
{
    CIM_Error_PerceivedSeverity_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_PerceivedSeverity_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_PerceivedSeverity_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Values_qual_data_value[] =
{
    MI_T("28"),
    MI_T("29"),
    MI_T("46"),
    MI_T("47"),
    MI_T("48"),
    MI_T("49"),
    MI_T("50"),
    MI_T("51"),
    MI_T("39"),
};

static MI_CONST MI_ConstStringA CIM_Error_PerceivedSeverity_Values_qual_value =
{
    CIM_Error_PerceivedSeverity_Values_qual_data_value,
    MI_COUNT(CIM_Error_PerceivedSeverity_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_PerceivedSeverity_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_PerceivedSeverity_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_PerceivedSeverity_quals[] =
{
    &CIM_Error_PerceivedSeverity_Description_qual,
    &CIM_Error_PerceivedSeverity_ValueMap_qual,
    &CIM_Error_PerceivedSeverity_Values_qual,
};

/* property CIM_Error.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Error_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    CIM_Error_PerceivedSeverity_quals, /* qualifiers */
    MI_COUNT(CIM_Error_PerceivedSeverity_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, PerceivedSeverity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_Description_qual_value = MI_T("52");

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCause_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T("30"),
    MI_T("31"),
    MI_T("32"),
    MI_T("33"),
    MI_T("34"),
    MI_T("35"),
    MI_T("36"),
    MI_T("37"),
    MI_T("38"),
    MI_T("39"),
    MI_T("40"),
    MI_T("41"),
    MI_T("42"),
    MI_T("43"),
    MI_T("44"),
    MI_T("45"),
    MI_T("46"),
    MI_T("47"),
    MI_T("48"),
    MI_T("49"),
    MI_T("50"),
    MI_T("51"),
    MI_T("52"),
    MI_T("53"),
    MI_T("54"),
    MI_T("55"),
    MI_T("56"),
    MI_T("57"),
    MI_T("58"),
    MI_T("59"),
    MI_T("60"),
    MI_T("61"),
    MI_T("62"),
    MI_T("63"),
    MI_T("64"),
    MI_T("65"),
    MI_T("66"),
    MI_T("67"),
    MI_T("68"),
    MI_T("69"),
    MI_T("70"),
    MI_T("71"),
    MI_T("72"),
    MI_T("73"),
    MI_T("74"),
    MI_T("75"),
    MI_T("76"),
    MI_T("77"),
    MI_T("78"),
    MI_T("79"),
    MI_T("80"),
    MI_T("81"),
    MI_T("82"),
    MI_T("83"),
    MI_T("84"),
    MI_T("85"),
    MI_T("86"),
    MI_T("87"),
    MI_T("88"),
    MI_T("89"),
    MI_T("90"),
    MI_T("91"),
    MI_T("92"),
    MI_T("93"),
    MI_T("94"),
    MI_T("95"),
    MI_T("96"),
    MI_T("97"),
    MI_T("98"),
    MI_T("99"),
    MI_T("100"),
    MI_T("101"),
    MI_T("102"),
    MI_T("103"),
    MI_T("104"),
    MI_T("105"),
    MI_T("106"),
    MI_T("107"),
    MI_T("108"),
    MI_T("109"),
    MI_T("110"),
    MI_T("111"),
    MI_T("112"),
    MI_T("113"),
    MI_T("114"),
    MI_T("115"),
    MI_T("116"),
    MI_T("117"),
    MI_T("118"),
    MI_T("119"),
    MI_T("120"),
    MI_T("121"),
    MI_T("122"),
    MI_T("123"),
    MI_T("124"),
    MI_T("125"),
    MI_T("126"),
    MI_T("127"),
    MI_T("128"),
    MI_T("129"),
    MI_T("130"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_ValueMap_qual_value =
{
    CIM_Error_ProbableCause_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCause_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_Values_qual_data_value[] =
{
    MI_T("28"),
    MI_T("29"),
    MI_T("53"),
    MI_T("54"),
    MI_T("55"),
    MI_T("56"),
    MI_T("57"),
    MI_T("58"),
    MI_T("59"),
    MI_T("60"),
    MI_T("61"),
    MI_T("62"),
    MI_T("63"),
    MI_T("64"),
    MI_T("65"),
    MI_T("66"),
    MI_T("67"),
    MI_T("68"),
    MI_T("69"),
    MI_T("70"),
    MI_T("71"),
    MI_T("72"),
    MI_T("73"),
    MI_T("74"),
    MI_T("75"),
    MI_T("76"),
    MI_T("77"),
    MI_T("78"),
    MI_T("79"),
    MI_T("80"),
    MI_T("81"),
    MI_T("82"),
    MI_T("83"),
    MI_T("84"),
    MI_T("85"),
    MI_T("86"),
    MI_T("87"),
    MI_T("88"),
    MI_T("89"),
    MI_T("90"),
    MI_T("91"),
    MI_T("92"),
    MI_T("93"),
    MI_T("94"),
    MI_T("95"),
    MI_T("96"),
    MI_T("97"),
    MI_T("32"),
    MI_T("98"),
    MI_T("99"),
    MI_T("100"),
    MI_T("101"),
    MI_T("102"),
    MI_T("103"),
    MI_T("104"),
    MI_T("105"),
    MI_T("106"),
    MI_T("107"),
    MI_T("108"),
    MI_T("109"),
    MI_T("110"),
    MI_T("111"),
    MI_T("112"),
    MI_T("113"),
    MI_T("114"),
    MI_T("115"),
    MI_T("116"),
    MI_T("117"),
    MI_T("118"),
    MI_T("119"),
    MI_T("120"),
    MI_T("121"),
    MI_T("122"),
    MI_T("123"),
    MI_T("124"),
    MI_T("125"),
    MI_T("126"),
    MI_T("127"),
    MI_T("128"),
    MI_T("129"),
    MI_T("130"),
    MI_T("131"),
    MI_T("132"),
    MI_T("133"),
    MI_T("134"),
    MI_T("135"),
    MI_T("136"),
    MI_T("137"),
    MI_T("138"),
    MI_T("139"),
    MI_T("140"),
    MI_T("141"),
    MI_T("142"),
    MI_T("143"),
    MI_T("144"),
    MI_T("145"),
    MI_T("146"),
    MI_T("147"),
    MI_T("148"),
    MI_T("149"),
    MI_T("150"),
    MI_T("151"),
    MI_T("152"),
    MI_T("153"),
    MI_T("154"),
    MI_T("155"),
    MI_T("156"),
    MI_T("157"),
    MI_T("158"),
    MI_T("159"),
    MI_T("160"),
    MI_T("161"),
    MI_T("162"),
    MI_T("163"),
    MI_T("164"),
    MI_T("165"),
    MI_T("166"),
    MI_T("167"),
    MI_T("168"),
    MI_T("169"),
    MI_T("170"),
    MI_T("171"),
    MI_T("172"),
    MI_T("173"),
    MI_T("174"),
    MI_T("175"),
    MI_T("176"),
    MI_T("177"),
    MI_T("178"),
    MI_T("179"),
    MI_T("180"),
    MI_T("39"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_Values_qual_value =
{
    CIM_Error_ProbableCause_Values_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCause_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCauseDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCause_quals[] =
{
    &CIM_Error_ProbableCause_Description_qual,
    &CIM_Error_ProbableCause_ValueMap_qual,
    &CIM_Error_ProbableCause_Values_qual,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCause */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCause_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0070650D, /* code */
    MI_T("ProbableCause"), /* name */
    CIM_Error_ProbableCause_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCause_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCause), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_Description_qual_value = MI_T("181");

static MI_CONST MI_Qualifier CIM_Error_ProbableCauseDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ProbableCauseDescription_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCause"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCauseDescription_quals[] =
{
    &CIM_Error_ProbableCauseDescription_Description_qual,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCauseDescription */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCauseDescription_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00706E18, /* code */
    MI_T("ProbableCauseDescription"), /* name */
    CIM_Error_ProbableCauseDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCauseDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCauseDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_RecommendedActions_Description_qual_value = MI_T("182");

static MI_CONST MI_Qualifier CIM_Error_RecommendedActions_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_RecommendedActions_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_RecommendedActions_quals[] =
{
    &CIM_Error_RecommendedActions_Description_qual,
};

/* property CIM_Error.RecommendedActions */
static MI_CONST MI_PropertyDecl CIM_Error_RecommendedActions_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00727312, /* code */
    MI_T("RecommendedActions"), /* name */
    CIM_Error_RecommendedActions_quals, /* qualifiers */
    MI_COUNT(CIM_Error_RecommendedActions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, RecommendedActions), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSource_Description_qual_value = MI_T("183");

static MI_CONST MI_Qualifier CIM_Error_ErrorSource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSource_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSource_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSource_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSource_quals[] =
{
    &CIM_Error_ErrorSource_Description_qual,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorSource */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSource_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650B, /* code */
    MI_T("ErrorSource"), /* name */
    CIM_Error_ErrorSource_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSource_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSource), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Description_qual_value = MI_T("184");

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSourceFormat_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value[] =
{
    MI_T("0"),
    MI_T("1"),
    MI_T("2"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_ValueMap_qual_value =
{
    CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSourceFormat_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Values_qual_data_value[] =
{
    MI_T("28"),
    MI_T("29"),
    MI_T("185"),
    MI_T("39"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_Values_qual_value =
{
    CIM_Error_ErrorSourceFormat_Values_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_ErrorSourceFormat_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSource"),
    MI_T("CIM_Error.OtherErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSourceFormat_quals[] =
{
    &CIM_Error_ErrorSourceFormat_Description_qual,
    &CIM_Error_ErrorSourceFormat_ValueMap_qual,
    &CIM_Error_ErrorSourceFormat_Values_qual,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_Error_ErrorSourceFormat_value = 0;

/* property CIM_Error.ErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00657411, /* code */
    MI_T("ErrorSourceFormat"), /* name */
    CIM_Error_ErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSourceFormat_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    &CIM_Error_ErrorSourceFormat_value,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_Description_qual_value = MI_T("186");

static MI_CONST MI_Qualifier CIM_Error_OtherErrorSourceFormat_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_OtherErrorSourceFormat_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorSourceFormat_quals[] =
{
    &CIM_Error_OtherErrorSourceFormat_Description_qual,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006F7416, /* code */
    MI_T("OtherErrorSourceFormat"), /* name */
    CIM_Error_OtherErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Description_qual_value = MI_T("187");

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCode_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T(".."),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_ValueMap_qual_value =
{
    CIM_Error_CIMStatusCode_ValueMap_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCode_ValueMap_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Values_qual_data_value[] =
{
    MI_T("188"),
    MI_T("189"),
    MI_T("190"),
    MI_T("191"),
    MI_T("192"),
    MI_T("193"),
    MI_T("194"),
    MI_T("195"),
    MI_T("196"),
    MI_T("197"),
    MI_T("198"),
    MI_T("199"),
    MI_T("200"),
    MI_T("201"),
    MI_T("202"),
    MI_T("203"),
    MI_T("204"),
    MI_T("205"),
    MI_T("206"),
    MI_T("207"),
    MI_T("208"),
    MI_T("209"),
    MI_T("210"),
    MI_T("211"),
    MI_T("212"),
    MI_T("213"),
    MI_T("214"),
    MI_T("215"),
    MI_T("216"),
    MI_T("39"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_Values_qual_value =
{
    CIM_Error_CIMStatusCode_Values_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_Values_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCode_Values_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCodeDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCode_quals[] =
{
    &CIM_Error_CIMStatusCode_Description_qual,
    &CIM_Error_CIMStatusCode_ValueMap_qual,
    &CIM_Error_CIMStatusCode_Values_qual,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCode */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCode_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063650D, /* code */
    MI_T("CIMStatusCode"), /* name */
    CIM_Error_CIMStatusCode_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCode_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCode), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_Description_qual_value = MI_T("217");

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCodeDescription_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_CIMStatusCodeDescription_Description_qual_value
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCode"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCodeDescription_quals[] =
{
    &CIM_Error_CIMStatusCodeDescription_Description_qual,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCodeDescription */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCodeDescription_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00636E18, /* code */
    MI_T("CIMStatusCodeDescription"), /* name */
    CIM_Error_CIMStatusCodeDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCodeDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
};

static MI_CONST MI_Boolean CIM_Error_Indication_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Indication_qual_value
};

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("218");

static MI_CONST MI_Qualifier CIM_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Error_Version_qual_value
};

static MI_CONST MI_Boolean CIM_Error_Exception_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Error_Exception_qual =
{
    MI_T("Exception"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_Exception_qual_value
};

static MI_CONST MI_Char* CIM_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Error_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Error_Description_qual_value = MI_T("219");

static MI_CONST MI_Qualifier CIM_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Error_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_quals[] =
{
    &CIM_Error_Indication_qual,
    &CIM_Error_Version_qual,
    &CIM_Error_Exception_qual,
    &CIM_Error_UMLPackagePath_qual,
    &CIM_Error_Description_qual,
};

/* class CIM_Error */
MI_CONST MI_ClassDecl CIM_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00637209, /* code */
    MI_T("CIM_Error"), /* name */
    CIM_Error_quals, /* qualifiers */
    MI_COUNT(CIM_Error_quals), /* numQualifiers */
    CIM_Error_props, /* properties */
    MI_COUNT(CIM_Error_props), /* numProperties */
    sizeof(CIM_Error), /* size */
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
** OMI_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* OMI_Error_error_Code_Description_qual_value = MI_T("220");

static MI_CONST MI_Qualifier OMI_Error_error_Code_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Code_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Code_quals[] =
{
    &OMI_Error_error_Code_Description_qual,
};

/* property OMI_Error.error_Code */
static MI_CONST MI_PropertyDecl OMI_Error_error_Code_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650A, /* code */
    MI_T("error_Code"), /* name */
    OMI_Error_error_Code_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Code_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Code), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_Error_error_Type_Description_qual_value = MI_T("221");

static MI_CONST MI_Qualifier OMI_Error_error_Type_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Type_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Type_quals[] =
{
    &OMI_Error_error_Type_Description_qual,
};

/* property OMI_Error.error_Type */
static MI_CONST MI_PropertyDecl OMI_Error_error_Type_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065650A, /* code */
    MI_T("error_Type"), /* name */
    OMI_Error_error_Type_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Type_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Type), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* OMI_Error_error_Category_Description_qual_value = MI_T("222");

static MI_CONST MI_Qualifier OMI_Error_error_Category_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Category_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_error_Category_Values_qual_data_value[] =
{
    MI_T("223"),
    MI_T("224"),
    MI_T("225"),
    MI_T("226"),
    MI_T("227"),
    MI_T("228"),
    MI_T("229"),
    MI_T("230"),
    MI_T("231"),
    MI_T("232"),
    MI_T("233"),
    MI_T("234"),
    MI_T("235"),
    MI_T("236"),
    MI_T("237"),
    MI_T("238"),
    MI_T("239"),
    MI_T("240"),
    MI_T("241"),
    MI_T("242"),
    MI_T("243"),
    MI_T("244"),
    MI_T("245"),
    MI_T("246"),
    MI_T("247"),
    MI_T("248"),
    MI_T("249"),
    MI_T("250"),
    MI_T("251"),
    MI_T("252"),
    MI_T("253"),
    MI_T("254"),
};

static MI_CONST MI_ConstStringA OMI_Error_error_Category_Values_qual_value =
{
    OMI_Error_error_Category_Values_qual_data_value,
    MI_COUNT(OMI_Error_error_Category_Values_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_Error_error_Category_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Category_Values_qual_value
};

static MI_CONST MI_Char* OMI_Error_error_Category_ValueMap_qual_data_value[] =
{
    MI_T("1"),
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
    MI_T("11"),
    MI_T("12"),
    MI_T("13"),
    MI_T("14"),
    MI_T("15"),
    MI_T("16"),
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
    MI_T("27"),
    MI_T("28"),
    MI_T("29"),
    MI_T("30"),
    MI_T("31"),
};

static MI_CONST MI_ConstStringA OMI_Error_error_Category_ValueMap_qual_value =
{
    OMI_Error_error_Category_ValueMap_qual_data_value,
    MI_COUNT(OMI_Error_error_Category_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier OMI_Error_error_Category_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_error_Category_ValueMap_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_error_Category_quals[] =
{
    &OMI_Error_error_Category_Description_qual,
    &OMI_Error_error_Category_Values_qual,
    &OMI_Error_error_Category_ValueMap_qual,
};

/* property OMI_Error.error_Category */
static MI_CONST MI_PropertyDecl OMI_Error_error_Category_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0065790E, /* code */
    MI_T("error_Category"), /* name */
    OMI_Error_error_Category_quals, /* qualifiers */
    MI_COUNT(OMI_Error_error_Category_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Error, error_Category), /* offset */
    MI_T("OMI_Error"), /* origin */
    MI_T("OMI_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
    &OMI_Error_error_Code_prop,
    &OMI_Error_error_Type_prop,
    &OMI_Error_error_Category_prop,
};

static MI_CONST MI_Boolean OMI_Error_Indication_qual_value = 1;

static MI_CONST MI_Qualifier OMI_Error_Indication_qual =
{
    MI_T("Indication"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_Indication_qual_value
};

static MI_CONST MI_Boolean OMI_Error_Exception_qual_value = 1;

static MI_CONST MI_Qualifier OMI_Error_Exception_qual =
{
    MI_T("Exception"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_Exception_qual_value
};

static MI_CONST MI_Char* OMI_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier OMI_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &OMI_Error_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* OMI_Error_Description_qual_value = MI_T("255");

static MI_CONST MI_Qualifier OMI_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_Version_qual_value = MI_T("218");

static MI_CONST MI_Qualifier OMI_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &OMI_Error_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST OMI_Error_quals[] =
{
    &OMI_Error_Indication_qual,
    &OMI_Error_Exception_qual,
    &OMI_Error_UMLPackagePath_qual,
    &OMI_Error_Description_qual,
    &OMI_Error_Version_qual,
};

/* class OMI_Error */
MI_CONST MI_ClassDecl OMI_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006F7209, /* code */
    MI_T("OMI_Error"), /* name */
    OMI_Error_quals, /* qualifiers */
    MI_COUNT(OMI_Error_quals), /* numQualifiers */
    OMI_Error_props, /* properties */
    MI_COUNT(OMI_Error_props), /* numProperties */
    sizeof(OMI_Error), /* size */
    MI_T("CIM_Error"), /* superClass */
    &CIM_Error_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** MSFT_DSCResource
**
**==============================================================================
*/

static MI_CONST MI_Char* MSFT_DSCResource_ResourceId_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier MSFT_DSCResource_ResourceId_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_ResourceId_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_ResourceId_Required_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_ResourceId_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_ResourceId_Required_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ResourceId_Override_qual_value = MI_T("ResourceId");

static MI_CONST MI_Qualifier MSFT_DSCResource_ResourceId_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_ResourceId_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_ResourceId_quals[] =
{
    &MSFT_DSCResource_ResourceId_Description_qual,
    &MSFT_DSCResource_ResourceId_Required_qual,
    &MSFT_DSCResource_ResourceId_Override_qual,
};

/* property MSFT_DSCResource.ResourceId */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_ResourceId_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x0072640A, /* code */
    MI_T("ResourceId"), /* name */
    MSFT_DSCResource_ResourceId_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_ResourceId_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, ResourceId), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCResource_SourceInfo_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier MSFT_DSCResource_SourceInfo_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_SourceInfo_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_SourceInfo_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_SourceInfo_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_SourceInfo_Write_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_SourceInfo_Override_qual_value = MI_T("SourceInfo");

static MI_CONST MI_Qualifier MSFT_DSCResource_SourceInfo_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_SourceInfo_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_SourceInfo_quals[] =
{
    &MSFT_DSCResource_SourceInfo_Description_qual,
    &MSFT_DSCResource_SourceInfo_Write_qual,
    &MSFT_DSCResource_SourceInfo_Override_qual,
};

/* property MSFT_DSCResource.SourceInfo */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_SourceInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736F0A, /* code */
    MI_T("SourceInfo"), /* name */
    MSFT_DSCResource_SourceInfo_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_SourceInfo_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, SourceInfo), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCResource_DependsOn_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier MSFT_DSCResource_DependsOn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_DependsOn_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_DependsOn_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_DependsOn_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_DependsOn_Write_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_DependsOn_Override_qual_value = MI_T("DependsOn");

static MI_CONST MI_Qualifier MSFT_DSCResource_DependsOn_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_DependsOn_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_DependsOn_quals[] =
{
    &MSFT_DSCResource_DependsOn_Description_qual,
    &MSFT_DSCResource_DependsOn_Write_qual,
    &MSFT_DSCResource_DependsOn_Override_qual,
};

/* property MSFT_DSCResource.DependsOn */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_DependsOn_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E09, /* code */
    MI_T("DependsOn"), /* name */
    MSFT_DSCResource_DependsOn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_DependsOn_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, DependsOn), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCResource_ModuleName_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_ModuleName_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_ModuleName_Required_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleName_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_ModuleName_Required_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ModuleName_Override_qual_value = MI_T("ModuleName");

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleName_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_ModuleName_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_ModuleName_quals[] =
{
    &MSFT_DSCResource_ModuleName_Description_qual,
    &MSFT_DSCResource_ModuleName_Required_qual,
    &MSFT_DSCResource_ModuleName_Override_qual,
};

/* property MSFT_DSCResource.ModuleName */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_ModuleName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D650A, /* code */
    MI_T("ModuleName"), /* name */
    MSFT_DSCResource_ModuleName_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_ModuleName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, ModuleName), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCResource_ModuleVersion_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleVersion_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_ModuleVersion_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_ModuleVersion_Required_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleVersion_Required_qual =
{
    MI_T("Required"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_ModuleVersion_Required_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ModuleVersion_Override_qual_value = MI_T("ModuleVersion");

static MI_CONST MI_Qualifier MSFT_DSCResource_ModuleVersion_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_ModuleVersion_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_ModuleVersion_quals[] =
{
    &MSFT_DSCResource_ModuleVersion_Description_qual,
    &MSFT_DSCResource_ModuleVersion_Required_qual,
    &MSFT_DSCResource_ModuleVersion_Override_qual,
};

/* property MSFT_DSCResource.ModuleVersion */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_ModuleVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED|MI_FLAG_READONLY, /* flags */
    0x006D6E0D, /* code */
    MI_T("ModuleVersion"), /* name */
    MSFT_DSCResource_ModuleVersion_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_ModuleVersion_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, ModuleVersion), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCResource_ConfigurationName_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier MSFT_DSCResource_ConfigurationName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_ConfigurationName_Description_qual_value
};

static MI_CONST MI_Boolean MSFT_DSCResource_ConfigurationName_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_ConfigurationName_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_ConfigurationName_Write_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ConfigurationName_Override_qual_value = MI_T("ConfigurationName");

static MI_CONST MI_Qualifier MSFT_DSCResource_ConfigurationName_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_ConfigurationName_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_ConfigurationName_quals[] =
{
    &MSFT_DSCResource_ConfigurationName_Description_qual,
    &MSFT_DSCResource_ConfigurationName_Write_qual,
    &MSFT_DSCResource_ConfigurationName_Override_qual,
};

/* property MSFT_DSCResource.ConfigurationName */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_ConfigurationName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636511, /* code */
    MI_T("ConfigurationName"), /* name */
    MSFT_DSCResource_ConfigurationName_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_ConfigurationName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, ConfigurationName), /* offset */
    MI_T("OMI_BaseResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_ResourceName_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_ResourceName_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_ResourceName_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ResourceName_Description_qual_value = MI_T("256");

static MI_CONST MI_Qualifier MSFT_DSCResource_ResourceName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_ResourceName_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_ResourceName_quals[] =
{
    &MSFT_DSCResource_ResourceName_Read_qual,
    &MSFT_DSCResource_ResourceName_Description_qual,
};

/* property MSFT_DSCResource.ResourceName */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_ResourceName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0072650C, /* code */
    MI_T("ResourceName"), /* name */
    MSFT_DSCResource_ResourceName_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_ResourceName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, ResourceName), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_InstanceName_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_InstanceName_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_InstanceName_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_InstanceName_Description_qual_value = MI_T("257");

static MI_CONST MI_Qualifier MSFT_DSCResource_InstanceName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_InstanceName_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_InstanceName_quals[] =
{
    &MSFT_DSCResource_InstanceName_Read_qual,
    &MSFT_DSCResource_InstanceName_Description_qual,
};

/* property MSFT_DSCResource.InstanceName */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_InstanceName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0069650C, /* code */
    MI_T("InstanceName"), /* name */
    MSFT_DSCResource_InstanceName_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_InstanceName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, InstanceName), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_InDesiredState_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_InDesiredState_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_InDesiredState_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_InDesiredState_Description_qual_value = MI_T("258");

static MI_CONST MI_Qualifier MSFT_DSCResource_InDesiredState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_InDesiredState_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_InDesiredState_quals[] =
{
    &MSFT_DSCResource_InDesiredState_Read_qual,
    &MSFT_DSCResource_InDesiredState_Description_qual,
};

/* property MSFT_DSCResource.InDesiredState */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_InDesiredState_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0069650E, /* code */
    MI_T("InDesiredState"), /* name */
    MSFT_DSCResource_InDesiredState_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_InDesiredState_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, InDesiredState), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_StateChanged_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_StateChanged_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_StateChanged_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_StateChanged_Description_qual_value = MI_T("259");

static MI_CONST MI_Qualifier MSFT_DSCResource_StateChanged_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_StateChanged_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_StateChanged_quals[] =
{
    &MSFT_DSCResource_StateChanged_Read_qual,
    &MSFT_DSCResource_StateChanged_Description_qual,
};

/* property MSFT_DSCResource.StateChanged */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_StateChanged_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0073640C, /* code */
    MI_T("StateChanged"), /* name */
    MSFT_DSCResource_StateChanged_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_StateChanged_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, StateChanged), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_StartDate_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_StartDate_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_StartDate_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_StartDate_Description_qual_value = MI_T("260");

static MI_CONST MI_Qualifier MSFT_DSCResource_StartDate_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_StartDate_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_StartDate_quals[] =
{
    &MSFT_DSCResource_StartDate_Read_qual,
    &MSFT_DSCResource_StartDate_Description_qual,
};

/* property MSFT_DSCResource.StartDate */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_StartDate_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00736509, /* code */
    MI_T("StartDate"), /* name */
    MSFT_DSCResource_StartDate_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_StartDate_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, StartDate), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_DurationInSeconds_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_DurationInSeconds_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_DurationInSeconds_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_DurationInSeconds_Description_qual_value = MI_T("261");

static MI_CONST MI_Qualifier MSFT_DSCResource_DurationInSeconds_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_DurationInSeconds_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_DurationInSeconds_quals[] =
{
    &MSFT_DSCResource_DurationInSeconds_Read_qual,
    &MSFT_DSCResource_DurationInSeconds_Description_qual,
};

/* property MSFT_DSCResource.DurationInSeconds */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_DurationInSeconds_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00647311, /* code */
    MI_T("DurationInSeconds"), /* name */
    MSFT_DSCResource_DurationInSeconds_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_DurationInSeconds_quals), /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, DurationInSeconds), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_RebootRequested_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_RebootRequested_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_RebootRequested_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_RebootRequested_Description_qual_value = MI_T("262");

static MI_CONST MI_Qualifier MSFT_DSCResource_RebootRequested_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_RebootRequested_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_RebootRequested_quals[] =
{
    &MSFT_DSCResource_RebootRequested_Read_qual,
    &MSFT_DSCResource_RebootRequested_Description_qual,
};

/* property MSFT_DSCResource.RebootRequested */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_RebootRequested_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0072640F, /* code */
    MI_T("RebootRequested"), /* name */
    MSFT_DSCResource_RebootRequested_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_RebootRequested_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, RebootRequested), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_InitialState_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_InitialState_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_InitialState_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_InitialState_Description_qual_value = MI_T("263");

static MI_CONST MI_Qualifier MSFT_DSCResource_InitialState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_InitialState_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_InitialState_quals[] =
{
    &MSFT_DSCResource_InitialState_Read_qual,
    &MSFT_DSCResource_InitialState_Description_qual,
};

/* property MSFT_DSCResource.InitialState */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_InitialState_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0069650C, /* code */
    MI_T("InitialState"), /* name */
    MSFT_DSCResource_InitialState_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_InitialState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, InitialState), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_FinalState_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_FinalState_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_FinalState_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_FinalState_Description_qual_value = MI_T("264");

static MI_CONST MI_Qualifier MSFT_DSCResource_FinalState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_FinalState_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_FinalState_quals[] =
{
    &MSFT_DSCResource_FinalState_Read_qual,
    &MSFT_DSCResource_FinalState_Description_qual,
};

/* property MSFT_DSCResource.FinalState */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_FinalState_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0066650A, /* code */
    MI_T("FinalState"), /* name */
    MSFT_DSCResource_FinalState_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_FinalState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, FinalState), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_DSCResource_Error_Read_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCResource_Error_Read_qual =
{
    MI_T("Read"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCResource_Error_Read_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_Error_Description_qual_value = MI_T("265");

static MI_CONST MI_Qualifier MSFT_DSCResource_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_Error_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_Error_quals[] =
{
    &MSFT_DSCResource_Error_Read_qual,
    &MSFT_DSCResource_Error_Description_qual,
};

/* property MSFT_DSCResource.Error */
static MI_CONST MI_PropertyDecl MSFT_DSCResource_Error_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00657205, /* code */
    MI_T("Error"), /* name */
    MSFT_DSCResource_Error_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_Error_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCResource, Error), /* offset */
    MI_T("MSFT_DSCResource"), /* origin */
    MI_T("MSFT_DSCResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_DSCResource_props[] =
{
    &MSFT_DSCResource_ResourceId_prop,
    &MSFT_DSCResource_SourceInfo_prop,
    &MSFT_DSCResource_DependsOn_prop,
    &MSFT_DSCResource_ModuleName_prop,
    &MSFT_DSCResource_ModuleVersion_prop,
    &MSFT_DSCResource_ConfigurationName_prop,
    &OMI_BaseResource_PsDscRunAsCredential_prop,
    &MSFT_DSCResource_ResourceName_prop,
    &MSFT_DSCResource_InstanceName_prop,
    &MSFT_DSCResource_InDesiredState_prop,
    &MSFT_DSCResource_StateChanged_prop,
    &MSFT_DSCResource_StartDate_prop,
    &MSFT_DSCResource_DurationInSeconds_prop,
    &MSFT_DSCResource_RebootRequested_prop,
    &MSFT_DSCResource_InitialState_prop,
    &MSFT_DSCResource_FinalState_prop,
    &MSFT_DSCResource_Error_prop,
};

static MI_CONST MI_Char* MSFT_DSCResource_Description_qual_value = MI_T("266");

static MI_CONST MI_Qualifier MSFT_DSCResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCResource_Description_qual_value
};

static MI_CONST MI_Char* MSFT_DSCResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_DSCResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCResource_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCResource_quals[] =
{
    &MSFT_DSCResource_Description_qual,
    &MSFT_DSCResource_ClassVersion_qual,
};

/* class MSFT_DSCResource */
MI_CONST MI_ClassDecl MSFT_DSCResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6510, /* code */
    MI_T("MSFT_DSCResource"), /* name */
    MSFT_DSCResource_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCResource_quals), /* numQualifiers */
    MSFT_DSCResource_props, /* properties */
    MI_COUNT(MSFT_DSCResource_props), /* numProperties */
    sizeof(MSFT_DSCResource), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
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
    &CIM_Error_rtti,
    &InSpec_Controls_rtti,
    &InSpec_Results_rtti,
    &InSpec_Statistics_rtti,
    &MSFT_ChefInSpecResource_rtti,
    &MSFT_Credential_rtti,
    &MSFT_DSCResource_rtti,
    &OMI_BaseResource_rtti,
    &OMI_Error_rtti,
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

