#ifndef STASYAN_LEXER_HPP
#define STASYAN_LEXER_HPP

#include <cstddef>
#include <string>

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

const int INT_BASE = 0x100;
const int SPEC_BASE = 0x200;
const int KEY_BASE = 0x300;
enum TokenType{
  ZERO = 0,
  ID_TYPE = 1,
  ID_OBJECT,
  STRING,
  VARIABLE,
  ERROR,
  END,
  COMMENT,

  INTEGER = INT_BASE,

  OPEN_BRACK = SPEC_BASE,
  CLOSE_BRACK,
  EQ_OP,
  MORE,
  MORE_EQ,
  LESS,
  LESS_EQ,
  EQ_EQ,
  NOT_EQ,
  MUL,
  DIV,
  ADD,
  SUB,

  IF = KEY_BASE,
  ELSE,
  FALSE,
  TRUE,
  LOOP,
  THEN,
  WHILE,
  NOT, 
  PRINT,
  PRINTLN,
};

class Token{
  TokenType token_type;
  std::string yytext;
  size_t int_val;

  public:
    Token();
    Token(TokenType type, const char* text, size_t val);
    ~Token();
    TokenType GetType();
    size_t GetVal();
    std::string& GetStr();

    Token& operator=(const Token&) = default;
};

// Я не знаю, зачем я тут наследуюсь. Поначалу показалось, что надо будет, потом оказалось, что не надо, но уверен,
// будет надо на следующем этапе, если нет, уберу
class StasyaLexClass : public yyFlexLexer{
  private:
    size_t cur_loc;
    size_t cur_line;

  public:
    StasyaLexClass(): cur_loc(0), cur_line(1) {};
    ~StasyaLexClass() = default;
};

#endif