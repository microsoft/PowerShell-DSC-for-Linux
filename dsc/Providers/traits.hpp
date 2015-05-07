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
