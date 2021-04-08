#pragma once
#include <iostream>
#include <string>
#include "output-utils.h"

std::string linuxExec(std::string cmd, std::string stdin = "", bool debug = false){
  if (debug) out::debugLog("Running command " + cmd +"...");
  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  if (stdin != "")
    cmd = "echo \"" + stdin + "\" | " + cmd;
  cmd.append(" 2>&1");
  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}
/*
std::string compileCpp(std::string inputFile, std::string outputFileName){
  std::string compilerFlags = "";
  compilerFlags += "-fdiagnostics-color=always ";
  std::string compilationResult = linuxExec("g++ "+compilerFlags+inputFile+" -o "+outputFileName+".out"); 
  return compilationResult;
}

int compile(std::string inputFile, std::string language, std::string outputFileName){
  if (language == "c++"){
    std::string compilationResult = compileCpp(inputFile, outputFileName);
    if (compilationResult == "")
      out::compilationSuccess();
    else
      out::compilationFailure(compilationResult);
    return 0;
  }
  else{
    return 10;
  }
}
*/