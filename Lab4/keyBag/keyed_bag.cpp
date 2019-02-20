


#include <stdio.h>
#include <assert.h>
#include "keyed_bag.h"


namespace coen79_lab4{
    
    /* MODIFICATION MEMBER FUNCTIONS */
    
    //contructor: creates new bag
    keyed_bag::keyed_bag(){
        //declares 2 new arrays of size CAPACITY to hold
        used = 0;
    }
    
    //erases all keys and data
    void keyed_bag::erase(){
        used = 0;
        //setting used to zero will allow every key to be overwritten
        //meaning the bagged is essentially seen as empty
    }
    
    //erases given key and associated data if key is in the bag
    bool keyed_bag::erase(const key_type &key){
        //for handles 0 case
        for(int i=0; i<used; i++){
            //if the key is found, the key and data in the last spot are moved to
            //the location of the old key to overite it, and used is decremented
            if(keys[i]==key) {
                keys[i] = keys[used];
                data[i] = data[used];
                used--;
                return true;
            }
            
        }
        //else
        return false;
    }
    
    //assuming there is room, a new value and key is added to the bag
    void keyed_bag::insert(const value_type &entry, const key_type key){
        assert(used<CAPACITY);
        data[used] = entry;
        keys[used] = key;
        used++;
    }
    
    
    //inserts all of passed bags keys and data to this keyed bag
    void keyed_bag::operator +=(const keyed_bag &addend){
        assert(used +addend.size() <=CAPACITY);
        assert(!this->hasDuplicateKey(addend));
        for(int i=0; i<addend.size(); i++){
            this->insert(addend.data[i], addend.keys[i]);
            //inserts each item into keyed bag
        }
        
    }
    
    
    /* CONSTANT MEMBER FUNCTIONS */
    
    //returns weather or not given key is in keyed_bag
    bool keyed_bag::has_key(const key_type &key) const {
        //looks for key in keyed bag
        for(int i=0; i<used; i++){
            if(keys[i]==key){
                //key found
                return true;
            }
        }
        //else
        return false;
    }
    
    //returns data associated with given key
    keyed_bag::value_type keyed_bag::get(const key_type &key) const{
        assert(has_key(key));
        //search keys
        int i=0;
        while(i<used && keys[i]!=key){
            i++;
        }
        return data[i];
        
    }
    
    
    //returns number of used spaces in keys[]
    keyed_bag::size_type keyed_bag::size() const{
        return used;
    }
    
    //returns number of times the target is found in data[]
    //irrelevant of what its key is
    keyed_bag::size_type keyed_bag::count(const value_type &target) const{
        size_type count=0;
        for(int i=0;i<used;i++){
            if(data[i]==target){
                count++;
                //count incremented when data found
            }
        }
        return count;

    }
    
    
    //
    bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const{
        for(int i=0;i<used; i++){
            for(int j=0; j< otherBag.size(); j++){
                if(keys[i]==otherBag.keys[j]){
                    return true;
                }
            }
        }
        return false;

    }
    
    /* NON-MEMBER FUNCTIONS */
    
    keyed_bag operator +(const keyed_bag &b1, const keyed_bag &b2){
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
        assert(!b1.hasDuplicateKey(b2));
        keyed_bag bag1 = keyed_bag(b1);
        bag1+=b2;
        return bag1;
    }
    
}
