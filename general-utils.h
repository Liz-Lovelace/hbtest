#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::string linuxExec(std::string cmd){
  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");
  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}

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
  for(int i = 0; i < word.size(); i++){
    if(str[i+n] != word[i]){
      return false;
    }
  }
  return true;
}

std::string fileToStr(std::string filename, bool debug = false){
  if(debug)std::cout << "Reading file \"" << filename << "\"..." << std::endl;
  std::ifstream file;
  file.open(filename, std::ios::in);
  std::string str = "";
  while(!file.eof()){
    char ch = file.get();
    str += ch;
  }
  file.close();
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
  return lines;
}