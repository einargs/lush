%{
  #include "../generated/Parser.hh"

  #include <string>
  #include <stdio.h>

  int yyerror(FileNode** rootNode, yyscan_t scanner, const char* msg) {
    fprintf(stderr, "Error (line ): %s\n", msg);
    return 1;
  }
%}

/** options **/
%option outfile="generated/Lexer.cc" header-file="generated/Lexer.hh"

/*%option c++*/
/* noyywrap is used to redirect flex to different files */
%option noyywrap
%option never-interactive nounistd
%option reentrant
%option bison-bridge

/** tokens **/
/* special character tokens */
L_PAREN "("
R_PAREN ")"
L_BRACE "{"
R_BRACE "}"
L_BRACKET "["
R_BRACKET "]"
P_BRACKET "[]"

ELVIS "?:"
EQUALS "="
COLON ":"
QM "?"
PERIOD "."
BACKSLASH "\\"

/* token fragments */
IDENT_CHAR [a-zA-Z_]
DIGIT [0-9]

/* multi-char tokens */
LOWCASE_IDENT [a-z]{IDENT_CHAR}*
UPCASE_IDENT [A-Z]{IDENT_CHAR}*

LIT_INT {DIGIT}+
LIT_DEC {DIGIT}+"."{DIGIT}*
LIT_ATOM ":"{IDENT_CHAR}+
LIT_STR "\"".*"\""

WS [\t\n\r ]+

/* */
%%
"(" { return T_L_PAREN; }
")" { return T_R_PAREN; }
"{" { return T_L_BRACE; }
"}" { return T_R_BRACE; }
"[" { return T_L_BRACKET; }
"]" { return T_R_BRACKET; }
"[]" { return T_P_BRACKET; }

"?:" { return T_ELVIS; }
"=" { return T_EQUALS; }
":" { return T_COLON; }
"?" { return T_QM; }
"." { return T_PERIOD; }
"\\" { return T_BACKSLASH; }

{LOWCASE_IDENT} {
  yylval->text = new std::string(yytext, yyleng);
  return T_LOWCASE_IDENT;
}

{UPCASE_IDENT} {
  yylval->text = new std::string(yytext, yyleng);
  return T_UPCASE_IDENT;
}

{LIT_INT} {
  yylval->text = new std::string(yytext, yyleng);
  return T_LIT_INT;
}

{LIT_DEC} {
  yylval->text = new std::string(yytext, yyleng);
  return T_LIT_DEC;
}

{LIT_ATOM} {
  yylval->text = new std::string(yytext+1, yyleng-1);
  return T_LIT_ATOM;
}

{LIT_STR} {
  yylval->text = new std::string(yytext+1, yyleng-2);
  return T_LIT_STR;
}

{WS} { }
