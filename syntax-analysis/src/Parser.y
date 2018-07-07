%{
  #include "ast/Node.h"
  #include "Parser.h"
  #include "Lexer.h"
%}

%code requires {
  #ifndef YY_TYPEDEF_YY_SCANNER_T
  #define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
  #endif
}

%output "Parser.c"
%defines "Parser.h"

%define api.pure
%lex-param { yyscan_t scanner }
%parse-param { Node** node }
%parse-param { yyscan_t scanner }

%union {
  char* text;
}

/* special symbol token pairs */
%token T_L_PAREN T_R_PAREN
%token T_L_BRACE T_R_BRACE
%token T_L_BRACKET T_R_BRACKET T_P_BRACKET

/* special symbol token loners */
%token T_ELVIS T_EQUALS T_COLON T_QM T_PERIOD T_BACKSLASH

/* value tokens */
%token <text> T_LOWCASE_IDENT T_UPCASE_IDENT

%token <text> T_LIT_INT T_LIT_DEC T_LIT_ATOM T_LIT_STR


%start lush_file

%%

lush_file
  : expression
  ;

expression
  : literal
  | function_call
  | variable_access
  | parenthetical
  | block
  | lambda_function
  | elvis_expression
  ;

literal
  : number_literal
  | string_literal
  | atom_literal
  | compound_literal
  ;

number_literal
  : T_LIT_INT
  | T_LIT_DEC
  ;

string_literal
  : T_LIT_STR
  ;

atom_literal
  : T_LIT_ATOM
  ;

compound_literal
  : tuple_literal
  | list_literal
  | struct_literal
  ;

tuple_literal
  : T_L_BRACE tuple_literal_members T_R_BRACE
  | T_L_BRACE T_R_BRACE
  ;

tuple_literal_members
  : tuple_literal_members expression
  | expression
  ;

list_literal
  : T_L_BRACKET list_literal_members T_R_BRACKET
  | T_L_BRACKET T_R_BRACKET
  ;

list_literal_members
  : list_literal_members expression
  | expression
  ;

struct_literal
  : struct_literal struct_literal_pair
  | struct_literal_pair
  ;

struct_literal_pair
  : struct_field_ident T_COLON expression
  ;

struct_field_ident
  : T_LOWCASE_IDENT
  ;

function_call
  : variable_ref function_call_args
  ;

function_call_args
  : function_call_args function_call_arg
  | function_call_arg
  ;

function_call_arg
  : expression
  ;

variable_ref
  : namespace T_PERIOD T_LOWCASE_IDENT
  | T_LOWCASE_IDENT
  ;

type_ref
  : namespace T_PERIOD T_UPCASE_IDENT
  | T_UPCASE_IDENT
  ;

namespace
  : namespace PERIOD T_UPCASE_IDENT
  | T_UPCASE_IDENT
  ;

variable_access
  : variable_ref
  ;

parenthetical
  : T_L_PAREN expression T_R_PAREN
  ;

lambda_function
  : T_BACKSLASH lambda_function_args T_EQUALS expression
  ;

lambda_function_args
  : lambda_function_args lambda_function_arg
  | lambda_function_arg
  ;

lambda_function_arg
  : T_LOWCASE_IDENT
  ;

elvis_expression
  : expression T_ELVIS expression
  ;

definition
  : variable_def
  | function_def
  | type_def
  ;

variable_definition
  : variable_ref type T_EQUALS expression
  ;

function_def
  : function_def_header function_params T_EQUALS expression
  ;

function_def_header
  : variable_ref type
  ;

function_params
  : function_params function_param
  | function_param
  ;

function_param
  : function_param_name type

function_param_name
  : T_LOWCASE_IDENT
  ;

block
  : definition expression
  ;

type_def
  : type_ref T_EQUALS type
  ;

type
  | type_ref
  | compound_type
  ;

compound_type
  : tuple_type
  | maybe_type
  | list_type
  | struct_type
  ;

tuple_type
  : T_L_BRACE tuple_type_members T_R_BRACE
  | T_L_BRACE T_R_BRACE
  ;

tuple_type_members
  : tuple_type_members tuple_type
  | tuple_type
  ;

maybe_type
  : type T_QM
  ;

struct_type
  : struct_type struct_type_pair
  | struct_type_pair
  ;

struct_type_pair
  : struct_field_ident T_COLON type
  ;
