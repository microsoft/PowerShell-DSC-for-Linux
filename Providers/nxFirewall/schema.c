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
#include "MSFT_nxFirewallResource.h"

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
** MSFT_nxFirewallResource
**
**==============================================================================
*/

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Name_Key_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Name_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Name_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Name_quals[] =
{
    &MSFT_nxFirewallResource_Name_Key_qual,
};

/* property MSFT_nxFirewallResource.Name */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    MSFT_nxFirewallResource_Name_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Name), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_InterfaceName_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_InterfaceName_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_InterfaceName_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_InterfaceName_quals[] =
{
    &MSFT_nxFirewallResource_InterfaceName_Write_qual,
};

/* property MSFT_nxFirewallResource.InterfaceName */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_InterfaceName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650D, /* code */
    MI_T("InterfaceName"), /* name */
    MSFT_nxFirewallResource_InterfaceName_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_InterfaceName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, InterfaceName), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_FirewallType_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_FirewallType_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_FirewallType_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_FirewallType_ValueMap_qual_data_value[] =
{
    MI_T("Iptables"),
    MI_T("Ip6tables"),
    MI_T("yast"),
    MI_T("ufw"),
    MI_T("susefirewall2"),
    MI_T("firewalld"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_FirewallType_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_FirewallType_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_FirewallType_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_FirewallType_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_FirewallType_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_FirewallType_Values_qual_data_value[] =
{
    MI_T("2"),
    MI_T("3"),
    MI_T("4"),
    MI_T("5"),
    MI_T("6"),
    MI_T("7"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_FirewallType_Values_qual_value =
{
    MSFT_nxFirewallResource_FirewallType_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_FirewallType_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_FirewallType_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_FirewallType_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_FirewallType_quals[] =
{
    &MSFT_nxFirewallResource_FirewallType_Write_qual,
    &MSFT_nxFirewallResource_FirewallType_ValueMap_qual,
    &MSFT_nxFirewallResource_FirewallType_Values_qual,
};

/* property MSFT_nxFirewallResource.FirewallType */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_FirewallType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066650C, /* code */
    MI_T("FirewallType"), /* name */
    MSFT_nxFirewallResource_FirewallType_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_FirewallType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, FirewallType), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Protocol_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Protocol_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Protocol_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Protocol_ValueMap_qual_data_value[] =
{
    MI_T("tcp"),
    MI_T("udp"),
    MI_T("icmp"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Protocol_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_Protocol_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Protocol_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Protocol_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Protocol_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Protocol_Values_qual_data_value[] =
{
    MI_T("8"),
    MI_T("9"),
    MI_T("10"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Protocol_Values_qual_value =
{
    MSFT_nxFirewallResource_Protocol_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Protocol_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Protocol_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Protocol_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Protocol_quals[] =
{
    &MSFT_nxFirewallResource_Protocol_Write_qual,
    &MSFT_nxFirewallResource_Protocol_ValueMap_qual,
    &MSFT_nxFirewallResource_Protocol_Values_qual,
};

/* property MSFT_nxFirewallResource.Protocol */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Protocol_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706C08, /* code */
    MI_T("Protocol"), /* name */
    MSFT_nxFirewallResource_Protocol_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Protocol_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Protocol), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Ensure_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Ensure_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Ensure_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Ensure_ValueMap_qual_data_value[] =
{
    MI_T("Present"),
    MI_T("Absent"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Ensure_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_Ensure_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Ensure_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Ensure_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Ensure_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Ensure_Values_qual_data_value[] =
{
    MI_T("11"),
    MI_T("12"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Ensure_Values_qual_value =
{
    MSFT_nxFirewallResource_Ensure_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Ensure_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Ensure_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Ensure_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Ensure_quals[] =
{
    &MSFT_nxFirewallResource_Ensure_Write_qual,
    &MSFT_nxFirewallResource_Ensure_ValueMap_qual,
    &MSFT_nxFirewallResource_Ensure_Values_qual,
};

/* property MSFT_nxFirewallResource.Ensure */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Ensure_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656506, /* code */
    MI_T("Ensure"), /* name */
    MSFT_nxFirewallResource_Ensure_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Ensure_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Ensure), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_AddressFamily_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_AddressFamily_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_AddressFamily_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_AddressFamily_ValueMap_qual_data_value[] =
{
    MI_T("IPv4"),
    MI_T("IPv6"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_AddressFamily_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_AddressFamily_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_AddressFamily_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_AddressFamily_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_AddressFamily_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_AddressFamily_Values_qual_data_value[] =
{
    MI_T("13"),
    MI_T("14"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_AddressFamily_Values_qual_value =
{
    MSFT_nxFirewallResource_AddressFamily_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_AddressFamily_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_AddressFamily_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_AddressFamily_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_AddressFamily_quals[] =
{
    &MSFT_nxFirewallResource_AddressFamily_Write_qual,
    &MSFT_nxFirewallResource_AddressFamily_ValueMap_qual,
    &MSFT_nxFirewallResource_AddressFamily_Values_qual,
};

/* property MSFT_nxFirewallResource.AddressFamily */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_AddressFamily_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061790D, /* code */
    MI_T("AddressFamily"), /* name */
    MSFT_nxFirewallResource_AddressFamily_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_AddressFamily_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, AddressFamily), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Access_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Access_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Access_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Access_ValueMap_qual_data_value[] =
{
    MI_T("Allow"),
    MI_T("Block"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Access_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_Access_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Access_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Access_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Access_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Access_Values_qual_data_value[] =
{
    MI_T("15"),
    MI_T("16"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Access_Values_qual_value =
{
    MSFT_nxFirewallResource_Access_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Access_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Access_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Access_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Access_quals[] =
{
    &MSFT_nxFirewallResource_Access_Write_qual,
    &MSFT_nxFirewallResource_Access_ValueMap_qual,
    &MSFT_nxFirewallResource_Access_Values_qual,
};

/* property MSFT_nxFirewallResource.Access */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Access_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617306, /* code */
    MI_T("Access"), /* name */
    MSFT_nxFirewallResource_Access_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Access_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Access), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_State_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_State_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_State_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_State_ValueMap_qual_data_value[] =
{
    MI_T("ESTABLISHED"),
    MI_T("RELATED"),
    MI_T("NEW"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_State_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_State_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_State_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_State_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_State_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_State_Values_qual_data_value[] =
{
    MI_T("17"),
    MI_T("18"),
    MI_T("19"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_State_Values_qual_value =
{
    MSFT_nxFirewallResource_State_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_State_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_State_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_State_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_State_quals[] =
{
    &MSFT_nxFirewallResource_State_Write_qual,
    &MSFT_nxFirewallResource_State_ValueMap_qual,
    &MSFT_nxFirewallResource_State_Values_qual,
};

/* property MSFT_nxFirewallResource.State */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_State_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736505, /* code */
    MI_T("State"), /* name */
    MSFT_nxFirewallResource_State_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_State_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, State), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Direction_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Direction_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Direction_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Direction_ValueMap_qual_data_value[] =
{
    MI_T("INPUT"),
    MI_T("OUTPUT"),
    MI_T("FORWARD"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Direction_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_Direction_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Direction_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Direction_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Direction_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Direction_Values_qual_data_value[] =
{
    MI_T("20"),
    MI_T("21"),
    MI_T("22"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Direction_Values_qual_value =
{
    MSFT_nxFirewallResource_Direction_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Direction_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Direction_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Direction_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Direction_quals[] =
{
    &MSFT_nxFirewallResource_Direction_Write_qual,
    &MSFT_nxFirewallResource_Direction_ValueMap_qual,
    &MSFT_nxFirewallResource_Direction_Values_qual,
};

/* property MSFT_nxFirewallResource.Direction */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Direction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E09, /* code */
    MI_T("Direction"), /* name */
    MSFT_nxFirewallResource_Direction_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Direction_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Direction), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SourceHost_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SourceHost_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SourceHost_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SourceHost_quals[] =
{
    &MSFT_nxFirewallResource_SourceHost_Write_qual,
};

/* property MSFT_nxFirewallResource.SourceHost */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_SourceHost_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740A, /* code */
    MI_T("SourceHost"), /* name */
    MSFT_nxFirewallResource_SourceHost_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SourceHost_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, SourceHost), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SourcePort_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SourcePort_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SourcePort_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SourcePort_quals[] =
{
    &MSFT_nxFirewallResource_SourcePort_Write_qual,
};

/* property MSFT_nxFirewallResource.SourcePort */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_SourcePort_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740A, /* code */
    MI_T("SourcePort"), /* name */
    MSFT_nxFirewallResource_SourcePort_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SourcePort_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, SourcePort), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_DestinationHost_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_DestinationHost_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_DestinationHost_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_DestinationHost_quals[] =
{
    &MSFT_nxFirewallResource_DestinationHost_Write_qual,
};

/* property MSFT_nxFirewallResource.DestinationHost */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_DestinationHost_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064740F, /* code */
    MI_T("DestinationHost"), /* name */
    MSFT_nxFirewallResource_DestinationHost_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_DestinationHost_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, DestinationHost), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_DestinationPort_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_DestinationPort_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_DestinationPort_Write_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_DestinationPort_quals[] =
{
    &MSFT_nxFirewallResource_DestinationPort_Write_qual,
};

/* property MSFT_nxFirewallResource.DestinationPort */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_DestinationPort_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064740F, /* code */
    MI_T("DestinationPort"), /* name */
    MSFT_nxFirewallResource_DestinationPort_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_DestinationPort_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, DestinationPort), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_Position_Write_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Position_Write_qual =
{
    MI_T("Write"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Position_Write_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Position_ValueMap_qual_data_value[] =
{
    MI_T("top"),
    MI_T("after-top"),
    MI_T("before-end"),
    MI_T("end"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Position_ValueMap_qual_value =
{
    MSFT_nxFirewallResource_Position_ValueMap_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Position_ValueMap_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Position_ValueMap_qual =
{
    MI_T("ValueMap"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_Position_ValueMap_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Position_Values_qual_data_value[] =
{
    MI_T("23"),
    MI_T("24"),
    MI_T("25"),
    MI_T("26"),
};

static MI_CONST MI_ConstStringA MSFT_nxFirewallResource_Position_Values_qual_value =
{
    MSFT_nxFirewallResource_Position_Values_qual_data_value,
    MI_COUNT(MSFT_nxFirewallResource_Position_Values_qual_data_value),
};

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Position_Values_qual =
{
    MI_T("Values"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Position_Values_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_Position_quals[] =
{
    &MSFT_nxFirewallResource_Position_Write_qual,
    &MSFT_nxFirewallResource_Position_ValueMap_qual,
    &MSFT_nxFirewallResource_Position_Values_qual,
};

/* property MSFT_nxFirewallResource.Position */
static MI_CONST MI_PropertyDecl MSFT_nxFirewallResource_Position_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E08, /* code */
    MI_T("Position"), /* name */
    MSFT_nxFirewallResource_Position_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_Position_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource, Position), /* offset */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_nxFirewallResource_props[] =
{
    &MSFT_nxFirewallResource_Name_prop,
    &MSFT_nxFirewallResource_InterfaceName_prop,
    &MSFT_nxFirewallResource_FirewallType_prop,
    &MSFT_nxFirewallResource_Protocol_prop,
    &MSFT_nxFirewallResource_Ensure_prop,
    &MSFT_nxFirewallResource_AddressFamily_prop,
    &MSFT_nxFirewallResource_Access_prop,
    &MSFT_nxFirewallResource_State_prop,
    &MSFT_nxFirewallResource_Direction_prop,
    &MSFT_nxFirewallResource_SourceHost_prop,
    &MSFT_nxFirewallResource_SourcePort_prop,
    &MSFT_nxFirewallResource_DestinationHost_prop,
    &MSFT_nxFirewallResource_DestinationPort_prop,
    &MSFT_nxFirewallResource_Position_prop,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_Description_qual_value = MI_T("27");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_quals[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_Static_qual,
    &MSFT_nxFirewallResource_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxFirewallResource");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_InputResource_Description_qual_value = MI_T("28");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_InputResource_quals[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_In_qual,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_nxFirewallResource.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxFirewallResource_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxFirewallResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_Flags_Description_qual_value = MI_T("29");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_Flags_quals[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_Flags_In_qual,
    &MSFT_nxFirewallResource_GetTargetResource_Flags_Description_qual,
};

/* parameter MSFT_nxFirewallResource.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_nxFirewallResource_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxFirewallResource");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_OutputResource_Description_qual_value = MI_T("30");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_OutputResource_quals[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_Out_qual,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_Description_qual,
};

/* parameter MSFT_nxFirewallResource.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    MSFT_nxFirewallResource_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxFirewallResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_GetTargetResource_MIReturn_Description_qual_value = MI_T("27");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_MIReturn_quals[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_MIReturn_Static_qual,
    &MSFT_nxFirewallResource_GetTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_nxFirewallResource.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_nxFirewallResource_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxFirewallResource_GetTargetResource_params[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_MIReturn_param,
    &MSFT_nxFirewallResource_GetTargetResource_InputResource_param,
    &MSFT_nxFirewallResource_GetTargetResource_Flags_param,
    &MSFT_nxFirewallResource_GetTargetResource_OutputResource_param,
};

/* method MSFT_nxFirewallResource.GetTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxFirewallResource_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    MSFT_nxFirewallResource_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_quals), /* numQualifiers */
    MSFT_nxFirewallResource_GetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxFirewallResource_GetTargetResource_params), /* numParameters */
    sizeof(MSFT_nxFirewallResource_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxFirewallResource_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_Description_qual_value = MI_T("31");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_Static_qual,
    &MSFT_nxFirewallResource_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxFirewallResource");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_InputResource_Description_qual_value = MI_T("32");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_InputResource_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_In_qual,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_nxFirewallResource.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxFirewallResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_Flags_Description_qual_value = MI_T("33");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_Flags_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_Flags_In_qual,
    &MSFT_nxFirewallResource_TestTargetResource_Flags_Description_qual,
};

/* parameter MSFT_nxFirewallResource.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_Result_Description_qual_value = MI_T("34");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_Result_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_Result_Out_qual,
    &MSFT_nxFirewallResource_TestTargetResource_Result_Description_qual,
};

/* parameter MSFT_nxFirewallResource.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Description_qual_value = MI_T("35");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_ProviderContext_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Out_qual,
    &MSFT_nxFirewallResource_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter MSFT_nxFirewallResource.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_TestTargetResource_MIReturn_Description_qual_value = MI_T("31");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_MIReturn_quals[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_MIReturn_Static_qual,
    &MSFT_nxFirewallResource_TestTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_nxFirewallResource.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxFirewallResource_TestTargetResource_params[] =
{
    &MSFT_nxFirewallResource_TestTargetResource_MIReturn_param,
    &MSFT_nxFirewallResource_TestTargetResource_InputResource_param,
    &MSFT_nxFirewallResource_TestTargetResource_Flags_param,
    &MSFT_nxFirewallResource_TestTargetResource_Result_param,
    &MSFT_nxFirewallResource_TestTargetResource_ProviderContext_param,
};

/* method MSFT_nxFirewallResource.TestTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxFirewallResource_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    MSFT_nxFirewallResource_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_quals), /* numQualifiers */
    MSFT_nxFirewallResource_TestTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxFirewallResource_TestTargetResource_params), /* numParameters */
    sizeof(MSFT_nxFirewallResource_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxFirewallResource_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_Description_qual_value = MI_T("36");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_quals[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_Static_qual,
    &MSFT_nxFirewallResource_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("MSFT_nxFirewallResource");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_InputResource_Description_qual_value = MI_T("32");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_InputResource_quals[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_In_qual,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_Description_qual,
};

/* parameter MSFT_nxFirewallResource.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    MSFT_nxFirewallResource_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_nxFirewallResource"), /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_ProviderContext_Description_qual_value = MI_T("37");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_ProviderContext_quals[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_ProviderContext_In_qual,
    &MSFT_nxFirewallResource_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter MSFT_nxFirewallResource.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    MSFT_nxFirewallResource_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_Flags_Description_qual_value = MI_T("33");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_Flags_quals[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_Flags_In_qual,
    &MSFT_nxFirewallResource_SetTargetResource_Flags_Description_qual,
};

/* parameter MSFT_nxFirewallResource.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    MSFT_nxFirewallResource_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean MSFT_nxFirewallResource_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &MSFT_nxFirewallResource_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_SetTargetResource_MIReturn_Description_qual_value = MI_T("36");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_MIReturn_quals[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_MIReturn_Static_qual,
    &MSFT_nxFirewallResource_SetTargetResource_MIReturn_Description_qual,
};

/* parameter MSFT_nxFirewallResource.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_nxFirewallResource_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    MSFT_nxFirewallResource_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_nxFirewallResource_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_nxFirewallResource_SetTargetResource_params[] =
{
    &MSFT_nxFirewallResource_SetTargetResource_MIReturn_param,
    &MSFT_nxFirewallResource_SetTargetResource_InputResource_param,
    &MSFT_nxFirewallResource_SetTargetResource_ProviderContext_param,
    &MSFT_nxFirewallResource_SetTargetResource_Flags_param,
};

/* method MSFT_nxFirewallResource.SetTargetResource() */
MI_CONST MI_MethodDecl MSFT_nxFirewallResource_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    MSFT_nxFirewallResource_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_quals), /* numQualifiers */
    MSFT_nxFirewallResource_SetTargetResource_params, /* parameters */
    MI_COUNT(MSFT_nxFirewallResource_SetTargetResource_params), /* numParameters */
    sizeof(MSFT_nxFirewallResource_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_nxFirewallResource"), /* origin */
    MI_T("MSFT_nxFirewallResource"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_nxFirewallResource_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_nxFirewallResource_meths[] =
{
    &MSFT_nxFirewallResource_GetTargetResource_rtti,
    &MSFT_nxFirewallResource_TestTargetResource_rtti,
    &MSFT_nxFirewallResource_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT MSFT_nxFirewallResource_funcs =
{
  (MI_ProviderFT_Load)MSFT_nxFirewallResource_Load,
  (MI_ProviderFT_Unload)MSFT_nxFirewallResource_Unload,
  (MI_ProviderFT_GetInstance)MSFT_nxFirewallResource_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_nxFirewallResource_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_nxFirewallResource_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_nxFirewallResource_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_nxFirewallResource_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_Description_qual_value = MI_T("1");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &MSFT_nxFirewallResource_Description_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &MSFT_nxFirewallResource_ClassVersion_qual_value
};

static MI_CONST MI_Char* MSFT_nxFirewallResource_FriendlyName_qual_value = MI_T("nxFirewall");

static MI_CONST MI_Qualifier MSFT_nxFirewallResource_FriendlyName_qual =
{
    MI_T("FriendlyName"),
    MI_STRING,
    MI_FLAG_RESTRICTED,
    &MSFT_nxFirewallResource_FriendlyName_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MSFT_nxFirewallResource_quals[] =
{
    &MSFT_nxFirewallResource_Description_qual,
    &MSFT_nxFirewallResource_ClassVersion_qual,
    &MSFT_nxFirewallResource_FriendlyName_qual,
};

/* class MSFT_nxFirewallResource */
MI_CONST MI_ClassDecl MSFT_nxFirewallResource_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6517, /* code */
    MI_T("MSFT_nxFirewallResource"), /* name */
    MSFT_nxFirewallResource_quals, /* qualifiers */
    MI_COUNT(MSFT_nxFirewallResource_quals), /* numQualifiers */
    MSFT_nxFirewallResource_props, /* properties */
    MI_COUNT(MSFT_nxFirewallResource_props), /* numProperties */
    sizeof(MSFT_nxFirewallResource), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    MSFT_nxFirewallResource_meths, /* methods */
    MI_COUNT(MSFT_nxFirewallResource_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_nxFirewallResource_funcs, /* functions */
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
    &MSFT_nxFirewallResource_rtti,
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

