#ifndef INCLUDED_EXTENSION_HPP
#define INCLUDED_EXTENSION_HPP


#include <boost/python.hpp>
#include <string>


class Foo
{
public:
    /*ctor*/ Foo (std::string msg) : m_Msg (msg) {}

    void setMsg (std::string msg) { m_Msg = msg; }
    void setMsg () { m_Msg.clear (); }

    std::string getMsg () { return m_Msg; }

private:
    std::string m_Msg;
};


#endif // INCLUDED_EXTENSION_HPP
