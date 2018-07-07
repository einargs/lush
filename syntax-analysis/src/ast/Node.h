#ifndef __NODE_H__
#define __NODE_H__

typedef struct ExpressionNode ExpressionNode;
typedef struct LiteralNode LiteralNode;
typedef struct FunctionCallNode FunctionCallNode;
typedef struct VariableRefNode VariableRefNode;
typedef struct LambdaFunctionNode LambdaFunctionNode;
typedef struct ElvisNode ElvisNode;
typedef struct BlockNode BlockNode;
typedef struct NumberNode NumberNode;
typedef struct StringNode StringNode;
typedef struct AtomNode AtomNode;
typedef struct TupleNode TupleNode;
typedef struct ListNode ListNode;
typedef struct StructNode StructNode;
typedef struct StructPairNode StructPairNode;
typedef struct TypeRefNode TypeRefNode;
typedef struct NamespaceNode NamespaceNode;
typedef struct DefinitionNode DefinitionNode;
typedef struct VariableDefNode VariableDefNode;
typedef struct FunctionDefNode FunctionDefNode;
typedef struct TypeDefNode TypeDefNode;
typedef struct FunctionDefHeaderNode FunctionDefHeaderNode;
typedef struct FunctionParamNode FunctionParamNode;
typedef struct TypeNode TypeNode;
typedef struct TupleTypeNode TupleTypeNode;
typedef struct MaybeTypeNode MaybeTypeNode;
typedef struct ListTypeNode ListTypeNode;
typedef struct StructTypeNode StructTypeNode;
typedef struct StructTypePairNode StructTypePairNode;

typedef enum {
  Exp_literal;
  Exp_functionCall;
  Exp_variableRef;
  Exp_lambdaFunction;
  Exp_elvisExp;
  Exp_block;
} ExpressionSubType;

typedef union {
  LiteralNode* literal;
  FunctionCallNode* functionCall;
  VariableRefNode* variableRef;
  LambdaFunctionNode* lambdaFunction;
  ElvisNode* elvisExp;
  BlockNode* block;
} ExpressionSubNodeP;

typedef struct {
  ExpressionSubType subType;
  ExpressionSubNodeP subNode;
} ExpressionNode;

typedef enum {
  Lit_number;
  Lit_string;
  Lit_atom;
  Lit_tuple;
  Lit_list;
  Lit_structure;
} LiteralSubType;

typedef union {
  NumberNode* number;
  StringNode* string;
  AtomNode* atom;
  TupleNode* tuple;
  ListNode* list;
  StructNode* structure;
} LiteralSubNodeP;

typedef struct {
  LiteralSubType subType;
  LiteralSubNodeP subNode;
} LiteralNode;



#endif
