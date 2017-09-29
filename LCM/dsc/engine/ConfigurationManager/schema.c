/* @migen@ */
/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <ctype.h>
#include <MI.h>
#include "MSFT_DSCLocalConfigurationManager.h"
#include "MSFT_DSCWebPullClient.h"
#include "MSFT_DSCMetaConfiguration.h"
#include "OMI_Error.h"

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
** MSFT_DSCMetaConfiguration
**
**==============================================================================
*/

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_Description_qual_value = MI_T("341");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_quals[] =
{
    &MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.ConfigurationModeFrequencyMins */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063731E, /* code */
    MI_T("ConfigurationModeFrequencyMins"), /* name */
    MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationModeFrequencyMins_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationModeFrequencyMins), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_Description_qual_value = MI_T("355");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_quals[] =
{
    &MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.RebootNodeIfNeeded */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00726412, /* code */
    MI_T("RebootNodeIfNeeded"), /* name */
    MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_RebootNodeIfNeeded_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, RebootNodeIfNeeded), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationMode_Description_qual_value = MI_T("356");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationMode_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_ConfigurationMode_Description_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationMode_ValueMap_qual_data_value[] =
{
    MI_T("ApplyOnly"),
    MI_T("ApplyAndMonitor"),
    MI_T("ApplyAndAutoCorrect"),
    MI_T("MonitorOnly")
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
    &MSFT_DSCMetaConfiguration_ConfigurationMode_Description_qual,
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

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_Credential_Description_qual_value = MI_T("354");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_Credential_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_Credential_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_Credential_quals[] =
{
    &MSFT_DSCMetaConfiguration_Credential_EmbeddedInstance_qual,
    &MSFT_DSCMetaConfiguration_Credential_Description_qual,
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

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_RefreshMode_Description_qual_value = MI_T("366");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_RefreshMode_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_RefreshMode_Description_qual_value
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
    &MSFT_DSCMetaConfiguration_RefreshMode_Description_qual,
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

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_CertificateID_Description_qual_value = MI_T("344");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_CertificateID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_CertificateID_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_CertificateID_quals[] =
{
    &MSFT_DSCMetaConfiguration_CertificateID_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.CertificateID */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_CertificateID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063640D, /* code */
    MI_T("CertificateID"), /* name */
    MSFT_DSCMetaConfiguration_CertificateID_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_CertificateID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, CertificateID), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ConfigurationID_Description_qual_value = MI_T("346");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ConfigurationID_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_ConfigurationID_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_ConfigurationID_quals[] =
{
    &MSFT_DSCMetaConfiguration_ConfigurationID_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.ConfigurationID */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_ConfigurationID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x0063640F, /* code */
    MI_T("ConfigurationID"), /* name */
    MSFT_DSCMetaConfiguration_ConfigurationID_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_ConfigurationID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, ConfigurationID), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_DownloadManagerName_Description_qual_value = MI_T("347");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_DownloadManagerName_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_DownloadManagerName_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_DownloadManagerName_quals[] =
{
    &MSFT_DSCMetaConfiguration_DownloadManagerName_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.DownloadManagerName */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_DownloadManagerName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00646513, /* code */
    MI_T("DownloadManagerName"), /* name */
    MSFT_DSCMetaConfiguration_DownloadManagerName_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_DownloadManagerName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, DownloadManagerName), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_DownloadManagerCustomData_Description_qual_value = MI_T("348");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_DownloadManagerCustomData_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_DownloadManagerCustomData_Description_qual_value
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
    &MSFT_DSCMetaConfiguration_DownloadManagerCustomData_Description_qual,
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

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_RefreshFrequencyMins_Description_qual_value = MI_T("349");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_RefreshFrequencyMins_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_RefreshFrequencyMins_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_RefreshFrequencyMins_quals[] =
{
    &MSFT_DSCMetaConfiguration_RefreshFrequencyMins_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.RefreshFrequencyMins */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_RefreshFrequencyMins_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00727314, /* code */
    MI_T("RefreshFrequencyMins"), /* name */
    MSFT_DSCMetaConfiguration_RefreshFrequencyMins_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_RefreshFrequencyMins_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, RefreshFrequencyMins), /* offset */
    MI_T("MSFT_DSCMetaConfiguration"), /* origin */
    MI_T("MSFT_DSCMetaConfiguration"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_AllowModuleOverwrite_Description_qual_value = MI_T("389");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_AllowModuleOverwrite_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_AllowModuleOverwrite_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_AllowModuleOverwrite_quals[] =
{
    &MSFT_DSCMetaConfiguration_AllowModuleOverwrite_Description_qual,
};

/* property MSFT_DSCMetaConfiguration.AllowModuleOverwrite */
static MI_CONST MI_PropertyDecl MSFT_DSCMetaConfiguration_AllowModuleOverwrite_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x00616514, /* code */
    MI_T("AllowModuleOverwrite"), /* name */
    MSFT_DSCMetaConfiguration_AllowModuleOverwrite_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCMetaConfiguration_AllowModuleOverwrite_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCMetaConfiguration, AllowModuleOverwrite), /* offset */
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

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Description_qual_value = MI_T("423");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Description_qual_value
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
    MI_T("421"),
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
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_Description_qual,
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
    &MSFT_DSCMetaConfiguration_LocalConfigurationManagerState_prop,
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCMetaConfiguration_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_DSCMetaConfiguration_Description_qual_value = MI_T("350");

static MI_CONST MI_Qualifier MSFT_DSCMetaConfiguration_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCMetaConfiguration_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCMetaConfiguration_quals[] =
{
    &MSFT_DSCMetaConfiguration_ClassVersion_qual,
    &MSFT_DSCMetaConfiguration_Description_qual,
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

static MI_CONST MI_Boolean MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Stream_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Stream_qual =
{
    MI_T("Stream"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Stream_qual_value
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
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Stream_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_EmbeddedInstance_qual,
    &MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_Out_qual,
};

/* parameter MSFT_DSCLocalConfigurationManager.GetConfiguration(): configurations */
static MI_CONST MI_ParameterDecl MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x0063730E, /* code */
    MI_T("configurations"), /* name */
    MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCLocalConfigurationManager_GetConfiguration_configurations_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
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

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_ApplyConfiguration_Description_qual_value = MI_T("426");

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

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_ApplyConfiguration_MIReturn_Description_qual_value = MI_T("426");

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

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_Description_qual_value = MI_T("281");

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

static MI_CONST MI_Char* MSFT_DSCLocalConfigurationManager_PerformRequiredConfigurationChecks_MIReturn_Description_qual_value = MI_T("281");

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
** MSFT_ModuleSpecification
**
**==============================================================================
*/

/* property MSFT_ModuleSpecification.ModuleName */
static MI_CONST MI_PropertyDecl MSFT_ModuleSpecification_ModuleName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D650A, /* code */
    MI_T("ModuleName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ModuleSpecification, ModuleName), /* offset */
    MI_T("MSFT_ModuleSpecification"), /* origin */
    MI_T("MSFT_ModuleSpecification"), /* propagator */
    NULL,
};

/* property MSFT_ModuleSpecification.ModuleVersion */
static MI_CONST MI_PropertyDecl MSFT_ModuleSpecification_ModuleVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_READONLY, /* flags */
    0x006D6E0D, /* code */
    MI_T("ModuleVersion"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_ModuleSpecification, ModuleVersion), /* offset */
    MI_T("MSFT_ModuleSpecification"), /* origin */
    MI_T("MSFT_ModuleSpecification"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_ModuleSpecification_props[] =
{
    &MSFT_ModuleSpecification_ModuleName_prop,
    &MSFT_ModuleSpecification_ModuleVersion_prop,
};

static MI_CONST MI_Boolean MSFT_ModuleSpecification_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_ModuleSpecification_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_ModuleSpecification_Abstract_qual_value
};

static MI_CONST MI_Char* MSFT_ModuleSpecification_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_ModuleSpecification_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_ModuleSpecification_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_ModuleSpecification_Description_qual_value = MI_T("427");

static MI_CONST MI_Qualifier MSFT_ModuleSpecification_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_ModuleSpecification_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_ModuleSpecification_quals[] =
{
    &MSFT_ModuleSpecification_Abstract_qual,
    &MSFT_ModuleSpecification_ClassVersion_qual,
    &MSFT_ModuleSpecification_Description_qual,
};

/* class MSFT_ModuleSpecification */
MI_CONST MI_ClassDecl MSFT_ModuleSpecification_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x006D6E18, /* code */
    MI_T("MSFT_ModuleSpecification"), /* name */
    MSFT_ModuleSpecification_quals, /* qualifiers */
    MI_COUNT(MSFT_ModuleSpecification_quals), /* numQualifiers */
    MSFT_ModuleSpecification_props, /* properties */
    MI_COUNT(MSFT_ModuleSpecification_props), /* numProperties */
    sizeof(MSFT_ModuleSpecification), /* size */
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
** MSFT_DSCWebPullClient
**
**==============================================================================
*/


static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCAction_Description_qual_value = MI_T("428");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCAction_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCAction_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_FileHash_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_FileHash_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_FileHash_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_FileHash_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_FileHash_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): FileHash */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_FileHash_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666808, /* code */
    MI_T("FileHash"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_FileHash_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_FileHash_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, FileHash), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): ConfigurationID */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063640F, /* code */
    MI_T("ConfigurationID"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, ConfigurationID), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): NotCompliant */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E740C, /* code */
    MI_T("NotCompliant"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, NotCompliant), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_StatusCode_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_StatusCode_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_StatusCode_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_StatusCode_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_StatusCode_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): StatusCode */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_StatusCode_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073650A, /* code */
    MI_T("StatusCode"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_StatusCode_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_StatusCode_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, StatusCode), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_Credential_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_Credential_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_Credential_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCAction_Credential_EmbeddedInstance_qual_value = MI_T("MSFT_Credential");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_Credential_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_Credential_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_Credential_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_Credential_In_qual,
    &MSFT_DSCWebPullClient_GetDSCAction_Credential_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): Credential */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_Credential_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636C0A, /* code */
    MI_T("Credential"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_Credential_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_Credential_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Credential"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, Credential), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_CustomData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_CustomData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_CustomData_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCAction_CustomData_EmbeddedInstance_qual_value = MI_T("MSFT_KeyValuePair");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_CustomData_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_CustomData_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_CustomData_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_CustomData_In_qual,
    &MSFT_DSCWebPullClient_GetDSCAction_CustomData_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): CustomData */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_CustomData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063610A, /* code */
    MI_T("CustomData"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_CustomData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_CustomData_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_KeyValuePair"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, CustomData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_Result_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_Result_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_Result_Out_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): Result */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_Result_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, Result), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Description_qual_value = MI_T("428");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_MIReturn_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCAction_MIReturn_Description_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCAction(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCAction_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCAction, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCAction_params[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_MIReturn_param,
    &MSFT_DSCWebPullClient_GetDSCAction_FileHash_param,
    &MSFT_DSCWebPullClient_GetDSCAction_ConfigurationID_param,
    &MSFT_DSCWebPullClient_GetDSCAction_NotCompliant_param,
    &MSFT_DSCWebPullClient_GetDSCAction_StatusCode_param,
    &MSFT_DSCWebPullClient_GetDSCAction_Credential_param,
    &MSFT_DSCWebPullClient_GetDSCAction_CustomData_param,
    &MSFT_DSCWebPullClient_GetDSCAction_Result_param,
};

