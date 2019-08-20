#ifndef BOOST_SAFE_FLOAT_CAST_BASE_POLICY_HPP
#define BOOST_SAFE_FLOAT_CAST_BASE_POLICY_HPP

#include <type_traits>
#include <boost/safe_float.hpp>

namespace boost
{
namespace safe_float
{
namespace policy
{
/**
 * @brief Base policy for cast
 */
template<class FP>
struct cast_policy
{
    template<typename T>
    static constexpr bool can_cast_from = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_from = false;

    template<typename T>
    static void cast_from(FP& target, T source)
    {
        target = source;
    }

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;

    template<typename T>
    static T cast_to(FP source)
    {
        return T(source);
    }
};

template<class FP>
struct cast_none
{
    template<typename T>
    static constexpr bool can_cast_from = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_from = false;

    template<typename T>
    static constexpr bool can_cast_to = false;

    template<typename T>
    static constexpr bool can_explicitly_cast_to = false;
};


template<typename FP, typename CAST_POLICY>
struct cast_helper
{
    template<typename T, std::enable_if_t<CAST_POLICY::template can_cast_from<T>, int> = 0>
    static void construct_implicitly(FP& target, T source)
    {
        CAST_POLICY::template cast_from<T>(target, source);
    }
    template<typename T, std::enable_if_t<CAST_POLICY::template can_explicitly_cast_from<T>, int> = 0>
    static void construct_explicitly(FP& target, T source)
    {
        CAST_POLICY::template cast_from<T>(target, source);
    }

    template<typename T, std::enable_if_t<CAST_POLICY::template can_cast_to<T>, int> = 0>
    static T convert_implicitly(FP source)
    {
        return CAST_POLICY::template cast_to<T>(source);
    }
    template<typename T, std::enable_if_t<CAST_POLICY::template can_explicitly_cast_to<T>, int> = 0>
    static T convert_explicitly(FP source)
    {
        return CAST_POLICY::template cast_to<T>(source);
    }
};


} // namespace policy
} // namespace safe_float
} // namespace boost
#endif // BOOST_SAFE_FLOAT_CHECK_BASE_POLICY_HPP
