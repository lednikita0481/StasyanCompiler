%option c++
%option nounput
%option noinput
%option noyywrap
%option yylineno
%s COMMENT_PR

%{
  using std::cout;
  using std::endl;

  #include "../include/Frontend/stasyan_lex.hpp"
%}

%%
"("                         {cout << "Special sym: " << yytext << endl; return TokenType::OPEN_BRACK;}
")"                         {cout << "Special sym: " << yytext << endl; return TokenType::CLOSE_BRACK;}
">"                         {cout << "Special sym: " << yytext << endl; return TokenType::MORE;}
">="                        {cout << "Special sym: " << yytext << endl; return TokenType::MORE_EQ;}
"<"                         {cout << "Special sym: " << yytext << endl; return TokenType::LESS;}
"<="                        {cout << "Special sym: " << yytext << endl; return TokenType::LESS_EQ;}
"="                         {cout << "Special sym: " << yytext << endl; return TokenType::EQ_OP;}
"=="                        {cout << "Special sym: " << yytext << endl; return TokenType::EQ_EQ;}
"!="                        {cout << "Special sym: " << yytext << endl; return TokenType::NOT_EQ;}
"*"                         {cout << "Special sym: " << yytext << endl; return TokenType::MUL;}
"/"                         {cout << "Special sym: " << yytext << endl; return TokenType::DIV;}
"+"                         {cout << "Special sym: " << yytext << endl; return TokenType::ADD;}
"-"                         {cout << "Special sym: " << yytext << endl; return TokenType::SUB;}

(?i:"if")                   {cout << "Key word: " << yytext << endl; return TokenType::IF;}
(?i:"else")                 {cout << "Key word: " << yytext << endl; return TokenType::ELSE;}
"f"(?i:"alse")              {cout << "Key word: " << yytext << endl; return TokenType::FALSE;}
"t"(?i:"rue")               {cout << "Key word: " << yytext << endl; return TokenType::TRUE;}
(?i:"loop")                 {cout << "Key word: " << yytext << endl; return TokenType::LOOP;}
(?i:"then")                 {cout << "Key word: " << yytext << endl; return TokenType::THEN;}
(?i:"while")                {cout << "Key word: " << yytext << endl; return TokenType::WHILE;}
(?i:"not")                  {cout << "Key word: " << yytext << endl; return TokenType::NOT;}
(?i:"print")                {cout << "Key word: " << yytext << endl; return TokenType::PRINT;}
(?i:"println")              {cout << "Key word: " << yytext << endl; return TokenType::PRINTLN;}



"\""[^(EOF|\0)]*[\"]+       {cout << "String: " << yytext << endl; return TokenType::STRING;}

[0-9]+                      {cout << "Integer: " << yytext << endl; return TokenType::INTEGER;}
[A-Z][a-zA-Z_0-9]*          {cout << "Identifier: type " << yytext << endl; return TokenType::ID_TYPE;}
[a-z][a-zA-Z_0-9]*          {cout << "Identifier: object " << yytext << endl; return TokenType::ID_OBJECT;}

[ \t\n\v]+                  {}

.                           {cout << "Дичь какая-то" << endl; return TokenType::ERROR;}

"--"[^\n]*\n                {cout << "Тут комменты" << endl;}

<INITIAL>"(...)"            {BEGIN(COMMENT_PR); cout << "Старт большого комментария" << endl; return TokenType::COMMENT;}
<COMMENT_PR>[^"(...)"]+     {/* eat */}
<COMMENT_PR>"(...)"         {BEGIN(INITIAL); cout << "Конец большого комментария" << endl; return TokenType::COMMENT;}

%%