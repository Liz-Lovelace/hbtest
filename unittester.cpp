#include "general-utils.h"
#include <string>
#include <iostream>
#include <vector>
int main(){
  std::string str = "hello\nworld\nI'm a big ol' string with big ambitions!!!\n";
  std::vector<std::string> vec = strToLines(str);
  for (int i = 0; i < vec.size(); i++) {
    std::cout << i << vec[i] << std::endl;
  }
  return 0;
}