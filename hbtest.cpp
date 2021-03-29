/* USAGE
hbtest codefile [-c] [-d] [-t "tests.txt"] [-colormode mono|bash] [-l cpp|out] 
  -c           turn continuous debug mode on [default off]
  -t           changes default test file [default = tests.txt]
  -colormode   change color mode between mono (no color manipulation), bash (linux terminal color) [default = bash]
  -l           change debug language between cpp (c++ source file), out (linux executable) [default = autodetect]
  -d           debug hbtest itself
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "hbcolor.h"
#include "general-utils.h"
#include "config-utils.h"
#include "test-utils.h"

int compile(Config config){
  std::string compilerFlags = "";
  if (config.colorMode == "bash")
    compilerFlags += "-fdiagnostics-color=always ";
  else
    compilerFlags += "-fdiagnostics-color=never ";
  std::string compilationResult = "Compiler did not run";
  if (config.language == "c++")  
    compilationResult = linuxExec("g++ " + compilerFlags +  config.codeFile 
                        + " -o " + config.codeFileName + ".out"); 
  else{
    std::cout << col::color("Please specify the code language with the -l flag", col::red) << std::endl;
    return 1;
  }
  if(compilationResult != ""){
    std::cout << col::color("Compilation failed", col::white, col::red, true) << std::endl << std::endl
              << compilationResult;
    return 1;
  } else {
    //TODO add compilation time
    std::cout << col::color("Done compiling", col::green, col::black, true) << " file " << config.codeFile << std::endl;
    return 0;
  }
}


int main(int argn, char** argCharv){
  Config config = readConfig(parseArguments(argn, argCharv));
  if (config.debug){ col::shortTest(); config.printConfig();}
  std::string testStr = fileToStr(config.testFile);
  testStr = formatTestStr(testStr);
  std::vector<TestCase> testVec = parseTestStr(testStr, config.debug);
  //compilation
  /*compile(config);
  for (int i = 0; i < testVec.size(); i++){
    std::string result = run("./"+config.codeFileName + ".out " + testVec[i].getArgs());
    if(testVec[i].check(result))
      std::cout << col::color("PASSED", col::green, col::black, 1); 
    else
      std::cout << col::color("FAILED", col::red, col::black, 1);
    std::cout << " " << testVec[i].getName();
    std::cout << std::endl; 
  }*/
  return 0;
}
//TODO: Finish line-by-line test parsing, add stdin functionality.