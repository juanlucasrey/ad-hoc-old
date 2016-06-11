//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef __ddouble__partitionGenerator__
#define __ddouble__partitionGenerator__

#include <vector>
#include <algorithm>
using namespace std;

class partitionGenerator
{
public:
    partitionGenerator(const size_t& nin);
    bool next(vector<size_t>& b);
    size_t multiplicity(const vector<size_t>& b);
    
private:
    size_t n;
    bool first;
    vector<size_t> factorials;
};

class partitionGeneratorDistinct
{
public:
    partitionGeneratorDistinct(const size_t& nin);
    bool next(vector<size_t>& b);
private:
    size_t n;
    bool first;
};

class multisetGenerator
{
public:
    multisetGenerator(const size_t& casesin,const size_t& unitsin);
    bool next(vector<size_t>& b);
    bool prev(vector<size_t>& b);
private:
    size_t cases;
    size_t units;
    bool first;
};

class combinationGenerator
{
public:
    combinationGenerator(const size_t& cases, const size_t& base);
    
    bool next(vector<size_t>& b);
    
private:
    size_t cases;
    size_t base;
    bool first;
};

inline size_t combins(size_t d1,size_t d2,const bool d2totalElements = false)
{
    if(d2totalElements)
    {
        if(d2<d1)
            return 0;
    }
    else
    {
        if (d2 < d1)
            swap(d1, d2);
    }
    
    if (d1 == 0)
        return 1;
    
    
    size_t n;
    
    if(d2totalElements)
        n = d2;
    else
        n = d1 + d2;
            
    size_t r = n;
    n--;
    
    for(size_t d = 2; d <= d1; ++d,--n)
    {
        r *= n;
        r /= d;
    }
    
    return r;
};

inline size_t combins2(size_t d1,size_t d2)
{
    if (d2 < d1)
        swap(d1, d2);
    
    if (d1 == 0)
        return 1;
    
    size_t n = d2;
    
    size_t r = n;
    n--;
    
    for(size_t d = 2; d <= d1; ++d,--n)
    {
        r *= n;
        r /= d;
    }
    
    return r;
};

inline size_t multisetcoeff(const size_t& n,const size_t& k)
{
    return combins(n-1,k);
}

inline size_t multisetcount(const vector<size_t>& b,const size_t& k)
{
    size_t ballsLeft = k;
    size_t r = 0;
    size_t m = b.size();
    for(size_t i = 0; ballsLeft != 0 && i < m; i++)
    {
        for(size_t j = b[i]; j < ballsLeft; j++)
            r += combins(m-i-2,ballsLeft-j-1);
        
        ballsLeft -= b[i];
    }
    
    return r;
}

#endif /* defined(__ddouble__partitionGenerator__) */