/* method MSFT_DSCWebPullClient.GetDSCAction() */
MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCAction_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676E0C, /* code */
    MI_T("GetDSCAction"), /* name */
    MSFT_DSCWebPullClient_GetDSCAction_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_quals), /* numQualifiers */
    MSFT_DSCWebPullClient_GetDSCAction_params, /* parameters */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCAction_params), /* numParameters */
    sizeof(MSFT_DSCWebPullClient_GetDSCAction), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCWebPullClient"), /* origin */
    MI_T("MSFT_DSCWebPullClient"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCWebPullClient_Invoke_GetDSCAction, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCDocument_Description_qual_value = MI_T("429");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCDocument_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCDocument_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): ConfigurationID */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063640F, /* code */
    MI_T("ConfigurationID"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, ConfigurationID), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): DestinationPath */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064680F, /* code */
    MI_T("DestinationPath"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, DestinationPath), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_Credential_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_Credential_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_Credential_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCDocument_Credential_EmbeddedInstance_qual_value = MI_T("MSFT_Credential");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_Credential_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_Credential_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_Credential_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_Credential_In_qual,
    &MSFT_DSCWebPullClient_GetDSCDocument_Credential_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): Credential */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_Credential_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636C0A, /* code */
    MI_T("Credential"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_Credential_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_Credential_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Credential"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, Credential), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_CustomData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_CustomData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_CustomData_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCDocument_CustomData_EmbeddedInstance_qual_value = MI_T("MSFT_KeyValuePair");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_CustomData_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_CustomData_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_CustomData_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_CustomData_In_qual,
    &MSFT_DSCWebPullClient_GetDSCDocument_CustomData_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): CustomData */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_CustomData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063610A, /* code */
    MI_T("CustomData"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_CustomData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_CustomData_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_KeyValuePair"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, CustomData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_Result_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_Result_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_Result_Out_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): Result */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_Result_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, Result), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Description_qual_value = MI_T("429");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_Description_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCDocument(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCDocument, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCDocument_params[] =
{
    &MSFT_DSCWebPullClient_GetDSCDocument_MIReturn_param,
    &MSFT_DSCWebPullClient_GetDSCDocument_ConfigurationID_param,
    &MSFT_DSCWebPullClient_GetDSCDocument_DestinationPath_param,
    &MSFT_DSCWebPullClient_GetDSCDocument_Credential_param,
    &MSFT_DSCWebPullClient_GetDSCDocument_CustomData_param,
    &MSFT_DSCWebPullClient_GetDSCDocument_Result_param,
};

/* method MSFT_DSCWebPullClient.GetDSCDocument() */
MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCDocument_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067740E, /* code */
    MI_T("GetDSCDocument"), /* name */
    MSFT_DSCWebPullClient_GetDSCDocument_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_quals), /* numQualifiers */
    MSFT_DSCWebPullClient_GetDSCDocument_params, /* parameters */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCDocument_params), /* numParameters */
    sizeof(MSFT_DSCWebPullClient_GetDSCDocument), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCWebPullClient"), /* origin */
    MI_T("MSFT_DSCWebPullClient"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCWebPullClient_Invoke_GetDSCDocument, /* method */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCModule_Description_qual_value = MI_T("430");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCModule_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCModule_Description_qual,
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): ConfigurationID */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063640F, /* code */
    MI_T("ConfigurationID"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, ConfigurationID), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_In_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_In_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): DestinationPath */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064680F, /* code */
    MI_T("DestinationPath"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, DestinationPath), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_Credential_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Credential_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Credential_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCModule_Credential_EmbeddedInstance_qual_value = MI_T("MSFT_Credential");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Credential_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Credential_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_Credential_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_Credential_In_qual,
    &MSFT_DSCWebPullClient_GetDSCModule_Credential_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): Credential */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_Credential_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636C0A, /* code */
    MI_T("Credential"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_Credential_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_Credential_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Credential"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, Credential), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_CustomData_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_CustomData_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_CustomData_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCModule_CustomData_EmbeddedInstance_qual_value = MI_T("MSFT_KeyValuePair");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_CustomData_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_CustomData_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_CustomData_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_CustomData_In_qual,
    &MSFT_DSCWebPullClient_GetDSCModule_CustomData_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): CustomData */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_CustomData_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063610A, /* code */
    MI_T("CustomData"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_CustomData_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_CustomData_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_KeyValuePair"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, CustomData), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_Module_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Module_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Module_In_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCModule_Module_EmbeddedInstance_qual_value = MI_T("MSFT_ModuleSpecification");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Module_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Module_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_Module_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_Module_In_qual,
    &MSFT_DSCWebPullClient_GetDSCModule_Module_EmbeddedInstance_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): Module */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_Module_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D6506, /* code */
    MI_T("Module"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_Module_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_Module_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_ModuleSpecification"), /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, Module), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_Result_Out_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_Result_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_Result_Out_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): Result */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_Result_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, Result), /* offset */
};

