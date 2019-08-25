#ifndef BOOST_SAFE_FLOAT_LITERALS_HPP
#define BOOST_SAFE_FLOAT_LITERALS_HPP

#include <boost/safe_float.hpp>


namespace boost
{
namespace safe_float
{
namespace literals
{
namespace detail
{
#define HEX_PARSE_ERROR "Not a valid hex floating point number literal"
#define DEC_PARSE_ERROR "Not a valid dec floating point number literal"
#define VALUE_ERROR "Floating point number isn't a positive power of 0.5"


template<char... digits>
struct bigint;

template<typename MANTISSA, int EXPONENT>
struct number {
    using mantissa = MANTISSA;
    static constexpr int exponent = EXPONENT;
};

template<typename T>
struct is_number : std::false_type {};

template<typename M, int E>
struct is_number<number<M, E>> : std::true_type {};

template<int MIN, int MAX> 
struct min_max_pow {
    static constexpr int min = MIN;
    static constexpr int max = MAX;
};

template<typename BI, int EXP>
struct shift_left_helper;

template<char... digits, int EXP>
struct shift_left_helper<bigint<digits...>, EXP> {
    using type = typename shift_left_helper<bigint<digits..., 0>, EXP-1>::type;
};

template<char... digits>
struct shift_left_helper<bigint<digits...>, 0> {
    using type = bigint<digits...>;
};

template<typename BI, int EXP>
struct shift_right_helper;

template<char... digits, int EXP>
struct shift_right_helper<bigint<digits...>, EXP> {
    using type = typename shift_right_helper<bigint<0, digits...>, EXP-1>::type;
};

template<char... digits>
struct shift_right_helper<bigint<digits...>, 0> {
    using type = bigint<digits...>;
};

template<char... digits>
struct bigint {
    template<char next>
    using append = bigint<digits..., next>;

    template<int EXP>
    using shift_left = typename shift_left_helper<bigint, EXP>::type;
    
    template<int EXP>
    using shift_right = typename shift_right_helper<bigint, EXP>::type;
    
