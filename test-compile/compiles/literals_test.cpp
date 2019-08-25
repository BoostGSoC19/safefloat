#include <boost/safe_float/literals.hpp>
#include <iostream>


int main() {
    using namespace boost::safe_float::literals;
    3.125e-2_sf;
    1.913321263417004522523336509411129302549170461134053766727447509765625E-21_sd;
}