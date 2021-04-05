#include <string>
#include <iostream>
#include "utils/general-utils.h"
#include "utils/config-utils.h"

int main(int argn, char **argv){
  std::vector<std::string> vec = parseArguments(argn, argv);
  for (long unsigned int i = 0; i < vec.size(); i++)
    std::cout <<i << ": "<< vec[i] << std::endl;
  std::cout << std::endl;
  Config c = readConfig(vec);
  c.printConfig();
  return 0;
}