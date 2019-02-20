

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include "mystring.h"
#include <cstring>
#include <algorithm>

//invariants of string
//string will always have an array of characters
//allocated > current_length

namespace coen79_lab5{
   /* Constructors */
    string::string(const char std[]){
        assert(std[ strlen(std) ] == '\0');
        allocated = strlen(std)+1;
        current_length = strlen(std);;
        characters = new char[allocated];
        for(int i= 0; i<=current_length; i++){
            characters[i]=std[i];
        }
    }
    
    string::string(char c){
        allocated = 2;
        current_length = 1;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
        

    }
    
    string::string(const string& source){
        current_length = source.length();
        allocated = current_length+1;
        characters = new char[allocated];
        *this+=source;
        
        
    }
    
    /* MODIFICATION MEMBER FUNCTIONS */
    //attaches addend to end of string
    void string::operator +=(const string &addend){
        if (addend.length() + current_length >= allocated){
            reserve(2*current_length+addend.length());
        }
        strncat(characters, addend.characters, addend.length());
        current_length+=addend.length();
    }
    
    //addend array concatinated to end of string
    void string::operator +=(const char addend[]){
        if (strlen(addend) + current_length >= allocated){
            reserve(2*current_length+strlen(addend));
        }
        strncat(characters, addend, strlen(addend));
        current_length += strlen(addend);
        
    }
    
    //single character added to end of string
    void string::operator +=(char addend){
        if (1 + current_length >= allocated){
            reserve(2*current_length);
        }
        characters[current_length] = addend;
        current_length+=1;
    }
    
    //allocates new memoery when needed
    void string::reserve(size_t n){
        if(n<=allocated)
            return;
        char* res = new char[n];
        strncpy(res, characters, current_length+1);
        delete characters;
        characters = res;
        allocated = n;
    }
    
    //inserts source string into this string before the character at the given index
    void string::insert(const string &source, unsigned int position){
        assert(position<=length());
        if (1 + current_length >= allocated){
            reserve(2*(1 + current_length));
        }
        //shift to make space
        for(int i = current_length-position; i>=0; i--){
            characters[position + i + source.length()] = characters[position + i];
        }
        
        int x=0;
        for(int j=position-1; j<position-1+source.length(); j++){
            characters[j] = source.characters[x];
            ++x;
        }
        
        /*
        std::copy(characters+position, characters+position, source.length());
        current_length += source.length();
         */
        
    }
    
    //num characters are deleted starting at at index of position
    void string::dlt(unsigned int position, unsigned int num){
        assert((position + num)<=length());
        //shifts all numbers num spots back to fill deleted spots
        for( int i=position; characters[i+num-1]!='\0'; i++){
            characters[i] = characters[i+num];
        }
        
    }
    
    //chracter at index position is replaced with c
    void string::replace(char c, unsigned int position){
        assert(position<length());
        characters[position]=c;
        
    }
    
    //replaces a substring with a given source
    void string::replace(const string &source, unsigned int position){
        assert( (position+source.length()) <=length() );
        for(int i=0; i<source.length(); i++){
            characters[position+i] = source[i];
        }
    }
    
    /* CONSTANT MEMBER FUNCTIONS */
    
    
    //returns value at given position in the string
    char string::operator[](size_t position) const{
        assert(position<length());
        return characters[position];
        
    }
    
    //returns location of first instance of char c
    //not found returns -1
    int string::search(char c) const{
        for(int i = 0; i<current_length; i++){
            if(characters[i]==c){
                return i;
            }
        }
        return -1;
    }
    
    //returns location of start of found substring
    //returns -1 if not found
    int string::search(const string &substring) const{

        for(int loc=0; loc<length(); loc++){
            int x=0;
            while(characters[loc+x]== substring[x]){
                ++x;
                if (x==substring.length()){
                    return loc;
                }
            }
            
        }
        return -1;
    }
    
    //returns number of occurences of c in the string
    unsigned int string::count(char c) const{
        int num = 0;
        for(int i=0; i<current_length; i++){
            if(characters[i]==c){
                ++num;
            }
        }
        return num;
    }
    
    /* NON-MEMBER FUNCTIONS */
    
    //reads and returns a string from istream
    std::istream& operator >> (std::istream& ins, string& target){
        while(ins && isspace(ins.peek()))
            ins.ignore();
        char temp;
        target = "";
        while(ins && !isspace(ins.peek())){
            std::cin >> temp;
            target +=temp;
        }
        return ins;
        
    }
    
    //concatenates string 1 and string 2
    string operator +(const string& s1, const string& s2){
        string *sum = new string(s1);
        *sum+=s2;
        return *sum;
    }
    
    string operator +(const string& s1, const char addend[ ]){
        string *sum = new string(s1);
        sum->reserve(strlen(addend));
        
        for(int i=0; i<strlen(addend); i++){
            sum->insert(addend[i], sum->length());
        }
        return *sum;
    }

    
    

    
    
    /* FRIEND FUCNTIONS */
    //writes string to outs
    std::ostream& operator <<(std::ostream& outs, const string& source){
        outs<< source.characters;
        return outs;
    }
    
    //checks equality
    bool operator ==(const string& s1, const string& s2){
        if(s1.length() != s2.length())
            return false;
        
        for(int i=0; i<s1.length(); i++){
            if(s1[i]!=s2[i]){
                return false;
            }
        }
        
        return true;
    }
    
    //oposite of ==
    bool operator !=(const string& s1, const string& s2){
        return !(s1==s2);
    }
    
    //returns true if s1 comes before s2 in alphabet
    bool operator > (const string& s1, const string& s2){
        if (strcmp(s1.characters, s2.characters)>1)
            return true;
            
        else
            return false;
        
    }
    
    //returns true if s1 comes after s2 in alphabet
    bool operator < (const string& s1, const string& s2){
        if (strcmp(s1.characters, s2.characters)<1)
            return true;
        else
            return false;
    }
    
    //returns true if s1 comes before or is the same as s2
    bool operator >=(const string& s1, const string& s2){
        if(s1>s2 || s1==s2)
            return true;
        else
            return false;
    }
    //returns true if s1 comes after or is the same as s2
    bool operator <=(const string& s1, const string& s2){
        if(s1<s2 || s1==s2)
            return true;
        else
            return false;

    }

    
}
                    
                    
                    
