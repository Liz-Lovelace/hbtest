/* USAGE
habit codefile [-d] [-t "tests.txt"] [-colormode mono|bash] [-l cpp|out] 
  //-c           turn continuous debug mode on [default off]
  -t           changes default test file [default = tests.txt]
  -l           change debug language between cpp (c++ source file), out (linux executable) [default = autodetect]
  -d           debug hbtest itself
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "utils/hbcolor.h"
#include "utils/general-utils.h"
#include "utils/config-utils.h"
#include "utils/test-utils.h"
#include "utils/exec-utils.h"
#include "utils/output-utils.h"

int main(int argn, char** argCharv){
  Config config = readConfig(parseArguments(argn, argCharv));
  if (config.debug){col::shortTest(); config.printConfig();}
  std::string testStr = fileToStr(config.testFile);
  testStr = formatTestStr(testStr);
  std::vector<TestCase> testVec = parseTestStr(testStr, config.debug);
  for (long unsigned int i = 0; i < testVec.size(); i++){
    std::string testStdout = linuxExec(config.testCommand +" "+ testVec[i].getArgs(), testVec[i].getStdin());
    bool testResult = testVec[i].check(testStdout);
    if (testResult)
      std::cout << col::color("OK", col::green, col::black, 1) << " ";
    else
      std::cout << col::color("ERR", col::black, col::red, 1) << " ";
    std::cout << testVec[i].getName() << std::endl;
    if (!testResult && testStdout.size() < 10000){
      std::cout 
      << col::color("Command:", col::blue)                     << std::endl 
      << config.testCommand << " " << testVec[i].getArgs()     << std::endl
      << col::color("Stdin:", col::blue)                       << std::endl
      << testVec[i].getStdin()                                 << std::endl
      << col::color("Expected:", col::blue)                    << std::endl
      << testVec[i].getCorrect()                               << std::endl
      << col::color("Recieved:", col::blue)                    << std::endl
      <<testStdout                                             << std::endl << std::endl;
    }
  }
  return 0;
}
//TODO: Finish line-by-line test parsing, add stdin functionality.