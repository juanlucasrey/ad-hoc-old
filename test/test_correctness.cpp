//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bdouble.h"

TEST_CASE( "Multiplication is computed", "[multiplication]" )
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1*x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    REQUIRE( der == testvalue );
    
    der = y.der(x2);
    testvalue = 1.5;
    REQUIRE( der == testvalue );
    
    bdouble::clear_tape();
}
