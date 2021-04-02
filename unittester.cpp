#include <string>
#include <iostream>
#include "exec-utils.h"

int main(){
  std::cout << linuxExec("./add.out", "6");
  return 0;
}