    static constexpr size_t length = sizeof...(digits);
};

template<typename T, unsigned long long init = 0>
struct bigint_value;

template<char first, char... rest, unsigned long long init>
struct bigint_value<bigint<first, rest...>, init> {
    static constexpr unsigned long long value = bigint_value<bigint<rest...>, init*10 + first>::value;
};

template<unsigned long long init>
struct bigint_value<bigint<>, init> {
    static constexpr unsigned long long value = init;
};

template<typename BI, typename RES, bool carry>
struct halve_helper;

template<char first, char... digits, char... other, bool carry>
struct halve_helper<bigint<first, digits...>, bigint<other...>, carry> {
    using type = typename halve_helper<bigint<digits...>, bigint<other..., (carry ? 5 : 0) + first/2>, (first % 2 == 1)>::type;
};

template<char... other, bool carry>
struct halve_helper<bigint<>, bigint<other...>, carry> {
    using type = bigint<other...>;
};

template<typename BI, typename RES>
struct halve_helper_first;

template<char first, char... digits>
struct halve_helper_first<bigint<first, digits...>, bigint<>> {
    using type = typename halve_helper<bigint<digits...>, bigint<first/2>, (first % 2 == 1)>::type;
};

template<char...digits>
struct halve_helper_first<bigint<1, digits...>, bigint<>> {
    using type = typename halve_helper<bigint<digits...>, bigint<>, true>::type;
};

template<typename BI>
using halve = typename halve_helper_first<BI, bigint<>>::type;

template<typename BI, typename RES, bool carry>
struct double_helper;

template<char first, char... digits, char... other, bool carry>
struct double_helper<bigint<first, digits...>, bigint<other...>, carry> {
    using type = typename double_helper<bigint<digits...>, bigint<other..., (first*2 + (carry?1:0))%10>, (first >= 5)>::type;
};

template<char... other, bool carry>
struct double_helper<bigint<>, bigint<other...>, carry> {
    using type = bigint<other...>;
};

template<typename BI, typename RES>
struct double_helper_first;

template<char first, char... digits>
struct double_helper_first<bigint<first, digits...>, bigint<>> {
    using type = typename double_helper<bigint<digits...>, bigint<(first*2)%10>, (first >= 5)>::type;
};

template<char... digits>
struct double_helper_first<bigint<5, digits...>, bigint<>> {
    using type = typename double_helper<bigint<digits...>, bigint<>, true>::type;
};

template<typename BI>
using double_op = typename double_helper_first<BI, bigint<>>::type;

template<typename BI>
struct is_odd;

template<char first, char... digits>
struct is_odd<bigint<first, digits...>> {
    static constexpr bool value = is_odd<bigint<digits...>>::value;
};

template<char digit>
struct is_odd<bigint<digit>> {
    static constexpr bool value = (digit % 2 == 1);
};

template<typename BI>
struct ends_with_gt5;

template<char first, char... digits>
struct ends_with_gt5<bigint<first, digits...>> {
    static constexpr bool value = ends_with_gt5<bigint<digits...>>::value;
};

template<char digit>
struct ends_with_gt5<bigint<digit>> {
    static constexpr bool value = (digit >= 5);
};


// TODO Find a way to get min/max power of 2 with less template recursion
// It could speed up compilation and avoid error with long numbers


template<typename MANTISSA>
struct get_min_pow_int_helper {
    static constexpr int value = (is_odd<MANTISSA>::value ? 0 : get_min_pow_int_helper<halve<MANTISSA>>::value + 1);
};

template<>
struct get_min_pow_int_helper<bigint<1>> {
    static constexpr int value = 0;
};

template<typename MANTISSA>
constexpr int get_min_pow_int() {
    return get_min_pow_int_helper<MANTISSA>::value;
}

template<typename MANTISSA, typename enable = void>
struct get_max_pow_dec_helper {
    static constexpr int value = (ends_with_gt5<MANTISSA>::value ? -1 : get_max_pow_dec_helper<double_op<MANTISSA>>::value - 1);
};

template<char digit>
struct get_max_pow_dec_helper<bigint<digit>, std::enable_if_t<(digit >=5)>> {
    static constexpr int value = -1;
};

template<typename MANTISSA>
constexpr int get_max_pow_dec() {
    return get_max_pow_dec_helper<MANTISSA>::value;
}

template<typename MANTISSA>
struct get_max_pow_int_helper {
    static constexpr int value = 1 + get_max_pow_int_helper<halve<MANTISSA>>::value;
};

template<>
struct get_max_pow_int_helper<bigint<1>> {
    static constexpr int value = 0;
};

template<typename MANTISSA>
constexpr int get_max_pow_int() {
    return get_max_pow_int_helper<MANTISSA>::value;
}

// TODO Stop recursion after a while if the number isn't made of powers of 2
template<typename MANTISSA, unsigned MAX_STEPS, typename enable = void>
struct get_min_pow_dec_helper;

template<typename MANTISSA, unsigned MAX_STEPS>
struct get_min_pow_dec_helper<MANTISSA, MAX_STEPS, std::enable_if_t<(MANTISSA::length > 1 && MAX_STEPS > 0)>> {
    static constexpr int value = get_min_pow_dec_helper<double_op<MANTISSA>, MAX_STEPS-1>::value - 1;
};

template<char digit, unsigned MAX_STEPS>
struct get_min_pow_dec_helper<bigint<digit>, MAX_STEPS, std::enable_if_t<(digit == 5 && MAX_STEPS > 0)>> {
    static constexpr int value = -1;
};

template<char digit, unsigned MAX_STEPS>
struct get_min_pow_dec_helper<bigint<digit>, MAX_STEPS, std::enable_if_t<(digit != 5 && MAX_STEPS > 0)>> {
    static constexpr int value = get_min_pow_dec_helper<double_op<bigint<digit>>, MAX_STEPS-1>::value - 1;
};

// If template recursion goes too far, stop it, number is not made of power of 2
template<typename MANTISSA>
struct get_min_pow_dec_helper<MANTISSA, 0, void> {
    static constexpr int value = -10000; // Give a value that will indicates the number isn't representable
};

template<typename MANTISSA>
constexpr int get_min_pow_dec() {
    return get_min_pow_dec_helper<MANTISSA, 800>::value;
}

template<typename BI, typename RES, unsigned count>
struct extract_begin_helper;

template<char first, char... digits, char... other, unsigned count>
struct extract_begin_helper<bigint<first, digits...>, bigint<other...>, count> {
    using type = typename extract_begin_helper<bigint<digits...>, bigint<other..., first>, count-1>::type;
};

template<char first, char...digits, char...other>
struct extract_begin_helper<bigint<first, digits...>, bigint<other...>, 0> {
    using type = bigint<other...>;
};

template<char... other, unsigned count>
struct extract_begin_helper<bigint<>, bigint<other...>, count> {
    using type = bigint<other...>;
}; 

template<typename BI, unsigned count>
using extract_begin = typename extract_begin_helper<BI, bigint<>, count>::type;

template<typename BI, unsigned count>
struct extract_end_helper;

template<char first, char... digits, unsigned count>
struct extract_end_helper<bigint<first, digits...>, count> {
    using type = std::conditional_t<(bigint<first, digits...>::length > count), 
    typename extract_end_helper<bigint<digits...>, count>::type,
    bigint<first, digits...>>;
};

template<unsigned count>
struct extract_end_helper<bigint<>, count> {
    using type = bigint<>;
};

template<typename BI, unsigned count>
using extract_end = typename extract_end_helper<BI, count>::type;

template<typename NUMBER, typename INVERTED>
struct inverse_helper;

template<char first, char... rest, char... other>
struct inverse_helper<bigint<first, rest...>, bigint<other...>>  {
    using type = typename inverse_helper<bigint<rest...>, bigint<first, other...>>::type;
};

template<char... other>
struct inverse_helper<bigint<>, bigint<other...>> {
    using type = bigint<other...>;
};

template<typename NUMBER>
using inverse = typename inverse_helper<NUMBER, bigint<>>::type;

// A struct to be used in static_assert
template<typename T>
struct always_false
{
    static constexpr bool value = false;
};

// A constexpr version of isxdigit working on ASCII
constexpr bool isxdigit(char c)
{
    return ((c >= '0' and c <= '9') or (c >= 'a' and c <= 'f') or (c >= 'A' and c <= 'F'));
}

// A constexpr version of isdigit working on ASCII
constexpr bool isdigit(char c)
{
    return (c >= '0' and c <= '9');
}

// constexpr function to get the represented value of a hex digit
constexpr int hexvalue(char xdigit)
{
    return (xdigit >= '0' and xdigit <= '9') ?
               xdigit - '0' :
               (xdigit >= 'a' and xdigit <= 'f') ? xdigit - 'a' + 10 :
                                                   (xdigit >= 'A' and xdigit <= 'F') ? xdigit - 'A' + 10 : 0;
}

// constexpr function to get the represented value of a digit
constexpr int decvalue(char digit)
{
    return (digit >= '0' and digit <= '9') ? digit - '0' : 0;
}

// constexpr function that count bit equal to 1
constexpr int count_bit(unsigned long long a)
{
    int count = 0;
    while (a != 0)
    {
        if (a & 0x1) count++;
        a >>= 1;
    }

    return count;
}

// A constexpr function that count the number of bit with value 0 before a bit with 1
constexpr int count_shift(unsigned long long a)
{
    int count = 0;
    while (a != 0)
    {
        if (a & 0x1) return count;
        count++;
        a >>= 1;
    }

    return count;
}

template<typename T>
constexpr T trivial_pow(T x, int e)
{
    return e < 0 ? 1 / trivial_pow(x, -e) : e == 0 ? 1 : x * trivial_pow(x, e - 1);
}

// A function to know is a literal begins with an hex prefix
template<char FIRST>
constexpr bool has_hex_prefix()
{
    return false;
}

template<char FIRST, char SECOND, char... REST>
constexpr bool has_hex_prefix()
{
    return FIRST == '0' and (SECOND == 'x' or SECOND == 'X');
}

/*
 * Hex parsing related functions (better understanding by reading from bottom to top)
 */

// Function used to validate the number and returning its value
template<typename RT, unsigned long long MANTISSA, int POW, bool SIGN, int EXPONENT>
constexpr RT validate_hex()
{
    // Is it a power of two ?
    static_assert(count_bit(MANTISSA) == 1, VALUE_ERROR);
    // Is the exponent negative (positive power of 0.5 means negative power of 2)
    static_assert(count_shift(MANTISSA) + POW + (SIGN ? EXPONENT : -EXPONENT) < 0, VALUE_ERROR);
    return static_cast<RT>(MANTISSA) * trivial_pow(2.0l, POW + (SIGN ? EXPONENT : -EXPONENT));
}


// Function used to parse the digit of the exponent
template<typename RT, unsigned long long MANTISSA, int POW, bool SIGN, int EXPONENT>
constexpr RT parse_hex_exponent()
{
    return validate_hex<RT, MANTISSA, POW, SIGN, EXPONENT>();
}

template<typename RT, unsigned long long MANTISSA, int POW, bool SIGN, int EXPONENT, char FIRST, char... REST>
constexpr RT parse_hex_exponent()
{
    static_assert(isdigit(FIRST), HEX_PARSE_ERROR);
    return parse_hex_exponent<RT, MANTISSA, POW, SIGN, EXPONENT * 10 + decvalue(FIRST), REST...>();
}


// This function parses the first character after the 'p'
template<typename RT, unsigned long long MANTISSA, int POW>
constexpr RT parse_hex_exponent_sign()
{
    static_assert(always_false<RT>::value, HEX_PARSE_ERROR);
    return RT{};
}

template<typename RT, unsigned long long MANTISSA, int POW, char FIRST, char... REST>
constexpr RT parse_hex_exponent_sign()
{
    static_assert(isxdigit(FIRST) or FIRST == '+' or FIRST == '-', HEX_PARSE_ERROR);
    if constexpr (isxdigit(FIRST))
        return parse_hex_exponent<RT, MANTISSA, POW, true, hexvalue(FIRST), REST...>();
    else
    {
        // If we have a sign, we need to make there is at least one other character after
        static_assert(sizeof...(REST) > 0, HEX_PARSE_ERROR);
        if constexpr (FIRST == '+')
            return parse_hex_exponent<RT, MANTISSA, POW, true, 0, REST...>();
        else
            return parse_hex_exponent<RT, MANTISSA, POW, false, 0, REST...>();
    }
}


// Function used to parse the characters of a hex float literal that appear after the period
template<typename RT, unsigned long long MANTISSA, int POW>
constexpr RT parse_hex_post_period()
{
    static_assert(always_false<RT>::value, HEX_PARSE_ERROR);
    return RT{};
}

template<typename RT, unsigned long long MANTISSA, int POW, char FIRST, char... REST>
constexpr RT parse_hex_post_period()
{
    static_assert(isxdigit(FIRST) or FIRST == 'p' or FIRST == 'P', HEX_PARSE_ERROR);
    if constexpr (isxdigit(FIRST))
        return parse_hex_post_period<RT, MANTISSA * 16 + hexvalue(FIRST), POW - 4, REST...>();
    else
        return parse_hex_exponent_sign<RT, MANTISSA, POW, REST...>();
}


// Function used to parse the characters of a hex float literal that appear before the period
template<typename RT, unsigned long long MANTISSA>
constexpr RT parse_hex_pre_period()
{
    // If they are no more characters and we're here it means that is not a good hex float literal
    static_assert(always_false<RT>::value, HEX_PARSE_ERROR);
    return RT{};
}

template<typename RT, unsigned long long MANTISSA, char FIRST, char... REST>
constexpr RT parse_hex_pre_period()
{
    static_assert(isxdigit(FIRST) or FIRST == '.' or FIRST == 'p' or FIRST == 'P', HEX_PARSE_ERROR);
    if constexpr (isxdigit(FIRST))
        return parse_hex_pre_period<RT, MANTISSA * 16 + hexvalue(FIRST), REST...>();
    else if constexpr (FIRST == '.')
        return parse_hex_post_period<RT, MANTISSA, 0, REST...>();
    else
        return parse_hex_exponent_sign<RT, MANTISSA, 0, REST...>();
}


template<typename RT, char FIRST, char SECOND, char... REST>
constexpr RT test_hex()
{
    // Discard 2 first char as they are the hex marker
    return parse_hex_pre_period<RT, 0, REST...>();
}

template<typename RT>
struct in_range_for_helper;

template<>
struct in_range_for_helper<float> {
    static constexpr bool calc(int min, int max) {
        return (max - min <= 23) && (max <  128) && (max > -127);
    }
};

template<>
struct in_range_for_helper<double> {
    static constexpr bool calc(int min, int max) {
        return (max - min <= 52) && (max <  1024) && (max > -1023);
    }
};

template<>
struct in_range_for_helper<long double> {
    static constexpr bool calc(int min, int max) {
        return (max - min <= 64) && (max <  16384) && (max > -16383);
    }
};

template<typename RT>
constexpr bool in_range_for(int min, int max) {
    return in_range_for_helper<RT>::calc(min, max);
}

template<typename MANTISSA, int EXPONENT>
constexpr auto get_min_max_pow() {
    // TODO Special cases when 0 or 0 dot something
    if constexpr(EXPONENT >= 0) // Only integer part
    {
        using shifted = typename MANTISSA::template shift_left<EXPONENT>;
        constexpr int min_pow = get_min_pow_int<shifted>();
        constexpr int max_pow = get_max_pow_int<shifted>();

        return min_max_pow<min_pow, max_pow>{};
    } else if constexpr(-EXPONENT >= MANTISSA::length) // Only decimal part
    {
        using shifted = typename MANTISSA::template shift_right<-EXPONENT-MANTISSA::length>;
        using inversed = inverse<shifted>;
        constexpr int min_pow = get_min_pow_dec<inversed>();
        constexpr int max_pow = get_max_pow_dec<inversed>();

        return min_max_pow<min_pow, max_pow>{};
    } else
    {
        using int_part = extract_begin<MANTISSA, MANTISSA::length+EXPONENT>;
        using dec_part = extract_end<MANTISSA, -EXPONENT>;
        constexpr int min_pow = get_min_pow_dec<inverse<dec_part>>();
        constexpr int max_pow = get_max_pow_int<int_part>();

        return min_max_pow<min_pow, max_pow>{};
    }
}

template<typename RT, typename MANTISSA, int EXPONENT>
constexpr bool is_representable() {
    // TODO Special cases when 0 or 0 dot something
    using min_max = decltype(get_min_max_pow<MANTISSA, EXPONENT>());
    return in_range_for<RT>(min_max::min, min_max::max);
}


// Validate value and returns it
template<typename RT, typename MANTISSA, int POW, bool SIGN, int EXPONENT>
constexpr RT validate_dec()
{
    static_assert(is_representable<RT, MANTISSA, POW + (SIGN ? EXPONENT : -EXPONENT)>(),
        "This number cannot be represented exactly");
    constexpr unsigned long long mantissa = bigint_value<MANTISSA>::value;
    constexpr RT value =
        (POW + (SIGN ? EXPONENT : -EXPONENT) < 0 ? mantissa / trivial_pow(10.0l, -POW - (SIGN ? EXPONENT : -EXPONENT)) :
                                                   mantissa * trivial_pow(10.0l, POW + (SIGN ? EXPONENT : -EXPONENT)));
    return value;
}


// This function parses the exponent past the first character
template<typename MANTISSA, int POW, bool SIGN, int EXPONENT>
constexpr auto parse_dec_exponent()
{
    return number<MANTISSA, POW + (SIGN ? EXPONENT : -EXPONENT)>{};
}

template<typename MANTISSA, int POW, bool SIGN, int EXPONENT, char FIRST, char... REST>
constexpr auto parse_dec_exponent()
{
    static_assert(isdigit(FIRST), DEC_PARSE_ERROR);
    return parse_dec_exponent<MANTISSA, POW, SIGN, EXPONENT * 10 + decvalue(FIRST), REST...>();
}


// This function parses the first character of the exponent
template<typename MANTISSA, int POW>
constexpr auto parse_dec_exponent_sign()
{
    static_assert(always_false<MANTISSA>::value, DEC_PARSE_ERROR);
    return int{};
}

template<typename MANTISSA, int POW, char FIRST, char... REST>
constexpr auto parse_dec_exponent_sign()
{
    static_assert(isdigit(FIRST) or ((FIRST == '+' or FIRST == '-') and sizeof...(REST) > 0), DEC_PARSE_ERROR);
    if constexpr (isdigit(FIRST))
        return parse_dec_exponent<MANTISSA, POW, true, decvalue(FIRST), REST...>();
    else if constexpr (FIRST == '+')
        return parse_dec_exponent<MANTISSA, POW, true, 0, REST...>();
    else
        return parse_dec_exponent<MANTISSA, POW, false, 0, REST...>();
}


// This function parses the characters that are after the period
template<typename MANTISSA, int POW>
constexpr auto parse_dec_post_period()
{
    return number<MANTISSA, POW>{};
}

template<typename MANTISSA, int POW, char FIRST, char... REST>
constexpr auto parse_dec_post_period()
{
    static_assert(isdigit(FIRST) or FIRST == 'e' or FIRST == 'E', DEC_PARSE_ERROR);
    if constexpr (isdigit(FIRST))
        return parse_dec_post_period<typename MANTISSA::template append<decvalue(FIRST)>, POW - 1, REST...>();
    else
        return parse_dec_exponent_sign<MANTISSA, POW, REST...>();
}


// This character parses the first characters before the period
template<typename MANTISSA>
constexpr auto parse_dec_pre_period()
{
    return validate_dec<MANTISSA, 0, true, 0>();
}

template<typename MANTISSA, char FIRST, char... REST>
constexpr auto parse_dec_pre_period()
{
    static_assert(isdigit(FIRST) or FIRST == '.' or FIRST == 'e' or FIRST == 'E', DEC_PARSE_ERROR);
    if constexpr (isdigit(FIRST))
        return parse_dec_pre_period<typename MANTISSA::template append<decvalue(FIRST)>, REST...>();
    else if constexpr (FIRST == '.')
        return parse_dec_post_period<MANTISSA, 0, REST...>();
    else
        return parse_dec_exponent_sign<MANTISSA, 0, REST...>();
}


template<char... STR>
constexpr auto test_dec()
{
    return parse_dec_pre_period<bigint<>, STR...>();
}

// Don't pollute global namespace
#undef HEX_PARSE_ERROR
#undef DEC_PARSE_ERROR
#undef VALUE_ERROR


template<char... STR>
constexpr auto parse_float_literal()
{
    if constexpr (has_hex_prefix<STR...>())
        return test_hex<double, STR...>();
    else
        return test_dec<STR...>();
}
} // namespace detail


template<char... STR>
boost::safe_float::safe_float<float> operator""_sf()
{
    using number = decltype(detail::parse_float_literal<STR...>());
    if constexpr(detail::is_number<number>::value) {
        using mantissa = typename number::mantissa;
        constexpr int exponent = number::exponent;

        static_assert(detail::is_representable<float, mantissa, exponent>(),
                      "This number cannot be represented exactly");

        constexpr unsigned long long mantissa_value = detail::bigint_value<mantissa>::value;
        constexpr float value =
            (exponent < 0 ? mantissa_value / detail::trivial_pow(10.0l, -exponent) :
             mantissa_value * detail::trivial_pow(10.0l, exponent));
        return boost::safe_float::safe_float<float>(value);
    }
}

template<char... STR>
boost::safe_float::safe_float<double> operator""_sd()
{
    using number = decltype(detail::parse_float_literal<STR...>());
    if constexpr(detail::is_number<number>::value) {
        using mantissa = typename number::mantissa;
        constexpr int exponent = number::exponent;

        static_assert(detail::is_representable<double, mantissa, exponent>(),
                      "This number cannot be represented exactly");
        
        constexpr unsigned long long mantissa_value = detail::bigint_value<mantissa>::value;
        constexpr double value =
            (exponent < 0 ? mantissa_value / detail::trivial_pow(10.0l, -exponent) :
             mantissa_value * detail::trivial_pow(10.0l, exponent));
        return boost::safe_float::safe_float<double>(value);
    }
    return boost::safe_float::safe_float<double>(0.0);
}

template<char... STR>
boost::safe_float::safe_float<long double> operator""_sld()
{
    using number = decltype(detail::parse_float_literal<STR...>());
    if constexpr(detail::is_number<number>::value) {
        using mantissa = typename number::mantissa;
        constexpr int exponent = number::exponent;

        static_assert(detail::is_representable<long double, mantissa, exponent>(),
                      "This number cannot be represented exactly");

        constexpr unsigned long long mantissa_value = detail::bigint_value<mantissa>::value;
        constexpr long double value =
            (exponent < 0 ? mantissa_value / detail::trivial_pow(10.0l, -exponent) :
             mantissa_value * detail::trivial_pow(10.0l, exponent));
        return boost::safe_float::safe_float<long double>(value);
    }
    return boost::safe_float::safe_float<long double>(0.0l);
}

} // namespace literals
} // namespace safe_float
} // namespace boost

#endif // BOOST_SAFE_FLOAT_LITERALS_HPP