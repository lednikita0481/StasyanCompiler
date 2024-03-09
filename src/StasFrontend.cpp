#include "../include/Frontend/StasFrontend.hpp"
#include <cstring>
#include <iostream>

StasLangFrontend::StasLangFrontend(const char* file_name): Lexer_{new StasyaLexClass}, Tokens() {
  input_.open(file_name);
  if (!input_.is_open()){
    std::cout << "ERROR while oppening file " << file_name << std::endl;
  }

  Lexer_->switch_streams(input_, std::cout);
};

StasLangFrontend::~StasLangFrontend(){
  delete Lexer_;
  if (input_.is_open()) input_.close();
};


void StasLangFrontend::LexicalErrorProcessing(bool unclosed_comment = false){
  std::cout << "ERROR on line " << Lexer_->lineno() << ". ";

  if (unclosed_comment){
    std::cout << "You forgot to close the comment (...)" << std::endl;
    return;
  }

  const char* text_fault = Lexer_->YYText();

  if (!strcmp(".", text_fault)){
    std::cout << "May be you forgot to close long comment (...)" << std::endl;
    return;
  }

  std::cout << "Unknown mistake" << std::endl;
}

int StasLangFrontend::Tokenise(){
  TokenType type = TokenType::END;
  bool in_comment = false;

  while (type != TokenType::ERROR && type != TokenType::ZERO) {
    type = static_cast<TokenType>(Lexer_->yylex());

    if (type == TokenType::ERROR){
      LexicalErrorProcessing();
      return -1;
    }

    if (type == TokenType::COMMENT){
      in_comment = !in_comment;
      continue;
    }

    if (type == TokenType::ZERO) {
      if (!in_comment) return 0;
      
      LexicalErrorProcessing(true);
      return -1;
    }

    size_t integer = (type != TokenType::INTEGER)? 0 : std::stoi(Lexer_->YYText());
    Tokens.push_back(Token(type, Lexer_->YYText(), integer));
  }

  std::cout << "Reached unreachable" << std::endl;
  return -2;
}

static const char* enum_type_str(TokenType type){
  #define CASE_STR(type) \
    case(type):          \
      return #type

  switch (type) {
    CASE_STR(ZERO);
    CASE_STR(ID_TYPE);
    CASE_STR(ID_OBJECT);
    CASE_STR(STRING);
    CASE_STR(VARIABLE);
    CASE_STR(ERROR);
    CASE_STR(END);
    CASE_STR(INTEGER);
    CASE_STR(OPEN_BRACK);
    CASE_STR(CLOSE_BRACK);
    CASE_STR(EQ_OP);
    CASE_STR(MORE);
    CASE_STR(MORE_EQ);
    CASE_STR(LESS);
    CASE_STR(LESS_EQ);
    CASE_STR(EQ_EQ);
    CASE_STR(NOT_EQ);
    CASE_STR(MUL);
    CASE_STR(DIV);
    CASE_STR(ADD);
    CASE_STR(SUB);
    CASE_STR(IF);
    CASE_STR(ELSE);
    CASE_STR(FALSE);
    CASE_STR(TRUE);
    CASE_STR(LOOP);
    CASE_STR(THEN);
    CASE_STR(WHILE);
    CASE_STR(NOT);
    CASE_STR(PRINT);
    CASE_STR(PRINTLN);
    CASE_STR(COMMENT);
  };

  #undef CASE_STR
}


void StasLangFrontend::TokenSeqPrint(){
  for (int i = 0; i < Tokens.size(); i++){
    std::cout << "Token " << i << ", type: " << enum_type_str(Tokens[i].GetType());

    if (Tokens[i].GetType() == INTEGER) std::cout << ", int: " << Tokens[i].GetVal();

    if (Tokens[i].GetType() == STRING)    std::cout << ", str: "  << Tokens[i].GetStr();
    if (Tokens[i].GetType() == ID_TYPE)   std::cout << ", type: " << Tokens[i].GetStr();
    if (Tokens[i].GetType() == ID_OBJECT) std::cout << ", obj: "  << Tokens[i].GetStr();
    if (Tokens[i].GetType() == VARIABLE)  std::cout << ", var: "  << Tokens[i].GetStr();

    std::cout << std::endl;
  }
}