//
//  1_counter.cpp
//  Lab1
//  description: takes in a string a of characters and prints out
//  number of alphanumeric characters and non-alphanumeric characters
//  Created by christopher j nelson on 1/12/18.
//
//

//included libraries
#include <iostream>
#include <ctype.h>
#include <string>

using namespace std;

//runtime: O(n)
int main() {
    int numAlpha = 0;
    int nonAlpha = 0;
    string inputStr;

    cout<< "please enter a character string"<<endl;
    getline(cin, inputStr);  //stores characters passed as input into variable inputStr
    
    //counts through each character to check whether or not is alphanumeric
    //if it is, it adds 1 to numAlpha, otherwise 1 is added to nonAlpha
    for (int i=0; i<inputStr.length(); i++) {
        if (isalnum(inputStr[i]) ){
            numAlpha++;
        }
        
        else if (inputStr[i]!=char(32)) {
            nonAlpha++;
        }
    }
         
    //prints results
    cout <<"The string you entered has:"<<endl;
    cout<<numAlpha<<" alphanumeric characters and"<<endl;
    cout<<nonAlpha<<" non-alphanumeric charcaters"<<endl;
    cout<<endl;
    return EXIT_SUCCESS;
}
