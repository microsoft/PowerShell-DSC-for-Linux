#include "extension.hpp"
#include <boost/python.hpp>


using namespace boost::python;


// this is how overloading works
void (Foo::*setMsg_1)(std::string) = &Foo::setMsg;
void (Foo::*setMsg_2)() = &Foo::setMsg;


BOOST_PYTHON_MODULE (extension)
{
    class_<Foo> ("Foo", init<std::string>())
        .def ("getMsg", &Foo::getMsg)
        .def ("setMsg", setMsg_1) // overloading - see above
        .def ("setMsg", setMsg_2) // overloading - see above
    ;
}
