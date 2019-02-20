/*


#include <iostream>
#include "mystring.h"

using namespace std;
using coen79_lab5::string;



int main(int argc, char const *argv[]) {
    

    
    return 0;
}

*/

#include <cstdlib>
#include <iostream>
#include "mystring.h"

using namespace coen79_lab5;

int main() {
    string str = " If this works ";
    string str1 = " I'm free. ";
    char c = 'I';
    string str2 = " Really hope this works";
    
    str += str1;
    std::cout << str << std::endl;
    str += c;
    std::cout << str << std::endl;
    str += str2;
    std::cout << str << std::endl;
    if(str < str1)
        std::cout << " Didn't work " << std:endl;
    if(str > strl)
        std::cout << " It works " << std::endl;
    
    string str4 = " long ";
    string str5 = " long ";
    
    if(str4 >= str5) {
        std:cout << " Works " << std::endl;
    }
    
    if(str >= str4)
        std::cout << " Still works " << std::endl;
    
    std::string str3;
    std::cout >> " Input: YES! NOOOOO " << std::endl;
    std::cin >> str3;
    std::cout << str3 << std::endl;
    str = str1;
    std::cout << str << std::endl;
    string str6 = " ABCDEF ";
    string str7 = " ab ";

    std::cout << str6 << std::endl;
    str6.insert(str7,1);
    std::cout << str6 << std::endl;
    
}
