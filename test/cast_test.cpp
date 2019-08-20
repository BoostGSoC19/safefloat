#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>


#include <cmath>
#include <limits>


#include <boost/safe_float.hpp>
#include <boost/safe_float/convenience.hpp>
#include <boost/safe_float/policy/cast_to_primitive.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::safe_float;

/**
  This test suite checks the methods providing casting.
  */

BOOST_AUTO_TEST_SUITE( safe_float_casting_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_get_stored_value, FPT, test_types){
    //set initial values
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::min();
    FPT c = std::numeric_limits<FPT>::infinity();
    FPT d = 0;
    FPT e = 1;
    //create safe version of the values
    safe_float<FPT> sa(std::numeric_limits<FPT>::max());
    safe_float<FPT> sb(std::numeric_limits<FPT>::min());
    safe_float<FPT> sc(std::numeric_limits<FPT>::infinity());
    safe_float<FPT> sd(d);
    safe_float<FPT> se(e);
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
    BOOST_CHECK_EQUAL(e, se.get_stored_value());
}

template<typename FP, template<typename> typename CAST>
using sf_test_cast = safe_float<FP, policy::check_all, policy::on_fail_throw, CAST>;

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_none) {
    // Cannot be converted from any primitive but is explicitly constructible from float
    using sf = sf_test_cast<float, policy::cast_from_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Cannot be converted from any primitive but is explicitly constructible from double
    using sd = sf_test_cast<double, policy::cast_from_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));
    
    
    // Cannot be converted from any primitive but is explicitly constructible from long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_none_explicit) {
    // Cannot be converted from any primitive but is explicitly constructible from float
    using sf = sf_test_cast<float, policy::cast_from_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Cannot be converted from any primitive but is explicitly constructible from double
    using sd = sf_test_cast<double, policy::cast_from_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));


    // Cannot be converted from any primitive but is explicitly constructible from long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_same) {
    // Can be converted from float only
    using sf = sf_test_cast<float, policy::cast_from_primitive::same>;

    BOOST_CHECK((std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Can be converted from double only
    using sd = sf_test_cast<double, policy::cast_from_primitive::same>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));


    // Can be converted from long double only
    using sld = sf_test_cast<long double, policy::cast_from_primitive::same>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_same_explicit) {
    // Cannot be converted from any primitive but is explicitly constructible from float
    using sf = sf_test_cast<float, policy::cast_from_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Cannot be converted from any primitive but is explicitly constructible from double
    using sd = sf_test_cast<double, policy::cast_from_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));


    // Cannot be converted from any primitive but is explicitly constructible from long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_more_precise) {
    // Can be converted from float, double and long double
    using sf = sf_test_cast<float, policy::cast_from_primitive::more_precise>;

    BOOST_CHECK((std::is_convertible_v<float, sf>));
    BOOST_CHECK((std::is_convertible_v<double, sf>));
    BOOST_CHECK((std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((std::is_constructible_v<sf, double>));
    BOOST_CHECK((std::is_constructible_v<sf, long double>));


    // Can be converted from double and long double
    using sd = sf_test_cast<double, policy::cast_from_primitive::more_precise>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((std::is_convertible_v<double, sd>));
    BOOST_CHECK((std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((std::is_constructible_v<sd, long double>));


    // Can be converted from long double only
    using sld = sf_test_cast<long double, policy::cast_from_primitive::more_precise>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_more_precise_explicit) {
    // Can be explicitly constructed from float, double and long double
    using sf = sf_test_cast<float, policy::cast_from_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((std::is_constructible_v<sf, double>));
    BOOST_CHECK((std::is_constructible_v<sf, long double>));


    // Can be explicitly constructed from double and long double
    using sd = sf_test_cast<double, policy::cast_from_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((not std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((std::is_constructible_v<sd, long double>));


    // Can be explicitly constructed from long double only
    using sld = sf_test_cast<long double, policy::cast_from_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((not std::is_constructible_v<sld, float>));
    BOOST_CHECK((not std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_less_precise) {
    // Can be converted from float
    using sf = sf_test_cast<float, policy::cast_from_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Can be converted from float and double
    using sd = sf_test_cast<double, policy::cast_from_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<float, sd>));
    BOOST_CHECK((std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));


    // Can be converted from float, double and long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<float, sld>));
    BOOST_CHECK((std::is_convertible_v<double, sld>));
    BOOST_CHECK((std::is_convertible_v<long double, sld>));
    BOOST_CHECK((std::is_constructible_v<sld, float>));
    BOOST_CHECK((std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_less_precise_explicit) {
    // Can be explicitly constructed from float
    using sf = sf_test_cast<float, policy::cast_from_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((not std::is_constructible_v<sf, double>));
    BOOST_CHECK((not std::is_constructible_v<sf, long double>));


    // Can be explicitly constructed from float and double
    using sd = sf_test_cast<double, policy::cast_from_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((not std::is_constructible_v<sd, long double>));


    // Can be explicitly constructed from float, double and long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((std::is_constructible_v<sld, float>));
    BOOST_CHECK((std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_all) {
    // Can be converted from float, double and long double
    using sf = sf_test_cast<float, policy::cast_from_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<float, sf>));
    BOOST_CHECK((std::is_convertible_v<double, sf>));
    BOOST_CHECK((std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((std::is_constructible_v<sf, double>));
    BOOST_CHECK((std::is_constructible_v<sf, long double>));


    // Can be converted from float, double and long double
    using sd = sf_test_cast<double, policy::cast_from_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<float, sd>));
    BOOST_CHECK((std::is_convertible_v<double, sd>));
    BOOST_CHECK((std::is_convertible_v<long double, sd>));
    BOOST_CHECK((std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((std::is_constructible_v<sd, long double>));


    // Can be converted from float, double and long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<float, sld>));
    BOOST_CHECK((std::is_convertible_v<double, sld>));
    BOOST_CHECK((std::is_convertible_v<long double, sld>));
    BOOST_CHECK((std::is_constructible_v<sld, float>));
    BOOST_CHECK((std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_primitive_all_explicit) {
    // Can be explicitly constructed from float, double and long double
    using sf = sf_test_cast<float, policy::cast_from_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sf>));
    BOOST_CHECK((not std::is_convertible_v<double, sf>));
    BOOST_CHECK((not std::is_convertible_v<long double, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, float>));
    BOOST_CHECK((std::is_constructible_v<sf, double>));
    BOOST_CHECK((std::is_constructible_v<sf, long double>));


    // Can be explicitly constructed from float, double and long double
    using sd = sf_test_cast<double, policy::cast_from_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sd>));
    BOOST_CHECK((not std::is_convertible_v<double, sd>));
    BOOST_CHECK((not std::is_convertible_v<long double, sd>));
    BOOST_CHECK((std::is_constructible_v<sd, float>));
    BOOST_CHECK((std::is_constructible_v<sd, double>));
    BOOST_CHECK((std::is_constructible_v<sd, long double>));


    // Can be explicitly constructed from float, double and long double
    using sld = sf_test_cast<long double, policy::cast_from_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<float, sld>));
    BOOST_CHECK((not std::is_convertible_v<double, sld>));
    BOOST_CHECK((not std::is_convertible_v<long double, sld>));
    BOOST_CHECK((std::is_constructible_v<sld, float>));
    BOOST_CHECK((std::is_constructible_v<sld, double>));
    BOOST_CHECK((std::is_constructible_v<sld, long double>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_none) {
    // Cannot be converted to any primitive
    using sf = sf_test_cast<float, policy::cast_to_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Cannot be converted to any primitive
    using sd = sf_test_cast<double, policy::cast_to_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((not std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Cannot be converted to any primitive
    using sld = sf_test_cast<long double, policy::cast_to_primitive::none>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((not std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_none_explicit) {
    // Cannot be converted to any primitive
    using sf = sf_test_cast<float, policy::cast_to_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Cannot be converted to any primitive
    using sd = sf_test_cast<double, policy::cast_to_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((not std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Cannot be converted to any primitive
    using sld = sf_test_cast<long double, policy::cast_to_primitive::none_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((not std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_same) {
    // Can be converted to float only
    using sf = sf_test_cast<float, policy::cast_to_primitive::same>;

    BOOST_CHECK((std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Can be converted to double only
    using sd = sf_test_cast<double, policy::cast_to_primitive::same>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Can be converted to long double only
    using sld = sf_test_cast<long double, policy::cast_to_primitive::same>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_same_explicit) {
    // Cannot be converted to any primitive but is explicitly castable to float
    using sf = sf_test_cast<float, policy::cast_to_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Cannot be converted to any primitive but is explicitly castable to double
    using sd = sf_test_cast<double, policy::cast_to_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Cannot be converted to any primitive but is explicitly castable to long double
    using sld = sf_test_cast<long double, policy::cast_to_primitive::same_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_more_precise) {
    // Can be converted to float, double and long double
    using sf = sf_test_cast<float, policy::cast_to_primitive::more_precise>;

    BOOST_CHECK((std::is_convertible_v<sf, float>));
    BOOST_CHECK((std::is_convertible_v<sf, double>));
    BOOST_CHECK((std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((std::is_constructible_v<double, sf>));
    BOOST_CHECK((std::is_constructible_v<long double, sf>));


    // Can be converted to double and long double
    using sd = sf_test_cast<double, policy::cast_to_primitive::more_precise>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((std::is_convertible_v<sd, double>));
    BOOST_CHECK((std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((std::is_constructible_v<long double, sd>));


    // Can be converted to long double only
    using sld = sf_test_cast<long double, policy::cast_to_primitive::more_precise>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_more_precise_explicit) {
    // Can be explicitly converted to float, double and long double
    using sf = sf_test_cast<float, policy::cast_to_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((std::is_constructible_v<double, sf>));
    BOOST_CHECK((std::is_constructible_v<long double, sf>));


    // Can be explicitly converted to double and long double
    using sd = sf_test_cast<double, policy::cast_to_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((std::is_constructible_v<long double, sd>));


    // Can be explicitly converted to long double only
    using sld = sf_test_cast<long double, policy::cast_to_primitive::more_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((not std::is_constructible_v<float, sld>));
    BOOST_CHECK((not std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_less_precise) {
    // Can be converted to float
    using sf = sf_test_cast<float, policy::cast_to_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Can be converted to float and double
    using sd = sf_test_cast<double, policy::cast_to_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<sd, float>));
    BOOST_CHECK((std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Can be converted to float, double and long double
    using sld = sf_test_cast<long double, policy::cast_to_primitive::less_precise>;

    BOOST_CHECK((std::is_convertible_v<sld, float>));
    BOOST_CHECK((std::is_convertible_v<sld, double>));
    BOOST_CHECK((std::is_convertible_v<sld, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sld>));
    BOOST_CHECK((std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_less_precise_explicit) {
    // Can be explicitly converted to float
    using sf = sf_test_cast<float, policy::cast_to_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((not std::is_constructible_v<double, sf>));
    BOOST_CHECK((not std::is_constructible_v<long double, sf>));


    // Can be explicitly converted to float and double
    using sd = sf_test_cast<double, policy::cast_to_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((not std::is_constructible_v<long double, sd>));


    // Can be explicitly converted to float, double and long double
    using sld = sf_test_cast<long double, policy::cast_to_primitive::less_precise_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sld>));
    BOOST_CHECK((std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_all) {
    // Can be converted to float, double and long double
    using sf = sf_test_cast<float, policy::cast_to_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<sf, float>));
    BOOST_CHECK((std::is_convertible_v<sf, double>));
    BOOST_CHECK((std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((std::is_constructible_v<double, sf>));
    BOOST_CHECK((std::is_constructible_v<long double, sf>));


    // Can be converted to float, double and long double
    using sd = sf_test_cast<double, policy::cast_to_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<sd, float>));
    BOOST_CHECK((std::is_convertible_v<sd, double>));
    BOOST_CHECK((std::is_convertible_v<sd, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((std::is_constructible_v<long double, sd>));


    // Can be converted to float, double and long double
    using sld = sf_test_cast<long double, policy::cast_to_primitive::all>;

    BOOST_CHECK((std::is_convertible_v<sld, float>));
    BOOST_CHECK((std::is_convertible_v<sld, double>));
    BOOST_CHECK((std::is_convertible_v<sld, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sld>));
    BOOST_CHECK((std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_to_primitive_all_explicit) {
    // Can be explicitly converted to float, double and long double
    using sf = sf_test_cast<float, policy::cast_to_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sf, float>));
    BOOST_CHECK((not std::is_convertible_v<sf, double>));
    BOOST_CHECK((not std::is_convertible_v<sf, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sf>));
    BOOST_CHECK((std::is_constructible_v<double, sf>));
    BOOST_CHECK((std::is_constructible_v<long double, sf>));


    // Can be explicitly converted to float, double and long double
    using sd = sf_test_cast<double, policy::cast_to_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sd, float>));
    BOOST_CHECK((not std::is_convertible_v<sd, double>));
    BOOST_CHECK((not std::is_convertible_v<sd, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sd>));
    BOOST_CHECK((std::is_constructible_v<double, sd>));
    BOOST_CHECK((std::is_constructible_v<long double, sd>));


    // Can be explicitly converted to float, double and long double
    using sld = sf_test_cast<long double, policy::cast_to_primitive::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<sld, float>));
    BOOST_CHECK((not std::is_convertible_v<sld, double>));
    BOOST_CHECK((not std::is_convertible_v<sld, long double>));
    BOOST_CHECK((std::is_constructible_v<float, sld>));
    BOOST_CHECK((std::is_constructible_v<double, sld>));
    BOOST_CHECK((std::is_constructible_v<long double, sld>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_cast_from_int, FPT, test_types){
    //set initial values
    int a = 0;
    int b = 1;
    int c = -284554;
    int d = 684654;
    //create safe version of the values
    using sf = safe_float<FPT, policy::check_all, policy::on_fail_throw, policy::allow_cast_from<int>::policy>;
    sf sa = a;
    sf sb = b;
    sf sc = c;
    sf sd = d;
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_explicit_cast_from_int, FPT, test_types){
    //set initial values
    int a = 0;
    int b = 1;
    int c = -284554;
    int d = 684654;
    //create safe version of the values
    using sf = safe_float<FPT, policy::check_all, policy::on_fail_throw, policy::allow_explicit_cast_from<int>::policy>;
    sf sa(a);
    sf sb(b);
    sf sc(c);
    sf sd(d);
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_cast_to_int, FPT, test_types){
    //create safe version of the values
    using sf = safe_float<FPT, policy::check_all, policy::on_fail_throw, policy::allow_cast_to<int>::policy>;
    sf sa((FPT)0);
    sf sb((FPT)1);
    sf sc((FPT)-284554);
    sf sd((FPT)684654);

    // cast to int
    int a = sa;
    int b = sb;
    int c = sc;
    int d = sd;
    
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_explicit_cast_to_int, FPT, test_types){
    //create safe version of the values
    using sf = safe_float<FPT, policy::check_all, policy::on_fail_throw, policy::allow_cast_to<int>::policy>;
    sf sa((FPT)0);
    sf sb((FPT)1);
    sf sc((FPT)-284554);
    sf sd((FPT)684654);

    // cast to int
    int a(sa);
    int b(sb);
    int c(sc);
    int d(sd);
    
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a, sa.get_stored_value());
    BOOST_CHECK_EQUAL(b, sb.get_stored_value());
    BOOST_CHECK_EQUAL(c, sc.get_stored_value());
    BOOST_CHECK_EQUAL(d, sd.get_stored_value());
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_explicit_cast_from_safe, FPT, test_types){
    // base values
    using base_sf = safe_float<FPT, policy::check_bothflow>;
    base_sf a((FPT)0.0);
    base_sf b((FPT)1.0);
    
    //create safe version of the values
    using sf = safe_float<FPT, policy::check_underflow, policy::on_fail_throw, policy::cast_from_safe_policy::more_restrictive>;
    
    sf sa = a;
    sf sb = b;

    BOOST_CHECK((std::is_convertible_v<base_sf, sf>));
    BOOST_CHECK((std::is_constructible_v<sf, base_sf>));
    
    //check the values match when obtaining the stored value
    BOOST_CHECK_EQUAL(a.get_stored_value(), sa.get_stored_value());
    BOOST_CHECK_EQUAL(b.get_stored_value(), sb.get_stored_value());
}

template<typename FP, template<typename> typename CAST>
using sf_all = safe_float<FP, policy::check_all, policy::on_fail_throw, CAST>;

template<typename FP, template<typename> typename CAST>
using sf_of = safe_float<FP, policy::check_overflow, policy::on_fail_throw, CAST>;

template<typename FP, template<typename> typename CAST>
using sf_add1 = safe_float<FP, policy::compose_check<policy::check_addition_overflow, policy::check_addition_invalid_result>::policy, policy::on_fail_throw, CAST>;

template<typename FP, template<typename> typename CAST>
using sf_add2 = safe_float<FP, policy::compose_check<policy::check_addition_invalid_result, policy::check_addition_overflow>::policy, policy::on_fail_throw, CAST>;

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_more_restrictive, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::more_restrictive>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::more_restrictive>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::more_restrictive>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::more_restrictive>;
    
    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_more_restrictive_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::more_restrictive_explicit>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::more_restrictive_explicit>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::more_restrictive_explicit>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::more_restrictive_explicit>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_less_restrictive, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::less_restrictive>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::less_restrictive>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::less_restrictive>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::less_restrictive>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_less_restrictive_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::less_restrictive_explicit>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::less_restrictive_explicit>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::less_restrictive_explicit>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::less_restrictive_explicit>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_equivalent, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::equivalent>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::equivalent>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::equivalent>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::equivalent>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_equivalent_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::equivalent_explicit>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::equivalent_explicit>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::equivalent_explicit>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::equivalent_explicit>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_all, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::all>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::all>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::all>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::all>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_from_safe_all_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_none>;
    using source_of = sf_of<FPT, policy::cast_none>;
    using source_add1 = sf_add1<FPT, policy::cast_none>;
    using source_add2 = sf_add2<FPT, policy::cast_none>;

    using target_all = sf_all<FPT, policy::cast_from_safe_policy::all_explicit>;
    using target_of = sf_of<FPT, policy::cast_from_safe_policy::all_explicit>;
    using target_add1 = sf_add1<FPT, policy::cast_from_safe_policy::all_explicit>;
    using target_add2 = sf_add2<FPT, policy::cast_from_safe_policy::all_explicit>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE(safe_float_cast_from_safe) {
    using source_float_all = sf_all<float, policy::cast_none>;
    using source_double_of = sf_of<double, policy::cast_none>;
    using source_long_double_add1 = sf_add1<long double, policy::cast_none>;
    using source_float_add2 = sf_add2<float, policy::cast_none>;
    
    // Test of some combination of criteria on floating point types and policies
    using target_float_all = sf_all<float, policy::cast_from_safe<policy::cast_from_primitive::same, policy::cast_from_safe_policy::less_restrictive>::policy>;
    using target_double_of = sf_of<double, policy::cast_from_safe<policy::cast_from_primitive::less_precise, policy::cast_from_safe_policy::more_restrictive>::policy>;
    using target_double_add1 = sf_add1<double, policy::cast_from_safe<policy::cast_from_primitive::all, policy::cast_from_safe_policy::all>::policy>;
    using target_long_double_add2 = sf_add2<long double, policy::cast_from_safe<policy::cast_from_primitive::more_precise, policy::cast_from_safe_policy::equivalent>::policy>;

    BOOST_CHECK((std::is_convertible_v<source_float_all, target_float_all>));
    BOOST_CHECK((std::is_convertible_v<source_float_all, target_double_of>));
    BOOST_CHECK((std::is_convertible_v<source_float_all, target_double_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_float_all, target_long_double_add2>));
    BOOST_CHECK((std::is_constructible_v<target_float_all, source_float_all>));
    BOOST_CHECK((std::is_constructible_v<target_double_of, source_float_all>));
    BOOST_CHECK((std::is_constructible_v<target_double_add1, source_float_all>));
    BOOST_CHECK((not std::is_constructible_v<target_long_double_add2, source_float_all>));

    BOOST_CHECK((not std::is_convertible_v<source_double_of, target_float_all>));
    BOOST_CHECK((std::is_convertible_v<source_double_of, target_double_of>));
    BOOST_CHECK((std::is_convertible_v<source_double_of, target_double_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_double_of, target_long_double_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_float_all, source_double_of>));
    BOOST_CHECK((std::is_constructible_v<target_double_of, source_double_of>));
    BOOST_CHECK((std::is_constructible_v<target_double_add1, source_double_of>));
    BOOST_CHECK((not std::is_constructible_v<target_long_double_add2, source_double_of>));

    BOOST_CHECK((not std::is_convertible_v<source_long_double_add1, target_float_all>));
    BOOST_CHECK((not std::is_convertible_v<source_long_double_add1, target_double_of>));
    BOOST_CHECK((std::is_convertible_v<source_long_double_add1, target_double_add1>));
    BOOST_CHECK((std::is_convertible_v<source_long_double_add1, target_long_double_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_float_all, source_long_double_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_double_of, source_long_double_add1>));
    BOOST_CHECK((std::is_constructible_v<target_double_add1, source_long_double_add1>));
    BOOST_CHECK((std::is_constructible_v<target_long_double_add2, source_long_double_add1>));

    BOOST_CHECK((std::is_convertible_v<source_float_add2, target_float_all>));
    BOOST_CHECK((not std::is_convertible_v<source_float_add2, target_double_of>));
    BOOST_CHECK((std::is_convertible_v<source_float_add2, target_double_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_float_add2, target_long_double_add2>));
    BOOST_CHECK((std::is_constructible_v<target_float_all, source_float_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_double_of, source_float_add2>));
    BOOST_CHECK((std::is_constructible_v<target_double_add1, source_float_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_long_double_add2, source_float_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_more_restrictive, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::more_restrictive>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::more_restrictive>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::more_restrictive>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::more_restrictive>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_more_restrictive_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::more_restrictive_explicit>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::more_restrictive_explicit>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::more_restrictive_explicit>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::more_restrictive_explicit>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_less_restrictive, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::less_restrictive>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::less_restrictive>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::less_restrictive>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::less_restrictive>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_less_restrictive_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::less_restrictive_explicit>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::less_restrictive_explicit>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::less_restrictive_explicit>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::less_restrictive_explicit>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_equivalent, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::equivalent>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::equivalent>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::equivalent>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::equivalent>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_equivalent_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::equivalent_explicit>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::equivalent_explicit>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::equivalent_explicit>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::equivalent_explicit>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((not std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((not std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_all, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::all>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::all>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::all>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::all>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(safe_float_cast_to_safe_all_explicit, FPT, test_types) {
    using source_all = sf_all<FPT, policy::cast_to_safe_policy::all_explicit>;
    using source_of = sf_of<FPT, policy::cast_to_safe_policy::all_explicit>;
    using source_add1 = sf_add1<FPT, policy::cast_to_safe_policy::all_explicit>;
    using source_add2 = sf_add2<FPT, policy::cast_to_safe_policy::all_explicit>;

    using target_all = sf_all<FPT, policy::cast_none>;
    using target_of = sf_of<FPT, policy::cast_none>;
    using target_add1 = sf_add1<FPT, policy::cast_none>;
    using target_add2 = sf_add2<FPT, policy::cast_none>;

    BOOST_CHECK((not std::is_convertible_v<source_all, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_all, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_all>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_all>));

    BOOST_CHECK((not std::is_convertible_v<source_of, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_of, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_of>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_of>));

    BOOST_CHECK((not std::is_convertible_v<source_add1, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add1, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add1>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add1>));

    BOOST_CHECK((not std::is_convertible_v<source_add2, target_all>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_of>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add1>));
    BOOST_CHECK((not std::is_convertible_v<source_add2, target_add2>));
    BOOST_CHECK((std::is_constructible_v<target_all, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_of, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add1, source_add2>));
    BOOST_CHECK((std::is_constructible_v<target_add2, source_add2>));
}

BOOST_AUTO_TEST_SUITE_END()


