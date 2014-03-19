#ifndef INCLUDED_PYTHONIOHELPERS_HPP
#define INCLUDED_PYTHONIOHELPERS_HPP


#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <iosfwd>


namespace SCX
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
};


std::ostream&
PythonUnicodeInfo (
    std::ostream& strm)
{
    strm << "Py_UNICODE_SIZE: " << Py_UNICODE_SIZE;
#ifdef Py_UNICODE_WIDE
    strm << " (Py_UNICODE_WIDE is defined)";
#else
    strm << " (Py_UNICODE_WIDE is not defined)";
#endif
    return strm;
}


std::wostream&
PythonUnicodeInfo (
    std::wostream& strm)
{
    strm << L"Py_UNICODE_SIZE: " << Py_UNICODE_SIZE;
#ifdef Py_UNICODE_WIDE
    strm << L" (Py_UNICODE_WIDE is defined)";
#else
    strm << L" (Py_UNICODE_WIDE is not defined)";
#endif
    return strm;
}


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
PythonPath (
    std::basic_ostream<charT, traits>& strm)
{
    typedef SCX::PythonTextConstants<charT> Text;
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


template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::CALLABLE[] = "callable";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::UNDEFINED[] = "undefined boost::python::object";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::NULL_STR[] = "Null";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::OPEN_LIST = '[';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::CLOSE_LIST = ']';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::OPEN_TUPLE = '(';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::CLOSE_TUPLE = ')';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::OPEN_DICT = '{';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::CLOSE_DICT = '}';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::DELIMITER = ',';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::PATH_INDENT[] = "    ";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::OPEN_BRACE = '[';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::CLOSE_BRACE = ']';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::COLON = ':';

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::DOUBLE_QUOTE = '\"';


/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::CALLABLE[] = L"callable";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::UNDEFINED[] = L"undefined boost::python::object";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::NULL_STR[] = L"Null";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::OPEN_LIST = L'[';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::CLOSE_LIST = L']';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::OPEN_TUPLE = L'(';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::CLOSE_TUPLE = L')';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::OPEN_DICT = L'{';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::CLOSE_DICT = L'}';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::DELIMITER = L',';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::PATH_INDENT[] = L"    ";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::OPEN_BRACE = L'[';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::CLOSE_BRACE = L']';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::COLON = L':';

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::DOUBLE_QUOTE = L'\"';


} // namespace SCX


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::object const& obj);

template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::list const& list);

template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::tuple const& tuple);

template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::dict const& dict);


template<typename charT,
         typename traits>
std::basic_ostream<charT, traits>&
operator << (
    std::basic_ostream<charT, traits>& strm,
    boost::python::object& obj)
{
    typedef SCX::PythonTextConstants<charT> Text;
    using boost::python::extract;

    if (obj)
    {
        extract<long> getInt (obj);
        if (getInt.check ())
        {
            return strm << getInt ();
        }
        extract<double> getDouble (obj);
        if (getDouble.check ())
        {
            return strm << getDouble ();
        }
        extract<char const*> getStr (obj);
        if (getStr.check ())
        {
            return strm << getStr ();
        }
        extract<boost::python::list> getList (obj);
        if (getList.check ())
        {
            return strm << getList ();
        }
        extract<boost::python::tuple> getTuple (obj);
        if (getTuple.check ())
        {
            return strm << getTuple ();
        }
        extract<boost::python::dict> getDict (obj);
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
    typedef SCX::PythonTextConstants<charT> Text;
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
    typedef SCX::PythonTextConstants<charT> Text;
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
    typedef SCX::PythonTextConstants<charT> Text;
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


#endif //INCLUDED_PYTHONIOHELPERS_HPP
