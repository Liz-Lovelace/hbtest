#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace col{
  int black = 30;
  int red = 31;
  int green = 32;
  int yellow = 33;
  int blue = 34;
  int magenta = 35;
  int cyan = 36;
  int white = 37;

  int reset = 0;
  int bold = 1;
  int underline = 4;
  int xbold = 21;
  int xunderline = 24;

  std::string color(std::string str, 
                    int color = col::white, 
                    int background = col::black + 10, 
                    bool bold = false, 
                    bool underline = false){
    background += 10;
    std::string params = std::to_string(color);
                  params += ';' + std::to_string(background);
    if (bold)     params += ';' + std::to_string(col::bold);
    if (underline)params += ';' + std::to_string(col::underline);
    return "\33[" + params + 'm' + str + "\033[0m";
  }

  void shortTest(){
    std::cout << color("Color test", col::green, col::white, true) << std::endl;
  }
  
  void test(){
    std::cout << color("does it work?", col::white, col::black, true) << '\n' << color("YES IT DOES", col::green, col::blue, true) << "\n\n";
    std::cout << color(" ☭     ", col::yellow, col::red) << '\n';
    std::cout << color("       ", col::yellow, col::red) << "\n\n";
    for (int a = 0; a < 8; a++){
      for (int b = 0; b < 8; b++){
        std::cout << color(" 染\u2588 ", 30 + a, 30 + b);
      }
      std::cout << '\n';
      for (int b = 0; b < 8; b++){
        std::cout << color(" 染\u2588 ", 30 + a, 30 + b, true);
      }
      std::cout << '\n';
    }
    std::cout << '\n';
    for (int a = 0; a < 8; a++){
      for (int b = 0; b < 8; b++){
        std::cout << color(" ░▒▓", 30 + a, 30 + b);
      }
      std::cout << '\n';
      for (int b = 0; b < 8; b++){
        std::cout << color(" ░▒▓", 30 + a, 30 + b, true);
      }
      std::cout << '\n';
    }
  }
}