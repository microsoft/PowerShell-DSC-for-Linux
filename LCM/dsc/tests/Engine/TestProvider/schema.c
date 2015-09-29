/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
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
#include "TEST_Test1.h"
#include "TEST_Test2.h"
#include "TEST_Stop.h"
#include "TEST_Test4NoOMI.h"
#include "Test_Test3User.h"

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
** TEST_Test1
**
**==============================================================================
*/

static MI_CONST MI_Boolean TEST_Test1_Id1_Key_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_Id1_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_Id1_Key_qual_value
};

static MI_CONST MI_Char* TEST_Test1_Id1_Description_qual_value = MI_T("2");

static MI_CONST MI_Qualifier TEST_Test1_Id1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_Id1_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_Id1_quals[] =
{
    &TEST_Test1_Id1_Key_qual,
    &TEST_Test1_Id1_Description_qual,
};

/* property TEST_Test1.Id1 */
static MI_CONST MI_PropertyDecl TEST_Test1_Id1_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00693103, /* code */
    MI_T("Id1"), /* name */
    TEST_Test1_Id1_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_Id1_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1, Id1), /* offset */
    MI_T("TEST_Test1"), /* origin */
    MI_T("TEST_Test1"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TEST_Test1_props[] =
{
    &TEST_Test1_Id1_prop,
};

static MI_CONST MI_Boolean TEST_Test1_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_GetTargetResource_quals[] =
{
    &TEST_Test1_GetTargetResource_Static_qual,
    &TEST_Test1_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test1_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_GetTargetResource_InputResource_quals[] =
{
    &TEST_Test1_GetTargetResource_InputResource_In_qual,
    &TEST_Test1_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test1_GetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test1.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test1_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test1_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test1_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_GetTargetResource_Flags_quals[] =
{
    &TEST_Test1_GetTargetResource_Flags_In_qual,
    &TEST_Test1_GetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test1.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test1_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test1_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_OutputResource_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_GetTargetResource_OutputResource_quals[] =
{
    &TEST_Test1_GetTargetResource_OutputResource_Out_qual,
    &TEST_Test1_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &TEST_Test1_GetTargetResource_OutputResource_Description_qual,
};

/* parameter TEST_Test1.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl TEST_Test1_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    TEST_Test1_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test1_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_GetTargetResource_MIReturn_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test1_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_GetTargetResource_MIReturn_quals[] =
{
    &TEST_Test1_GetTargetResource_MIReturn_Static_qual,
    &TEST_Test1_GetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test1.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test1_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test1_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test1_GetTargetResource_params[] =
{
    &TEST_Test1_GetTargetResource_MIReturn_param,
    &TEST_Test1_GetTargetResource_InputResource_param,
    &TEST_Test1_GetTargetResource_Flags_param,
    &TEST_Test1_GetTargetResource_OutputResource_param,
};

/* method TEST_Test1.GetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test1_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    TEST_Test1_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_GetTargetResource_quals), /* numQualifiers */
    TEST_Test1_GetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test1_GetTargetResource_params), /* numParameters */
    sizeof(TEST_Test1_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test1"), /* origin */
    MI_T("TEST_Test1"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test1_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_quals[] =
{
    &TEST_Test1_TestTargetResource_Static_qual,
    &TEST_Test1_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_InputResource_quals[] =
{
    &TEST_Test1_TestTargetResource_InputResource_In_qual,
    &TEST_Test1_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test1_TestTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test1.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test1_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test1_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test1_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_Flags_quals[] =
{
    &TEST_Test1_TestTargetResource_Flags_In_qual,
    &TEST_Test1_TestTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test1.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test1_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test1_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_Result_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_Result_quals[] =
{
    &TEST_Test1_TestTargetResource_Result_Out_qual,
    &TEST_Test1_TestTargetResource_Result_Description_qual,
};

/* parameter TEST_Test1.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl TEST_Test1_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    TEST_Test1_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_ProviderContext_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_ProviderContext_quals[] =
{
    &TEST_Test1_TestTargetResource_ProviderContext_Out_qual,
    &TEST_Test1_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test1.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test1_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test1_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_TestTargetResource_MIReturn_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test1_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_TestTargetResource_MIReturn_quals[] =
{
    &TEST_Test1_TestTargetResource_MIReturn_Static_qual,
    &TEST_Test1_TestTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test1.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test1_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test1_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test1_TestTargetResource_params[] =
{
    &TEST_Test1_TestTargetResource_MIReturn_param,
    &TEST_Test1_TestTargetResource_InputResource_param,
    &TEST_Test1_TestTargetResource_Flags_param,
    &TEST_Test1_TestTargetResource_Result_param,
    &TEST_Test1_TestTargetResource_ProviderContext_param,
};

/* method TEST_Test1.TestTargetResource() */
MI_CONST MI_MethodDecl TEST_Test1_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    TEST_Test1_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_TestTargetResource_quals), /* numQualifiers */
    TEST_Test1_TestTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test1_TestTargetResource_params), /* numParameters */
    sizeof(TEST_Test1_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test1"), /* origin */
    MI_T("TEST_Test1"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test1_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test1_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_SetTargetResource_quals[] =
{
    &TEST_Test1_SetTargetResource_Static_qual,
    &TEST_Test1_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test1_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_SetTargetResource_InputResource_quals[] =
{
    &TEST_Test1_SetTargetResource_InputResource_In_qual,
    &TEST_Test1_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test1_SetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test1.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test1_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test1_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test1_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_ProviderContext_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_SetTargetResource_ProviderContext_quals[] =
{
    &TEST_Test1_SetTargetResource_ProviderContext_In_qual,
    &TEST_Test1_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test1.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test1_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test1_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_SetTargetResource_Flags_quals[] =
{
    &TEST_Test1_SetTargetResource_Flags_In_qual,
    &TEST_Test1_SetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test1.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test1_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test1_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test1_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test1_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test1_SetTargetResource_MIReturn_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test1_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_SetTargetResource_MIReturn_quals[] =
{
    &TEST_Test1_SetTargetResource_MIReturn_Static_qual,
    &TEST_Test1_SetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test1.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test1_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test1_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test1_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test1_SetTargetResource_params[] =
{
    &TEST_Test1_SetTargetResource_MIReturn_param,
    &TEST_Test1_SetTargetResource_InputResource_param,
    &TEST_Test1_SetTargetResource_ProviderContext_param,
    &TEST_Test1_SetTargetResource_Flags_param,
};

/* method TEST_Test1.SetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test1_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    TEST_Test1_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_SetTargetResource_quals), /* numQualifiers */
    TEST_Test1_SetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test1_SetTargetResource_params), /* numParameters */
    sizeof(TEST_Test1_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test1"), /* origin */
    MI_T("TEST_Test1"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test1_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TEST_Test1_meths[] =
{
    &TEST_Test1_GetTargetResource_rtti,
    &TEST_Test1_TestTargetResource_rtti,
    &TEST_Test1_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT TEST_Test1_funcs =
{
  (MI_ProviderFT_Load)TEST_Test1_Load,
  (MI_ProviderFT_Unload)TEST_Test1_Unload,
  (MI_ProviderFT_GetInstance)TEST_Test1_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TEST_Test1_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TEST_Test1_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TEST_Test1_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TEST_Test1_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* TEST_Test1_Description_qual_value = MI_T("12");

static MI_CONST MI_Qualifier TEST_Test1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test1_Description_qual_value
};

static MI_CONST MI_Char* TEST_Test1_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier TEST_Test1_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &TEST_Test1_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test1_quals[] =
{
    &TEST_Test1_Description_qual,
    &TEST_Test1_ClassVersion_qual,
};

/* class TEST_Test1 */
MI_CONST MI_ClassDecl TEST_Test1_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074310A, /* code */
    MI_T("TEST_Test1"), /* name */
    TEST_Test1_quals, /* qualifiers */
    MI_COUNT(TEST_Test1_quals), /* numQualifiers */
    TEST_Test1_props, /* properties */
    MI_COUNT(TEST_Test1_props), /* numProperties */
    sizeof(TEST_Test1), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    TEST_Test1_meths, /* methods */
    MI_COUNT(TEST_Test1_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TEST_Test1_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** TEST_Test2
**
**==============================================================================
*/

static MI_CONST MI_Boolean TEST_Test2_Id1_Key_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_Id1_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_Id1_Key_qual_value
};

static MI_CONST MI_Char* TEST_Test2_Id1_Description_qual_value = MI_T("2");

static MI_CONST MI_Qualifier TEST_Test2_Id1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_Id1_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_Id1_quals[] =
{
    &TEST_Test2_Id1_Key_qual,
    &TEST_Test2_Id1_Description_qual,
};

/* property TEST_Test2.Id1 */
static MI_CONST MI_PropertyDecl TEST_Test2_Id1_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00693103, /* code */
    MI_T("Id1"), /* name */
    TEST_Test2_Id1_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_Id1_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2, Id1), /* offset */
    MI_T("TEST_Test2"), /* origin */
    MI_T("TEST_Test2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TEST_Test2_props[] =
{
    &TEST_Test2_Id1_prop,
};

static MI_CONST MI_Boolean TEST_Test2_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_GetTargetResource_quals[] =
{
    &TEST_Test2_GetTargetResource_Static_qual,
    &TEST_Test2_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test2_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_GetTargetResource_InputResource_quals[] =
{
    &TEST_Test2_GetTargetResource_InputResource_In_qual,
    &TEST_Test2_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test2_GetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test2.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test2_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test2_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test2_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_GetTargetResource_Flags_quals[] =
{
    &TEST_Test2_GetTargetResource_Flags_In_qual,
    &TEST_Test2_GetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test2.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test2_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test2_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_OutputResource_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_GetTargetResource_OutputResource_quals[] =
{
    &TEST_Test2_GetTargetResource_OutputResource_Out_qual,
    &TEST_Test2_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &TEST_Test2_GetTargetResource_OutputResource_Description_qual,
};

/* parameter TEST_Test2.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl TEST_Test2_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    TEST_Test2_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test2_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_GetTargetResource_MIReturn_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test2_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_GetTargetResource_MIReturn_quals[] =
{
    &TEST_Test2_GetTargetResource_MIReturn_Static_qual,
    &TEST_Test2_GetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test2.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test2_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test2_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test2_GetTargetResource_params[] =
{
    &TEST_Test2_GetTargetResource_MIReturn_param,
    &TEST_Test2_GetTargetResource_InputResource_param,
    &TEST_Test2_GetTargetResource_Flags_param,
    &TEST_Test2_GetTargetResource_OutputResource_param,
};

/* method TEST_Test2.GetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test2_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    TEST_Test2_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_GetTargetResource_quals), /* numQualifiers */
    TEST_Test2_GetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test2_GetTargetResource_params), /* numParameters */
    sizeof(TEST_Test2_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test2"), /* origin */
    MI_T("TEST_Test2"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test2_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_quals[] =
{
    &TEST_Test2_TestTargetResource_Static_qual,
    &TEST_Test2_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_InputResource_quals[] =
{
    &TEST_Test2_TestTargetResource_InputResource_In_qual,
    &TEST_Test2_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test2_TestTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test2.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test2_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test2_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test2_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_Flags_quals[] =
{
    &TEST_Test2_TestTargetResource_Flags_In_qual,
    &TEST_Test2_TestTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test2.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test2_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test2_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_Result_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_Result_quals[] =
{
    &TEST_Test2_TestTargetResource_Result_Out_qual,
    &TEST_Test2_TestTargetResource_Result_Description_qual,
};

/* parameter TEST_Test2.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl TEST_Test2_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    TEST_Test2_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_ProviderContext_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_ProviderContext_quals[] =
{
    &TEST_Test2_TestTargetResource_ProviderContext_Out_qual,
    &TEST_Test2_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test2.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test2_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test2_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_TestTargetResource_MIReturn_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test2_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_TestTargetResource_MIReturn_quals[] =
{
    &TEST_Test2_TestTargetResource_MIReturn_Static_qual,
    &TEST_Test2_TestTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test2.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test2_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test2_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test2_TestTargetResource_params[] =
{
    &TEST_Test2_TestTargetResource_MIReturn_param,
    &TEST_Test2_TestTargetResource_InputResource_param,
    &TEST_Test2_TestTargetResource_Flags_param,
    &TEST_Test2_TestTargetResource_Result_param,
    &TEST_Test2_TestTargetResource_ProviderContext_param,
};

/* method TEST_Test2.TestTargetResource() */
MI_CONST MI_MethodDecl TEST_Test2_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    TEST_Test2_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_TestTargetResource_quals), /* numQualifiers */
    TEST_Test2_TestTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test2_TestTargetResource_params), /* numParameters */
    sizeof(TEST_Test2_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test2"), /* origin */
    MI_T("TEST_Test2"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test2_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test2_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_SetTargetResource_quals[] =
{
    &TEST_Test2_SetTargetResource_Static_qual,
    &TEST_Test2_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test2_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_SetTargetResource_InputResource_quals[] =
{
    &TEST_Test2_SetTargetResource_InputResource_In_qual,
    &TEST_Test2_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test2_SetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test2.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test2_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test2_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test2_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_ProviderContext_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_SetTargetResource_ProviderContext_quals[] =
{
    &TEST_Test2_SetTargetResource_ProviderContext_In_qual,
    &TEST_Test2_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test2.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test2_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test2_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_SetTargetResource_Flags_quals[] =
{
    &TEST_Test2_SetTargetResource_Flags_In_qual,
    &TEST_Test2_SetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test2.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test2_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test2_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test2_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test2_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test2_SetTargetResource_MIReturn_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test2_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_SetTargetResource_MIReturn_quals[] =
{
    &TEST_Test2_SetTargetResource_MIReturn_Static_qual,
    &TEST_Test2_SetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test2.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test2_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test2_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test2_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test2_SetTargetResource_params[] =
{
    &TEST_Test2_SetTargetResource_MIReturn_param,
    &TEST_Test2_SetTargetResource_InputResource_param,
    &TEST_Test2_SetTargetResource_ProviderContext_param,
    &TEST_Test2_SetTargetResource_Flags_param,
};

/* method TEST_Test2.SetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test2_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    TEST_Test2_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_SetTargetResource_quals), /* numQualifiers */
    TEST_Test2_SetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test2_SetTargetResource_params), /* numParameters */
    sizeof(TEST_Test2_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test2"), /* origin */
    MI_T("TEST_Test2"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test2_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TEST_Test2_meths[] =
{
    &TEST_Test2_GetTargetResource_rtti,
    &TEST_Test2_TestTargetResource_rtti,
    &TEST_Test2_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT TEST_Test2_funcs =
{
  (MI_ProviderFT_Load)TEST_Test2_Load,
  (MI_ProviderFT_Unload)TEST_Test2_Unload,
  (MI_ProviderFT_GetInstance)TEST_Test2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TEST_Test2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TEST_Test2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TEST_Test2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TEST_Test2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* TEST_Test2_Description_qual_value = MI_T("12");

static MI_CONST MI_Qualifier TEST_Test2_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test2_Description_qual_value
};

static MI_CONST MI_Char* TEST_Test2_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier TEST_Test2_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &TEST_Test2_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test2_quals[] =
{
    &TEST_Test2_Description_qual,
    &TEST_Test2_ClassVersion_qual,
};

/* class TEST_Test2 */
MI_CONST MI_ClassDecl TEST_Test2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074320A, /* code */
    MI_T("TEST_Test2"), /* name */
    TEST_Test2_quals, /* qualifiers */
    MI_COUNT(TEST_Test2_quals), /* numQualifiers */
    TEST_Test2_props, /* properties */
    MI_COUNT(TEST_Test2_props), /* numProperties */
    sizeof(TEST_Test2), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    TEST_Test2_meths, /* methods */
    MI_COUNT(TEST_Test2_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TEST_Test2_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** TEST_Stop
**
**==============================================================================
*/

static MI_CONST MI_Boolean TEST_Stop_Id1_Key_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_Id1_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_Id1_Key_qual_value
};

static MI_CONST MI_Char* TEST_Stop_Id1_Description_qual_value = MI_T("2");

static MI_CONST MI_Qualifier TEST_Stop_Id1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_Id1_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_Id1_quals[] =
{
    &TEST_Stop_Id1_Key_qual,
    &TEST_Stop_Id1_Description_qual,
};

/* property TEST_Stop.Id1 */
static MI_CONST MI_PropertyDecl TEST_Stop_Id1_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00693103, /* code */
    MI_T("Id1"), /* name */
    TEST_Stop_Id1_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_Id1_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop, Id1), /* offset */
    MI_T("TEST_Stop"), /* origin */
    MI_T("TEST_Stop"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TEST_Stop_props[] =
{
    &TEST_Stop_Id1_prop,
};

static MI_CONST MI_Boolean TEST_Stop_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_GetTargetResource_quals[] =
{
    &TEST_Stop_GetTargetResource_Static_qual,
    &TEST_Stop_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Stop_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_GetTargetResource_InputResource_quals[] =
{
    &TEST_Stop_GetTargetResource_InputResource_In_qual,
    &TEST_Stop_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Stop_GetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Stop.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Stop_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Stop_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Stop_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_GetTargetResource_Flags_quals[] =
{
    &TEST_Stop_GetTargetResource_Flags_In_qual,
    &TEST_Stop_GetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Stop.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Stop_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Stop_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_OutputResource_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_GetTargetResource_OutputResource_quals[] =
{
    &TEST_Stop_GetTargetResource_OutputResource_Out_qual,
    &TEST_Stop_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &TEST_Stop_GetTargetResource_OutputResource_Description_qual,
};

/* parameter TEST_Stop.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl TEST_Stop_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    TEST_Stop_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Stop_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_GetTargetResource_MIReturn_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Stop_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_GetTargetResource_MIReturn_quals[] =
{
    &TEST_Stop_GetTargetResource_MIReturn_Static_qual,
    &TEST_Stop_GetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Stop.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Stop_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Stop_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Stop_GetTargetResource_params[] =
{
    &TEST_Stop_GetTargetResource_MIReturn_param,
    &TEST_Stop_GetTargetResource_InputResource_param,
    &TEST_Stop_GetTargetResource_Flags_param,
    &TEST_Stop_GetTargetResource_OutputResource_param,
};

/* method TEST_Stop.GetTargetResource() */
MI_CONST MI_MethodDecl TEST_Stop_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    TEST_Stop_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_GetTargetResource_quals), /* numQualifiers */
    TEST_Stop_GetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Stop_GetTargetResource_params), /* numParameters */
    sizeof(TEST_Stop_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Stop"), /* origin */
    MI_T("TEST_Stop"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Stop_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_quals[] =
{
    &TEST_Stop_TestTargetResource_Static_qual,
    &TEST_Stop_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_InputResource_quals[] =
{
    &TEST_Stop_TestTargetResource_InputResource_In_qual,
    &TEST_Stop_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Stop_TestTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Stop.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Stop_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Stop_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Stop_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_Flags_quals[] =
{
    &TEST_Stop_TestTargetResource_Flags_In_qual,
    &TEST_Stop_TestTargetResource_Flags_Description_qual,
};

/* parameter TEST_Stop.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Stop_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Stop_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_Result_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_Result_quals[] =
{
    &TEST_Stop_TestTargetResource_Result_Out_qual,
    &TEST_Stop_TestTargetResource_Result_Description_qual,
};

/* parameter TEST_Stop.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl TEST_Stop_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    TEST_Stop_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_ProviderContext_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_ProviderContext_quals[] =
{
    &TEST_Stop_TestTargetResource_ProviderContext_Out_qual,
    &TEST_Stop_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Stop.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Stop_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Stop_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_TestTargetResource_MIReturn_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Stop_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_TestTargetResource_MIReturn_quals[] =
{
    &TEST_Stop_TestTargetResource_MIReturn_Static_qual,
    &TEST_Stop_TestTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Stop.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Stop_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Stop_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Stop_TestTargetResource_params[] =
{
    &TEST_Stop_TestTargetResource_MIReturn_param,
    &TEST_Stop_TestTargetResource_InputResource_param,
    &TEST_Stop_TestTargetResource_Flags_param,
    &TEST_Stop_TestTargetResource_Result_param,
    &TEST_Stop_TestTargetResource_ProviderContext_param,
};

/* method TEST_Stop.TestTargetResource() */
MI_CONST MI_MethodDecl TEST_Stop_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    TEST_Stop_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_TestTargetResource_quals), /* numQualifiers */
    TEST_Stop_TestTargetResource_params, /* parameters */
    MI_COUNT(TEST_Stop_TestTargetResource_params), /* numParameters */
    sizeof(TEST_Stop_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Stop"), /* origin */
    MI_T("TEST_Stop"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Stop_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Stop_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_SetTargetResource_quals[] =
{
    &TEST_Stop_SetTargetResource_Static_qual,
    &TEST_Stop_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Stop_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_SetTargetResource_InputResource_quals[] =
{
    &TEST_Stop_SetTargetResource_InputResource_In_qual,
    &TEST_Stop_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Stop_SetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Stop.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Stop_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Stop_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Stop_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_ProviderContext_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_SetTargetResource_ProviderContext_quals[] =
{
    &TEST_Stop_SetTargetResource_ProviderContext_In_qual,
    &TEST_Stop_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Stop.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Stop_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Stop_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_SetTargetResource_Flags_quals[] =
{
    &TEST_Stop_SetTargetResource_Flags_In_qual,
    &TEST_Stop_SetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Stop.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Stop_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Stop_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Stop_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Stop_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Stop_SetTargetResource_MIReturn_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Stop_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_SetTargetResource_MIReturn_quals[] =
{
    &TEST_Stop_SetTargetResource_MIReturn_Static_qual,
    &TEST_Stop_SetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Stop.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Stop_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Stop_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Stop_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Stop_SetTargetResource_params[] =
{
    &TEST_Stop_SetTargetResource_MIReturn_param,
    &TEST_Stop_SetTargetResource_InputResource_param,
    &TEST_Stop_SetTargetResource_ProviderContext_param,
    &TEST_Stop_SetTargetResource_Flags_param,
};

/* method TEST_Stop.SetTargetResource() */
MI_CONST MI_MethodDecl TEST_Stop_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    TEST_Stop_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_SetTargetResource_quals), /* numQualifiers */
    TEST_Stop_SetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Stop_SetTargetResource_params), /* numParameters */
    sizeof(TEST_Stop_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Stop"), /* origin */
    MI_T("TEST_Stop"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Stop_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TEST_Stop_meths[] =
{
    &TEST_Stop_GetTargetResource_rtti,
    &TEST_Stop_TestTargetResource_rtti,
    &TEST_Stop_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT TEST_Stop_funcs =
{
  (MI_ProviderFT_Load)TEST_Stop_Load,
  (MI_ProviderFT_Unload)TEST_Stop_Unload,
  (MI_ProviderFT_GetInstance)TEST_Stop_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TEST_Stop_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TEST_Stop_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TEST_Stop_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TEST_Stop_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* TEST_Stop_Description_qual_value = MI_T("13");

static MI_CONST MI_Qualifier TEST_Stop_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Stop_Description_qual_value
};

static MI_CONST MI_Char* TEST_Stop_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier TEST_Stop_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &TEST_Stop_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Stop_quals[] =
{
    &TEST_Stop_Description_qual,
    &TEST_Stop_ClassVersion_qual,
};

/* class TEST_Stop */
MI_CONST MI_ClassDecl TEST_Stop_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00747009, /* code */
    MI_T("TEST_Stop"), /* name */
    TEST_Stop_quals, /* qualifiers */
    MI_COUNT(TEST_Stop_quals), /* numQualifiers */
    TEST_Stop_props, /* properties */
    MI_COUNT(TEST_Stop_props), /* numProperties */
    sizeof(TEST_Stop), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    TEST_Stop_meths, /* methods */
    MI_COUNT(TEST_Stop_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TEST_Stop_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** TEST_Test3User
**
**==============================================================================
*/

static MI_CONST MI_Boolean TEST_Test3User_Id1_Key_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_Id1_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_Id1_Key_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_Id1_Description_qual_value = MI_T("2");

static MI_CONST MI_Qualifier TEST_Test3User_Id1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_Id1_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_Id1_quals[] =
{
    &TEST_Test3User_Id1_Key_qual,
    &TEST_Test3User_Id1_Description_qual,
};

/* property TEST_Test3User.Id1 */
static MI_CONST MI_PropertyDecl TEST_Test3User_Id1_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00693103, /* code */
    MI_T("Id1"), /* name */
    TEST_Test3User_Id1_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_Id1_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User, Id1), /* offset */
    MI_T("TEST_Test3User"), /* origin */
    MI_T("TEST_Test3User"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TEST_Test3User_props[] =
{
    &TEST_Test3User_Id1_prop,
};

static MI_CONST MI_Boolean TEST_Test3User_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_quals[] =
{
    &TEST_Test3User_GetTargetResource_Static_qual,
    &TEST_Test3User_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test3User_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_InputResource_quals[] =
{
    &TEST_Test3User_GetTargetResource_InputResource_In_qual,
    &TEST_Test3User_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test3User_GetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test3User.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test3User_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test3User_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_Flags_quals[] =
{
    &TEST_Test3User_GetTargetResource_Flags_In_qual,
    &TEST_Test3User_GetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test3User.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test3User_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test3User_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_OutputResource_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_OutputResource_quals[] =
{
    &TEST_Test3User_GetTargetResource_OutputResource_Out_qual,
    &TEST_Test3User_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &TEST_Test3User_GetTargetResource_OutputResource_Description_qual,
};

/* parameter TEST_Test3User.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl TEST_Test3User_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    TEST_Test3User_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_GetTargetResource_MIReturn_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test3User_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_MIReturn_quals[] =
{
    &TEST_Test3User_GetTargetResource_MIReturn_Static_qual,
    &TEST_Test3User_GetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test3User.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test3User_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test3User_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test3User_GetTargetResource_params[] =
{
    &TEST_Test3User_GetTargetResource_MIReturn_param,
    &TEST_Test3User_GetTargetResource_InputResource_param,
    &TEST_Test3User_GetTargetResource_Flags_param,
    &TEST_Test3User_GetTargetResource_OutputResource_param,
};

/* method TEST_Test3User.GetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test3User_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    TEST_Test3User_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_GetTargetResource_quals), /* numQualifiers */
    TEST_Test3User_GetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test3User_GetTargetResource_params), /* numParameters */
    sizeof(TEST_Test3User_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test3User"), /* origin */
    MI_T("TEST_Test3User"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test3User_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_quals[] =
{
    &TEST_Test3User_TestTargetResource_Static_qual,
    &TEST_Test3User_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_InputResource_quals[] =
{
    &TEST_Test3User_TestTargetResource_InputResource_In_qual,
    &TEST_Test3User_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test3User_TestTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test3User.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test3User_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test3User_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_Flags_quals[] =
{
    &TEST_Test3User_TestTargetResource_Flags_In_qual,
    &TEST_Test3User_TestTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test3User.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test3User_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test3User_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_Result_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_Result_quals[] =
{
    &TEST_Test3User_TestTargetResource_Result_Out_qual,
    &TEST_Test3User_TestTargetResource_Result_Description_qual,
};

/* parameter TEST_Test3User.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl TEST_Test3User_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    TEST_Test3User_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_ProviderContext_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_ProviderContext_quals[] =
{
    &TEST_Test3User_TestTargetResource_ProviderContext_Out_qual,
    &TEST_Test3User_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test3User.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test3User_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test3User_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_TestTargetResource_MIReturn_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test3User_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_MIReturn_quals[] =
{
    &TEST_Test3User_TestTargetResource_MIReturn_Static_qual,
    &TEST_Test3User_TestTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test3User.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test3User_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test3User_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test3User_TestTargetResource_params[] =
{
    &TEST_Test3User_TestTargetResource_MIReturn_param,
    &TEST_Test3User_TestTargetResource_InputResource_param,
    &TEST_Test3User_TestTargetResource_Flags_param,
    &TEST_Test3User_TestTargetResource_Result_param,
    &TEST_Test3User_TestTargetResource_ProviderContext_param,
};

/* method TEST_Test3User.TestTargetResource() */
MI_CONST MI_MethodDecl TEST_Test3User_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    TEST_Test3User_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_TestTargetResource_quals), /* numQualifiers */
    TEST_Test3User_TestTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test3User_TestTargetResource_params), /* numParameters */
    sizeof(TEST_Test3User_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test3User"), /* origin */
    MI_T("TEST_Test3User"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test3User_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test3User_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_quals[] =
{
    &TEST_Test3User_SetTargetResource_Static_qual,
    &TEST_Test3User_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test3User_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_InputResource_quals[] =
{
    &TEST_Test3User_SetTargetResource_InputResource_In_qual,
    &TEST_Test3User_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test3User_SetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test3User.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test3User_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test3User_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_ProviderContext_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_ProviderContext_quals[] =
{
    &TEST_Test3User_SetTargetResource_ProviderContext_In_qual,
    &TEST_Test3User_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test3User.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test3User_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test3User_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_Flags_quals[] =
{
    &TEST_Test3User_SetTargetResource_Flags_In_qual,
    &TEST_Test3User_SetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test3User.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test3User_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test3User_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test3User_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test3User_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_SetTargetResource_MIReturn_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test3User_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_MIReturn_quals[] =
{
    &TEST_Test3User_SetTargetResource_MIReturn_Static_qual,
    &TEST_Test3User_SetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test3User.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test3User_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test3User_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test3User_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test3User_SetTargetResource_params[] =
{
    &TEST_Test3User_SetTargetResource_MIReturn_param,
    &TEST_Test3User_SetTargetResource_InputResource_param,
    &TEST_Test3User_SetTargetResource_ProviderContext_param,
    &TEST_Test3User_SetTargetResource_Flags_param,
};

/* method TEST_Test3User.SetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test3User_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    TEST_Test3User_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_SetTargetResource_quals), /* numQualifiers */
    TEST_Test3User_SetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test3User_SetTargetResource_params), /* numParameters */
    sizeof(TEST_Test3User_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test3User"), /* origin */
    MI_T("TEST_Test3User"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test3User_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TEST_Test3User_meths[] =
{
    &TEST_Test3User_GetTargetResource_rtti,
    &TEST_Test3User_TestTargetResource_rtti,
    &TEST_Test3User_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT TEST_Test3User_funcs =
{
  (MI_ProviderFT_Load)TEST_Test3User_Load,
  (MI_ProviderFT_Unload)TEST_Test3User_Unload,
  (MI_ProviderFT_GetInstance)TEST_Test3User_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TEST_Test3User_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TEST_Test3User_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TEST_Test3User_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TEST_Test3User_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* TEST_Test3User_Description_qual_value = MI_T("14");

static MI_CONST MI_Qualifier TEST_Test3User_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test3User_Description_qual_value
};

static MI_CONST MI_Char* TEST_Test3User_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier TEST_Test3User_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &TEST_Test3User_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test3User_quals[] =
{
    &TEST_Test3User_Description_qual,
    &TEST_Test3User_ClassVersion_qual,
};

/* class TEST_Test3User */
MI_CONST MI_ClassDecl TEST_Test3User_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074720E, /* code */
    MI_T("TEST_Test3User"), /* name */
    TEST_Test3User_quals, /* qualifiers */
    MI_COUNT(TEST_Test3User_quals), /* numQualifiers */
    TEST_Test3User_props, /* properties */
    MI_COUNT(TEST_Test3User_props), /* numProperties */
    sizeof(TEST_Test3User), /* size */
    MI_T("OMI_BaseResource"), /* superClass */
    &OMI_BaseResource_rtti, /* superClassDecl */
    TEST_Test3User_meths, /* methods */
    MI_COUNT(TEST_Test3User_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TEST_Test3User_funcs, /* functions */
    NULL /* owningClass */
};

/*
**==============================================================================
**
** TEST_Test4NoOMI
**
**==============================================================================
*/

static MI_CONST MI_Boolean TEST_Test4NoOMI_Id1_Key_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_Id1_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_Id1_Key_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_Id1_Description_qual_value = MI_T("2");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_Id1_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_Id1_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_Id1_quals[] =
{
    &TEST_Test4NoOMI_Id1_Key_qual,
    &TEST_Test4NoOMI_Id1_Description_qual,
};

/* property TEST_Test4NoOMI.Id1 */
static MI_CONST MI_PropertyDecl TEST_Test4NoOMI_Id1_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY|MI_FLAG_READONLY, /* flags */
    0x00693103, /* code */
    MI_T("Id1"), /* name */
    TEST_Test4NoOMI_Id1_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_Id1_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI, Id1), /* offset */
    MI_T("TEST_Test4NoOMI"), /* origin */
    MI_T("TEST_Test4NoOMI"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TEST_Test4NoOMI_props[] =
{
    &TEST_Test4NoOMI_Id1_prop,
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_GetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_GetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_quals[] =
{
    &TEST_Test4NoOMI_GetTargetResource_Static_qual,
    &TEST_Test4NoOMI_GetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_GetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_InputResource_quals[] =
{
    &TEST_Test4NoOMI_GetTargetResource_InputResource_In_qual,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test4NoOMI.GetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_GetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test4NoOMI_GetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_GetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_GetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_GetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_Flags_quals[] =
{
    &TEST_Test4NoOMI_GetTargetResource_Flags_In_qual,
    &TEST_Test4NoOMI_GetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test4NoOMI.GetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_GetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test4NoOMI_GetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_GetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_GetTargetResource_OutputResource_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_OutputResource_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_OutputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_OutputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_OutputResource_Description_qual_value = MI_T("6");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_OutputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_OutputResource_quals[] =
{
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_Out_qual,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_EmbeddedInstance_qual,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_Description_qual,
};

/* parameter TEST_Test4NoOMI.GetTargetResource(): OutputResource */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_GetTargetResource_OutputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650E, /* code */
    MI_T("OutputResource"), /* name */
    TEST_Test4NoOMI_GetTargetResource_OutputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_OutputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_GetTargetResource, OutputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_GetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_GetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_GetTargetResource_MIReturn_Description_qual_value = MI_T("3");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_GetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_GetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_MIReturn_quals[] =
{
    &TEST_Test4NoOMI_GetTargetResource_MIReturn_Static_qual,
    &TEST_Test4NoOMI_GetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test4NoOMI.GetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_GetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test4NoOMI_GetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_GetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test4NoOMI_GetTargetResource_params[] =
{
    &TEST_Test4NoOMI_GetTargetResource_MIReturn_param,
    &TEST_Test4NoOMI_GetTargetResource_InputResource_param,
    &TEST_Test4NoOMI_GetTargetResource_Flags_param,
    &TEST_Test4NoOMI_GetTargetResource_OutputResource_param,
};

/* method TEST_Test4NoOMI.GetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test4NoOMI_GetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00676511, /* code */
    MI_T("GetTargetResource"), /* name */
    TEST_Test4NoOMI_GetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_quals), /* numQualifiers */
    TEST_Test4NoOMI_GetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test4NoOMI_GetTargetResource_params), /* numParameters */
    sizeof(TEST_Test4NoOMI_GetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test4NoOMI"), /* origin */
    MI_T("TEST_Test4NoOMI"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test4NoOMI_Invoke_GetTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_Static_qual,
    &TEST_Test4NoOMI_TestTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_InputResource_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_InputResource_In_qual,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test4NoOMI.TestTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_TestTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test4NoOMI_TestTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_TestTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_Flags_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_Flags_In_qual,
    &TEST_Test4NoOMI_TestTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test4NoOMI.TestTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_TestTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test4NoOMI_TestTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_TestTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_Result_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Result_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_Result_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_Result_Description_qual_value = MI_T("8");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_Result_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_Result_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_Result_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_Result_Out_qual,
    &TEST_Test4NoOMI_TestTargetResource_Result_Description_qual,
};

/* parameter TEST_Test4NoOMI.TestTargetResource(): Result */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_TestTargetResource_Result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("Result"), /* name */
    TEST_Test4NoOMI_TestTargetResource_Result_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_Result_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_TestTargetResource, Result), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_ProviderContext_Out_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_ProviderContext_Out_qual =
{
    MI_T("Out"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_ProviderContext_Out_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_ProviderContext_Description_qual_value = MI_T("9");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_ProviderContext_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_ProviderContext_Out_qual,
    &TEST_Test4NoOMI_TestTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test4NoOMI.TestTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_TestTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test4NoOMI_TestTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_TestTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_TestTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_TestTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_TestTargetResource_MIReturn_Description_qual_value = MI_T("7");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_TestTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_TestTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_MIReturn_quals[] =
{
    &TEST_Test4NoOMI_TestTargetResource_MIReturn_Static_qual,
    &TEST_Test4NoOMI_TestTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test4NoOMI.TestTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_TestTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test4NoOMI_TestTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_TestTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test4NoOMI_TestTargetResource_params[] =
{
    &TEST_Test4NoOMI_TestTargetResource_MIReturn_param,
    &TEST_Test4NoOMI_TestTargetResource_InputResource_param,
    &TEST_Test4NoOMI_TestTargetResource_Flags_param,
    &TEST_Test4NoOMI_TestTargetResource_Result_param,
    &TEST_Test4NoOMI_TestTargetResource_ProviderContext_param,
};

/* method TEST_Test4NoOMI.TestTargetResource() */
MI_CONST MI_MethodDecl TEST_Test4NoOMI_TestTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746512, /* code */
    MI_T("TestTargetResource"), /* name */
    TEST_Test4NoOMI_TestTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_quals), /* numQualifiers */
    TEST_Test4NoOMI_TestTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test4NoOMI_TestTargetResource_params), /* numParameters */
    sizeof(TEST_Test4NoOMI_TestTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test4NoOMI"), /* origin */
    MI_T("TEST_Test4NoOMI"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test4NoOMI_Invoke_TestTargetResource, /* method */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_SetTargetResource_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_SetTargetResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_quals[] =
{
    &TEST_Test4NoOMI_SetTargetResource_Static_qual,
    &TEST_Test4NoOMI_SetTargetResource_Description_qual,
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_SetTargetResource_InputResource_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_InputResource_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_InputResource_EmbeddedInstance_qual_value = MI_T("OMI_BaseResource");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_InputResource_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_InputResource_Description_qual_value = MI_T("4");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_InputResource_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_InputResource_quals[] =
{
    &TEST_Test4NoOMI_SetTargetResource_InputResource_In_qual,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_EmbeddedInstance_qual,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_Description_qual,
};

/* parameter TEST_Test4NoOMI.SetTargetResource(): InputResource */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_SetTargetResource_InputResource_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0069650D, /* code */
    MI_T("InputResource"), /* name */
    TEST_Test4NoOMI_SetTargetResource_InputResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_InputResource_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("OMI_BaseResource"), /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_SetTargetResource, InputResource), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_SetTargetResource_ProviderContext_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_ProviderContext_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_ProviderContext_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_ProviderContext_Description_qual_value = MI_T("11");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_ProviderContext_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_SetTargetResource_ProviderContext_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_ProviderContext_quals[] =
{
    &TEST_Test4NoOMI_SetTargetResource_ProviderContext_In_qual,
    &TEST_Test4NoOMI_SetTargetResource_ProviderContext_Description_qual,
};

/* parameter TEST_Test4NoOMI.SetTargetResource(): ProviderContext */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_SetTargetResource_ProviderContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070740F, /* code */
    MI_T("ProviderContext"), /* name */
    TEST_Test4NoOMI_SetTargetResource_ProviderContext_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_ProviderContext_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_SetTargetResource, ProviderContext), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_SetTargetResource_Flags_In_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_Flags_In_qual =
{
    MI_T("In"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_Flags_In_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_Flags_Description_qual_value = MI_T("5");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_Flags_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_SetTargetResource_Flags_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_Flags_quals[] =
{
    &TEST_Test4NoOMI_SetTargetResource_Flags_In_qual,
    &TEST_Test4NoOMI_SetTargetResource_Flags_Description_qual,
};

/* parameter TEST_Test4NoOMI.SetTargetResource(): Flags */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_SetTargetResource_Flags_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667305, /* code */
    MI_T("Flags"), /* name */
    TEST_Test4NoOMI_SetTargetResource_Flags_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_Flags_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_SetTargetResource, Flags), /* offset */
};

static MI_CONST MI_Boolean TEST_Test4NoOMI_SetTargetResource_MIReturn_Static_qual_value = 1;

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_MIReturn_Static_qual =
{
    MI_T("Static"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &TEST_Test4NoOMI_SetTargetResource_MIReturn_Static_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_SetTargetResource_MIReturn_Description_qual_value = MI_T("10");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_SetTargetResource_MIReturn_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_SetTargetResource_MIReturn_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_MIReturn_quals[] =
{
    &TEST_Test4NoOMI_SetTargetResource_MIReturn_Static_qual,
    &TEST_Test4NoOMI_SetTargetResource_MIReturn_Description_qual,
};

/* parameter TEST_Test4NoOMI.SetTargetResource(): MIReturn */
static MI_CONST MI_ParameterDecl TEST_Test4NoOMI_SetTargetResource_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TEST_Test4NoOMI_SetTargetResource_MIReturn_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TEST_Test4NoOMI_SetTargetResource, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TEST_Test4NoOMI_SetTargetResource_params[] =
{
    &TEST_Test4NoOMI_SetTargetResource_MIReturn_param,
    &TEST_Test4NoOMI_SetTargetResource_InputResource_param,
    &TEST_Test4NoOMI_SetTargetResource_ProviderContext_param,
    &TEST_Test4NoOMI_SetTargetResource_Flags_param,
};

/* method TEST_Test4NoOMI.SetTargetResource() */
MI_CONST MI_MethodDecl TEST_Test4NoOMI_SetTargetResource_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00736511, /* code */
    MI_T("SetTargetResource"), /* name */
    TEST_Test4NoOMI_SetTargetResource_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_quals), /* numQualifiers */
    TEST_Test4NoOMI_SetTargetResource_params, /* parameters */
    MI_COUNT(TEST_Test4NoOMI_SetTargetResource_params), /* numParameters */
    sizeof(TEST_Test4NoOMI_SetTargetResource), /* size */
    MI_UINT32, /* returnType */
    MI_T("TEST_Test4NoOMI"), /* origin */
    MI_T("TEST_Test4NoOMI"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TEST_Test4NoOMI_Invoke_SetTargetResource, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TEST_Test4NoOMI_meths[] =
{
    &TEST_Test4NoOMI_GetTargetResource_rtti,
    &TEST_Test4NoOMI_TestTargetResource_rtti,
    &TEST_Test4NoOMI_SetTargetResource_rtti,
};

static MI_CONST MI_ProviderFT TEST_Test4NoOMI_funcs =
{
  (MI_ProviderFT_Load)TEST_Test4NoOMI_Load,
  (MI_ProviderFT_Unload)TEST_Test4NoOMI_Unload,
  (MI_ProviderFT_GetInstance)TEST_Test4NoOMI_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TEST_Test4NoOMI_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TEST_Test4NoOMI_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TEST_Test4NoOMI_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TEST_Test4NoOMI_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* TEST_Test4NoOMI_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &TEST_Test4NoOMI_ClassVersion_qual_value
};

static MI_CONST MI_Char* TEST_Test4NoOMI_Description_qual_value = MI_T("15");

static MI_CONST MI_Qualifier TEST_Test4NoOMI_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &TEST_Test4NoOMI_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TEST_Test4NoOMI_quals[] =
{
    &TEST_Test4NoOMI_ClassVersion_qual,
    &TEST_Test4NoOMI_Description_qual,
};

/* class TEST_Test4NoOMI */
MI_CONST MI_ClassDecl TEST_Test4NoOMI_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074690F, /* code */
    MI_T("TEST_Test4NoOMI"), /* name */
    TEST_Test4NoOMI_quals, /* qualifiers */
    MI_COUNT(TEST_Test4NoOMI_quals), /* numQualifiers */
    TEST_Test4NoOMI_props, /* properties */
    MI_COUNT(TEST_Test4NoOMI_props), /* numProperties */
    sizeof(TEST_Test4NoOMI), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    TEST_Test4NoOMI_meths, /* methods */
    MI_COUNT(TEST_Test4NoOMI_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TEST_Test4NoOMI_funcs, /* functions */
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
    &TEST_Stop_rtti,
    &TEST_Test1_rtti,
    &TEST_Test2_rtti,
    &TEST_Test3User_rtti,
    &TEST_Test4NoOMI_rtti,
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

