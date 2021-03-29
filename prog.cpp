#include <iostream>
#include <string>

int main(int argc, char* argv[]){
  std::string argument = "";
  for(int i = 1; i < argc; i++){
    int ich = 0;
    while(argv[i][ich]){
      argument+=argv[i][ich];
      ich++;
    }
  }
  if (argument == "capital of great britan")
    std::cout << "London" << std::endl;
  else if (argument == "3+5")
    std::cout << "8" << std::endl;
  else if (argument == "9+10")
    std::cout << "21" << std::endl;
  else std::cout << std::stoi(argument) / 10 << std::endl;
  return 0;
}