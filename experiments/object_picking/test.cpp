#include <iostream>

int main(){
  int num[72];
  int j = 0;
  for(int i=0; i<72; i++){
    num[i] = i;
  }
  for (int i = 0; i < 72; i++)
  {

    if (i%3 == 2)
    {
      i++;

      continue;
    }
    else
    {
      j=i;
      std::cout << num[i] << " " << std::endl;
      std::cout << num[i+1] << " " << std::endl;
      i+=2;
    }
  }
  std::cout << j << std::endl;
}
