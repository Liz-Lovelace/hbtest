#include "general-utils.h"
#include "test-utils.h"
#include <string>
#include <iostream>
#include <vector>

int main(){
  std::string testStr = fileToStr("tests.txt");
  testStr = formatTestStr(testStr);
  std::vector<TestCase> testVec = parseTestStr(testStr);
  for (long unsigned int i = 0; i < testVec.size(); i++)
    testVec[i].print();
  return 0;
}