//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "bdouble.h"
#include <cmath>
#include <algorithm>
#include <stack>
#include <boost/math/special_functions/polygamma.hpp>
#include "partitionGenerator.h"

size_t bdouble::mDefaultOrder = 1;

//tape
vector<size_t> bdouble::op_trace(0,0);
vector<size_t> bdouble::index_trace(0,0);
vector<double> bdouble::val_trace(0.0,0);
size_t bdouble::indexcount = 0;

bdouble::bdouble(const double& rhs)
{
    mThisId = indexcount;
    indexcount += 1;
    
    mValue = rhs;
}

bdouble::bdouble(const bdouble& rhs)
{
    mValue = rhs.mValue;
    mThisId = rhs.mThisId;
}

bdouble& bdouble::operator= (const bdouble& rhs)
{
    mValue = rhs.mValue;
    mThisId = rhs.mThisId;
    
    return *this;
}

bdouble& bdouble::operator=(bdouble&& rhs)
{
    *this = rhs;
    return rhs;
}

bdouble bdouble::operator+(const bdouble& rhs) const
{
    const bdouble& lhs = (*this);
    
    //optimization: if the id is the same
    //then this is effectively a function
    //of one parameter
    if(lhs.id() == rhs.id())
        return rhs*2;
    else
    {
        bdouble res(lhs.mValue + rhs.mValue);
        
        bdouble::op_trace.push_back(bplusv);
        bdouble::index_trace.push_back(rhs.mThisId);
        bdouble::index_trace.push_back(lhs.mThisId);
        bdouble::index_trace.push_back(res.mThisId);
        
        return res;
    }
}

bdouble bdouble::operator-(const bdouble& rhs) const
{
    const bdouble& lhs = (*this);
    
    //optimization: if the id is the same
    //then this is effectively a function
    //of one parameter
    if(lhs.id() == rhs.id())
        return rhs*0;
    else
    {
        bdouble res(lhs.mValue - rhs.mValue);
        
        bdouble::op_trace.push_back(bminusv);
        bdouble::index_trace.push_back(rhs.mThisId);
        bdouble::index_trace.push_back(lhs.mThisId);
        bdouble::index_trace.push_back(res.mThisId);
        
        return res;
    }
}

bdouble bdouble::operator*(const bdouble& rhs) const
{
    const bdouble& lhs = (*this);
    
    //optimization: if the id is the same
    //then this is effectively a function
    //of one parameter
    if(lhs.id() == rhs.id())
        return pow(rhs,2);
    else
    {
        bdouble res(lhs.mValue * rhs.mValue);
        
        bdouble::op_trace.push_back(bmultv);
        bdouble::index_trace.push_back(rhs.mThisId);
        bdouble::index_trace.push_back(lhs.mThisId);
        bdouble::index_trace.push_back(res.mThisId);
        bdouble::val_trace.push_back(rhs.mValue);
        bdouble::val_trace.push_back(lhs.mValue);

        return res;
    }
}

bdouble bdouble::operator/(const bdouble& rhs) const
{
    return (*this)*inv(rhs);
}

