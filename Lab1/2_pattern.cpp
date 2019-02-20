//
//  2_pattern.cpp
//  Lab1
//  desription: prints out pattern of number string 0 through 9 forward and in reverse
//  every other line, with each line indented one more space
//  Created by christopher j nelson on 1/12/18.
//
//

//included libraries
#include <iostream>
#include <iomanip>

using namespace std;


int main() {
    string numF = "0123456789"; //forward num string
    string numB = "9876543210"; //backward num string
    const int numLines = 10; //number of lines for pattern to be printed
    
    for (int i=0; i<numLines; i++){
        cout<<setw(i+10);
        //forward num string is printed on even lines
        if (i%2==0){
            cout<<numF<<endl;
        }
        //backward num string is printed on odd lines
        else{
            cout<<numB<<endl;
        }
    }
    
    return EXIT_SUCCESS;
}
