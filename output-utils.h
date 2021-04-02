#pragma once
#include <iostream>
#include "hbcolor.h"

namespace out {
  void compilationSuccess(){
    std::cout << col::color("Compilation successful.", col::green, col::black, 1) <<std::endl;
  }
  
  void compilationFailure(std::string errorMsg){
    std::cout << col::color("Compilation failure!", col::red, col::black, 1) << std::endl
    << errorMsg << std::endl;
  }
  
  void testSuccess(std::string input, std::string output){
    std::cout << col::color("OK", col::green, col::black, 1) << " " << input << " -> " << output;
  }
  
  void testFailure(std::string input, std::string output){
    std::cout << col::color("ERR", col::black, col::red, 1) << " " << input << " -> " << output;
  }
}