#define function_define_store_value(name)               \
bdouble name (const bdouble& in)                        \
{                                                       \
    bdouble::val_trace.push_back(in.mValue);            \
    bdouble::val_trace.push_back( name (in.mValue));    \
                                                        \
    bdouble res(bdouble::val_trace.back());             \
                                                        \
    bdouble::op_trace.push_back(name##v);               \
    bdouble::index_trace.push_back(in.mThisId);         \
    bdouble::index_trace.push_back(res.mThisId);        \
                                                        \
    return res;                                         \
}

function_define_store_value(cos);
function_define_store_value(sin);
function_define_store_value(expm1);
function_define_store_value(log);
function_define_store_value(log1p);
function_define_store_value(log10);
function_define_store_value(log2);
function_define_store_value(cosh);
function_define_store_value(sinh);
function_define_store_value(erf);
function_define_store_value(erfc);
function_define_store_value(acos);
function_define_store_value(asin);
function_define_store_value(atan);
function_define_store_value(acosh);
function_define_store_value(asinh);
function_define_store_value(atanh);
function_define_store_value(lgamma);
function_define_store_value(tgamma);

#undef function_define_store_value

#define function_define_no_store_value(name)            \
bdouble name (const bdouble& in)                        \
{                                                       \
    bdouble::val_trace.push_back( name (in.mValue));    \
                                                        \
    bdouble res(bdouble::val_trace.back());             \
                                                        \
    bdouble::op_trace.push_back(name##v);               \
    bdouble::index_trace.push_back(in.mThisId);         \
    bdouble::index_trace.push_back(res.mThisId);        \
                                                        \
    return res;                                         \
}

function_define_no_store_value(exp);
function_define_no_store_value(exp2);
function_define_no_store_value(tan);
function_define_no_store_value(tanh);

#undef function_define_no_store_value

bdouble inv(const bdouble& in)
{
    bdouble::val_trace.push_back(1.0/in.mValue);
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(invv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
}

bdouble pow(const bdouble& in, const int& deg)
{
    bdouble::val_trace.push_back(in.mValue);
    bdouble::val_trace.push_back(deg);
    bdouble::val_trace.push_back(pow(in.mValue,deg));
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(powintv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
    
}

bdouble pow(const bdouble& in, const double& deg)
{
    bdouble::val_trace.push_back(in.mValue);
    bdouble::val_trace.push_back(deg);
    bdouble::val_trace.push_back(pow(in.mValue,deg));
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(powv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
}

bdouble pow(const double& val, const bdouble& in)
{
    return exp(log(val)*in);
}

bdouble pow(const bdouble& lhs, const bdouble& rhs)
{
    return exp(log(lhs)*rhs);
}

bdouble sqrt(const bdouble& in)
{
    bdouble::val_trace.push_back(in.mValue);
    bdouble::val_trace.push_back(0.5);
    bdouble::val_trace.push_back(sqrt(in.mValue));
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(powv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
}

bdouble cbrt(const bdouble& in)
{
    bdouble::val_trace.push_back(in.mValue);
    bdouble::val_trace.push_back(0.3333333333333333333333333333333333333333333333333333333333333333333333);
    bdouble::val_trace.push_back(cbrt(in.mValue));
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(powv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
}

bdouble N(const bdouble& in)
{
    bdouble::val_trace.push_back(in.mValue);
    bdouble::val_trace.push_back(0.5*(1.0+std::erf(in.mValue*M_SQRT1_2)));
    
    bdouble res(bdouble::val_trace.back());
    
    bdouble::op_trace.push_back(nv);
    bdouble::index_trace.push_back(in.mThisId);
    bdouble::index_trace.push_back(res.mThisId);
    
    return res;
}

bdouble ldexp(const bdouble& in, const int& exp)
{
    return in*ldexp(1.0,exp);
}

void TE_multconst(const double& value,const double& coeff,vector<double>& output,size_t loc = 0)
{
    while(loc < 2)
    {
        if(loc == 0)
            output[loc] = value*coeff;
        else if(loc == 1)
            output[loc] = coeff;
        
        loc++;
    }
}

void TE_sumconst(const double& value,const double& coeff,vector<double>& output,size_t loc = 0)
{
    while(loc < 2)
    {
        if(loc == 0)
            output[loc] = value + coeff;
        else if(loc == 1)
            output[loc] = 1.0;
        
        loc++;
    }
}

void TE_minusconst(const double& value,const double& coeff,vector<double>& output,size_t loc = 0)
{
    while(loc < 2)
    {
        if(loc == 0)
            output[loc] = coeff - value;
        else if(loc == 1)
            output[loc] = -1.0;
        
        loc++;
    }
}

void TE_cos(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::cos(value);
        else if(loc == 1)
            output[loc] = -std::sin(value);
        else if (loc <4)
            output[loc] = -output[loc-2];
        else
            output[loc] = output[loc-4];
        
        loc++;
    }
}

void TE_sin(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::sin(value);
        else if(loc == 1)
            output[loc] = std::cos(value);
        else if (loc <4)
            output[loc] = -output[loc-2];
        else
            output[loc] = output[loc-4];
        
        loc++;
    }
}

void TE_exp(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::exp(value);
        else
            output[loc] = output[0];
        
        loc++;
    }
}

void TE_exp2(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        double ratio = std::log(2.0);
        if(loc == 0)
            output[loc] = std::exp2(value);
        else
            output[loc] = ratio*output[loc-1];
        
        loc++;
    }
}

void TE_expm1(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::expm1(value);
        else if(loc == 1)
            output[loc] = std::exp(value);
        else
            output[loc] = output[1];
        
        loc++;
    }
}

void TE_pow(const double& value,const double& deg,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::pow(value,deg);
        loc++;
    }
    
    double newDeg = deg - (double)loc;
    double coeff = 1.0 + newDeg;
    while(loc != output.size())
    {
        if(coeff)
            output[loc] = coeff*std::pow(value,newDeg);
        
        coeff *= newDeg;
        newDeg -= 1.0;
        loc++;
    }
}

void TE_powint(const double& value,const double& deg,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::pow(value,deg);
        loc++;
    }
    
    int newDeg = (int)deg - (int)loc;
    double coeff = 1.0 + newDeg;
    while(loc != output.size())
    {
        if(coeff)
            output[loc] = coeff*std::pow(value,newDeg);
        
        coeff *= newDeg;
        newDeg -= 1;
        loc++;
    }
    
    /*int degint = (int)deg - (int)loc + 1;
    double value_inv = 1/value;
    
    while(loc != output.size())
    {
        if(loc == 0)
        {
            output[loc] = std::pow(value,degint);
            degint--;
        }
        else
        {
            if(degint)
            {
                if(output[loc-1])
                    output[loc] = degint*output[loc-1]*value_inv;
                
                degint--;
            }
            else
                output[loc] = 0;
        }
        
        loc++;
    }*/
}

void TE_inv(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = 1/value;
        else
            output[loc] = -((int)loc)*output[loc-1]*output[0];
        
        loc++;
    }
}

void TE_log(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::log(value);
        else if(loc == 1)
            output[loc] = 1/value;
        else
            output[loc] = -((double)loc-1)*output[loc-1]*output[1];
        
        loc++;
    }
}

void TE_log1p(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::log1p(value);
        else if(loc == 1)
            output[loc] = 1/(value+1.0);
        else
            output[loc] = -((double)loc-1)*output[loc-1]*output[1];
        
        loc++;
    }
}

void TE_log10(const double& value,vector<double>& output,size_t loc = 0)
{
    const double value_inv = 1/value;
    const double ratio = 1/M_LN10;
    
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::log10(value);
        else
        {
            if(loc == 1)
                output[loc] = ratio*value_inv;
            else
                output[loc] = -((double)loc-1)*output[loc-1]*value_inv;
        }
        
        loc++;
    }
}

void TE_log2(const double& value,vector<double>& output,size_t loc = 0)
{
    const double value_inv = 1/value;
    const double ratio = 1/M_LN2;
    
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::log10(value);
        else
        {
            if(loc == 1)
                output[loc] = ratio*value_inv;
            else
                output[loc] = -((double)loc-1)*output[loc-1]*value_inv;
        }
        
        loc++;
    }
}

void TE_cosh(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::cosh(value);
        else if(loc == 1)
            output[loc] = std::sinh(value);
        else
            output[loc] = output[loc-2];
        
        loc++;
    }
}

void TE_sinh(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::sinh(value);
        else if(loc == 1)
            output[loc] = std::cosh(value);
        else
            output[loc] = output[loc-2];
        
        loc++;
    }
}

//we use f''(X) + 2Xf'(X) = 0
void TE_erf(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::erf(value);
        else if(loc == 1)
            output[loc] = exp(-value*value)*M_2_SQRTPI;
        else if(loc == 2)
            output[loc] = -2*value*output[loc-1];
        else
            output[loc] = -2*value*output[loc-1] - 2*((int)loc-2)*output[loc-2];
        
        loc++;
    }
}

//we use f''(X) + 2Xf'(X) = 0
void TE_erfc(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = std::erfc(value);
        else if(loc == 1)
            output[loc] = -exp(-value*value)*M_2_SQRTPI;
        else if(loc == 2)
            output[loc] = -2*value*output[loc-1];
        else
            output[loc] = -2*value*output[loc-1] - 2*((int)loc-2)*output[loc-2];
        
        loc++;
    }
}

//we use f''(X) + Xf'(X) = 0
void TE_N(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = 0.5*(1.0+std::erf(value*M_SQRT1_2));
        else if(loc == 1)
            output[loc] = 0.5*M_2_SQRTPI*M_SQRT1_2*exp(-value*value*0.5);
        else if(loc == 2)
            output[loc] = -value*output[loc-1];
        else
            output[loc] = -value*output[loc-1] - ((int)loc-2)*output[loc-2];
        
        loc++;
    }
}

