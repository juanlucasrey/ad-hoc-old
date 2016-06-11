//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef __ddouble__bdouble__
#define __ddouble__bdouble__

#include <vector>
using namespace std;

const size_t
emptyv = 0, constv = 1, indepv = 2, copyconstructor = 3, copyassignement = 4,
bplusv = 5, bminusv = 6, bmultv = 7, sumconstv = 8, minusconstv = 9, multconstv = 10,
cosv = 11, sinv = 12, expv = 13, exp2v = 14, expm1v = 15, powv = 16, powintv = 17, invv = 18,
logv = 19, log10v = 20, log2v = 21, coshv = 22, sinhv = 23, erfv = 24, erfcv = 25, nv= 26,
tanv = 27, tanhv = 28, acosv = 29, asinv = 30, atanv = 31, acoshv = 32, asinhv = 33, atanhv = 34,
lgammav = 35, tgammav = 36, log1pv = 37;

class bdouble
{
public:
    
    bdouble(const double& rhs = 0.0);
    bdouble(const bdouble& rhs);
    
    bdouble& operator=(const bdouble& rhs);
    bdouble& operator=(bdouble&& rhs);
    
    double der(const vector<size_t>& id,const vector<size_t>& order);
    
    template<typename ... Types>
    double der(const Types & ... rest)
    {
        //the tape has not been run
        if(mCoeff.size() == 0)
            run_tape();
        
        vector<size_t> idxes(mId.size()+1,0);
        idxes[0] = mOrder;
        size_t var_id = -1;
        return der_aux(var_id,idxes,rest...);
    }
    
    bdouble operator+(const bdouble& rhs) const;
    bdouble operator-(const bdouble& rhs) const;
    bdouble operator*(const bdouble& rhs) const;
    bdouble operator/(const bdouble& rhs) const;
    
    template <class T>
    bdouble& operator+=(const T& rhs)
    {
        *this = *this + rhs;
        return *this;
    }
    
    template <class T>
    bdouble& operator-=(const T& rhs)
    {
        *this = *this - rhs;
        return *this;
    }
    
    template <class T>
    bdouble& operator*=(const T& rhs)
    {
        *this = *this * rhs;
        return *this;
    }
    
    template <class T>
    bdouble& operator/=(const T& rhs)
    {
        *this = *this / rhs;
        return *this;
    }
    
    template <class T>
    friend bdouble operator+(const T& lhs, const bdouble& in)
    {
        return in.operator+(lhs);
    }
    
    template <class T>
    bdouble operator+(const T& rhs) const
    {
        //if T is 0 then this is identity
        if(rhs != 0)
        {
            const bdouble& in = (*this);
            
            bdouble::val_trace.push_back((double)rhs + in.mValue);
            
            bdouble res(bdouble::val_trace.back());
            
            bdouble::op_trace.push_back(sumconstv);
            bdouble::index_trace.push_back(in.mThisId);
            bdouble::index_trace.push_back(res.mThisId);
            
            return res;
        }
        else
            return *this;
    }
    
    template <class T>
    friend bdouble operator-(const T& lhs, const bdouble& in)
    {
        bdouble::val_trace.push_back((double)lhs - in.mValue);
        
        bdouble res(bdouble::val_trace.back());
        
        bdouble::op_trace.push_back(minusconstv);
        bdouble::index_trace.push_back(in.mThisId);
        bdouble::index_trace.push_back(res.mThisId);
        
        return res;
    }
    
    template <class T>
    bdouble operator-(const T& rhs) const
    {
        return (*this).operator+(-rhs);
    }
    
    template <class T>
    friend bdouble operator*(const T& lhs, const bdouble& in)
    {
        return in.operator*(lhs);
    }
    
    template <class T>
    bdouble operator*(const T& rhs) const
    {
        //if T is 1 then this is identity
        if(rhs != 1)
        {
            const bdouble& in = (*this);
            
            bdouble::val_trace.push_back((double)rhs);
            bdouble::val_trace.push_back((double)rhs * in.mValue);
            
            bdouble res(bdouble::val_trace.back());
            
            bdouble::op_trace.push_back(multconstv);
            bdouble::index_trace.push_back(in.mThisId);
            bdouble::index_trace.push_back(res.mThisId);
            
            return res;
        }
        else
            return *this;
    }
    
    template <class T>
    friend bdouble operator/(const T& lhs, const bdouble& in)
    {
        return inv(in)*lhs;
    }
    
    template <class T>
    bdouble operator/(const T& rhs) const
    {
        return (*this).operator*(1/rhs);
    }
    
    //standard functions
    friend bdouble cos(const bdouble& in);
    friend bdouble sin(const bdouble& in);
    friend bdouble exp(const bdouble& in);
    friend bdouble exp2(const bdouble& in);
    friend bdouble expm1(const bdouble& in);
    friend bdouble sqrt(const bdouble& in);
    friend bdouble cbrt(const bdouble& in);
    friend bdouble log(const bdouble& in);
    friend bdouble log1p(const bdouble& in);
    friend bdouble log10(const bdouble& in);
    friend bdouble log2(const bdouble& in);
    friend bdouble cosh(const bdouble& in);
    friend bdouble sinh(const bdouble& in);
    friend bdouble erf(const bdouble& in);
    friend bdouble erfc(const bdouble& in);
    friend bdouble tan(const bdouble& in);
    friend bdouble tanh(const bdouble& in);
    friend bdouble acos(const bdouble& in);
    friend bdouble asin(const bdouble& in);
    friend bdouble atan(const bdouble& in);
    friend bdouble acosh(const bdouble& in);
    friend bdouble asinh(const bdouble& in);
    friend bdouble atanh(const bdouble& in);
    friend bdouble lgamma(const bdouble& in);
    friend bdouble tgamma(const bdouble& in);
    friend bdouble ldexp(const bdouble& in, const int& exp);
    
