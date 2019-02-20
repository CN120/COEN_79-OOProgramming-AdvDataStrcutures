//
//  sequence1.cpp
//  Lab3
//
//  Created by christopher j nelson on 1/26/18.
//  Copyright © 2018 christopher j nelson. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <cmath> //for absolute value
#include "sequence1.h"
namespace coen79_lab3 {
    
    sequence::sequence(){
        used = 0;
        pos = 0;
    }
    
    //resets iterator to position 0
    void sequence::start(){
		pos=0;
    }
    
    //sets iterator to last itm in the sequence
    void sequence::end(){
        pos = used-1;
    }
    
    
    //sets iterator to last value possible or CAPACITY-1
    void sequence::last(){
        pos = CAPACITY-1;
    }
    //returns the item in the sequence at the current position of the iterator
    sequence::value_type sequence::current() const{
        assert(is_item());
        return data[pos];
    }

    
    //The iterator's value is increased by 1, unless it is already at the end ofthe sequence.
    void sequence::advance(){
        assert(is_item());
        if (pos<used-1){
            pos++;
        }
    }
    
    
    //The iterator's value is reduced by 1, unless it is already at the beginningof the sequence.
    void sequence::retreat(){
        if (pos>0){
            pos--;
        }
    }
    
    //a copy of entry is inserted before current item, and becomes the current item
    //assuming there is room
    void sequence::insert(const value_type& entry){
        assert(used<CAPACITY);
        //moves data other data entries forward to make room for new entry
        //includes used=0 case
        for(int i=used; i>pos; i--){
            data[i]=data[i-1];
        }
        data[pos]=entry; //inserts entry
        used++;
    }

    //inserts entry after the current item, assuming there is room
    void sequence::attach(const value_type &entry){
        assert(used<CAPACITY);
        if(used==0){
            data[0]=entry;
        }
        //adds entry behind the item ahead of currnt
        else{
            advance();
            insert(entry);
        }
    }

    //removes the current item from the sequence
    void sequence::remove_current(){
        assert(is_item());
        for(int i=pos; i<used-1; i++){
			data[i]=data[i+1];
        }
        used--;
    }

    //inserts entry at beginning of the sequence
	void sequence::insert_front(const value_type& entry){
        assert(used<CAPACITY);
		sequence::start();
        insert(entry);
    }
    
    //inserts entry at back of the sequence
    void sequence::attach_back(const value_type& entry){
        assert(used<CAPACITY);
        pos= used;
        data[pos] = entry;
        used++;
    }

    //removes item at beginning of sequence
    void sequence::remove_front(){
		sequence::start();
        assert(is_item());
        remove_current();
    }

    
    
    // CONSTANT MEMBER FUNCTIONS for the sequence class:

    //returns number of items in the sequence
	sequence::size_type sequence::size() const{
        return used;
    }
    
    //True when a valid item in the current position, false when not
    bool sequence::is_item( ) const{
        assert(pos>=0);
        return pos<used;
    }

    
    //returns item stored at given index
    sequence::value_type sequence::operator[](int index) const{
        assert(index<used);
        return data[index];
    }
    
    //returns mean of the values stored in the sequence
    double sequence::mean() const{
        double sum = 0;
        for(int i=0; i<used;i++){
            sum+=data[i];
        }
        return sum/used;
    }
    
    //returns the standard deviation of the values stored in the sequence
	double sequence::standardDeviation() const{
        double mean = sequence::mean();
		double stdDev=0;
        //computes total of all deviations
		for(int i=0; i<used;i++){
            stdDev+= std::abs(mean-data[i]);
		}
		return stdDev/used; //returns average of all deviations
    }

    //cobines two sequence instances
    sequence operator+(const sequence &lhs, const sequence &rhs){
        sequence total= sequence();
        //checks that a new sequence can fit both of passed sequences
        assert(lhs.size()+rhs.size()<=total.CAPACITY);
        sequence left = sequence(lhs); //copies lhs to left on stack
        sequence right = sequence(rhs); //copies rhs to right on stack
        left.start();
        right.start();
        
        //adds left items
        for (int i=0; i<left.size(); i++){
            total.attach_back(left.current());
            left.advance();
		}
        //adds right items
		for(int j=0; j<right.size(); j++) {
            total.attach_back(right.current());
            right.advance();
		}
		return total;
    }
    
    //Adds the items of rhs to the lhs and returns a copy of lhs
    sequence sequence::operator+=(const sequence& rhs){
        //used -> because "this" is a pointer
        //checks that a sequence has enough room for sequence rhs
        assert(this->size()+rhs.size()<=this->CAPACITY);
        sequence right = sequence(rhs); //copies rhs into right
        right.start();
        //adds items of right
		for(int i =0; i<right.size(); i++){
			this->attach_back(right.current());
            right.advance();
		}
        return *this;  //returns original object dereferenced
    }
    
    //returns the summation of the values stored in the sequence s
	sequence::value_type summation(const sequence &seq){
        sequence s = sequence(seq); //copies seq to s
        s.start();
		sequence::value_type sum = 0;
		for(int i=0; i<s.size();i++) {
			sum+= s.current(); //gets current value
			s.advance();
		}
        return sum;
    }

}