//we use (X^2-1)f''(X) + Xf'(X) = 0
void TE_acos(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::acos(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value - 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = -sqrt(-one_over_denom);
            else if(loc==2)
                output[loc] = -value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-3*value*output[loc-1] -output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-(2*n_pl_one-1)*value*output[loc-1]-n*n*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use (X^2-1)f''(X) + Xf'(X) = 0
void TE_asin(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::asin(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value - 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = sqrt(-one_over_denom);
            else if(loc==2)
                output[loc] = -value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-3*value*output[loc-1] -output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-(2*n_pl_one-1)*value*output[loc-1]-n*n*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use (X^2-1)f''(X) + Xf'(X) = 0
void TE_acosh(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::acosh(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value - 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = sqrt(one_over_denom);
            else if(loc==2)
                output[loc] = -value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-3*value*output[loc-1] -output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-(2*n_pl_one-1)*value*output[loc-1]-n*n*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use (X^2+1)f''(X) + 2Xf'(X) = 0
void TE_atan(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::atan(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value + 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = one_over_denom;
            else if(loc==2)
                output[loc] = -2*value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-4*value*output[loc-1] - 2*output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-2*value*n_pl_one*output[loc-1]-n*n_pl_one*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use (X^2+1)f''(X) + Xf'(X) = 0
void TE_asinh(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::asinh(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value + 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = sqrt(one_over_denom);
            else if(loc==2)
                output[loc] = -value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-3*value*output[loc-1] - output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-(2*n_pl_one-1)*value*output[loc-1]-n*n*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use (X^2-1)f''(X) + 2Xf'(X) = 0
void TE_atanh(const double& value,vector<double>& output,size_t loc = 0)
{
    if(output.size() && loc == 0)
    {
        output[0] = std::atanh(value);
        loc++;
    }
    
    if(loc != output.size())
    {
        double denom = value*value - 1;
        double one_over_denom = 1/denom;
        
        while(loc != output.size())
        {
            if(loc == 1)
                output[loc] = -one_over_denom;
            else if(loc==2)
                output[loc] = -2*value*output[loc-1]*one_over_denom;
            else if(loc==3)
                output[loc] = (-4*value*output[loc-1] - 2*output[loc-2])*one_over_denom;
            else
            {
                int n = (int)loc-2;
                int n_pl_one = (int)loc-1;
                output[loc] = (-2*value*n_pl_one*output[loc-1]-n*n_pl_one*output[loc-2])*one_over_denom;
            }
            
            loc++;
        }
    }
}

//we use f' = 1 + f^2
void TE_tan(const double& value,vector<double>& output,size_t loc = 0)
{
    if(loc == 0)
    {
        output[loc] = tan(value);
        loc++;
    }
    
    double fval = output[0];
    double fval_sq = fval*fval;
    
    vector<int> fval_coeffs(output.size()+1,0);
    fval_coeffs[1] = 1;
    
    //highest coefficient (1 at the moment) is an odd power
    bool odd = true;
    while(loc != output.size())
    {
        for(size_t i = odd; i<= (loc+1); i+=2)
        {
            int current_coeff = fval_coeffs[i];
            fval_coeffs[i] = 0;
            if(i)
            {
                double temp = current_coeff*(int)i;
                fval_coeffs[i-1] += temp;
                fval_coeffs[i+1] += temp;
            }
        }
        odd = !odd;
        
        double fval_der = 0;
        for(size_t i = (loc+1); i > odd; i-=2)
        {
            fval_der += fval_coeffs[i];
            fval_der *= fval_sq;
        }
        
        fval_der += fval_coeffs[odd];
        
        if(odd)
            fval_der *= fval;
        
        output[loc] = fval_der;
        loc++;
    }
}

//we use f' = 1 - f^2
void TE_tanh(const double& value,vector<double>& output,size_t loc = 0)
{
    if(loc == 0)
    {
        output[loc] = tanh(value);
        loc++;
    }
    
    double fval = output[0];
    double fval_sq = fval*fval;
    
    vector<int> fval_coeffs(output.size()+1,0);
    fval_coeffs[1] = 1;
    
    //highest coefficient (1 at the moment) is an odd power
    bool odd = true;
    while(loc != output.size())
    {
        for(size_t i = odd; i<= (loc+1); i+=2)
        {
            int current_coeff = fval_coeffs[i];
            fval_coeffs[i] = 0;
            if(i)
            {
                double temp = current_coeff*(int)i;
                fval_coeffs[i-1] += temp;
                fval_coeffs[i+1] -= temp;
            }
        }
        odd = !odd;
        
        double fval_der = 0;
        for(size_t i = (loc+1); i > odd; i-=2)
        {
            fval_der += fval_coeffs[i];
            fval_der *= fval_sq;
        }
        
        fval_der += fval_coeffs[odd];
        
        if(odd)
            fval_der *= fval;
        
        output[loc] = fval_der;
        loc++;
    }
}

void TE_lgamma(const double& value,vector<double>& output,size_t loc = 0)
{
    while(loc != output.size())
    {
        if(loc == 0)
            output[loc] = lgamma(value);
        else
            output[loc] = boost::math::polygamma(((int)loc-1),value);
        
        loc++;
    }
}

void TE_tgamma(const double& value,vector<double>& output,size_t loc = 0)
{
    if(loc == 0)
    {
        output[loc] = tgamma(value);
        loc++;
    }
    
    TE_lgamma(value,output,loc);
    
    for(size_t i = (output.size()-1); i >= loc; i--)
    {
        double der = 0;
        vector<size_t> part;
        partitionGenerator pg(i);
        while(pg.next(part))
        {
            double temp = pg.multiplicity(part);
            for(size_t j = 0; j < part.size(); j++)
                temp *= output[part[j]];
            
            der += temp;
        }
        
        output[i] = der*output[0];
    }
}

const double& bdouble::get(const vector<size_t>& idxes) const
{
    return mCoeff[multisetcount(idxes, mOrder)];
}

double& bdouble::get(const vector<size_t>& idxes)
{
    return mCoeff[multisetcount(idxes, mOrder)];
}

double bdouble::der(const vector<size_t>& id,const vector<size_t>& order)
{
    if(mCoeff.empty())
        run_tape();
    
    //they should be the same size
    if(order.size() != id.size())
        throw;
    
    vector<size_t> idxes(mId.size()+1,0);
    idxes[0] = mOrder;
    
    for(size_t i = 0; i < order.size(); i++)
        if (!addDer(idxes,id[i],order[i])) return 0;
    
    return get(idxes);
}

bool bdouble::addDer(vector<size_t>& idxes,const size_t& var_id,const size_t& order) const
{
    vector<size_t>::const_iterator it;
    it = find(mId.begin(), mId.end(), var_id);
    if (it != mId.end())
    {
        if(order > idxes[0])
            throw;
        
        idxes[distance(mId.begin(),it)+1] += order;
        idxes[0] -= order;
        
        return true;
    }
    else
        return false;
}

double bdouble::der_aux(size_t& var_id, vector<size_t>& idxes) const
{
    //this means that the previous argument had an implied order of 1
    if(var_id != -1)
        if (!addDer(idxes,var_id,1)) return 0;
    
    return get(idxes);
}

void bdouble::run_tape(const size_t orderOverride)
{
    if(orderOverride == -1)
        mOrder = mDefaultOrder;
    else
        mOrder = orderOverride;
    
    if(mOrder == 0)
        throw;
    
    //initially I overestimate the number of free slots
    //I will need for my calculation at the number
    //of variables used.
    deque<size_t> free_slots(indexcount);
    for(size_t i=0;i<indexcount;i++)
        free_slots[i] = i;
    
    vector<bool> op_relevant(op_trace.size(),false);
    vector<bool>::reverse_iterator op_relevant_rev_it = op_relevant.rbegin();
    vector<size_t>::const_reverse_iterator op_trace_rev_it = op_trace.rbegin();
    vector<size_t>::const_reverse_iterator index_trace_rev_it = index_trace.rbegin();
    
    vector<size_t> id_slot_map(indexcount,-1);
    vector<size_t> slot_id_map(indexcount,-1);
    
    size_t max_nvar = 1;
    size_t current_nvar = 0;
    
    vector<bool> var_concerned(indexcount,false);
    var_concerned[mThisId] = true;
    
    id_slot_map[mThisId] = free_slots.front();
    slot_id_map[free_slots.front()] = mThisId;
    free_slots.pop_front();
    current_nvar++;
    
    size_t res,arg1,arg2;
    
    for (; op_trace_rev_it!= op_trace.rend(); ++op_trace_rev_it,++op_relevant_rev_it)
    {
        res = *index_trace_rev_it++;
        if(var_concerned[res])
        {
            *op_relevant_rev_it = true;
            
            size_t res_pos = id_slot_map[res];
            free_slots.push_front(res_pos);
            slot_id_map[res_pos] = -1;
            id_slot_map[res] = -1;
            current_nvar--;
            
            arg1 = *index_trace_rev_it++;
            var_concerned[arg1] = true;
            if(id_slot_map[arg1] == -1)
            {
                id_slot_map[arg1] = free_slots.front();
                slot_id_map[free_slots.front()] = arg1;
                free_slots.pop_front();
                current_nvar++;
            }
            
            //if it's a function of 2 variables,
            //we have to take into account the second variable
            if(*op_trace_rev_it == bmultv ||
               *op_trace_rev_it == bplusv ||
               *op_trace_rev_it == bminusv)
            {
                arg1 = *index_trace_rev_it++;
                var_concerned[arg1] = true;
                if(id_slot_map[arg1] == -1)
                {
                    id_slot_map[arg1] = free_slots.front();
                    slot_id_map[free_slots.front()] = arg1;
                    free_slots.pop_front();
                    current_nvar++;
                }
            }
            
            max_nvar = max(current_nvar,max_nvar);
        }
        else
        {
            index_trace_rev_it++;
            
            //if it's a function of 2 variables,
            //we have to take into account the second variable
            if(*op_trace_rev_it == bmultv ||
               *op_trace_rev_it == bplusv ||
               *op_trace_rev_it == bminusv)
                index_trace_rev_it++;
        }
    }
    
    //we are now going to fill the free slots so that
    //at the end of the run all the initial ids will
    //fall ordered in the first mCoeff slots
    free_slots.clear();
    free_slots.resize(max_nvar);
    
    slot_id_map.erase (slot_id_map.begin()+max_nvar,slot_id_map.end());
    
    //here we fill the slots that correspond to initial variables
    //starting from 0
    size_t slot = 0;
    for(vector<size_t>::const_iterator id_slot_map_it = id_slot_map.begin(); id_slot_map_it != id_slot_map.end(); id_slot_map_it++)
    {
        if(*id_slot_map_it != -1)
        {
            free_slots[*id_slot_map_it] = slot;
            slot++;
        }
    }
    
    //here we fill the rest of the slots so that we have
    //max_nvar slots from 0 to (max_nvar-1)
    for(vector<size_t>::iterator slot_id_map_it = slot_id_map.begin(); slot_id_map_it != slot_id_map.end(); slot_id_map_it++)
    {
        if(*slot_id_map_it == -1)
        {
            free_slots[distance(slot_id_map.begin(),slot_id_map_it)] = slot;
            slot++;
        }
    }
    
    slot_id_map.clear();
    std::fill (id_slot_map.begin(),id_slot_map.end(),-1);
    
    mCoeff.resize(multisetcoeff(max_nvar+1,mOrder));
    mCoeff[0] = mValue;
    
    vector<size_t> idxes;
    idxes.clear();
    idxes.resize(free_slots.size()+1,0);
    idxes[0] = mOrder;
    
    mId.clear();
    mId.resize(free_slots.size(),-1);
    
    id_slot_map[mThisId] = free_slots.front();
    mId[free_slots.front()] = mThisId;
    free_slots.pop_front();
    idxes[0]--;
    idxes[id_slot_map[mThisId]+1]++;
    get(idxes) = 1.0;
    idxes[0]++;
    idxes[id_slot_map[mThisId]+1]--;
    
    op_relevant_rev_it = op_relevant.rbegin();
    op_trace_rev_it = op_trace.rbegin();
    index_trace_rev_it = index_trace.rbegin();
    vector<double>::const_reverse_iterator val_trace_rev_it = val_trace.rbegin();
    
    vector<size_t> idxes_sparse;
    
    for (; op_trace_rev_it!= op_trace.rend(); ++op_trace_rev_it,++op_relevant_rev_it)
        switch(*op_trace_rev_it)
    {
        case multconstv:
        case sumconstv:
        case minusconstv:
        case cosv:
        case sinv:
        case expv:
        case exp2v:
        case expm1v:
        case powv:
        case powintv:
        case invv:
        case logv:
        case log1pv:
        case log10v:
        case log2v:
        case coshv:
        case sinhv:
        case erfv:
        case erfcv:
        case nv:
        case tanv:
        case tanhv:
        case acosv:
        case asinv:
        case atanv:
        case acoshv:
        case asinhv:
        case atanhv:
        case lgammav:
        case tgammav:
            
            if(*op_relevant_rev_it)
            {
                res = *index_trace_rev_it++;
                size_t res_pos = id_slot_map[res];
                
                free_slots.push_front(res_pos);
                mId[res_pos] = -1;
                id_slot_map[res] = -1;
                
                arg1 = *index_trace_rev_it++;
                
                //second case works always, first case is faster
                if (mOrder == 1)
                {
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    size_t arg_pos = id_slot_map[arg1];
                    
                    double temp = mCoeff[res_pos+1];
                    mCoeff[res_pos+1] = 0;
                    
                    double result = *val_trace_rev_it++;
                    
                    switch(*op_trace_rev_it)
                    {
                        case multconstv:
                        {
                            double coeff = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp*coeff;
                            break;
                        }
                        case sumconstv:
                        {
                            mCoeff[arg_pos+1] += temp;
                            break;
                        }
                        case minusconstv:
                        {
                            mCoeff[arg_pos+1] -= temp;
                            break;
                        }
                        case cosv:
                            mCoeff[arg_pos+1] -= temp*sin((*val_trace_rev_it++));
                            break;
                        case sinv:
                            mCoeff[arg_pos+1] += temp*cos((*val_trace_rev_it++));
                            break;
                        case expv:
                            mCoeff[arg_pos+1] += temp*result;
                            break;
                        case exp2v:
                            mCoeff[arg_pos+1] += temp*std::log(2.0)*result;
                            break;
                        case expm1v:
                            mCoeff[arg_pos+1] += temp*exp((*val_trace_rev_it++));
                            break;
                        case powv:
                        case powintv:
                        {
                            double deg = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp*deg*pow((*val_trace_rev_it++),deg-1);
                            break;
                        }
                        case invv:
                            mCoeff[arg_pos+1] -= temp*result*result;
                            break;
                        case logv:
                            mCoeff[arg_pos+1] += temp/(*val_trace_rev_it++);
                            break;
                        case log1pv:
                            mCoeff[arg_pos+1] += temp/((*val_trace_rev_it++)+1);
                            break;
                        case log10v:
                            mCoeff[arg_pos+1] += temp/(M_LN10*(*val_trace_rev_it++));
                            break;
                        case log2v:
                            mCoeff[arg_pos+1] += temp/(M_LN2*(*val_trace_rev_it++));
                            break;
                        case coshv:
                            mCoeff[arg_pos+1] += temp*sinh((*val_trace_rev_it++));
                            break;
                        case sinhv:
                            mCoeff[arg_pos+1] += temp*cosh((*val_trace_rev_it++));
                            break;
                        case erfv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp*M_2_SQRTPI*exp(-value*value);
                            break;
                        }
                        case erfcv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] -= temp*M_2_SQRTPI*exp(-value*value);
                            break;
                        }
                        case nv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp*0.5*M_2_SQRTPI*M_SQRT1_2*exp(-value*value*0.5);
                            break;
                        }
                        case tanv:
                            mCoeff[arg_pos+1] += temp*(1 + result*result);
                            break;
                        case tanhv:
                            mCoeff[arg_pos+1] += temp*(1 - result*result);
                            break;
                        case acosv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] -= temp/sqrt(1-value*value);
                            break;
                        }
                        case asinv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp/sqrt(1-value*value);
                            break;
                        }
                        case atanv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp/(1+value*value);
                            break;
                        }
                        case acoshv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp/sqrt(value*value-1);
                            break;
                        }
                        case asinhv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp/sqrt(1+value*value);
                            break;
                        }
                        case atanhv:
                        {
                            double value = *val_trace_rev_it++;
                            mCoeff[arg_pos+1] += temp/(1-value*value);
                            break;
                        }
                        case lgammav:
                            mCoeff[arg_pos+1] += temp*boost::math::polygamma(0,*val_trace_rev_it++);
                            break;
                        case tgammav:
                            mCoeff[arg_pos+1] += temp*result*boost::math::polygamma(0,*val_trace_rev_it++);
                            break;
                    }
                }
                else
                {
                    bool arg1_alive = (id_slot_map[arg1] != -1);
                    
                    vector<size_t> sparse_to_dense;
                    sparse_to_dense.reserve(mId.size()-free_slots.size());
                    for(size_t i = 0; i < mId.size(); i++)
                        if((mId[i] != -1) && (!arg1_alive || i != id_slot_map[arg1]))
                            sparse_to_dense.push_back(i);
                    
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    size_t arg_pos = id_slot_map[arg1];
                    
                    vector<double> taylorexp(mOrder+1);
                    taylorexp[0] = *val_trace_rev_it++;
                    
                    switch(*op_trace_rev_it)
                    {
                        case multconstv:
                        {
                            double coeff = *val_trace_rev_it++;
                            TE_multconst(0,coeff,taylorexp,1);
                            break;
                        }
                        case sumconstv:
                        {
                            TE_sumconst(0,0,taylorexp,1);
                            break;
                        }
                        case minusconstv:
                        {
                            TE_minusconst(0,0,taylorexp,1);
                            break;
                        }
                        case cosv:
                            TE_cos(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case sinv:
                            TE_sin(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case expv:
                            TE_exp(0,taylorexp,1);
                            break;
                        case exp2v:
                            TE_exp2(0,taylorexp,1);
                            break;
                        case expm1v:
                            TE_expm1(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case powv:
                        {
                            double deg = *val_trace_rev_it++;
                            TE_pow(*val_trace_rev_it++,deg,taylorexp,1);
                            break;
                        }
                        case powintv:
                        {
                            double deg = *val_trace_rev_it++;
                            TE_powint(*val_trace_rev_it++,deg,taylorexp,1);
                            break;
                        }
                        case invv:
                            TE_inv(0,taylorexp,1);
                            break;
                        case logv:
                            TE_log(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case log1pv:
                            TE_log1p(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case log10v:
                            TE_log10(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case log2v:
                            TE_log2(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case coshv:
                            TE_cosh(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case sinhv:
                            TE_sinh(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case erfv:
                            TE_erf(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case erfcv:
                            TE_erfc(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case nv:
                            TE_N(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case tanv:
                            TE_tan(0,taylorexp,1);
                            break;
                        case tanhv:
                            TE_tanh(0,taylorexp,1);
                            break;
                        case acosv:
                            TE_acos(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case asinv:
                            TE_asin(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case atanv:
                            TE_atan(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case acoshv:
                            TE_acosh(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case asinhv:
                            TE_asinh(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case atanhv:
                            TE_atanh(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case lgammav:
                            TE_lgamma(*val_trace_rev_it++,taylorexp,1);
                            break;
                        case tgammav:
                            TE_tgamma(*val_trace_rev_it++,taylorexp,1);
                            break;
                    }
                    
                    vector<vector<double> > der_mult_cache(mOrder);
                    for(size_t i = 1; i <= der_mult_cache.size(); i++)
                    {
                        der_mult_cache[i-1].resize(i,0);
                        
                        vector<size_t> part;
                        partitionGenerator pg(i);
                        while(pg.next(part))
                        {
                            double temp = pg.multiplicity(part);
                            for(size_t j = 0; j < part.size(); j++)
                                temp *= taylorexp[part[j]];
                            
                            der_mult_cache[i-1][part.size()-1] += temp;
                        }
                    }
                    
                    idxes_sparse.clear();
                    idxes_sparse.resize(sparse_to_dense.size()+1,0);
                    
                    idxes.clear();
                    idxes.resize(mId.size()+1,0);
                    
                    //we need to keep at least one derivative for res
                    //hence the -1
                    multisetGenerator mg(idxes_sparse.size(),mOrder - 1);
                    
                    while(mg.next(idxes_sparse))
                    {
                        for(size_t i = 0; i < sparse_to_dense.size(); i++)
                            idxes[sparse_to_dense[i]+1] = idxes_sparse[i+1];
                        
                        size_t order = 1+idxes_sparse[0];
                        
                        if(!arg1_alive)
                        {
                            //we cache the derivs values first as we
                            //want to avoid calling them multiple times
                            vector<double> derivstemp(order);
                            for(size_t i = 0; i<order; i++)
                            {
                                idxes[0] = order - (i+1);
                                idxes[res_pos+1] = (i+1);
                                derivstemp[i] = get(idxes);
                            }
                            
                            //reset it again
                            order = 1+idxes_sparse[0];
                            idxes[0] = 0;
                            
                            //we need to go from higher to lower order here
                            //as the high order derivatives can be overriden
                            //before the lower order derivatives
                            while(order > 0)
                            {
                                double temp = 0;
                                for (size_t i = 0; i<order; i++)
                                    temp += derivstemp[i] * der_mult_cache[order-1][i];
                                
                                //because we know that arg1 wasn't included
                                //res_pos is the same as arg_pos
                                idxes[res_pos+1] = order;
                                get(idxes)= temp;
                                idxes[res_pos+1] = 0;
                                
                                idxes[0]++;
                                order--;
                            }
                        }
                        else
                        {
                            //we cache the derivs values first as we
                            //want to avoid calling them multiple times.
                            //in this case we cache all partial derivs
                            //in res and arg
                            vector<vector<double> > derivstemp(order);
                            for(size_t i = 1; i <= derivstemp.size(); i++)
                            {
                                derivstemp[i-1].resize(i,0);
                                idxes[arg_pos+1] = order - i;
                                
                                for (size_t j = 1; j<=i; j++)
                                {
                                    idxes[res_pos+1] = j;
                                    idxes[0] = i - j;
                                    derivstemp[i-1][j-1] = get(idxes);
                                }
                            }
                            
                            //reset it again
                            order = 1+idxes_sparse[0];
                            idxes[0] = 0;
                            size_t offset = 0;
                            
                            //we need to go from higher to lower order here
                            //as the high order derivatives can be overriden
                            //before the lower order derivatives
                            while(order > 0)
                            {
                                double temp = 0;
                                
                                for (size_t i = 0; i<order; i++)
                                {
                                    double temp2 = 0;
                                    for (size_t j = 0; j<der_mult_cache[i].size(); j++)
                                        temp2 += derivstemp[i+offset][j] * der_mult_cache[i][j];
                                    
                                    size_t multiplicity = combins(i+1,order,true);
                                    temp += temp2 * multiplicity;
                                }
                                
                                //we reset partial derivs that are now 0
                                for (size_t i = 0; i<order; i++)
                                {
                                    idxes[res_pos+1] = order - i;
                                    idxes[arg_pos+1] = i;
                                    get(idxes) = 0;
                                }
                                
                                //then we add up the new derivative
                                idxes[res_pos+1] = 0;
                                idxes[arg_pos+1] = order;
                                get(idxes) += temp;
                                idxes[arg_pos+1] = 0;
                                
                                idxes[0]++;
                                order--;
                                offset++;
                            }
                        }
                    }
                }
            }
            else
            {
                index_trace_rev_it += 2;
                switch(*op_trace_rev_it)
                {
                    case sumconstv:
                    case minusconstv:
                    case expv:
                    case exp2v:
                    case invv:
                    case tanv:
                    case tanhv:
                        val_trace_rev_it += 1;
                        break;
                    case powv:
                    case powintv:
                        val_trace_rev_it += 3;
                        break;
                    default:
                        val_trace_rev_it += 2;
                }
            }
            
            break;
        case bplusv:
        case bminusv:
            
            if(*op_relevant_rev_it)
            {
                res = *index_trace_rev_it++;
                size_t res_pos = id_slot_map[res];
                
                free_slots.push_front(res_pos);
                mId[res_pos] = -1;
                id_slot_map[res] = -1;
                
                arg1 = *index_trace_rev_it++;
                arg2 = *index_trace_rev_it++;
                
                //second case works always, first case is faster
                if (mOrder == 1)
                {
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    
                    if(id_slot_map[arg2] == -1)
                    {
                        id_slot_map[arg2] = free_slots.front();
                        mId[free_slots.front()] = arg2;
                        free_slots.pop_front();
                    }
                    
                    double temp = mCoeff[res_pos+1];
                    mCoeff[res_pos+1] = 0;
                    mCoeff[id_slot_map[arg1]+1] += temp;
                    if(*op_trace_rev_it == bplusv)
                        mCoeff[id_slot_map[arg2]+1] += temp;
                    else if(*op_trace_rev_it == bminusv)
                        mCoeff[id_slot_map[arg2]+1] -= temp;
                }
                else
                {
                    bool arg1_alive = (id_slot_map[arg1] != -1);
                    bool arg2_alive = (id_slot_map[arg2] != -1);
                    
                    vector<size_t> sparse_to_dense;
                    sparse_to_dense.reserve(mId.size()-free_slots.size());
                    for(size_t i = 0; i < mId.size(); i++)
                        if(mId[i] != -1 && i!=id_slot_map[arg1] && i!=id_slot_map[arg2])
                            sparse_to_dense.push_back(i);
                    
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    
                    if(id_slot_map[arg2] == -1)
                    {
                        id_slot_map[arg2] = free_slots.front();
                        mId[free_slots.front()] = arg2;
                        free_slots.pop_front();
                    }
                    
                    size_t arg1_pos = id_slot_map[arg1];
                    size_t arg2_pos = id_slot_map[arg2];
                    
                    idxes_sparse.clear();
                    idxes_sparse.resize(sparse_to_dense.size()+1,0);
                    
                    idxes.clear();
                    idxes.resize(mId.size()+1,0);
                    
                    //we need to keep at least one derivative for res
                    //hence the -1
                    multisetGenerator mg(idxes_sparse.size(),mOrder - 1);
                    
                    while(mg.next(idxes_sparse))
                    {
                        for(size_t i = 0; i < sparse_to_dense.size(); i++)
                            idxes[sparse_to_dense[i]+1] = idxes_sparse[i+1];
                        
                        size_t order = 1+idxes_sparse[0];
                        idxes[0] = 0;
                        
                        //we need to go from higher to lower order here
                        //as the high order derivatives can be overriden
                        //before the lower order derivatives
                        while(order > 0)
                        {
                            idxes[res_pos+1] = order;
                            vector<vector<double> > derivsarg1and2;
                            derivsarg1and2.resize(order);
                            for(size_t i = 0; i < order; i++)
                            {
                                bool icondition = (i==0) || arg1_alive;
                                if(icondition)
                                {
                                    idxes[arg1_pos+1] = i;
                                    derivsarg1and2[i].resize(order-i,0);
                                    for(size_t j = 0; j < (order-i); j++)
                                    {
                                        bool jcondition = (j==0) || arg2_alive;
                                        if(jcondition)
                                        {
                                            idxes[arg2_pos+1] = j;
                                            idxes[res_pos+1] = order - i - j;
                                            std::swap(derivsarg1and2[i][j],get(idxes));
                                        }
                                    }
                                }
                            }
                            
                            vector<size_t> idxarg1arg2;
                            multisetGenerator mg2(2,order);
                            
                            idxes[res_pos+1]= 0;
                            while(mg2.next(idxarg1arg2))
                            {
                                double temp = 0;
                                
                                for(size_t i = 0; i <= idxarg1arg2[0]; i++)
                                {
                                    bool icondition = (i==0) || arg1_alive;
                                    if(icondition)
                                    {
                                        double temp2 = combins(i,idxarg1arg2[0],true);
                                        for(size_t j = 0; j <= idxarg1arg2[1]; j++)
                                        {
                                            bool notlast = (i != idxarg1arg2[0]) || (j != idxarg1arg2[1]);
                                            bool jcondition = (j==0) || arg2_alive;
                                            if(notlast && jcondition)
                                            {
                                                if(*op_trace_rev_it == bplusv)
                                                    temp += temp2 * combins(j,idxarg1arg2[1],true) * derivsarg1and2[i][j];
                                                else if(*op_trace_rev_it == bminusv)
                                                {
                                                    if ( idxarg1arg2[1] % 2== 0 )
                                                        temp += temp2 * combins(j,idxarg1arg2[1],true) * derivsarg1and2[i][j];
                                                    else
                                                        temp -= temp2 * combins(j,idxarg1arg2[1],true) * derivsarg1and2[i][j];
                                                }
                                            }
                                        }
                                    }
                                }
                                
                                idxes[arg1_pos+1] = 0;
                                idxes[arg2_pos+1] = 0;
                                idxes[arg1_pos+1] += idxarg1arg2[0];
                                idxes[arg2_pos+1] += idxarg1arg2[1];
                                get(idxes) += temp;
                            }
                            
                            idxes[arg1_pos+1] = 0;
                            idxes[arg2_pos+1] = 0;
                            idxes[0]++;
                            order--;
                        }
                    }
                }
            }
            else
                index_trace_rev_it += 3;
            
            break;
            
        case bmultv:
            
            if(*op_relevant_rev_it)
            {
                res = *index_trace_rev_it++;
                size_t res_pos = id_slot_map[res];
                
                //slot_id_map.push_front(res_pos);
                free_slots.push_front(res_pos);
                mId[res_pos] = -1;
                id_slot_map[res] = -1;
                
                arg1 = *index_trace_rev_it++;
                arg2 = *index_trace_rev_it++;
                
                //second case works always, first case is faster
                if (mOrder == 1)
                {
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    
                    if(id_slot_map[arg2] == -1)
                    {
                        id_slot_map[arg2] = free_slots.front();
                        mId[free_slots.front()] = arg2;
                        free_slots.pop_front();
                    }
                    
                    double temp = mCoeff[res_pos+1];
                    mCoeff[res_pos+1] = 0;
                    mCoeff[id_slot_map[arg2]+1] += temp * (*val_trace_rev_it++);
                    mCoeff[id_slot_map[arg1]+1] += temp * (*val_trace_rev_it++);
                }
                else
                {
                    bool arg1_alive = (id_slot_map[arg1] != -1);
                    bool arg2_alive = (id_slot_map[arg2] != -1);
                    
                    vector<size_t> sparse_to_dense;
                    sparse_to_dense.reserve(mId.size()-free_slots.size());
                    for(size_t i = 0; i < mId.size(); i++)
                        if(mId[i] != -1 && i!=id_slot_map[arg1] && i!=id_slot_map[arg2])
                            sparse_to_dense.push_back(i);
                    
                    if(id_slot_map[arg1] == -1)
                    {
                        id_slot_map[arg1] = free_slots.front();
                        mId[free_slots.front()] = arg1;
                        free_slots.pop_front();
                    }
                    
                    if(id_slot_map[arg2] == -1)
                    {
                        id_slot_map[arg2] = free_slots.front();
                        mId[free_slots.front()] = arg2;
                        free_slots.pop_front();
                    }
                    
                    size_t arg1_pos = id_slot_map[arg1];
                    size_t arg2_pos = id_slot_map[arg2];
                    
                    double x1 = (*val_trace_rev_it++);
                    double x2 = (*val_trace_rev_it++);
                    vector<vector<double> > d_g_x1_x2;
                    
                    //create the triangle
                    d_g_x1_x2.resize(mOrder+1);
                    for(size_t i = 0; i <= mOrder; i++)
                        d_g_x1_x2[i].resize(mOrder+1-i);
                    
                    //fill the borders
                    d_g_x1_x2[0][0] = 1;
                    for(size_t i = 1; i <= mOrder; i++)
                    {
                        d_g_x1_x2[0][i] = d_g_x1_x2[0][i-1] * x1;
                        d_g_x1_x2[i][0] = d_g_x1_x2[i-1][0] * x2;
                    }
                    
                    //fill the inside
                    for(size_t i = 1; i <= mOrder; i++)
                        for(size_t j = 1; j <= mOrder-i; j++)
                            d_g_x1_x2[i][j] = d_g_x1_x2[0][j] * d_g_x1_x2[i][0];
                    
                    idxes_sparse.clear();
                    idxes_sparse.resize(sparse_to_dense.size()+1,0);
                    
                    idxes.clear();
                    idxes.resize(mId.size()+1,0);
                    
                    //we need to keep at least one derivative for res
                    //hence the -1
                    multisetGenerator mg(idxes_sparse.size(),mOrder - 1);
                    
                    while(mg.next(idxes_sparse))
                    {
                        for(size_t i = 0; i < sparse_to_dense.size(); i++)
                            idxes[sparse_to_dense[i]+1] = idxes_sparse[i+1];
                        
                        size_t order = 1+idxes_sparse[0];
                        idxes[0] = 0;
                        
                        vector<vector<vector<double> > > d_f_x1_x2_y;
                        d_f_x1_x2_y.resize(order);
                        for(size_t i = 0; i < order; i++)
                        {
                            bool icondition = (i==0) || arg1_alive;
                            if(icondition)
                            {
                                idxes[arg1_pos+1] = i;
                                d_f_x1_x2_y[i].resize(order-i);
                                for(size_t j = 0; j < (order-i); j++)
                                {
                                    bool jcondition = (j==0) || arg2_alive;
                                    if(jcondition)
                                    {
                                        idxes[arg2_pos+1] = j;
                                        d_f_x1_x2_y[i][j].resize(order-i-j);
                                        for(size_t k = 0; k < (order-i-j); k++)
                                        {
                                            idxes[res_pos+1] = k+1;
                                            idxes[0] = order - i - j - (k+1);
                                            
                                            std::swap(d_f_x1_x2_y[i][j][k],get(idxes));
                                        }
                                    }
                                }
                            }
                        }
                        
                        //we need to go from higher to lower order here
                        //as the high order derivatives can be overriden
                        //before the lower order derivatives
                        idxes[res_pos+1]= 0;
                        while(order > 0)
                        {
                            vector<size_t> idxarg1arg2;
                            multisetGenerator mg2(2,order);
                            
                            while(mg2.next(idxarg1arg2))
                            {
                                double temp = 0;
                                
                                size_t cross_ders = min(idxarg1arg2[0],idxarg1arg2[1]);
                                
                                for(size_t k = 0; k <= cross_ders; k++)
                                {
                                    double temp3 = combins(k,idxarg1arg2[0],true) * combins(k,idxarg1arg2[1],true);
                                    for(size_t i = 0; i <= (idxarg1arg2[0]-k); i++)
                                    {
                                        bool icondition = (i==0) || arg1_alive;
                                        if(icondition)
                                        {
                                            double temp2 = combins(i,idxarg1arg2[0]-k,true) * temp3;
                                            for(size_t j = 0; j <= (idxarg1arg2[1]-k); j++)
                                            {
                                                bool notlast = (k!=0) || (i != idxarg1arg2[0]) || (j != idxarg1arg2[1]);
                                                bool jcondition = (j==0) || arg2_alive;
                                                if(notlast && jcondition)
                                                    temp += temp2 * combins(j,idxarg1arg2[1]-k,true) * d_f_x1_x2_y[i][j][order-i-j-1-k] * d_g_x1_x2[idxarg1arg2[0]-i-k][idxarg1arg2[1]-j-k];
                                            }
                                        }
                                    }
                                }
                                
                                idxes[arg1_pos+1] = 0;
                                idxes[arg2_pos+1] = 0;
                                idxes[arg1_pos+1] += idxarg1arg2[0];
                                idxes[arg2_pos+1] += idxarg1arg2[1];
                                get(idxes) += temp;
                            }
                            
                            idxes[arg1_pos+1] = 0;
                            idxes[arg2_pos+1] = 0;
                            idxes[0]++;
                            order--;
                        }
                    }
                }
            }
            else
            {
                index_trace_rev_it += 3;
                val_trace_rev_it += 2;
            }
            
            break;
    }
    
    vector<size_t>::const_iterator cutoff = mId.begin();
    
    while(cutoff != mId.end() && *cutoff != -1)
        cutoff++;
    
    //we need to clean up data from mId and mCoeff
    if(cutoff != mId.end())
    {
        if(mOrder != 1)
        {
            idxes.clear();
            idxes.resize(mId.size()+1,0);
            multisetGenerator mg(idxes.size(),mOrder);
            
            vector<double>::iterator coarse = mCoeff.begin();
            vector<double>::iterator fine   = mCoeff.begin();
            
            vector<size_t>::const_iterator id_it;
            vector<size_t>::const_iterator id_it_begin = idxes.begin() + 1 + (cutoff - mId.begin());
            while(mg.next(idxes))
            {
                id_it = id_it_begin;
                
                while(id_it != idxes.end() && *id_it == 0)
                    id_it++;
                
                if(id_it == idxes.end())
                {
                    if(coarse != fine)
                        swap(*coarse,*fine);
                    
                    coarse++;
                }
                
                fine++;
            }
        }
        
        mId.erase(cutoff,mId.end());
        mCoeff.resize(multisetcoeff(mId.size()+1,mOrder));
    }
}

void bdouble::clear_tape()
{
    op_trace.clear();
    index_trace.clear();
    val_trace.clear();
    indexcount = 0;
}