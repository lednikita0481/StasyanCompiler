#include "../include/Frontend/stasyan_lex.hpp"
#include <cstddef>

Token::Token(): token_type(TokenType::ZERO), yytext("") {};
Token::Token(TokenType type, const char* text, size_t val = 0) : token_type(type), yytext(text), int_val(val) {};
Token::~Token() {};

TokenType Token::GetType() {return token_type;}
size_t Token::GetVal() {return int_val;}
std::string& Token::GetStr() {return yytext;}