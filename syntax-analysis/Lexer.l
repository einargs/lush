%{
  #include "Parser.h"

  #include <stdio.h>
%}

/** options **/
%option outfile="Lexer.c" header-file="Lexer.h"

/* noyywrap is used to redirect flex to different files */
%option noyywrap
/* not sure what some of these do; they're from the example */
/*%option reentrant never-interactive nounistd
%option bison-bridge*/

/** tokens **/
/* special character tokens */
L_PAREN "("
R_PAREN ")"
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
LOWCASE_IDENT [A-Z]{IDENT_CHAR}+
UPCASE_IDENT [a-z]{IDENT_CHAR}+

LIT_INT {DIGIT}+
LIT_DEC {DIGIT}+ "." {DIGIT}*
LIT_ATOM ":" {IDENT_CHAR}+
LIT_STR "\"" .* "\""

WS [\t\n ]+

/* */
%%
{ELVIS} { printf("elvis"); }



{WS} {}
