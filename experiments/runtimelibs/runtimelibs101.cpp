#include "runtimelibs101.h"
#include <string>

void printrtl()
{
     std::cout << "SUCCESS: inside printrtl no arguments." << std::endl;
}

void printrtl(std::string str)
{
     std::cout << str << std::endl;
}

std::string getString(std::string str)
{
     return str;
}

rtlib101::rtlib101()
{
     rtlstr = "rtlstr: initialized in default constructor.";
}

rtlib101::rtlib101(std::string str)
{
     rtlstr = str;
}

void rtlib101::print()
{
     std::cout << rtlstr << std::endl;
}

void rtlib101::print(std::string str)
{
     std::cout << str << std::endl;
}

std::string rtlib101::getString()
{
     return rtlstr;
}

rtlib101 createRTL()
{
     return rtlib101();
}