    friend bdouble pow(const bdouble& in, const int& deg);
    friend bdouble pow(const bdouble& in, const double& deg);
    friend bdouble pow(const double& val, const bdouble& in);
    friend bdouble pow(const bdouble& val, const bdouble& in);
    
    template <class T,class U>
    friend bdouble hypot(const T& arg1, const U& arg2)
    {
        return sqrt(arg1*arg1 + arg2*arg2);
    }
    
    template <class T,class U>
    friend bdouble atan2(const T& arg1, const U& arg2)
    {
        return atan(arg1/arg2);
    }
    
    template <class T,class U,class V>
    friend bdouble fma(const T& arg1, const U& arg2, const V& arg3)
    {
        return (arg1*arg2+arg3);
    }
    
    //non-standard functions
    friend bdouble N(const bdouble& in);
    friend bdouble inv(const bdouble& in);
    
    const size_t& id() const {return mThisId;}
    operator double() const {return mValue;}
    
    static void setOrder(size_t order) {mDefaultOrder = order;}
    void run_tape(const size_t orderOverride = -1);
    static void clear_tape();
    
private:
    
    double mValue;
    size_t mThisId;
    
    vector<double> mCoeff;
    vector<size_t> mId;
    size_t mOrder;
    
    //default order calculations
    static size_t mDefaultOrder;
    
    //tape
    static vector<size_t> op_trace;
    static vector<size_t> index_trace;
    static vector<double> val_trace;
    static size_t indexcount;
    
    //accesing mCoeff data
    const double& get(const vector<size_t>& idxes) const;
    double& get(const vector<size_t>& idxes);
    
    //functions to calculate taylor expansions
    friend void TE_multconst(const double& value,const double& coeff,vector<double>& output,size_t loc);
    friend void TE_sumconst(const double& value,const double& coeff,vector<double>& output,size_t loc);
    friend void TE_cos(const double& value,vector<double>& output,size_t loc);
    friend void TE_sin(const double& value,vector<double>& output,size_t loc);
    friend void TE_exp(const double& value,vector<double>& output,size_t loc);
    friend void TE_exp2(const double& value,vector<double>& output,size_t loc);
    friend void TE_expm1(const double& value,vector<double>& output,size_t loc);
    friend void TE_pow(const double& value,const double& deg,vector<double>& output,size_t loc);
    friend void TE_log(const double& value,vector<double>& output,size_t loc);
    friend void TE_log1p(const double& value,vector<double>& output,size_t loc);
    friend void TE_log10(const double& value,vector<double>& output,size_t loc);
    friend void TE_log2(const double& value,vector<double>& output,size_t loc);
    friend void TE_cosh(const double& value,vector<double>& output,size_t loc);
    friend void TE_sinh(const double& value,vector<double>& output,size_t loc);
    friend void TE_erf(const double& value,vector<double>& output,size_t loc);
    friend void TE_erfc(const double& value,vector<double>& output,size_t loc);
    friend void TE_N(const double& value,vector<double>& output,size_t loc);
    friend void TE_tan(const double& value,vector<double>& output,size_t loc);
    friend void TE_tanh(const double& value,vector<double>& output,size_t loc);
    friend void TE_acos(const double& value,vector<double>& output,size_t loc);
    friend void TE_asin(const double& value,vector<double>& output,size_t loc);
    friend void TE_atan(const double& value,vector<double>& output,size_t loc);
    friend void TE_acosh(const double& value,vector<double>& output,size_t loc);
    friend void TE_asinh(const double& value,vector<double>& output,size_t loc);
    friend void TE_atanh(const double& value,vector<double>& output,size_t loc);
    friend void TE_lgamma(const double& value,vector<double>& output,size_t loc);
    friend void TE_tgamma(const double& value,vector<double>& output,size_t loc);
    
    //aux
    template<typename ... Types>
    double der_aux(size_t& var_id, vector<size_t>& idxes,const size_t& order,const Types & ... rest) const
    {
        if(var_id == -1)
        {
            //if there's no var_id then order is actually a var_id
            var_id = order;
        }
        else
        {
            if (!addDer(idxes,var_id,order)) return 0;
            var_id = -1;
        }
        
        return der_aux(var_id,idxes,rest...);
    }
    
    template<typename ... Types>
    double der_aux(size_t& var_id, vector<size_t>& idxes,const bdouble& var,const Types & ... rest) const
    {
        //this means that the previous argument had an implied order of 1
        if(var_id != -1)
            if (!addDer(idxes,var_id,1)) return 0;
        
        var_id = var.id();
        
        return der_aux(var_id,idxes,rest...);
    }
    
    double der_aux(size_t& var_id, vector<size_t>& idxes) const;
    bool addDer(vector<size_t>& idxes,const size_t& var_id,const size_t& order) const;
};

#endif /* defined(__ddouble__bdouble__) */
