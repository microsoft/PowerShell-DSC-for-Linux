#include "python_io_helpers.hpp"


namespace scx
{

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

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::PY_UNICODE_SIZE[] = "Py_UNICODE_SIZE";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::PY_UNICODE_WIDE[] = "Py_UNICODE_WIDE";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::IS_DEFINED[] = "is defined";

template<typename charT> /*static*/ charT const
PythonTextConstants<charT>::IS_NOT_DEFINED[] = "is not defined";


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

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::PY_UNICODE_SIZE[] = L"Py_UNICODE_SIZE";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::PY_UNICODE_WIDE[] = L"Py_UNICODE_WIDE";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::IS_DEFINED[] = L"is defined";

/*static*/ PythonTextConstants<wchar_t>::charT const
PythonTextConstants<wchar_t>::IS_NOT_DEFINED[] = L"is not defined";

} // namespace scx
