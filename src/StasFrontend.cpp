#include "../include/Frontend/StasFrontend.hpp"
#include <cstring>
#include <iostream>

void StasLangFrontend::Lexical_Error_Processing(){
  const char* text_fault = Lexer_->YYText();

  if (!strcmp(".", text_fault)){
    std::cout << "May be you forgot to close long comment (...)" << std::endl;
    return;
  }

  if (!strcmp("\"", text_fault)){
    std::cout << "May be you forgot to close string \"" << std::endl;
    return;
  }

  std::cout << "Unknown mistake" << std::endl;
}

int StasLangFrontend::Tokenise(){
  TokenType type = TokenType::END;
  while (type != TokenType::ERROR && type != TokenType::ZERO) {
    type = static_cast<TokenType>(Lexer_->yylex());

    if (type == TokenType::ERROR){
      std::cout << "ERROR on line " << Lexer_->lineno() << ". ";
      Lexical_Error_Processing();
      return -1;
    }

    if (type == TokenType::ZERO) return 0;

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
  };

  #undef CASE_STR
}


void StasLangFrontend::TokenSeqPrint(){
  for (int i = 0; i < Tokens.size(); i++){
    std::cout << "Token " << i << ", type: " << enum_type_str(Tokens[i].get_type());

    if (Tokens[i].get_type() == INTEGER) std::cout << ", int: " << Tokens[i].get_val();

    if (Tokens[i].get_type() == STRING)    std::cout << ", str: "  << Tokens[i].get_str();
    if (Tokens[i].get_type() == ID_TYPE)   std::cout << ", type: " << Tokens[i].get_str();
    if (Tokens[i].get_type() == ID_OBJECT) std::cout << ", obj: "  << Tokens[i].get_str();
    if (Tokens[i].get_type() == VARIABLE)  std::cout << ", var: "  << Tokens[i].get_str();

    std::cout << std::endl;
  }
}