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

  void LexicalErrorProcessing(bool unclosed_comment);
  
  public:
    StasLangFrontend(const char* file_name);

    ~StasLangFrontend();

    int Tokenise();
    void TokenSeqPrint();

    StasLangFrontend& operator=(const StasLangFrontend&) = delete;
};

#endif