static MI_CONST MI_Boolean MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Description_qual_value = MI_T("430");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_MIReturn_quals[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Static_qual,
    &MSFT_DSCWebPullClient_GetDSCModule_MIReturn_Description_qual,
};

/* parameter MSFT_DSCWebPullClient.GetDSCModule(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_DSCWebPullClient_GetDSCModule_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DSCWebPullClient_GetDSCModule, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_DSCWebPullClient_GetDSCModule_params[] =
{
    &MSFT_DSCWebPullClient_GetDSCModule_MIReturn_param,
    &MSFT_DSCWebPullClient_GetDSCModule_ConfigurationID_param,
    &MSFT_DSCWebPullClient_GetDSCModule_DestinationPath_param,
    &MSFT_DSCWebPullClient_GetDSCModule_Credential_param,
    &MSFT_DSCWebPullClient_GetDSCModule_CustomData_param,
    &MSFT_DSCWebPullClient_GetDSCModule_Module_param,
    &MSFT_DSCWebPullClient_GetDSCModule_Result_param,
};

/* method MSFT_DSCWebPullClient.GetDSCModule() */
MI_CONST MI_MethodDecl MSFT_DSCWebPullClient_GetDSCModule_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067650C, /* code */
    MI_T("GetDSCModule"), /* name */
    MSFT_DSCWebPullClient_GetDSCModule_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_quals), /* numQualifiers */
    MSFT_DSCWebPullClient_GetDSCModule_params, /* parameters */
    MI_COUNT(MSFT_DSCWebPullClient_GetDSCModule_params), /* numParameters */
    sizeof(MSFT_DSCWebPullClient_GetDSCModule), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_DSCWebPullClient"), /* origin */
    MI_T("MSFT_DSCWebPullClient"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_DSCWebPullClient_Invoke_GetDSCModule, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_DSCWebPullClient_meths[] =
{
    &MSFT_DSCWebPullClient_GetDSCAction_rtti,
    &MSFT_DSCWebPullClient_GetDSCDocument_rtti,
    &MSFT_DSCWebPullClient_GetDSCModule_rtti,
};

static MI_CONST MI_ProviderFT MSFT_DSCWebPullClient_funcs =
{
  (MI_ProviderFT_Load)MSFT_DSCWebPullClient_Load,
  (MI_ProviderFT_Unload)MSFT_DSCWebPullClient_Unload,
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

static MI_CONST MI_Char* MSFT_DSCWebPullClient_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_DSCWebPullClient_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_DSCWebPullClient_Description_qual_value = MI_T("431");

static MI_CONST MI_Qualifier MSFT_DSCWebPullClient_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_DSCWebPullClient_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_DSCWebPullClient_quals[] =
{
    &MSFT_DSCWebPullClient_ClassVersion_qual,
    &MSFT_DSCWebPullClient_Description_qual,
};

/* class MSFT_DSCWebPullClient */
MI_CONST MI_ClassDecl MSFT_DSCWebPullClient_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7415, /* code */
    MI_T("MSFT_DSCWebPullClient"), /* name */
    MSFT_DSCWebPullClient_quals, /* qualifiers */
    MI_COUNT(MSFT_DSCWebPullClient_quals), /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(MSFT_DSCWebPullClient), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MSFT_DSCWebPullClient_meths, /* methods */
    MI_COUNT(MSFT_DSCWebPullClient_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_DSCWebPullClient_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Error_ErrorType_Description_qual_value = MI_T("35");

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

static MI_CONST MI_Char* CIM_Error_OtherErrorType_Description_qual_value = MI_T("48");

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

static MI_CONST MI_Char* CIM_Error_OwningEntity_Description_qual_value = MI_T("49");

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

static MI_CONST MI_Char* CIM_Error_MessageID_Description_qual_value = MI_T("50");

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

static MI_CONST MI_Char* CIM_Error_Message_Description_qual_value = MI_T("51");

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

static MI_CONST MI_Char* CIM_Error_MessageArguments_Description_qual_value = MI_T("52");

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

static MI_CONST MI_Char* CIM_Error_PerceivedSeverity_Description_qual_value = MI_T("53");

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
    MI_T("36"),
    MI_T("37"),
    MI_T("54"),
    MI_T("55"),
    MI_T("56"),
    MI_T("57"),
    MI_T("58"),
    MI_T("59"),
    MI_T("47"),
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

static MI_CONST MI_Char* CIM_Error_ProbableCause_Description_qual_value = MI_T("60");

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
    MI_T("36"),
    MI_T("37"),
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
    MI_T("40"),
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
    MI_T("181"),
    MI_T("182"),
    MI_T("183"),
    MI_T("184"),
    MI_T("185"),
    MI_T("186"),
    MI_T("187"),
    MI_T("188"),
    MI_T("47"),
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

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_Description_qual_value = MI_T("189");

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

static MI_CONST MI_Char* CIM_Error_RecommendedActions_Description_qual_value = MI_T("190");

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

static MI_CONST MI_Char* CIM_Error_ErrorSource_Description_qual_value = MI_T("191");

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

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_Description_qual_value = MI_T("192");

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
    MI_T("36"),
    MI_T("37"),
    MI_T("193"),
    MI_T("47"),
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

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_Description_qual_value = MI_T("194");

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

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_Description_qual_value = MI_T("195");

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
    MI_T("217"),
    MI_T("218"),
    MI_T("219"),
    MI_T("220"),
    MI_T("221"),
    MI_T("222"),
    MI_T("223"),
    MI_T("224"),
    MI_T("47"),
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

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_Description_qual_value = MI_T("225");

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

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("226");

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

static MI_CONST MI_Char* CIM_Error_Description_qual_value = MI_T("227");

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

static MI_CONST MI_Char* OMI_Error_error_Code_Description_qual_value = MI_T("382");

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

static MI_CONST MI_Char* OMI_Error_error_Type_Description_qual_value = MI_T("413");

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

static MI_CONST MI_Char* OMI_Error_error_Category_Description_qual_value = MI_T("403");

static MI_CONST MI_Qualifier OMI_Error_error_Category_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_error_Category_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_error_Category_Values_qual_data_value[] =
{
    MI_T("231"),
    MI_T("232"),
    MI_T("233"),
    MI_T("408"),
    MI_T("235"),
    MI_T("236"),
    MI_T("409"),
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
    MI_T("410"),
    MI_T("249"),
    MI_T("250"),
    MI_T("251"),
    MI_T("252"),
    MI_T("253"),
    MI_T("254"),
    MI_T("255"),
    MI_T("256"),
    MI_T("257"),
    MI_T("258"),
    MI_T("259"),
    MI_T("260"),
    MI_T("261"),
    MI_T("262"),
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

static MI_CONST MI_Char* OMI_Error_Description_qual_value = MI_T("407");

static MI_CONST MI_Qualifier OMI_Error_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &OMI_Error_Description_qual_value
};

static MI_CONST MI_Char* OMI_Error_Version_qual_value = MI_T("226");

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
    &MSFT_Credential_rtti,
    &MSFT_DSCLocalConfigurationManager_rtti,
    &MSFT_DSCMetaConfiguration_rtti,
    &MSFT_DSCWebPullClient_rtti,
    &MSFT_KeyValuePair_rtti,
    &MSFT_ModuleSpecification_rtti,
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

