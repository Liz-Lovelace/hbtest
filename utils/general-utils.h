#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "output-utils.h"

std::string reverse(std::string str){
  char ch;
  for (int i = 0; i <= str.size()/2; i++){
    ch = str[i];
    str[i] = str[str.size()-i-1];
    str[str.size()-i] = ch;
  }
  return str;
}

std::vector<std::string> parseArguments(int argn, char** argCharv){
  std::vector<std::string> vec;
  for (int i = 1; i < argn; i++){
    int i2 = 0;
    std::string acc;
    while(argCharv[i][i2]){
      acc += argCharv[i][i2];
      i2++;
    }
    vec.push_back(acc);
  }
  return vec;
}

bool checkWord(std::string word, std::string str, int n){
  for(int i = 0; i < word.size(); i++)
    if(str[i+n] != word[i])
      return false;
  return true;
}

std::string fileToStr(std::string filename, bool debug = false){
  std::ifstream file;
  if(debug)out::debugLog("Opening file \"" + filename + "\"...");
  file.open(filename, std::ios::in);
  if(!file)
    out::errorLog("Failed to open file " + filename);
  if(debug)out::debugLog("Successfully opened  \"" + filename + "\".");
  std::string str = "";
  while(!file.eof()){
    char ch = file.get();
    str += ch;
  }
  file.close();
  if(debug)out::debugLog("Closed file \"" + filename + "\".");
  return str;
}

std::vector<std::string> strToLines(std::string str){
  std::vector<std::string> lines;
  std::string newLine = "";
  for (int i = 0; i < str.size(); i++){
    if (str[i] == '\n'){
      lines.push_back(newLine);
      newLine = "";
      continue;
    }
    newLine += str[i];
  }
  if (newLine != "")
    lines.push_back(newLine);
  return lines;
}