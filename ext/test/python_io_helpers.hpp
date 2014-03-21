#ifndef INCLUDED_PYTHON_IO_HELPERS_HPP
#define INCLUDED_PYTHON_IO_HELPERS_HPP


#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <iosfwd>


namespace scx
{

template<typename charT>
class PythonTextConstants
{
public:
    static charT const CALLABLE[];
    static charT const UNDEFINED[];
    static charT const NULL_STR[];
    static charT const OPEN_LIST ;
    static charT const CLOSE_LIST;
    static charT const OPEN_TUPLE;
    static charT const CLOSE_TUPLE;
    static charT const OPEN_DICT;
    static charT const CLOSE_DICT;
    static charT const DELIMITER;
    static charT const PATH_INDENT[];
    static charT const OPEN_BRACE;
    static charT const CLOSE_BRACE;
    static charT const COLON;
    static charT const DOUBLE_QUOTE;
    static charT const PY_UNICODE_SIZE[];
    static charT const PY_UNICODE_WIDE[];
    static charT const IS_DEFINED[];
    static charT const IS_NOT_DEFINED[];
};


template<>
class PythonTextConstants<wchar_t>
{
public:
    typedef wchar_t charT;

    static charT const CALLABLE[];
    static charT const UNDEFINED[];
    static charT const NULL_STR[];
    static charT const OPEN_LIST;
    static charT const CLOSE_LIST;
    static charT const OPEN_TUPLE;
    static charT const CLOSE_TUPLE;
    static charT const OPEN_DICT;
    static charT const CLOSE_DICT;
    static charT const DELIMITER;
    static charT const PATH_INDENT[];
    static charT const OPEN_BRACE;
    static charT const CLOSE_BRACE;
    static charT const COLON;
    static charT const DOUBLE_QUOTE;
    static charT const PY_UNICODE_SIZE[];
    static charT const PY_UNICODE_WIDE[];
    static charT const IS_DEFINED[];
    static charT const IS_NOT_DEFINED[];
};


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
python_unicode_info (
    std::basic_ostream<charT, traits>& strm)
{
    typedef scx::PythonTextConstants<charT> Text;
    strm << Text::PY_UNICODE_SIZE << Text::COLON << Py_UNICODE_SIZE <<
        Text::DELIMITER << Text::PY_UNICODE_WIDE << Text::COLON;
#ifdef Py_UNICODE_WIDE
    return strm << Text::IS_DEFINED;
#else
    return strm << Text::IS_NOT_DEFINED;
#endif
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
python_path (
    std::basic_ostream<charT, traits>& strm)
{
    typedef scx::PythonTextConstants<charT> Text;
    boost::python::object sysModule = boost::python::import ("sys");
    boost::python::object path = sysModule.attr ("path");
    boost::python::extract<boost::python::list> getList (path);
    boost::python::list pathList =
        boost::python::extract<boost::python::list>(path);
    for (boost::python::ssize_t i = 0, len = boost::python::len (pathList);
         i < len;
         ++i)
    {
        strm << Text::PATH_INDENT << Text::OPEN_BRACE << i <<
            Text::CLOSE_BRACE << Text::COLON << Text::DOUBLE_QUOTE <<
            boost::python::extract<char const*>(pathList[i]) <<
            Text::DOUBLE_QUOTE;
        if (len > (i + 1))
        {
            strm << std::endl;
        }
    }
    return strm;
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
python_error_parser (
    std::basic_ostream<charT, traits>& strm)
{
    typedef scx::PythonTextConstants<charT> Text;
    PyObject* pType;
    PyObject* pValue;
    PyObject* pBT;
    PyErr_Fetch (&pType, &pValue, &pBT);
    PyErr_NormalizeException (&pType, &pValue, &pBT);
    boost::python::handle<> hType (pType);
    boost::python::handle<> hValue (boost::python::allow_null (pValue));
    boost::python::handle<> hBT (boost::python::allow_null (pBT));
    if (hValue)
    {
        boost::python::object traceback(boost::python::import("traceback"));
        boost::python::object format_exception(
            traceback.attr("format_exception"));
        boost::python::object formatted_list (
            format_exception(hType, hValue, hBT));
        boost::python::object formatted (
            boost::python::str ("").join (formatted_list));
        strm << formatted;
    }
    else
    {
        strm << boost::python::extract<char const*>(boost::python::str (hType));
    }
    return strm;
}

} // namespace scx


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::object& obj)
{
    typedef scx::PythonTextConstants<charT> Text;
    if (obj)
    {
        boost::python::extract<long> getInt (obj);
        if (getInt.check ())
        {
            return strm << getInt ();
        }
        boost::python::extract<double> getDouble (obj);
        if (getDouble.check ())
        {
            return strm << getDouble ();
        }
        boost::python::extract<char const*> getStr (obj);
        if (getStr.check ())
        {
            return strm << getStr ();
        }
        boost::python::extract<boost::python::list> getList (obj);
        if (getList.check ())
        {
            return strm << getList ();
        }
        boost::python::extract<boost::python::tuple> getTuple (obj);
        if (getTuple.check ())
        {
            return strm << getTuple ();
        }
        boost::python::extract<boost::python::dict> getDict (obj);
        if (getDict.check ())
        {
            return strm << getDict ();
        }
        if (PyCallable_Check (obj.ptr ()))
        {
            return strm << Text::CALLABLE;
        }
        return strm << Text::UNDEFINED;
    }
    return strm << Text::NULL_STR;
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::list const& list)
{
    typedef scx::PythonTextConstants<charT> Text;
    strm << Text::OPEN_LIST;
    boost::python::ssize_t const len = boost::python::len (list);
    for (boost::python::ssize_t i = 0; i < len; ++i)
    {
        boost::python::object item = list[i];
        strm << item;
        if (len > (i + 1))
        {
            strm << Text::DELIMITER;
        }
    }
    return strm << Text::CLOSE_LIST;
}

template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::tuple const& tuple)
{
    typedef scx::PythonTextConstants<charT> Text;
    strm << Text::OPEN_TUPLE;
    boost::python::ssize_t const len = boost::python::len (tuple);
    for (boost::python::ssize_t i = 0; i < len; ++i)
    {
        boost::python::object item = tuple[i];
        strm << item;
        if (len > (i + 1))
        {
            strm << Text::DELIMITER;
        }
    }
    return strm << Text::CLOSE_TUPLE;
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::dict const& dict)
{
    typedef scx::PythonTextConstants<charT> Text;
    boost::python::list items = dict.items ();
    strm << Text::OPEN_DICT;
    boost::python::ssize_t const len = boost::python::len (items);
    for (boost::python::ssize_t i = 0; i < len; ++i)
    {
        boost::python::object item = items[i];
        strm << item;
        if (len > (i + 1))
        {
            strm << Text::DELIMITER;
        }
    }
    return strm << Text::CLOSE_DICT;
}


#endif //INCLUDED_PYTHON_IO_HELPERS_HPP
