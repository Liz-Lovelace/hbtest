#pragma once
#include <iostream>
#include <vector>
#include "general-utils.h"
#include "output-utils.h"

struct Config {
  bool continuous = false;
  bool debug = false;
  std::string testFile = "tests.txt";
  std::string language = "detect";
  std::string codeFile;
  std::string codeFileName;
  
  void printConfig(){
    std::cout << "continuous "      << continuous     <<std::endl
              << "test file "       << testFile       <<std::endl
              << "tested file "     << codeFile       <<std::endl
              << "tested file path "<< codeFileName   <<std::endl   
              << "language "        << language       <<std::endl
              << "debug mode "      << debug          <<std::endl;
  }
};

Config readConfig(std::vector<std::string> argv){  
  if(argv.size() == 0)out::errorLog("No arguments provided.");
  Config config;
  config.codeFile = argv[0];
  for(int i = 0; i < argv.size(); i++){
          if(argv[i] == "-c")
      config.continuous = true;
    else if(argv[i] == "-t")
      config.testFile = argv[i+1];
    else if(argv[i] == "-d")
      config.debug = true;
    else if(argv[i] == "-l")
      config.language = argv[i+1];
  }
  //codeFile.cpp -> codeFile and c++
  config.codeFileName = config.codeFile;
  std::string fileName = config.codeFile;
  std::string fileExtention = "";
  int i = fileName.size()-1;
  while((i >= 0) && (fileName[i] != '.')){
    fileExtention += fileName[i];
    fileName.pop_back();
    i--;
  }
  if (fileName != ""){
    fileName.pop_back();
    config.codeFileName = fileName;
    fileExtention = reverse(fileExtention);
    if (config.language == "detect"){
      if (fileExtention == "cpp"){
        config.language = "c++";
      } else out::errorLog("Could not detect language with extention " + fileExtention);
    }
  }
  return config;
}