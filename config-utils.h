#pragma once
#include <iostream>
#include <vector>

struct Config {
  bool continuous = false;
  bool debug = false;
  std::string testFile = "tests.txt";
  std::string colorMode = "bash";
  std::string language = "detect";
  std::string codeFile;
  std::string codeFileName;
  
  void printConfig(){
    std::cout << "continuous "      << continuous     
              << "test file "       << testFile       <<'\n'
              << "color mode "      << colorMode      
              << "tested file "     << codeFile       <<'\n'
              << "tested file name "<< codeFileName   
              << "language "        << language       <<'\n'
              << "debug mode "      << debug          <<'\n';
  }
};

Config readConfig(std::vector<std::string> argv){  
  if(argv.size() == 0) std::cout << "No arguments provided." << std::endl;
  Config config;
  config.codeFile = argv[0];
  for(int i = 0; i < argv.size(); i++){
          if(argv[i] == "-c")
      config.continuous = true;
    else if(argv[i] == "-t")
      config.testFile = argv[i+1];
    else if(argv[i] == "-d")
      config.debug = true;
    else if(argv[i] == "-colormode")
      config.colorMode = argv[i+1];
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
    if(config.language == "detect"){
      if (fileExtention == "cpp"){
        config.language = "c++";
      } else std::cout << "could not detect language with extention " << fileExtention;
    }
  }
  return config;
}