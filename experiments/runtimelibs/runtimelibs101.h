#include <string>
#include <iostream>

extern "C"
void printrtl();

//extern "C"
void printrtl(std::string str);

extern "C"
std::string getString(std::string str);

class rtlib101{
public:
     std::string rtlstr;

     rtlib101();
     rtlib101(std::string str);

     void print();
     void print(std::string str);
     std::string getString();
};

extern "C"
rtlib101 creatRTL();
