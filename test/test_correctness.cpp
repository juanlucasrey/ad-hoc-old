#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../Catch/single_include/catch.hpp"

#include "../include/bdouble.h"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

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
    //XCTAssertEqual(der,testvalue);
    
    der = y.der(x2);
    testvalue = 1.5;
    REQUIRE( der == testvalue );
    //XCTAssertEqual(der,testvalue);
    
    bdouble::clear_tape();
}
