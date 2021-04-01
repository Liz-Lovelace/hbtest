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

#include "hbcolor.h"
#include "general-utils.h"
#include "config-utils.h"
#include "test-utils.h"
#include "exec-utils.h"

int main(int argn, char** argCharv){
  Config config = readConfig(parseArguments(argn, argCharv));
  if (config.debug){ col::shortTest(); config.printConfig();}
  std::string testStr = fileToStr(config.testFile);
  testStr = formatTestStr(testStr);
  std::vector<TestCase> testVec = parseTestStr(testStr, config.debug);
  if(compile(config.codeFile, config.language, config.codeFileName) != 0) return 1;
  return 0;
}
//TODO: Finish line-by-line test parsing, add stdin functionality.