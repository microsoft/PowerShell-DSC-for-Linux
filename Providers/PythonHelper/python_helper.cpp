#include "python_helper.hpp"


#include "debug_tags.hpp"


#include <boost/scoped_array.hpp>
#include <cstdlib>
#include <vector>
#include <sstream>


#ifndef PRINT_HELPER_BOOKEND
#define PRINT_HELPER_BOOKEND (0)
#endif

#if (PRINT_HELPER_BOOKEND)
#define HELPER_BOOKEND(text) SCX_BOOKEND (text)
#define HELPER_BOOKEND_EX(text, subText) SCX_BOOKEND_EX (text, subText)
#define HELPER_BOOKEND_PRINT(text) SCX_BOOKEND_PRINT (text)
#else
#define HELPER_BOOKEND(text)
#define HELPER_BOOKEND_EX(text, subText)
#define HELPER_BOOKEND_PRINT(text)
#endif


namespace scx
{


int
did_function_succeed (
    int result,
    boost::python::object const& retVals)
{
    HELPER_BOOKEND ("did_funtion_succeed");
    if (EXIT_SUCCESS == result)
    {
        if (boost::python::extract<boost::python::list>(retVals).check () &&
            0 < boost::python::len (retVals))
        {
            boost::python::extract<long> getInt (retVals[0]);
            // The python scripts return 0 as the value of the first element
            // when successful
            if (getInt.check () &&
                0 == getInt ())
            {
                HELPER_BOOKEND_PRINT ("succeeded");
                return EXIT_SUCCESS;
            }
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}


std::basic_string<MI_Char>
get_mi_value (
    MI_ConstUint32Field const& field)
{
    HELPER_BOOKEND_EX ("get_mi_value", " type=\"MI_ConstUint32Field\"");
    if (MI_TRUE == field.exists)
    {
        std::basic_ostringstream<MI_Char> cache;
        cache << field.value;
        HELPER_BOOKEND_PRINT (cache.str ());
        return cache.str ();
    }
    HELPER_BOOKEND_PRINT ("field doesn't exist");
    return std::basic_string<MI_Char> (EMPTY_STRING);
}


MI_Char const*
get_mi_value (
    MI_ConstStringField const& field)
{
    HELPER_BOOKEND_EX ("get_mi_value", " type=\"MI_ConstStringField\"");
    if (MI_TRUE == field.exists)
    {
        HELPER_BOOKEND_PRINT (field.value);
        return field.value;
    }
    return EMPTY_STRING;
}

MI_Char const*
get_mi_value (
    MI_ConstBooleanField const& field)
{
    HELPER_BOOKEND_EX ("get_mi_value", " type=\"MI_ConstBooleanField\"");
    if (MI_TRUE == field.exists)
    {
        if (MI_TRUE == field.value)
        {
            return TRUE_STRING;
        }
        else
        {
            return FALSE_STRING;
        }
    }
    return EMPTY_STRING;
}

std::basic_string<MI_Char>
get_mi_value (
    MI_ConstStringAField const& field)
{
    HELPER_BOOKEND_EX ("get_mi_value", " type=\"MI_ConstStringAField\"");
    if (MI_TRUE == field.exists)
    {
        std::basic_ostringstream<MI_Char> cache;
        typedef MI_Char const* const* pStr;
        pStr const end = field.value.data + field.value.size;
        pStr pos = field.value.data;
        if (end != pos)
        {
            cache << *pos;
            ++pos;
            while (end != pos)
            {
                cache << '\n' << *pos;
                ++pos;
            }
        }
        HELPER_BOOKEND_PRINT (cache.str ());
        return cache.str ();
    }
    HELPER_BOOKEND_PRINT ("field doesn't exist");
    return std::basic_string<MI_Char> (EMPTY_STRING);
}

int
set_mi_uint32 (
    MI_Instance* const newInstance,
    char const* const field,
    boost::python::object const& obj)
{
    HELPER_BOOKEND ("set_mi_uint32");
    boost::python::extract<char const*> getStr (obj);
    if (getStr.check ())
    {
        char* endPtr = 0;
        MI_Value temp;
        temp.uint32 = strtoul (getStr (), &endPtr, 0);
        if ('\0' == *endPtr)
        {
            if (MI_RESULT_OK ==
                MI_Instance_SetElement (
                    newInstance, field, &temp, MI_UINT32, 0))
            {
                HELPER_BOOKEND_PRINT ("succeeded");
                return EXIT_SUCCESS;
            }
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}


int
set_mi_string (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj)
{
    HELPER_BOOKEND ("set_mi_string");
    boost::python::extract<char const*> getStr (obj);
    if (getStr.check ())
    {
        char const* str = getStr ();
        if (MI_RESULT_OK == MI_Instance_SetElement (
                newInstance,
                field,
                reinterpret_cast<MI_Value const*>(&str),
                MI_STRING,
                0))
        {
            HELPER_BOOKEND_PRINT ("succeeded");
            return EXIT_SUCCESS;
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}

int
set_mi_datetime (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj)
{
    HELPER_BOOKEND ("set_mi_datetime");
    boost::python::extract<char const*> getStr (obj);
    if (getStr.check ())
    {
        char* endPtr = 0;
        time_t timeInSeconds = strtol (getStr (), &endPtr, 0);
        if ('\0' == *endPtr)
        {
            struct tm* timeInTm = localtime (&timeInSeconds);
            MI_Value temp;
            temp.datetime.u.timestamp.year = timeInTm->tm_year + 1900;
            temp.datetime.u.timestamp.month = timeInTm->tm_mon + 1;
            temp.datetime.u.timestamp.day = timeInTm->tm_mday;
            temp.datetime.u.timestamp.hour = timeInTm->tm_hour;
            temp.datetime.u.timestamp.minute = timeInTm->tm_min;
            temp.datetime.u.timestamp.second = timeInTm->tm_sec;
            temp.datetime.u.timestamp.utc = -8 * 60;
            if (MI_RESULT_OK ==
                MI_Instance_SetElement (
                    newInstance, field, &temp, MI_DATETIME, 0))
            {
                HELPER_BOOKEND_PRINT ("succeeded");
                return EXIT_SUCCESS;
            }
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}

int
set_mi_bool (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj)
{
    HELPER_BOOKEND ("set_mi_bool");
    boost::python::extract<char const*> getStr (obj);
    if (getStr.check ())
    {
        MI_Value value;
        if (0 == strcmp (getStr (), scx::TRUE_STRING))
        {
            value.boolean = MI_TRUE;
            if (MI_RESULT_OK == MI_Instance_SetElement (
                    newInstance, field, &value, MI_BOOLEAN, 0))
            {
                HELPER_BOOKEND_PRINT ("succeeded");
                return EXIT_SUCCESS;
            }
        }
        else if (0 == strcmp (getStr (), scx::FALSE_STRING) ||
                 0 == strlen (getStr ()))
        {
            value.boolean = MI_FALSE;
            if (MI_RESULT_OK == MI_Instance_SetElement (
                    newInstance, field, &value, MI_BOOLEAN, 0))
            {
                HELPER_BOOKEND_PRINT ("succeeded");
                return EXIT_SUCCESS;
            }
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}

int
set_mi_string_array (
    MI_Instance* const newInstance, 
    char const* const field,
    boost::python::object const& obj)
{
    HELPER_BOOKEND ("set_mi_string_array");
    boost::python::extract<char const*> getStr (obj);
    if (getStr.check ())
    {
        char const* original = getStr ();
        size_t len = strlen (original);
        boost::scoped_array<char> copy (strcpy (new char[len + 1], original));
        std::vector<MI_Char*> strings;
        char* start = copy.get ();
        char* end = start + len;
        strings.push_back (start);
        char* pos = std::find (start, end, '\n');
        while (pos != end)
        {
            start = pos + 1;
            *pos = '\0';
            strings.push_back (start);
            pos = std::find (start, end, '\n');
        }
        MI_Value value;
        value.stringa.data = strings.data ();
        value.stringa.size = strings.size ();
        if (MI_RESULT_OK == MI_Instance_SetElement (
                newInstance, field, &value, MI_STRINGA, 0))
        {
            HELPER_BOOKEND_PRINT ("succeeded");
            return EXIT_SUCCESS;
        }
    }
    HELPER_BOOKEND_PRINT ("failed");
    return EXIT_FAILURE;
}


} // namespace scx
