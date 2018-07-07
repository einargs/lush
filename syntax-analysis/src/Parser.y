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
  /* tokens */
  char* text;

  /* general types */
  LinkedList* expressionList; /* LinkedList<ExpressionNode*> */

  /* top level types */
  LushFile* lushFile;
  ExpressionNode* expression;

  /* expression types */
  LiteralNode* literal;
  FunctionCallNode* functionCall;
  VariableAccessNode* variableAccess;
  LambdaFunctionNode* lambdaFunction;
  ElvisNode* elvisExp;
  BlockNode* block;

  /* literal types */
  NumberNode* number;
  StringNode* string;
  AtomNode* atom;
  CompoundLiteralNode* compoundLiteral;

  /* compound literal types */
  TupleNode* tuple;
  ListNode* list;
  StructNode* structure; /* can't be named struct because that's a C keyword */

  /* struct types */
  LinkedList* structPairs; /* LinkedList<StructPairNode*> */
  StructPairNode* structPair;

  /* reference types */
  VariableRefNode* variableRef;
  TypeRefNode* typeRef;
  NamespaceNode* namespace;

  /* block types */
  DefinitionNode* definition;

  /* definition types */
  VariableDefNode* variableDef;
  FunctionDefNode* functionDef;
  TypeDefNode* typeDef;

  /* function def types */
  FunctionDefHeaderNode* functionDefHeader;
  LinkedList* functionParams; /* LinkedList<FunctionParamNode*> */
  FunctionParamNode* functionParam;

  /* type def types */
  TypeNode* type;

  /* type types */
  TupleTypeNode* tupleType;
  MaybeTypeNode* maybeType;
  ListTypeNode* listType;
  StructTypeNode* structType;

  /* tuple type types */
  LinkedList* tupleTypeMembers; /* LinkedList<TypeNode*> */

  /* struct type types */
  LinkedList* structTypePairs; /* LinkedList<StructTypePairNode*> */
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
%type <lushFile> lush_file
%type <expression> expression

/* expression types */
%type <literal> literal
%type <functionCall> function_call
%type <variableAccess> variable_access
%type <expression> parenthetical
%type <lambdaFunction> lambda_function
%type <elvisExp> elvis_expression
%type <block> block

/* literal types */
%type <number> number_literal
%type <string> string_literal
%type <atom> atom_literal
%type <compoundLiteral> compound_literal

/* compound literal types */
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
%type <variableRef> variable_ref
%type <typeRef> type_ref
%type <namespace> namespace

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
%type <type> type;

/* type types */
%type <tupleType> tuple_type
%type <maybeType> maybe_type

/* tuple type types */
%type <tupleTypeMembers> tuple_type_members

/* struct type types */
%type <structTypePairs> struct_type_pairs
%type <structTypePair> struct_type_pair

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
  | lambda_function
  | elvis_expression
  | block
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
  : struct_literal_pairs
  ;

struct_literal_pairs
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
  : T_BACKSLASH function_params T_EQUALS expression
  ;

elvis_expression
  : expression T_ELVIS expression
  ;

block
  : definition expression
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
  : tuple_type_members type
  | type
  ;

maybe_type
  : type T_QM
  ;

struct_type
  : struct_type_pairs
  ;

struct_type_pairs
  : struct_type struct_type_pair
  | struct_type_pair
  ;

struct_type_pair
  : struct_field_ident T_COLON type
  ;
