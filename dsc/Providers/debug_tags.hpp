#ifndef INCLUDED_DEBUG_TAGS_HPP
#define INCLUDED_DEBUG_TAGS_HPP


#include <iostream>
#include <string>


#ifndef PRINT_BOOKENDS
#define PRINT_BOOKENDS (0)
#endif


#if (PRINT_BOOKENDS)

#define SCX_BOOKEND(title) scx::BookEnd be (title)
#define SCX_BOOKEND_EX(title,sub_title) scx::BookEnd be (title, sub_title)
#define SCX_BOOKEND_PRINT(text) scx::BookEnd::print (text)

#else

#define SCX_BOOKEND(title)
#define SCX_BOOKEND_EX(title,sub_title)
#define SCX_BOOKEND_PRINT(text)

#endif


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
#if (PRINT_BOOKENDS)
    for (unsigned int i = 0; i < s_nIndent; ++i)
    {
        std::cout << INDENT;
    }
    std::cout << text << std::endl;
#endif
}


}


#endif // INCLUDED_DEBUG_TAGS_HPP
