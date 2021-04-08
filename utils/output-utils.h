#pragma once
#include <iostream>
#include "hbcolor.h"

namespace out {
/*
  void compilationSuccess(){
    std::cout << col::color("Compilation successful.", col::green, col::black, 1) <<std::endl;
  }
  
  void compilationFailure(std::string errorMsg){
    std::cout << col::color("Compilation failure!", col::red, col::black, 1) << std::endl
    << errorMsg << std::endl;
  }
*/
  
  
  void debugLog(std::string str){
    std::cout << col::color(str, col::blue) << std::endl;
  }
  
  void errorLog(std::string str){
    std::cout << col::color(str, col::black, col::red, 1) << std::endl;
    throw;
  }
}