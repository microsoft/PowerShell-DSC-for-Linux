/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


// Format.Placeholders.h
#if defined(_MSC_VER) || defined(INTLSTR_RC_INC)
    /* the format specifiers below follows the documentation of FormatMessage 
    from http://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx */
    #define Intlstr_UnverifiedPlaceholderFull(orderNumber, flags, Precesion, regularFormatSpecifier) \
        "%" #orderNumber "!" flags #Precesion regularFormatSpecifier "!"
#else
    /* the format specifiers below follows the specification 
       from http://www.opengroup.org/onlinepubs/009695399/functions/printf.html */
    #define Intlstr_UnverifiedPlaceholderFull(orderNumber, flags, Precesion, regularFormatSpecifier) \
        "%" #orderNumber "$" flags #Precesion regularFormatSpecifier
#endif

#define Intlstr_tstrfull(orderNumber, flags, Precesion) Intlstr_UnverifiedPlaceholderFull(orderNumber, flags, Precesion, PAL_PRItstr)
