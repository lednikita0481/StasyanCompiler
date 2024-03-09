#include <iostream>
#include <fstream>

#include "../include/Frontend/StasFrontend.hpp"

int main(const int argc, const char* argv[]){
  if (argc != 2){
    std::cout << "ERROR: Write input file as an argument" << std::endl;
    return 1;
  }

  StasLangFrontend Frontend(argv[1]);
  int res = Frontend.Tokenise();

  if (!res)
    Frontend.TokenSeqPrint();
}