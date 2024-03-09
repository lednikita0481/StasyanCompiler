#ifndef STASYAN_FRONTEND_HPP
#define STASYAN_FRONTEND_HPP

#include "stasyan_lex.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class StasLangFrontend{
  StasyaLexClass* Lexer_;
  std::ifstream input_;
  std::vector<Token> Tokens;

  void Lexical_Error_Processing();
  
  public:
    StasLangFrontend(const char* file_name): Lexer_{new StasyaLexClass}, Tokens() {
      input_.open(file_name);
      if (!input_.is_open()){
        std::cout << "ERROR while oppening file " << file_name << std::endl;
      }

      Lexer_->switch_streams(input_, std::cout);
    };

    ~StasLangFrontend(){
      delete Lexer_;
      if (input_.is_open()) input_.close();
    };

    int Tokenise();
    void TokenSeqPrint();
};

#endif