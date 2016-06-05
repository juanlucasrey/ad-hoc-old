//          Copyright Juan Lucas Rey 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "partitionGenerator.h"
#include <limits>

partitionGenerator::partitionGenerator(const size_t& nin)
{
    n = nin;
    first = true;
}

bool partitionGenerator::next(vector<size_t>& b)
{
    if(first)
    {
        b.clear();
        b.reserve(n);
        b.resize(1,n);
        
        first = false;
        return true;
    }
    else
    {
        if(b[0] == 1)
            return false;
        else
        {
            size_t rem_val = 0;
            
            while(b.size()>0 && b.back() == 1)
            {
                rem_val += b.back();
                b.pop_back();
            }
            
            b.back()--;
            rem_val++;
            
            while (rem_val > b.back())
            {
                b.push_back(b.back());
                rem_val = rem_val - b.back();
            }
            
            b.push_back(rem_val);
            
            return true;
        }
    }
}

size_t partitionGenerator::multiplicity(const vector<size_t>& b)
{
    if(factorials.empty())
    {
        factorials.resize(n+1);
        
        //by convention
        factorials[0] = 1;
        for(size_t i=1; i<=n; i++)
            factorials[i] = i*factorials[i-1];
    }
    
    size_t mult = factorials.back();
    
    //I only care if there are at least two elements of the same value, so
    //it means that I only care for values up to int(n/2)
    //this whole thing will be cached anyway so I'm not looking for
    //efficiency here..
    vector<size_t> elements_counter(n);
    for (vector<size_t>::const_iterator it = b.begin(); it!=b.end(); ++it)
    {
        mult /= factorials[*it];
        elements_counter[(*it)-1]++;
    }
    
    for (vector<size_t>::const_iterator it = elements_counter.begin(); it!=elements_counter.end(); ++it)
    {
        mult /= factorials[*it];
    }
    
    return mult;
}

partitionGeneratorDistinct::partitionGeneratorDistinct(const size_t& nin)
{
    n = nin;
    first = true;
}

bool partitionGeneratorDistinct::next(vector<size_t>& b)
{
    if(first)
    {
        //b.clear();
        //b.resize(n,1);
        
        //vs
        if(b.size() != n)
            b.resize(n);
        
        std::fill(b.begin(), b.end(), 1);
        
        first = false;
        return true;
    }
    else
    {
        size_t i,j;
        for(i = (n-1); i != numeric_limits<size_t>::max(); i--)
        {
            j = i-1;
            while(j != numeric_limits<size_t>::max() && b[j] < b[i])
                j--;
            
            if(j != numeric_limits<size_t>::max())
                break;
        }
        
        if(i != numeric_limits<size_t>::max())
        {
            b[i]++;
            for(size_t j = i+1; j < n ; j++)
                b[j] = 1;
            
            return true;
        }
        else
            return false;
    }
}

multisetGenerator::multisetGenerator(const size_t& casesin,const size_t& unitsin)
{
    cases = casesin;
    units = unitsin;
    first = true;
}

bool multisetGenerator::next(vector<size_t>& b)
{
    if(first)
    {
        //b.clear();
        //b.resize(cases,0);
        
        //vs
        if(b.size() != cases)
            b.resize(cases);
        
        std::fill(b.begin(), b.end(), 0);
        
        b[0] = units;
        first = false;
        return true;
    }
    else
    {
        if(b.back() == units)
            return false;
        else
        {
            size_t i = cases-2;

            while(b[i] == 0)
                i--;
            
            b[i+1]++;
            b[i]--;
            
            if(b.back()>0 && i+1 != b.size()-1)
            {
                b[i+1] += b.back();
                b.back() = 0;
            }
            
            return true;
        }
    }
}

bool multisetGenerator::prev(vector<size_t>& b)
{
    if(first)
    {
        //b.clear();
        //b.resize(cases,0);
        
        //vs
        if(b.size() != cases)
            b.resize(cases);
        
        std::fill(b.begin(), b.end(), 0);
        
        b.back() = units;
        first = false;
        return true;
    }
    else
    {
        if(b.front() == units)
            return false;
        else
        {
            size_t i;
            i = cases-1;
            while(b[i] == 0)
                i--;
            
            b[i-1]++;
            b[i]--;
            
            if(b[i]>0 && i+1 != b.size())
            {
                b.back() = b[i];
                b[i] = 0;
            }
            
            return true;
        }
    }
}

combinationGenerator::combinationGenerator(const size_t& casesin, const size_t& basein)
{
    cases = casesin;
    base = basein-1;
    first = true;
}

bool combinationGenerator::next(vector<size_t>& b)
{
    if(first)
    {
        b.clear();
        b.resize(cases,0);
        
        first = false;
        return true;
    }
    else
    {
        size_t j = 0;
        while(j<b.size())
        {
            if(b[j] == base)
                b[j] = 0;
            else
            {
                b[j]++;
                break;
            }
            j++;
        }
        
        if(j == b.size())
            return false;
        
        return true;
    }
}
