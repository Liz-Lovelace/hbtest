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

std::string compileCpp(std::string inputFile, std::string outputName){
  std::string compilerFlags = "";
  compilerFlags += "-fdiagnostics-color=always ";
  std::string compilationResult = linuxExec("g++ "+compilerFlags+inputFile+" -o "+outputName+".out"); 
  return compilationResult;
}

int compile(std::string inputFile, std::string language, std::string outputName){
  if (language == "c++"){
    std::string compilationResult = compileCpp(inputFile, outputName);
    if(compilationResult == ""){
      std::cout << col::color("Compilation success!", col::green, col::white) << std::endl;
      return 0;
    }
    else{
      std::cout << col::color("Compilation error!", col::black, col::red) << std::endl <<compilationResult;
      return 1;
    }
  }
  else{
    std::cout << col::color("Unknown lanugage " + language + ", terminating compilation!", col::red) << std::endl;
    return 10;
  }
}