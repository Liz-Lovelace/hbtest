/* USAGE
hbtest codefile [-d] [-t "tests.txt"] [-colormode mono|bash] [-l cpp|out] 
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
  if (config.debug){ col::shortTest(); config.printConfig();}
  std::string testStr = fileToStr(config.testFile);
  testStr = formatTestStr(testStr);
  std::vector<TestCase> testVec = parseTestStr(testStr, config.debug);
  compile(config.codeFile, config.language, config.codeFileName);
  for (long unsigned int i = 0; i < testVec.size(); i++){
    std::string testResult = linuxExec("./add.out " + testVec[i].getArgs(), testVec[i].getStdin());
    std::cout << testVec[i].getName() << ": ";
    if (testVec[i].check(testResult))
      out::testSuccess(testVec[i].getStdin(), testResult);
    else
      out::testFailure(testVec[i].getStdin(), testResult);
    std::cout << std::endl;
  }
  return 0;
}
//TODO: Finish line-by-line test parsing, add stdin functionality.