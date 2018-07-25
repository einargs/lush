%{
  #include "../generated/Parser.hh"
  #include "../generated/Lexer.hh"
  #include "../src/ast/Node.hh"
  #include <string>

  int yyerror(FileNode** rootNode, yyscan_t scanner, const char* msg);
  #define YYDEBUG 1
%}

%output "generated/Parser.cc"
%defines "generated/Parser.hh"

/*%skeleton "lalr1.cc"*/
%require "3.0.5"

/* see:
https://www.gnu.org/software/bison/manual/html_node/LR-Table-Construction.html
for more information about `%define lr.type ielr`. */
%define lr.type ielr

/* This causes bison to split when it encounters ambiguity. See the docs:
https://www.gnu.org/software/bison/manual/bison.html#GLR-Parsers */
%glr-parser
%verbose
%define parse.error verbose /* vebose errors during development. */
%define api.pure /* define a reentrant parser */
%define parse.trace
%lex-param { yyscan_t scanner }
%parse-param { FileNode** rootNode }
%parse-param { yyscan_t scanner }

%code requires {
  #include "../src/ast/Node.hh"
  #include <forward_list>
  #include <string>

  #ifndef YY_TYPEDEF_YY_SCANNER_T
  #define YY_TYPEDEF_YY_SCANNER_T
  typedef void* yyscan_t;
  #endif
}

