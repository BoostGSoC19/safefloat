#ifndef BOOST_SAFE_FLOAT_CAST_FROM_SAFE_HPP
#define BOOST_SAFE_FLOAT_CAST_FROM_SAFE_HPP

#include <type_traits>
#include <boost/safe_float/utility.hpp>
#include <boost/safe_float/policy/cast_base_policy.hpp>


namespace boost
{
namespace safe_float
{
namespace policy
{
namespace detail
{
// Proxies that enable test of can_cast_from/can_explicitly_cast_from with non safe_float
// types returning false instead of causing compilation error
template<typename CAST, typename T, typename enabled = void>
struct can_cast_from_value_type;

template<typename CAST, typename T>
struct can_cast_from_value_type<CAST, T, std::enable_if_t<!is_safe_float<T>::value>> : std::false_type
{};

template<typename CAST, typename T>
struct can_cast_from_value_type<CAST, T, std::enable_if_t<is_safe_float<T>::value>> :
    std::conditional_t<CAST::template can_cast_from<typename T::value_type>, std::true_type, std::false_type>
{};

template<typename CAST, typename T, typename enabled = void>
struct can_explicitly_cast_from_value_type;

template<typename CAST, typename T>
struct can_explicitly_cast_from_value_type<CAST, T, std::enable_if_t<!is_safe_float<T>::value>> : std::false_type
{};

template<typename CAST, typename T>
struct can_explicitly_cast_from_value_type<CAST, T, std::enable_if_t<is_safe_float<T>::value>> :
    std::conditional_t<CAST::template can_explicitly_cast_from<typename T::value_type>, std::true_type, std::false_type>
{};

template<typename SF, typename T>
struct can_cast_to : std::false_type {};

template<typename FP, template<typename> typename CHECK, typename REPORT, template<typename> typename CAST, typename T>
struct can_cast_to<safe_float<FP, CHECK, REPORT, CAST>, T> : std::conditional_t<CAST<safe_float<FP, CHECK, REPORT, CAST>>::template can_cast_to<T>, std::true_type, std::false_type> {};
} // namespace detail

template<template<typename> typename FLOAT_CAST, template<typename> typename POLICY_CAST, bool is_explicit = false>
struct cast_from_safe
{
    template<typename SF>
    struct policy
    {
        template<typename T>
        static constexpr bool can_cast_from =
            !is_explicit && is_safe_float<T>::value && detail::can_cast_from_value_type<FLOAT_CAST<SF>, T>::value
            && POLICY_CAST<SF>::template can_cast_from<T>;

        template<typename T>
        static constexpr bool can_explicitly_cast_from =
            is_explicit&& is_safe_float<T>::value
            && (detail::can_cast_from_value_type<FLOAT_CAST<SF>, T>::value || detail::can_explicitly_cast_from_value_type<FLOAT_CAST<SF>, T>::value)&&(
                POLICY_CAST<SF>::template can_cast_from<T> || POLICY_CAST<SF>::template can_explicitly_cast_from<T>)
            && !detail::can_cast_to<T, SF>::value; // Disable explicit construction from T if T can be implictly converted to SF

        template<typename T>
        static void cast_from(typename SF::value_type& target, T source)
        {
            cast_helper<typename SF::value_type, FLOAT_CAST<SF>>::template construct_explicitly(
                target, source.get_stored_value());
        }

        template<typename T>
        static constexpr bool can_cast_to = false;

        template<typename T>
        static constexpr bool can_explicitly_cast_to = false;
    };
};


namespace cast_from_safe_policy
{
template<typename SF, bool is_explicit = false, std::enable_if_t<is_safe_float<SF>::value, int> = 0>
struct more_restrictive_impl
{
    template<typename T>
    static constexpr bool can_cast_from = !is_explicit && is_safe_float<T>::value
                                          && is_subset<typename SF::check_policy, typename T::check_policy>::value;

    template<typename T>
    static constexpr bool can_explicitly_cast_from =
        is_explicit&& is_safe_float<T>::value&& is_subset<typename SF::check_policy, typename T::check_policy>::value;

    template<typename T>
    static void cast_from(typename SF::value_type& target, T source)
    {
        target = source.get_stored_value();
    }

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;
};

template<typename SF>
using more_restrictive = more_restrictive_impl<SF>;
template<typename SF>
using more_restrictive_explicit = more_restrictive_impl<SF, true>;


template<typename SF, bool is_explicit = false, std::enable_if_t<is_safe_float<SF>::value, int> = 0>
struct less_restrictive_impl
{
    template<typename T>
    static constexpr bool can_cast_from = !is_explicit && is_safe_float<T>::value
                                          && is_subset<typename T::check_policy, typename SF::check_policy>::value;

    template<typename T>
    static constexpr bool can_explicitly_cast_from =
        is_explicit&& is_safe_float<T>::value&& is_subset<typename T::check_policy, typename SF::check_policy>::value;

    template<typename T>
    static void cast_from(typename SF::value_type& target, T source)
    {
        target = source.get_stored_value();
    }

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;
};

template<typename SF>
using less_restrictive = less_restrictive_impl<SF>;
template<typename SF>
using less_restrictive_explicit = less_restrictive_impl<SF, true>;


template<typename SF, bool is_explicit = false, std::enable_if_t<is_safe_float<SF>::value, int> = 0>
struct equivalent_impl
{
    template<typename T>
    static constexpr bool can_cast_from = !is_explicit && is_safe_float<T>::value
                                          && is_equivalent<typename T::check_policy, typename SF::check_policy>::value;

    template<typename T>
    static constexpr bool can_explicitly_cast_from = is_explicit&& is_safe_float<T>::value&&
        is_equivalent<typename T::check_policy, typename SF::check_policy>::value;

    template<typename T>
    static void cast_from(typename SF::value_type& target, T source)
    {
        target = source.get_stored_value();
    }

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;
};

template<typename SF>
using equivalent = equivalent_impl<SF>;
template<typename SF>
using equivalent_explicit = equivalent_impl<SF, true>;

template<typename SF, bool is_explicit = false, std::enable_if_t<is_safe_float<SF>::value, int> = 0>
struct all_impl
{
    template<typename T>
    static constexpr bool can_cast_from = !is_explicit && is_safe_float<T>::value;

    template<typename T>
    static constexpr bool can_explicitly_cast_from = is_explicit&& is_safe_float<T>::value;

    template<typename T>
    static void cast_from(typename SF::value_type& target, T source)
    {
        target = source.get_stored_value();
    }

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;
};

template<typename SF>
using all = all_impl<SF>;
template<typename SF>
using all_explicit = all_impl<SF, true>;
} // namespace cast_from_safe_policy
} // namespace policy
} // namespace safe_float
} // namespace boost

#endif // BOOST_SAFE_FLOAT_CAST_FROM_SAFE_HPP