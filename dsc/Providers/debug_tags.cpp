/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "debug_tags.hpp"


#include <iostream>
#include <sstream>


namespace scx
{


/*static*/ unsigned int BookEnd::s_nIndent (0);
/*static*/ char const BookEnd::EMPTY_STRING[] = "";
/*static*/ char const BookEnd::INDENT[] = "  ";


/*ctor*/
BookEnd::BookEnd (
    char const* const title,
    char const* const subTitle)
  : m_Title (title ? title : EMPTY_STRING)
  , m_SubTitle (subTitle ? subTitle : EMPTY_STRING)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}

/*ctor*/
BookEnd::BookEnd (
    std::string const& title)
  : m_Title (title)
  , m_SubTitle (EMPTY_STRING)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}

/*ctor*/
BookEnd::BookEnd (
    std::string const& title,
    std::string const& subTitle)
  : m_Title (title)
  , m_SubTitle (subTitle)
{
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    ++s_nIndent;
    std::cout << '<' << m_Title << m_SubTitle << '>' << std::endl;
#endif
}
    
/*dtor*/
BookEnd::~BookEnd ()
{
#if (PRINT_BOOKENDS)
    --s_nIndent;
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    std::cout << "</" << m_Title << '>'  << std::endl;
#endif
}


}
