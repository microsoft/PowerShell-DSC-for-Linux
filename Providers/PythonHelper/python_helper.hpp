#ifndef INCLUDED_PYTHON_HELPER_HPP
#define INCLUDED_PYTHON_HELPER_HPP


#include "python_io_helper.hpp"


#include <boost/preprocessor.hpp>
#include <boost/python.hpp>
#include <cstdlib>
#include <iostream>
#include <MI.h>
#include <string>


namespace scx
{


MI_Char const TRUE_STRING[] = "True";
MI_Char const FALSE_STRING[] = "False";
MI_Char const EMPTY_STRING[] = "";


#define INVOKE_PYTHON_FUNCTION(z, n, _) \
    BOOST_PP_IF (n, template<, inline) \
        BOOST_PP_ENUM_PARAMS_Z (z, n, typename T) \
        BOOST_PP_EXPR_IF (n, >) \
    int \
    invoke_python_function ( \
        boost::python::object* retValOut, \
        boost::python::object const& fn \
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z (z, n, T, const& a)) \
    { \
        int result = EXIT_FAILURE; \
        try \
        { \
            if (retValOut) \
            { \
                *retValOut = fn (BOOST_PP_ENUM_PARAMS_Z (z, n, a)); \
                result = EXIT_SUCCESS; \
            } \
        } \
        catch (boost::python::error_already_set) \
        { \
            std::wcerr << python_error_parser << std::endl; \
        } \
        catch (std::exception ex) \
        { \
            std::wcerr << L"invoke_python_function failed on call: \"" << \
                ex.what () << "\"" << std::endl; \
        } \
        catch (...) \
        { \
            std::wcerr << L"invoke_python_function failed on call" << \
                std::endl; \
        } \
        return result; \
    }

BOOST_PP_REPEAT (BOOST_PYTHON_MAX_ARITY, INVOKE_PYTHON_FUNCTION, nil)


int
did_function_succeed (
    int result,
    boost::python::object const& retVals);

MI_Char const*
get_mi_value (
    MI_ConstStringField const& field);

MI_Char const*
get_mi_value (
    MI_ConstBooleanField const& field);

std::basic_string<MI_Char>
get_mi_value (
    MI_ConstStringAField const& field);

std::basic_string<MI_Char>
get_mi_value (
    MI_ConstUint32Field const& field);

int
set_mi_string (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj);

int
set_mi_datetime (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj);

int
set_mi_bool (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj);

int
set_mi_string_array (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj);

int
set_mi_uint32 (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj);


} // namespace scx


#endif // INCLUDED_PYTHON_HELPER_HPP
