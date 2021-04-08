#pragma once
#include <iostream>
#include <vector>
#include "general-utils.h"
#include "output-utils.h"

struct Config {
  bool debug = false;
  std::string testCommand;
  std::string testFile = "tests.txt";
    
  void printConfig(){
    std::cout << "test command "  << testCommand    << std::endl
              << "test file "     << testFile       << std::endl
              << "debug mode "    << debug          << std::endl;
  }
};

Config readConfig(std::vector<std::string> argv){  
  if (argv.size()==0)
    out::errorLog("No arguments provided.");
  Config config;
  config.testCommand = argv[0];
  for (int i = 0; i < argv.size(); i++){
    if(argv[i] == "-t")
      config.testFile = argv[i+1];
    else if(argv[i] == "-d")
      config.debug = true;
  }
  return config;
}