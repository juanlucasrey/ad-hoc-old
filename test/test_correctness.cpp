//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include "bdouble.h"

BOOST_AUTO_TEST_CASE( Multiplication )
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1*x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    der = y.der(x2);
    testvalue = 1.5;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Addition )
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1+x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    der = y.der(x2);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Addition_h )
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1+x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    der = y.der(x2);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    der = y.der(x1,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    der = y.der(x2,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der, testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Substraction )
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1-x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2);
    testvalue = -1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Substraction_h )
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1-x2;
    
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2);
    testvalue = -1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Sin_plus_one )
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    
    bdouble y = x1+sin(x1);
    
    der = y.der(x1);
    testvalue = 1.0 + cos(1.5);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,2);
    testvalue = -sin(1.5);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,3);
    testvalue = -cos(1.5);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Multiplication_right )
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= x * 3.2;
    
    testvalue = 3.2;
    der = y.der(x);
    BOOST_CHECK_SMALL(der - testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE( Multiplication_right_2 )
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=x * 5.5;
    
    testvalue = 5.5;
    der = y.der(x);
    BOOST_CHECK_SMALL(der - testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_constmul_left)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= 3.2 * x;
    
    testvalue = 3.2;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_constmul1_left_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= 5.5 * x;
    
    testvalue = 5.5;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_ldexp)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= ldexp(x,7);
    
    testvalue = 128;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_ldexp_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= ldexp(x,7);
    
    testvalue = 128;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    testvalue = 0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sin_constmul1_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sin (x * 5.5);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28x*5.5%29+%7C+x%3D0.5
    testvalue = -5.08366;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28x*5.5%29+%7C+x%3D0.5
    testvalue = -11.5452;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28x*5.5%29+%7C+x%3D0.5
    testvalue = 153.781;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+sin%28x*5.5%29+%7C+x%3D0.5
    testvalue = 349.244;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+sin%28x*5.5%29+%7C+x%3D0.5
    testvalue = -4651.87;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cos)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cos(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cos%28x%29+%7C+x%3D0.5
    testvalue = -0.479426;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cos_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cos(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cos%28x%29+%7C+x%3D0.5
    testvalue = -0.479426;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+cos%28x%29+%7C+x%3D0.5
    testvalue = -0.877583;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+cos%28x%29+%7C+x%3D0.5
    testvalue = 0.479426;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+cos%28x%29+%7C+x%3D0.5
    testvalue = 0.877583;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+cos%28x%29+%7C+x%3D0.5
    testvalue = -0.479426;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sin)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sin(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28x%29+%7C+x%3D0.5
    testvalue = 0.877583;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sin_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sin(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28x%29+%7C+x%3D0.5
    testvalue = 0.877583;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28x%29+%7C+x%3D0.5
    testvalue = -0.479426;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28x%29+%7C+x%3D0.5
    testvalue = -0.877583;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+sin%28x%29+%7C+x%3D0.5
    testvalue = 0.479426;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+sin%28x%29+%7C+x%3D0.5
    testvalue = 0.877583;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_exp)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=exp(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_exp_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=exp(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+exp%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_exp2)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=exp2(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.980258;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_exp2_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=exp2(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.980258;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.679463;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.470968;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.32645;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+%282%5Ex%29+%7C+x%3D0.5
    testvalue = 0.226278;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_expm1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=expm1(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_expm1_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=expm1(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+expm1%28x%29+%7C+x%3D0.5
    testvalue = 1.64872;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,5.5);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E5.5+%7C+x%3D0.5
    testvalue = 0.243068;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,5.5);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E5.5+%7C+x%3D0.5
    testvalue = 0.243068;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+x%5E5.5+%7C+x%3D0.5
    testvalue = 2.18761;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+x%5E5.5+%7C+x%3D0.5
    testvalue = 15.3133;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+x%5E5.5+%7C+x%3D0.5
    testvalue = 76.5664;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+x%5E5.5+%7C+x%3D0.5
    testvalue = 229.699;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_int)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E2+%7C+x%3D0.5
    testvalue = 1;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_int_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E2+%7C+x%3D0.5
    testvalue = 1;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+x%5E2+%7C+x%3D0.5
    testvalue = 2;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+x%5E2+%7C+x%3D0.5
    testvalue = 0;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+x%5E2+%7C+x%3D0.5
    testvalue = 0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+x%5E2+%7C+x%3D0.5
    testvalue = 0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_neg)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,-1);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = -4;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_neg_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(x,-1);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = -4;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = 16;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = -96;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = 768;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+x%5E%28-1%29+%7C+x%3D0.5
    testvalue = -7680;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_zero)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0;
    bdouble y=pow(x,2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E2+%7C+x%3D0
    testvalue = 0;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_left_zero_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0;
    bdouble y=pow(x,2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5E2+%7C+x%3D0
    testvalue = 0;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+x%5E2+%7C+x%3D0
    testvalue = 2;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+x%5E2+%7C+x%3D0
    testvalue = 0;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+x%5E2+%7C+x%3D0
    testvalue = 0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+x%5E2+%7C+x%3D0
    testvalue = 0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_right)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(5.5,x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+5.5%5Ex+%7C+x%3D0.5
    testvalue = 3.99799;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_right_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=pow(5.5,x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+5.5%5Ex+%7C+x%3D0.5
    testvalue = 3.99799;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+5.5%5Ex+%7C+x%3D0.5
    testvalue = 6.81556;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+5.5%5Ex+%7C+x%3D0.5
    testvalue = 11.6188;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+5.5%5Ex+%7C+x%3D0.5
    testvalue = 19.8072;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+5.5%5Ex+%7C+x%3D0.5
    testvalue = 33.7662;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_both)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 0.5;
    bdouble x2 = 5.5;
    bdouble y  = pow(x1,x2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 0.243068;
    der = y.der(x1);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdy+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = -0.0153165;
    der = y.der(x2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_pow_both_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x1 = 0.5;
    bdouble x2 = 5.5;
    bdouble y = pow(x1,x2);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 0.243068;
    der = y.der(x1);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdy+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = -0.0153165;
    der = y.der(x2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 2.18761;
    der = y.der(x1,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdydx+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = -0.124288;
    der = y.der(x1,x2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdy%5E2+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 0.0106166;
    der = y.der(x2,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 15.3133;
    der = y.der(x1,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = -0.632453;
    der = y.der(x1,2,x2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdy%5E2dx+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = 0.0555166;
    der = y.der(x1,x2,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdy%5E3+x%5Ey+%7C+x%3D0.5+%7C+y%3D5.5
    testvalue = -0.00735887;
    der = y.der(x2,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sqrt)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sqrt(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sqrt%28x%29+%7C+x%3D0.5
    testvalue = 0.707107;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sqrt_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sqrt(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sqrt%28x%29+%7C+x%3D0.5
    testvalue = 0.707107;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sqrt%28x%29+%7C+x%3D0.5
    testvalue = -0.707107;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sqrt%28x%29+%7C+x%3D0.5
    testvalue = 2.12132;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+sqrt%28x%29+%7C+x%3D0.5
    testvalue = -10.6066;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+sqrt%28x%29+%7C+x%3D0.5
    testvalue = 74.2462;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cbrt)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cbrt(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cbrt%28x%29+%7C+x%3D0.5
    testvalue = 0.529134;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cbrt_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cbrt(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cbrt%28x%29+%7C+x%3D0.5
    testvalue = 0.529134;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+cbrt%28x%29+%7C+x%3D0.5
    testvalue = -0.705512;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+cbrt%28x%29+%7C+x%3D0.5
    testvalue = 2.35171;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+cbrt%28x%29+%7C+x%3D0.5
    testvalue = -12.5424;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+cbrt%28x%29+%7C+x%3D0.5
    testvalue = 91.9778;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log%28x%29+%7C+x%3D0.5
    testvalue = 2.0;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log%28x%29+%7C+x%3D0.5
    testvalue = 2.0;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+log%28x%29+%7C+x%3D0.5
    testvalue = -4.0;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+log%28x%29+%7C+x%3D0.5
    testvalue = 16;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+log%28x%29+%7C+x%3D0.5
    testvalue = -96.0;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+log%28x%29+%7C+x%3D0.5
    testvalue = 768.0;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log1p)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log1p(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log1p%28x%29+%7C+x%3D0.5
    testvalue = 0.666667;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log1p_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log1p(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log1p%28x%29+%7C+x%3D0.5
    testvalue = 0.666667;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+log1p%28x%29+%7C+x%3D0.5
    testvalue = -0.444444;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+log1p%28x%29+%7C+x%3D0.5
    testvalue = 0.592593;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+log1p%28x%29+%7C+x%3D0.5
    testvalue = -1.18519;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+log1p%28x%29+%7C+x%3D0.5
    testvalue = 3.16049;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log10)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log10(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log10%28x%29+%7C+x%3D0.5
    testvalue = 0.868589;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log10_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log10(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log10%28x%29+%7C+x%3D0.5
    testvalue = 0.868589;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+log10%28x%29+%7C+x%3D0.5
    testvalue = -1.73718;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+log10%28x%29+%7C+x%3D0.5
    testvalue = 6.94871;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+log10%28x%29+%7C+x%3D0.5
    testvalue = -41.6923;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+log10%28x%29+%7C+x%3D0.5
    testvalue = 333.538;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log2)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log2(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log2%28x%29+%7C+x%3D0.5
    testvalue = 2.88539;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_log2_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=log2(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+log2%28x%29+%7C+x%3D0.5
    testvalue = 2.88539;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+log2%28x%29+%7C+x%3D0.5
    testvalue = -5.77078;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+log2%28x%29+%7C+x%3D0.5
    testvalue = 23.0831;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+log2%28x%29+%7C+x%3D0.5
    testvalue = -138.499;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+log2%28x%29+%7C+x%3D0.5
    testvalue = 1107.99;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cosh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cosh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cosh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cosh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=cosh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+cosh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+cosh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+cosh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+cosh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+cosh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sinh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sinh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sinh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sinh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sinh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sinh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sinh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sinh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+sinh%28x%29+%7C+x%3D0.5
    testvalue = 0.521095;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+sinh%28x%29+%7C+x%3D0.5
    testvalue = 1.12763;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_erf)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=erf(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+erf%28x%29+%7C+x%3D0.5
    testvalue = 0.878783;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_erf_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=erf(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+erf%28x%29+%7C+x%3D0.35
    testvalue = 0.998284;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+erf%28x%29+%7C+x%3D0.35
    testvalue = -0.698799;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+erf%28x%29+%7C+x%3D0.35
    testvalue = -1.50741;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+erf%28x%29+%7C+x%3D0.35
    testvalue = 3.85038;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+erf%28x%29+%7C+x%3D0.35
    testvalue = 6.34918;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_erfc)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=erfc(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+erfc%28x%29+%7C+x%3D0.5
    testvalue = -0.878783;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_erfc_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=erfc(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+erfc%28x%29+%7C+x%3D0.35
    testvalue = -0.998284;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+erfc%28x%29+%7C+x%3D0.35
    testvalue = 0.698799;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+erfc%28x%29+%7C+x%3D0.35
    testvalue = 1.50741;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+erfc%28x%29+%7C+x%3D0.35
    testvalue = -3.85038;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+erfc%28x%29+%7C+x%3D0.35
    testvalue = -6.34918;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_n)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=N(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.5
    testvalue = 0.352065;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_n_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=N(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.35
    testvalue = 0.37524;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.35
    testvalue = -0.131334;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.35
    testvalue = -0.329273;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.35
    testvalue = 0.377914;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+1%2F2+%28erf%28x%2Fsqrt%282%29%29%2B1%29+%7C+x%3D0.35
    testvalue = 0.85555;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tan)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=tan(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+tan%28x%29+%7C+x%3D0.5
    testvalue = 1.29845;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tan_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=tan(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+tan%28x%29+%7C+x%3D0.5
    testvalue = 1.29845;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+tan%28x%29+%7C+x%3D0.5
    testvalue = 1.41869;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+tan%28x%29+%7C+x%3D0.5
    testvalue = 4.92199;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+tan%28x%29+%7C+x%3D0.5
    testvalue = 16.4303;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+tan%28x%29+%7C+x%3D0.5
    testvalue = 81.1555;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tanh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=tanh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+tanh%28x%29+%7C+x%3D0.5
    testvalue = 0.786448;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tanh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=tanh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+tanh%28x%29+%7C+x%3D0.5
    testvalue = 0.786448;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+tanh%28x%29+%7C+x%3D0.5
    testvalue = -0.726862;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+tanh%28x%29+%7C+x%3D0.5
    testvalue = -0.565209;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+tanh%28x%29+%7C+x%3D0.5
    testvalue = 3.95222;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+tanh%28x%29+%7C+x%3D0.5
    testvalue = -3.26669;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_acos)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=acos(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+acos%28x%29+%7C+x%3D0.5
    testvalue = -1.1547;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_acos_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=acos(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+acos%28x%29+%7C+x%3D0.35
    testvalue = -1.06752;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+acos%28x%29+%7C+x%3D0.35
    testvalue = -0.425792;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+acos%28x%29+%7C+x%3D0.35
    testvalue = -1.72604;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+acos%28x%29+%7C+x%3D0.35
    testvalue = -5.38318;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+acos%28x%29+%7C+x%3D0.35
    testvalue = -32.733;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_asin)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=asin(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+asin%28x%29+%7C+x%3D0.5
    testvalue = 1.1547;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_asin_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=asin(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+asin%28x%29+%7C+x%3D0.35
    testvalue = 1.06752;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+asin%28x%29+%7C+x%3D0.35
    testvalue = 0.425792;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+asin%28x%29+%7C+x%3D0.35
    testvalue = 1.72604;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+asin%28x%29+%7C+x%3D0.35
    testvalue = 5.38318;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+asin%28x%29+%7C+x%3D0.35
    testvalue = 32.733;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_atan)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=atan(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+atan%28x%29+%7C+x%3D0.5
    testvalue = 0.8;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_atan_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=atan(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+atan%28x%29+%7C+x%3D0.35
    testvalue = 0.890869;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+atan%28x%29+%7C+x%3D0.35
    testvalue = -0.555553;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+atan%28x%29+%7C+x%3D0.35
    testvalue = -0.894399;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+atan%28x%29+%7C+x%3D0.35
    testvalue = 4.64281;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+atan%28x%29+%7C+x%3D0.35
    testvalue = -2.01967;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_acosh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 1.2;
    bdouble y=acosh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+acosh%28x%29+%7C+x%3D1.2
    testvalue = 1.50756;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_acosh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 1.35;
    bdouble y=acosh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+acosh%28x%29+%7C+x%3D1.35
    testvalue = 1.10264;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+acosh%28x%29+%7C+x%3D1.35
    testvalue = -1.8098;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+acosh%28x%29+%7C+x%3D1.35
    testvalue = 7.57087;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+acosh%28x%29+%7C+x%3D1.35
    testvalue = -53.3303;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+acosh%28x%29+%7C+x%3D1.35
    testvalue = 529.889;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_asinh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=asinh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+asinh%28x%29+%7C+x%3D0.5
    testvalue = 0.894427;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_asinh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=asinh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+asinh%28x%29+%7C+x%3D0.35
    testvalue = 0.943858;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+asinh%28x%29+%7C+x%3D0.35
    testvalue = -0.294299;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+asinh%28x%29+%7C+x%3D0.35
    testvalue = -0.565563;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+asinh%28x%29+%7C+x%3D0.35
    testvalue = 1.93045;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+asinh%28x%29+%7C+x%3D0.35
    testvalue = 0.321126;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_atanh)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=atanh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+atanh%28x%29+%7C+x%3D0.5
    testvalue = 1.3333333;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_atanh_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=atanh(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+atanh%28x%29+%7C+x%3D0.35
    testvalue = 1.1396;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+atanh%28x%29+%7C+x%3D0.35
    testvalue = 0.909084;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+atanh%28x%29+%7C+x%3D0.35
    testvalue = 4.04777;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+atanh%28x%29+%7C+x%3D0.35
    testvalue = 15.9029;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+atanh%28x%29+%7C+x%3D0.35
    testvalue = 106.099;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_lgamma)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=lgamma(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+lgamma%28x%29+%7C+x%3D0.5
    testvalue = -1.96351;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_lgamma_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=lgamma(x);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+lgamma%28x%29+%7C+x%3D0.35
    testvalue = -2.97107;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+lgamma%28x%29+%7C+x%3D0.35
    testvalue = 9.24046;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+lgamma%28x%29+%7C+x%3D0.35
    testvalue = -47.7338;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+lgamma%28x%29+%7C+x%3D0.35
    testvalue = 401.918;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+lgamma%28x%29+%7C+x%3D0.35
    testvalue = -4575.29;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.01);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tgamma)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=tgamma(x);
    
    y.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+gamma%28x%29+%7C+x%3D0.5
    testvalue = -3.48023;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_tgamma_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(5);
    double testvalue,der;
    
    bdouble x = 0.35;
    bdouble y=tgamma(x);
    
    y.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+gamma%28x%29+%7C+x%3D0.35
    testvalue = -7.56478;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+gamma%28x%29+%7C+x%3D0.35
    testvalue = 46.0031;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+gamma%28x%29+%7C+x%3D0.35
    testvalue = -398.02;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+gamma%28x%29+%7C+x%3D0.35
    testvalue = 4564.44;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.01);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+gamma%28x%29+%7C+x%3D0.35
    testvalue = -65259.3;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.01);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sinsin)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sin(sin(x));
    
    y.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = 0.778644;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sinsin_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(7);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y=sin(sin(x));
    
    y.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = 0.778644;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = -0.780622;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = -0.7961;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = 3.76751;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E5%2Fdx%5E5+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = 0.146924;
    der = y.der(x,5);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E6%2Fdx%5E6+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = -33.4154;
    der = y.der(x,6);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E7%2Fdx%5E7+sin%28sin%28x%29%29+%7C+x%3D0.5
    testvalue = 26.7665;
    der = y.der(x,7);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cossum)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= x + cos(x+0.5);
    
    y.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = 0.158529;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cossum_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(4);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= x + cos(x+0.5);
    
    y.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = 0.158529;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = -0.540302;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = 0.841471;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = 0.540302;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}


BOOST_AUTO_TEST_CASE(test_cosminus)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= x + cos(0.3-x);
    
    y.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x+%2B+cos(0.3-x))+%7C+x%3D0.5
    testvalue = 0.801331;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_cosminus_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(4);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y= x + cos(0.3-x);
    
    y.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x+%2B+cos(0.3-x))+%7C+x%3D0.5
    testvalue = 0.801331;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+(x+%2B+cos(x%2B0.5))+%7C+x%3D0.5
    testvalue = -0.980067;
    der = y.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+(x+%2B+cos(0.3-x))+%7C+x%3D0.5
    testvalue = 0.198669;
    der = y.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    //http://www.wolframalpha.com/input/?i=d%5E4%2Fdx%5E4+(x+%2B+cos(0.3-x))+%7C+x%3D0.5
    testvalue = 0.980067;
    der = y.der(x,4);
    BOOST_CHECK_SMALL(der-testvalue,0.000001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_mul_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1*x2;
    
    y.run_tape();
    der = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2);
    testvalue = 1.5;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,x2);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,3);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,2,x2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x1,x2,2);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = y.der(x2,3);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_random)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y = 0.8;
    
    bdouble res = sin(y*cos(x*exp(y)));
    
    res.run_tape();
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -2.52701;
    der = res.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = 8.33235;
    der = res.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -5.94029;
    der = res.der(x,2,y);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -10.6094;
    der = res.der(x,y,2);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdy%5E3+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -6.55845;
    der = res.der(y,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_random2)
{
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble y = 0.8;
    bdouble y2 = exp(y);
    
    bdouble x = 0.5;
    
    bdouble res = sin(log(y2)*cos(x*y2));
    
    res.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -1.49804;
    der = res.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdy+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -0.334221;
    der = res.der(y);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -2.52701;
    der = res.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdxdy+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -4.38949;
    der = res.der(x,y);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdy%5E2+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -3.07645;
    der = res.der(y,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28log%28exp%28y%29%29*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = 8.33235;
    der = res.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -5.94029;
    der = res.der(x,2,y);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -10.6094;
    der = res.der(x,y,2);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdy%5E3+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -6.55845;
    der = res.der(y,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testUnorderedIds)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    bdouble x3 = 0.5;
    
    bdouble y1 = sin(x1*x2);
    bdouble y2 = y1*x3;
    bdouble y3 = sin(x1*x3);
    bdouble y4 = y2+y3+x1+x2+x3;
    
    y4.run_tape();
    
    //http://www.wolframalpha.com/input/?i=x1+x3+cos(x+x1)%2B1+%7C+x1%3D1.5,x%3D1.0,x3%3D0.5
    testvalue = 1.05305;
    der = y4.der(x2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testUnorderedIds_h)
{
    bdouble::setOrder(4);
    //bdouble::setBackward();
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    bdouble x3 = 0.5;
    
    bdouble y1 = sin(x1*x2);
    bdouble y2 = y1*x3;
    bdouble y3 = sin(x1*x3);
    bdouble y4 = y2+y3+x1+x2+x3;
    
    y4.run_tape();
    double der = y4.der(x2,2,x1,x3);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testSumOrder2)
{
    bdouble::clear_tape();
    bdouble::setOrder(2);
    
    double testvalue;
    
    bdouble x1 = 1.5;
    bdouble x2 = 1.0;
    
    bdouble y = x1+x2;
    
    y.run_tape();
    double dydx1 = y.der(x1);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(dydx1,testvalue);
    
    double dydx2 = y.der(x2);
    testvalue = 1.0;
    BOOST_CHECK_EQUAL(dydx2,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testAdjointCodeGenerationRule1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    double testvalue;
    
    bdouble x0 = 0.5;
    bdouble x1 = 1.5;
    bdouble y0=sin(x0);
    bdouble y1=x0*x1;
    
    y0.run_tape();
    double dy0dx0 = y0.der(x0);
    testvalue = cos(0.5);
    BOOST_CHECK_EQUAL(dy0dx0,testvalue);
    
    double dy0dx1 = y0.der(x1);
    testvalue = 0.0;
    BOOST_CHECK_EQUAL(dy0dx1,testvalue);
    
    y1.run_tape();
    double dy1dx0 = y1.der(x0);
    testvalue = 1.5;
    BOOST_CHECK_EQUAL(dy1dx0,testvalue);
    
    double dy1dx1 = y1.der(x1);
    testvalue = 0.5;
    BOOST_CHECK_EQUAL(dy1dx1,testvalue);
    
    bdouble::clear_tape();
}

/*BOOST_AUTO_TEST_CASE(testAdjointCodeGenerationRule2
 {
 bdouble::clear_tape();
 bdouble::setOrder(3);
 
 double testvalue;
 
 bdouble x = 1.5;
 bdouble g = 0.5;
 
 //bdouble y = x+g;
 //bdouble y(x+g);
 
 //bdouble temp1 = (x*g) + (sin(g*g)*sin(x*g));
 
 bdouble temp1 = (x*g);
 bdouble temp2 = (sin(g*g)*sin(x*g));
 bdouble temp3 = temp1 + temp2;
 
 double dydx = temp3.der(x);
 
 bdouble::clear_tape();
 
 //bdouble temp2 =
 //bdouble temp2 = (x*g) + (sin(x*x)/sin(x*g));
 
 
 
 //double dydx = y.der(x);
 //testvalue = 1.0;
 //BOOST_CHECK_EQUAL(dydx,testvalue);
 
 //double dydg = y.der(g);
 //testvalue = 2.0;
 //BOOST_CHECK_EQUAL(dydg,testvalue);
 
 }*/

BOOST_AUTO_TEST_CASE(testAdjointCodeGenerationRule3)
{
    bdouble::clear_tape();
    bdouble::setOrder(2);
    double testvalue,der;
    
    bdouble x = 1.5;
    size_t x_id = x.id();
    x=sin(x*x);
    
    x.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%2Fdx+sin(x*x)+%7C+x%3D1.5
    testvalue = -1.88452;
    der = x.der(x_id);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_mul_itself)
{
    bdouble::clear_tape();
    bdouble::setOrder(2);
    double testvalue,der;
    
    bdouble x = 1.5;
    bdouble y= x*x;
    
    y.run_tape();
    
    testvalue = 3;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_sum_itself)
{
    bdouble::clear_tape();
    bdouble::setOrder(2);
    double testvalue,der;
    
    bdouble x = 1.5;
    bdouble y= x+x;
    
    y.run_tape();
    
    testvalue = 2;
    der = y.der(x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testSum1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1+x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x1);
    double testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testSum2)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1+x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x2);
    double testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testMinus1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1-x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x1);
    double testvalue = 1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testMinus2)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1-x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x2);
    double testvalue = -1.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testMult1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1*x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x1);
    double testvalue = 0.5;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testMult2)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1*x2 ;
    
    temp1.run_tape();
    
    double der = temp1.der(x2);
    double testvalue = 1.5;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_div)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1/x2;
    
    temp1.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x%2Fy)+%7C+x%3D1.5+%7C+y%3D0.5
    testvalue = 2.0;
    der = temp1.der(x1);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdy+(x%2Fy)+%7C+x%3D1.5+%7C+y%3D0.5
    testvalue = -6.0;
    der = temp1.der(x2);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_div_h)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1/x2 ;
    
    temp1.run_tape();
    //http://www.wolframalpha.com/input/?i=d%2Fdx+(x%2Fy)+%7C+x%3D1.5+%7C+y%3D0.5
    testvalue = 2.0;
    der = temp1.der(x1);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    //http://www.wolframalpha.com/input/?i=d%2Fdy+(x%2Fy)+%7C+x%3D1.5+%7C+y%3D0.5
    testvalue = -6.0;
    der = temp1.der(x2);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(testInitialization)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    
    double testvalue,der;
    
    bdouble x1 = 1.5;
    bdouble x2 = 0.5;
    
    bdouble temp1 = x1/x2;
    bdouble temp2 = sin(temp1);
    bdouble temp3 = exp(x2);
    bdouble temp4 = temp1 - temp3;
    bdouble temp5 = temp2 + temp4;
    bdouble temp6 = temp5 * temp4;
    
    bdouble y = temp6;
    
    testvalue = 2.016646669428201;
    BOOST_CHECK_EQUAL(y,testvalue);
    
    temp1.run_tape();
    der = temp1.der(x2);
    testvalue = -6.0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
}

template<typename T>
void f(const vector<T>& x, vector<T>& y)
{
    T v = tan(x[2] * x[3]);
    T w = x[1] - v;
    y[0] = x[0] * v / w;
    y[1] = y[0] * x[1];
}

void driver(const vector<double>& xv, const vector<double>& xt,
            vector<double>& yv, vector<double>& yt)
{
    const size_t n=xv.size(), m=yv.size();
    vector<bdouble> x(n), y(m);
    for (int i=0;i<n;i++)
        x[i]=xv[i];
    
    f(x,y);
    
    for (int i=0;i<m;i++)
    {
        yv[i]=y[i];
        
        y[i].run_tape();
        
        for (int j=0;j<n;j++)
            yt[i] += xt[j]*y[i].der(x[j]);
    }
}

void driver2(const vector<double>& xv, vector<double>& xa,
             vector<double>& yv, vector<double>& ya)
{
    //DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
    size_t n=xv.size(), m=yv.size();
    vector<bdouble> x(n), y(m);
    for (int i=0;i<n;i++)
    {
        x[i]=xv[i];
        //DCO_MODE::global_tape->register_variable(x[i]);
    }
    
    f(x,y);
    
    for (int i=0;i<m;i++)
    {
        //DCO_MODE::global_tape->register_output_variable(y[i]);
        //yv[i]=value(y[i]);
        yv[i]=y[i];
        //derivative(y[i])=ya[i];
    }
    
    for (int j=0;j<m;j++)
        y[j].run_tape();
    
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
            xa[i] += y[j].der(x[i]);
        //derivative(x[i])=xa[i];
    }
    
    //DCO_MODE::global_tape->interpret_adjoint();
    
    //for (int i=0;i<n;i++)
    //xa[i]=derivative(x[i]);
    
    //for (int i=0;i<m;i++)
    //ya[i]=derivative(y[i]);
    
    //DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

//https://www.nag.co.uk/downloads/impl/trial_version_dco_c++_userguide.pdf
//page 13
BOOST_AUTO_TEST_CASE(test_dco_1)
{
    bdouble::clear_tape();
    bdouble::setOrder(1);
    
    double testvalue;
    
    const int m=2, n=4; cout.precision(15);
    vector<double> xv(n), xt(n), yv(m), yt(m);
    for (int i=0;i<n;i++)
    {
        xv[i]=1;
        xt[i]=1;
    }
    
    driver(xv,xt,yv,yt);
    
    testvalue = -2.79401891249195;
    BOOST_CHECK_SMALL(yv[0]-testvalue,0.000000000000001);
    
    testvalue = -2.79401891249195;
    BOOST_CHECK_SMALL(yv[1]-testvalue,0.000000000000001);
    
    testvalue = 14.2435494001203;
    BOOST_CHECK_SMALL(yt[0]-testvalue,0.0000000000001);
    
    testvalue = 11.4495304876283;
    BOOST_CHECK_SMALL(yt[1]-testvalue,0.0000000000001);
}

BOOST_AUTO_TEST_CASE(test_dco_1b)
{
    bdouble::setOrder(1);
    bdouble::clear_tape();
    
    double testvalue,result;
    
    const size_t m=2, n=4; cout.precision(15);
    
    vector<bdouble> x(n), y(m);
    for (size_t i=0;i<n;i++)
        x[i]=1;
        
        f(x,y);
        
        vector<double> xt(n), yt(m);
        for (int i=0;i<n;i++)
            xt[i]=1;
            
            for (int i=0;i<m;i++)
            {
                y[i].run_tape();
                
                for (int j=0;j<n;j++)
                    yt[i] += xt[j]*y[i].der(x[j]);
                    }
    
    testvalue = -2.79401891249195;
    result = y[0];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = -2.79401891249195;
    result = y[1];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = 14.2435494001203;
    BOOST_CHECK_SMALL(yt[0]-testvalue,0.0000000000001);
    
    testvalue = 11.4495304876283;
    BOOST_CHECK_SMALL(yt[1]-testvalue,0.0000000000001);
}

//https://www.nag.co.uk/downloads/impl/trial_version_dco_c++_userguide.pdf
//page 16
BOOST_AUTO_TEST_CASE(test_dco_2)
{
    bdouble::setOrder(1);
    bdouble::clear_tape();
    
    double testvalue;
    
    const int m=2, n=4; cout.precision(15);
    vector<double> xv(n), xa(n), yv(m), ya(m);
    for (int i=0;i<n;i++)
    {
        xv[i]=1;
        xa[i]=1;
    }
    
    driver2(xv,xa,yv,ya);
    
    testvalue = -2.79401891249195;
    BOOST_CHECK_SMALL(yv[0]-testvalue,0.000000000000001);
    
    testvalue = -2.79401891249195;
    BOOST_CHECK_SMALL(yv[1]-testvalue,0.000000000000001);
    
    testvalue = -4.5880378249839;
    BOOST_CHECK_SMALL(xa[0]-testvalue,0.0000000000001);
    
    testvalue = -11.8190644542335;
    BOOST_CHECK_SMALL(xa[1]-testvalue,0.0000000000001);
    
    testvalue = 23.050091083483;
    BOOST_CHECK_SMALL(xa[2]-testvalue,0.0000000000001);
    
    testvalue = 23.050091083483;
    BOOST_CHECK_SMALL(xa[3]-testvalue,0.0000000000001);
}

//https://www.nag.co.uk/downloads/impl/trial_version_dco_c++_userguide.pdf
//page 16
BOOST_AUTO_TEST_CASE(test_dco_2b)
{
    bdouble::setOrder(1);
    bdouble::clear_tape();
    
    double testvalue, result;
    
    const int m=2, n=4; cout.precision(15);
    
    vector<bdouble> x(n), y(m);
    for (size_t i=0;i<n;i++)
        x[i]=1;
        
        f(x,y);
        
        vector<double> xa(n), ya(m);
        for (int i=0;i<n;i++)
            xa[i]=1;
            
            for (int i=0;i<m;i++)
                ya[i]=1;
                
                for (int j=0;j<m;j++)
                    y[j].run_tape();
                    
                    for (int i=0;i<n;i++)
                    {
                        for (int j=0;j<m;j++)
                            xa[i] += ya[j]*y[j].der(x[i]);
                            }
    
    testvalue = -2.79401891249195;
    result = y[0];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = -2.79401891249195;
    result = y[1];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = -4.5880378249839;
    BOOST_CHECK_SMALL(xa[0]-testvalue,0.0000000000001);
    
    testvalue = -11.8190644542335;
    BOOST_CHECK_SMALL(xa[1]-testvalue,0.0000000000001);
    
    testvalue = 23.050091083483;
    BOOST_CHECK_SMALL(xa[2]-testvalue,0.0000000000001);
    
    testvalue = 23.050091083483;
    BOOST_CHECK_SMALL(xa[3]-testvalue,0.0000000000001);
}

BOOST_AUTO_TEST_CASE(test_dco_3b)
{
    bdouble::setOrder(2);
    bdouble::clear_tape();
    
    double testvalue,result;
    
    const size_t m=2, n=4; cout.precision(15);
    
    vector<bdouble> x(n), y(m);
    for (size_t i=0;i<n;i++)
        x[i]=1;
        
        f(x,y);
        
        vector<double> xt(n), yt(m);
        for (int i=0;i<n;i++)
            xt[i]=1;
            
            //1st order
            for (int i=0;i<m;i++)
            {
                y[i].run_tape();
                
                for (int j=0;j<n;j++)
                    yt[i] += xt[j]*y[i].der(x[j]);
                    }
    
    testvalue = -2.79401891249195;
    result = y[0];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = -2.79401891249195;
    result = y[1];
    BOOST_CHECK_SMALL(result-testvalue,0.000000000000001);
    
    testvalue = 14.2435494001203;
    BOOST_CHECK_SMALL(yt[0]-testvalue,0.0000000000001);
    
    testvalue = 11.4495304876283;
    BOOST_CHECK_SMALL(yt[1]-testvalue,0.0000000000001);
}

BOOST_AUTO_TEST_CASE(testDerCall)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y = 0.8;
    
    bdouble res = sin(y*cos(x*exp(y)));
    
    res.run_tape();
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -2.52701;
    der = res.der(x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    der = res.der(x,x);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E3+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = 8.33235;
    der = res.der(x,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    der = res.der(x,x,2);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -5.94029;
    der = res.der(x,2,y);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdx%5E2dy+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -10.6094;
    der = res.der(x,y,2);
    BOOST_CHECK_SMALL(der-testvalue,0.0001);
    
    //http://www.wolframalpha.com/input/?i=d%5E3%2Fdy%5E3+sin%28y*cos%28x*exp%28y%29%29%29+%7C+x%3D0.5+%7C+y%3D0.8
    testvalue = -6.55845;
    der = res.der(y,3);
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    bdouble::clear_tape();
}

BOOST_AUTO_TEST_CASE(test_fma)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y = 0.8;
    bdouble z = 0.7;
    
    bdouble result = fma(x,y,z);
    
    der = result;
    testvalue = fma(0.5,0.8,0.7);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = result.der(x,y);
    testvalue = 1;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = result.der(x,y,z);
    testvalue = 0;
    BOOST_CHECK_EQUAL(der,testvalue);
}

BOOST_AUTO_TEST_CASE(test_hypot)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y = 0.8;
    
    bdouble result = hypot(x,y);
    
    der = result;
    testvalue = hypot(0.5,0.8);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdxdy+hypot(x,y)+%7C+x%3D0.5+%7C+y%3D0.8
    der = result.der(x,y);
    testvalue = -0.476404;
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+hypot(x,y)+%7C+x%3D0.5+%7C+y%3D0.8
    der = result.der(x,2);
    testvalue = 0.762246;
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
}

BOOST_AUTO_TEST_CASE(test_atan2)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    bdouble y = 0.8;
    
    bdouble result = atan2(x,y);
    
    der = result;
    testvalue = atan2(0.5,0.8);
    BOOST_CHECK_EQUAL(der,testvalue);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdxdy+atan2(x,y)+%7C+x%3D0.5+%7C+y%3D0.8
    der = result.der(x,y);
    testvalue = -0.492362;
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
    
    //http://www.wolframalpha.com/input/?i=d%5E2%2Fdx%5E2+atan2(x,y)+%7C+x%3D0.5+%7C+y%3D0.8
    der = result.der(x,2);
    testvalue = -1.009976;
    BOOST_CHECK_SMALL(der-testvalue,0.00001);
}

BOOST_AUTO_TEST_CASE(test_plusequal)
{
    bdouble::clear_tape();
    bdouble::setOrder(3);
    double testvalue,der;
    
    bdouble x = 0.5;
    size_t x_id = x.id();
    bdouble y = 0.8;
    
    x += y;
    
    der = x.der(x_id);
    testvalue = 1;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = x.der(y);
    testvalue = 1;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = x.der(x_id,y);
    testvalue = 0;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    bdouble::clear_tape();
    bdouble::setOrder(3);
    
    bdouble z = 0.5;
    size_t z_id = z.id();
    
    x += 0.8;
    
    der = z.der(z_id);
    testvalue = 1;
    BOOST_CHECK_EQUAL(der,testvalue);
    
    der = x.der(z_id,2);
    testvalue = 0;
    BOOST_CHECK_EQUAL(der,testvalue);
}