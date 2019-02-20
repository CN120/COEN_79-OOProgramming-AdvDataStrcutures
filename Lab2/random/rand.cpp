//
//  rand.cpp
//  Lab2
//
//  Created by Chris Nelson on 1/25/18.
//  Copyright © 2018 christopher j nelson. All rights reserved.
//

#include <stdio.h>
#include "random.h"



namespace coen79_lab2 {
    //constructor
    rand_gen::rand_gen(int seed1, int multiplier, int increment, int modulus){
        seed = seed1;
        mult = multiplier;
        inc = increment;
        mod = modulus;
    }
    
    int rand_gen::next(){
        //sets the seed to the result of previous seed before returning
        seed = (mult*seed+inc)%mod;
        return seed;
    }
    
    void rand_gen::set_seed(int newSeed){
        seed = newSeed;
    }
    
    void rand_gen::print_info() {
        std::cout<< "seed:"<<seed<<" multiplier:"<<mult<<" increment:"<<inc<<" modulus:"<<mod;
    }
    
    
    
}
