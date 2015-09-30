/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef INCLUDED_UTIL_TRAITS_HPP
#define INCLUDED_UTIL_TRAITS_HPP


namespace util
{


// integral_constant
//------------------------------------------------------------------------------
template<typename T, T v>
struct integral_constant
{
    static T const value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    /*T*/ operator T () const { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


// is_lvalue_reference
//------------------------------------------------------------------------------
template<typename T>
struct is_lvalue_reference : public false_type {};

template<typename T>
struct is_lvalue_reference<T&> : public true_type {};


// is_pointer
//------------------------------------------------------------------------------
template<typename T>
struct is_pointer : public false_type {};

template<typename T>
struct is_pointer<T*> : public true_type {};


// is_reference
//------------------------------------------------------------------------------
template<typename T>
struct is_reference : public is_lvalue_reference<T> {};


// conditional
//------------------------------------------------------------------------------
template<bool CONDITION, typename TRUE_TYPE, typename FALSE_TYPE>
struct conditional
{
    typedef TRUE_TYPE type;
};

template<typename TRUE_TYPE, typename FALSE_TYPE>
struct conditional<false, TRUE_TYPE, FALSE_TYPE>
{
    typedef FALSE_TYPE type;
};


// remove_reference
//------------------------------------------------------------------------------
template<typename T>
struct remove_reference
{
    typedef T type;
};

template<typename T>
struct remove_reference<T&>
{
    typedef T type;
};


} // namespace util


#endif // INCLUDED_UTIL_TRAITS_HPP
