#pragma once
#include "general-utils.h"

class TestCase{
private:
  std::string name;
  std::string args;
  std::string stdin;
  std::string correct;
public:
  TestCase(std::string _name = "noname", std::string _args = "", std::string _stdin = "", std::string _correct = ""){
    name = _name;
    args = _args;
    stdin = _stdin;
    correct = _correct;
  }
  
  std::string getName()    {return name;}
  std::string getArgs()    {return args;}
  std::string getStdin()   {return stdin;}
  std::string getCorrect() {return correct;}
  
  void setName(std::string val)    {name = val;}
  void setArgs(std::string val)    {args = val;}
  void setStdin(std::string val)   {stdin = val;}
  void setCorrect(std::string val) {correct = val;}

  bool check(std::string answer){return (answer == correct)||(answer == correct+'\n');}
  
  void print(){
  std::cout <<"test: "         << name     
            <<"args passed: "  << args    
            <<"stdin passed :" << stdin   
            <<"expected: "     << correct
            << std::endl;
  }
};

std::string formatTestStr(std::string testRaw, bool debug = false){
  // get rid of comments 
  for (int i = 0; i < testRaw.size(); i++){
    if(checkWord("//", testRaw, i)){
      int eraseL = i;
      int eraseR = i;
      while (testRaw[eraseR] != '\n'){
        eraseR++;
      }
      testRaw.erase(eraseL, eraseR-eraseL);
      i--;
    }
  }

  // get rid of spaces
  bool protection = false;
  for (int i = 0; i < testRaw.size(); i++){
    if(testRaw[i] == '"')  // so that the program doesn't mess with anything inside ";
      protection = !protection;
    if(!protection && testRaw[i] == ' '){
      testRaw.erase(i, 1);
      i--;
    }
  }
  if(protection) std::cout << "Protection isn't correct in test file";
  
  //format test
  for (int i = 1; i < testRaw.size(); i++){
    //remove all opening curly braces
    if (testRaw[i] == '{') {
      testRaw.erase(i, 1);
      i--;
    }
    //always have a newline before closing curly braces or quotes
    if (testRaw[i] == '}' && testRaw[i-1] != '\n'){
      testRaw.insert(i, "\n");
      i++;
    }
    if (testRaw[i] == '"'){ //"
      testRaw.insert(i+1, "\n");
      testRaw.insert(i, "\n");
      i+=2;
    }
  }
  
  // get rid of excess newlines
  for (int i = 0; i < testRaw.size(); i++){
    if(testRaw[i] == '\r'){
      testRaw.erase(i, 1);
      i--;
    }
    if(checkWord("\n\n", testRaw, i)){
      testRaw.erase(i, 1);
      i--;
    }
  }
  if (testRaw[0] == '\n') testRaw.erase(0,1);
  
  return testRaw;
}

std::vector<TestCase> parseTestStr(std::string testStr, bool debug = false){
  
  //make string into a vector of lines
  std::vector<std::string> testLines;
  std::string newLine = "";
  for (int i = 0; i < testStr.size(); i++){
    if (testStr[i] == '\n'){
      testLines.push_back(newLine);
      newLine = "";
      continue;
    }
    newLine += testStr[i];
  }
  
  // parse tests
  std::vector<TestCase> testVec;
  
  std::string processing = "name";
  std::string val = "";
  TestCase newCase;
  std::vector<std::string> keyVec;
  std::vector<std::string> valVec;/* finish
  if (ch == '}') {
    TestCase newCase(newName, newArgs, newStdin, newCorrect);
    newName = newArgs = newStdin = newCorrect = "";
    newCase.print();
    testVec.push_back(newCase);
    processing = "name";
    i++;
  }*/
  for (int i = 0; i < testLines.size(); i++){
    if (processing == "name"){
      newCase.setName(testLines[i]);
      processing = "key";
    } else if (processing == "key"){
      keyVec.push_back(testLines[i]);
      processing = "value";
    } else if (processing == "value"){
      //skip over first quote or finish reading value
      if (testLines[i][0] == '"' && val == ""){
        std::cout << "skipping quote on " << i << std::endl;
        continue;
      } else if(testLines[i][0] == '"' && val != ""){
        std::cout << "pushing back val = " << val << std::endl;
        valVec.push_back(val);
        val = "";
        processing = "key";
        continue;
      }
      std::cout << "adding line #" << i << ": "<< testLines[i] << "\n";
      std::cout << "val is now " << val << std::endl;
      val += testLines[i];
    }
  }
  
  if (debug) for (int i = 0; i < testLines.size(); i++) std::cout << i << ": " << testLines[i] << std::endl;
  if (debug) for (int i = 0; i < keyVec.size(); i++) std::cout << i << "key " << keyVec[i] << std::endl;
  if (debug) for (int i = 0; i < valVec.size(); i++) std::cout << i << "val " << valVec[i] << std::endl;
  return testVec;
}
