#include "runtimelibs101.h"

#include <iostream>
#include <string>

#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char** argv)
{
     void* lib_handle = dlopen("libruntimelib101.dylib", RTLD_LAZY);

     if( !lib_handle ){
          std::cerr << "Unable to load library: " << dlerror() << std::endl;
          exit(EXIT_FAILURE);
     }

     /*------------------------------*/
     void (*printrtl)();

     printrtl = (void (*)()) dlsym(lib_handle, "printrtl");

     if( !printrtl){
          std::cerr << "Unable to get symbol: " << dlerror() << std::endl;
          exit(EXIT_FAILURE);
     }
     printrtl();
     /*------------------------------*/

     /*------------------------------*/
     std::string (*getString)(std::string);

     getString = (std::string (*)(std::string)) dlsym(lib_handle, "getString");
     if( !getString ){
          std::cerr << "Unable to get symbol: " << dlerror() << std::endl;
          exit(EXIT_FAILURE);
     }

     std::cout << getString("SUCCESS: using getString with this string as an argument") << std::endl;
     /*------------------------------*/

     /*------------------------------*/
     rtlib101 (*createRTL)();
     createRTL = (rtlib101(*)()) dlsym(lib_handle, "createRTL");
     if( !createRTL ){
          std::cerr << "Unable to get symbol: " << dlerror() << std::endl;
          exit(EXIT_FAILURE);
     }
     /*------------------------------*/


     return 1;
}
