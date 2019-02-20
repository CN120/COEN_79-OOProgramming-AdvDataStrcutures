//
//  statistician.cpp
//  Lab2
//
//  Created by christopher j nelson on 1/19/18.
//  Copyright © 2018 christopher j nelson. All rights reserved.
//

#include "statistician.h"
#include "assert.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2{

    
    statistician::statistician(){
        count = 0;
        total = 0;

    }
    
    void statistician::next(double r){
        count++;
        total+=r;
        
        //for when sequence is empty
        if (count<2){
            min = r;
            max = r;
        }
        //sets max
        else if (r>max){
            max=r;
        }
        //sets min
        else if (r<min){
            min=r;
        }
        
    }
    
    int statistician::length() const{
        return count;
    }
    
    double statistician::sum() const{
        return total;
    }
    
    //calculates average
    double statistician::mean() const{
        assert(count!=0);
        return sum()/length();
    }
    
    double statistician::minimum() const{
        assert(count!=0);
        return min;
    }
    
    double statistician::maximum() const{
        assert(count!=0);
        return max;
    }
    
    void statistician::reset() {
        assert(count!=0);
        total=0;
        count=0;
        
    }
    
    
    bool operator==(statistician &s1, statistician &s2){
        //checks all values of each object against one another
        if(s1.length()==s2.length() && s1.mean()==s2.mean() && s1.minimum()==s2.minimum() && s1.maximum()==s2.maximum()){
            return true;
        }
        else{
            return false;
        }
    }

    statistician operator*(double scale, const statistician &s){
        statistician newStat;
        newStat.total = s.sum()*scale;
        //accounts for when scale is a negative number
        //min will become max and vice versa since signs will be flipped
        if (scale < 0){
            newStat.min = s.max*scale;
            newStat.max = s.min*scale;
        }
        else{
            newStat.min = s.min*scale;
            newStat.max = s.max*scale;
        }
        newStat.count = s.count;
        return newStat;
    
    }
    
    statistician operator+(statistician &s1, statistician &s2){
        statistician s3;
        s3.count=s1.length() + s2.length();
        s3.total=s1.sum() + s2.sum();
        
        //takes smallest minimum()
        if (s2.minimum() < s1.minimum()) {
            s3.min=s2.minimum();
        }
        else{
            s3.min=s1.minimum();
            
        }
        //takes greatest maximum()
        if (s2.maximum() > s1.maximum()) {
            s3.max=s2.maximum();
        }
        else{
            s3.max=s1.maximum();
        }
        //return new statistician
        return s3;
        
    }
    

}


