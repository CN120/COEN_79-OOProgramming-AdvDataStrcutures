//
//  3_convert.cpp
//  Lab1
//  description: takes a text file as a comman line argument
//  and returns words longer than ten when all non-alphanumeric charcters have been removed
//  Created by christopher j nelson on 1/12/18.
//

//included libraries
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>

using namespace std;

int main(int argc, char *argv[]){
    ifstream inFile;
    inFile.open(argv[1]);   //opens file passed as a command line argument
    string word;
    inFile>>word;   //passes first word, to varibale word
    
    while (inFile>>word){
        int wordLen = word.length(); //initial word length variable
        for(int i = 0; i<wordLen; i++){
            if (!isalpha(word[i])){
                word.erase(i,1);
                i--;  //decrement i, since each character gets moved back a slot after erasing a character
                wordLen--; //modifies owrd length after erasing character
            }
        }
        
        //word is capatalized and printed if it is at least 10 charcaters after deletion
        //of non alphanumeric  characters
        if (wordLen>9){
            for(int i = 0; i<word.length(); i++) {
                word[i]=toupper(word[i]);
            }
            cout<<word<<endl;
           
        }
    }
    
}
