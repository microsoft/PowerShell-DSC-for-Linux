/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef INCLUDED_DEBUG_TAGS_HPP
#define INCLUDED_DEBUG_TAGS_HPP


#include <iostream>
#include <string>


#define SCX_BOOKEND(title) scx::BookEnd be (title)
#define SCX_BOOKEND_EX(title,sub_title) scx::BookEnd be (title, sub_title)
#define SCX_BOOKEND_PRINT(text) scx::BookEnd::print (text)

namespace scx
{


class BookEnd
{
public:
    /*ctor*/ BookEnd (
        char const* const title,
        char const* const subTitle = 0);

    explicit /*ctor*/ BookEnd (
        std::string const& title);

    /*ctor*/ BookEnd (
        std::string const& title,
        std::string const& subTitle);

    /*dtor*/ ~BookEnd ();

    template<typename T>
    static void print (T const& text);

private:
    std::string const m_Title;
    std::string const m_SubTitle;

    static unsigned int s_nIndent;
    static char const EMPTY_STRING[];
    static char const INDENT[];
};


template<typename T>
/*static*/ void
BookEnd::print (
    T const& text)
{
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    std::cout << text << std::endl;
}


}


#endif // INCLUDED_DEBUG_TAGS_HPP