%union {
  /* token values */
  std::string* text;

  /* general types */
  std::forward_list<ExpressionNode*>* expressionList;

  /* top level types */
  FileNode* file;
  ExpressionNode* expression;

  /* expression types */
  LiteralNode* literal;
  FunctionCallNode* functionCall;
  VariableRefNode* variableRef;
  LambdaFunctionNode* lambdaFunction;
  ElvisNode* elvisExp;
  BlockNode* block;

  /* literal types */
  NumberNode* number;
  StringNode* string;
  AtomNode* atom;
  /* compound literal types */
  TupleNode* tuple;
  ListNode* list;
  StructNode* structure; /* can't be named struct because that's a C keyword */

  /* struct types */
  std::forward_list<StructPairNode*>* structPairs;
  StructPairNode* structPair;

  /* variable ref types */
  NamespaceNode* refNamespace;

  /* block types */
  DefinitionNode* definition;

  /* definition types */
  VariableDefNode* variableDef;
  FunctionDefNode* functionDef;
  TypeDefNode* typeDef;

  /* function def types */
  FunctionDefHeaderNode* functionDefHeader;
  std::forward_list<FunctionParamNode*>* functionParams;
  FunctionParamNode* functionParam;

  /* type def types */
  TypeNode* type;

  /* type types */
  TypeRefNode* typeRef;
  TupleTypeNode* tupleType;
  MaybeTypeNode* maybeType;
  ListTypeNode* listType;
  StructTypeNode* structType;

  /* tuple type types */
  std::forward_list<TypeNode*>* tupleTypeMembers;

  /* struct type types */
  std::forward_list<StructTypePairNode*>* structTypePairs;
  StructTypePairNode* structTypePair;
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

/** non-terminal types **/
%type <file> file
%type <expression> expression
%type <expression> function_call_arg_exp

/* expression types */
%type <literal> literal
%type <functionCall> function_call
%type <variableRef> variable_ref
%type <expression> parenthetical
%type <lambdaFunction> lambda_function
%type <elvisExp> elvis_expression
%type <block> block

/* literal types */
%type <number> number_literal
%type <string> string_literal
%type <atom> atom_literal
%type <tuple> tuple_literal
%type <list> list_literal
%type <structure> struct_literal

/* tuple literal types */
%type <expressionList> tuple_literal_members

/* list literal types */
%type <expressionList> list_literal_members

/* struct literal types */
%type <structPairs> struct_literal_pairs
%type <structPair> struct_literal_pair
%type <text> struct_field_ident

/* function call types */
%type <expressionList> function_call_args
%type <expression> function_call_arg

/* reference types */
%type <typeRef> type_ref
%type <refNamespace> namespace

/* block types */
%type <definition> definition

/* definition types */
%type <variableDef> variable_def
%type <functionDef> function_def
%type <typeDef> type_def

/* function def types */
%type <functionDefHeader> function_def_header
%type <functionParams> function_params
%type <functionParam> function_param
%type <text> function_param_name

/* type def types */
%type <type> type

/* type types */
%type <tupleType> tuple_type
%type <maybeType> maybe_type
%type <listType> list_type
%type <structType> struct_type

/* tuple type types */
%type <tupleTypeMembers> tuple_type_members

/* struct type types */
%type <structTypePairs> struct_type_pairs
%type <structTypePair> struct_type_pair

/*look into %prec and %dprec more */

%printer { fprintf (yyoutput, "%s", $$->getLocalIdent().c_str()); } variable_ref;
%printer { fprintf (yyoutput, "%s", $$->getLocalIdent().c_str()); } type_ref;
%printer { fprintf (yyoutput, "%s", $$->c_str()); } T_UPCASE_IDENT;
%printer { fprintf (yyoutput, "%s", $$->c_str()); } T_LOWCASE_IDENT;

%start file

%precedence P_FUNC_ARG
%precedence P_VAR_REF
%precedence P_FUNC_CALL
%precedence P_TYPE_DEF
%precedence P_VAR_DEF
%precedence P_FUNC_DEF
%precedence P_BLOCK

%%

file
  : expression {
    *rootNode = new FileNode(*$1);
  }
  ;

function_call_arg_exp
  : literal { $$ = (ExpressionNode*) $1; }
  | variable_ref { $$ = (ExpressionNode*) $1; }
  | parenthetical { $$ = (ExpressionNode*) $1; }
  | lambda_function { $$ = (ExpressionNode*) $1; }
  | elvis_expression { $$ = (ExpressionNode*) $1; }
  ;

expression
  : literal { $$ = (ExpressionNode*) $1; }
  | block { $$ = (ExpressionNode*) $1; } %prec P_BLOCK
  | function_call { $$ = (ExpressionNode*) $1; } %prec P_FUNC_CALL
  | variable_ref { $$ = (ExpressionNode*) $1; } %prec P_VAR_REF
  | parenthetical { $$ = (ExpressionNode*) $1; }
  | lambda_function { $$ = (ExpressionNode*) $1; }
  | elvis_expression { $$ = (ExpressionNode*) $1; }
  ;

literal
  : number_literal { $$ = (LiteralNode*) $1; }
  | string_literal { $$ = (LiteralNode*) $1; }
  | atom_literal { $$ = (LiteralNode*) $1; }
  | tuple_literal { $$ = (LiteralNode*) $1; }
  | list_literal { $$ = (LiteralNode*) $1; }
  | struct_literal { $$ = (LiteralNode*) $1; }
  ;

number_literal
  : T_LIT_INT { $$ = new NumberNode(std::stod(*$1)); }
  | T_LIT_DEC { $$ = new NumberNode(std::stod(*$1)); }
  ;

string_literal
  : T_LIT_STR { $$ = new StringNode(*$1); }
  ;

atom_literal
  : T_LIT_ATOM { $$ = new AtomNode(*$1); }
  ;

tuple_literal
  : T_L_BRACE tuple_literal_members T_R_BRACE {
    $$ = new TupleNode(*$2);
  }
  | T_L_BRACE T_R_BRACE {
    $$ = new TupleNode();
  }
  ;

tuple_literal_members
  : tuple_literal_members expression {
    $1->push_front($2);
    $$ = $1;
  }
  | expression {
    $$ = new std::forward_list<ExpressionNode*>(1, $1);
  }
  ;

list_literal
  : T_L_BRACKET list_literal_members T_R_BRACKET {
    $$ = new ListNode(*$2);
  }
  | T_L_BRACKET T_R_BRACKET {
    $$ = new ListNode();
  }
  ;

list_literal_members
  : list_literal_members expression {
    $1->push_front($2);
    $$ = $1;
  }
  | expression {
    $$ = new std::forward_list<ExpressionNode*>(1, $1);
  }
  ;

struct_literal
  : struct_literal_pairs {
    $$ = new StructNode(*$1);
  }
  ;

struct_literal_pairs
  : struct_literal_pairs struct_literal_pair {
    $1->push_front($2); $$ = $1;
  }
  | struct_literal_pair {
    $$ = new std::forward_list<StructPairNode*>(1, $1);
  }
  ;

struct_literal_pair
  : struct_field_ident T_COLON expression {
    $$ = new StructPairNode(*$1, *$3);
  }
  ;

struct_field_ident
  : T_LOWCASE_IDENT {
    $$ = $1;
  }
  ;

function_call
  : variable_ref function_call_args {
    $$ = new FunctionCallNode(*$1, *$2);
  }
  ;

function_call_args
  : function_call_args function_call_arg {
    $1->push_front($2);
    $$ = $1;
  }
  | function_call_arg {
    $$ = new std::forward_list<ExpressionNode*>(1, $1);
  }
  ;

function_call_arg
  : function_call_arg_exp {
    $$ = $1;
  }
  ;

variable_ref
  : namespace T_PERIOD T_LOWCASE_IDENT {
    $$ = new VariableRefNode(*$1, *$3);
  }
  | T_LOWCASE_IDENT {
    $$ = new VariableRefNode(*$1);
  }
  ;

namespace
  : namespace T_PERIOD T_UPCASE_IDENT {
    $$ = new NamespaceNode(*$1, *$3);
  }
  | T_UPCASE_IDENT {
    $$ = new NamespaceNode(*$1);
  }
  ;

parenthetical
  : T_L_PAREN expression T_R_PAREN {
    $$ = $2;
  }
  ;

lambda_function
  : T_BACKSLASH function_params T_EQUALS expression {
    $$ = new LambdaFunctionNode(*$2, *$4);
  }
  ;

elvis_expression
  : expression T_ELVIS expression {
    $$ = new ElvisNode(*$1, *$3);
  }
  ;

block
  : definition expression {
    $$ = new BlockNode(*$1, *$2);
  }
  ;

definition
  : variable_def { $$ = (DefinitionNode*) $1; } %prec P_VAR_DEF
  | function_def { $$ = (DefinitionNode*) $1; } %prec P_FUNC_DEF
  | type_def { $$ = (DefinitionNode*) $1; } %prec P_TYPE_DEF
  ;

variable_def
  : variable_ref type T_EQUALS expression {
    $$ = new VariableDefNode(*$1, *$2, *$4);
  }
  ;

function_def
  : function_def_header function_params T_EQUALS expression {
    $$ = new FunctionDefNode(*$1, *$2, *$4);
  }
  ;

function_def_header
  : variable_ref type {
    $$ = new FunctionDefHeaderNode(*$1, *$2);
  }
  ;

function_params
  : function_params function_param {
    $1->push_front($2);
    $$ = $1;
  }
  | function_param {
    $$ = new std::forward_list<FunctionParamNode*>(1, $1);
  }
  ;

function_param
  : function_param_name type {
    $$ = new FunctionParamNode(*$1, *$2);
  }
  ;

function_param_name
  : T_LOWCASE_IDENT {
    $$ = $1;
  }
  ;

type_def
  : type_ref T_EQUALS type {
    $$ = new TypeDefNode(*$1, *$3);
  }
  ;

type
  : type_ref { $$ = (TypeNode*) $1; }
  | tuple_type { $$ = (TypeNode*) $1; }
  | maybe_type { $$ = (TypeNode*) $1; }
  | list_type { $$ = (TypeNode*) $1; }
  | struct_type { $$ = (TypeNode*) $1; }
  ;

type_ref
  : namespace T_PERIOD T_UPCASE_IDENT {
    $$ = new TypeRefNode(*$1, *$3);
  }
  | T_UPCASE_IDENT {
    $$ = new TypeRefNode(*$1);
  }
  ;

tuple_type
  : T_L_BRACE tuple_type_members T_R_BRACE {
    $$ = new TupleTypeNode(*$2);
  }
  | T_L_BRACE T_R_BRACE {
    $$ = new TupleTypeNode();
  }
  ;

tuple_type_members
  : tuple_type_members type {
    $1->push_front($2);
    $$ = $1;
  }
  | type {
    $$ = new std::forward_list<TypeNode*>(1, $1);
  }
  ;

maybe_type
  : type T_QM {
    $$ = new MaybeTypeNode(*$1);
  }
  ;

list_type
  : type T_P_BRACKET {
    $$ = new ListTypeNode(*$1);
  }

struct_type
  : struct_type_pairs {
    $$ = new StructTypeNode(*$1);
  }
  ;

struct_type_pairs
  : struct_type_pairs struct_type_pair {
    $1->push_front($2);
    $$ = $1;
  }
  | struct_type_pair {
    $$ = new std::forward_list<StructTypePairNode*>(1, $1);
  }
  ;

struct_type_pair
  : struct_field_ident T_COLON type {
    $$ = new StructTypePairNode(*$1, *$3);
  }
  ;
