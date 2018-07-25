#ifndef SRC_AST_NODE_HH
#define SRC_AST_NODE_HH

#include "./NodeVisitor.hh"
class NodeVisitor;

#include <forward_list>
#include <string>

enum class NodeType {
  File,
  FunctionCall,
  Namespace,
  VariableRef,
  LambdaFunction,
  Elvis,
  Block,
  Number,
  String,
  Atom,
  Tuple,
  List,
  Struct,
  StructPair,
  VariableDef,
  FunctionDef,
  TypeDef,
  FunctionDefHeader,
  FunctionParam,
  TypeRef,
  TupleType,
  MaybeType,
  ListType,
  StructType,
  StructTypePair
};

// Forward declarations
class ExpressionNode;
class VariableRefNode;
class NamespaceNode;
class FunctionParamNode;
class DefinitionNode;
class StructPairNode;
class TypeNode;
class FunctionDefHeaderNode;
class TypeRefNode;
class StructTypePairNode;

// Abstract
class Node {
public:

  virtual void accept(NodeVisitor &visitor) = 0;
  virtual NodeType getType() = 0;
};

class FileNode: public Node {
  ExpressionNode &rootExpression;

public:
  NodeType getType() { return NodeType::File; }
  FileNode(ExpressionNode &root): rootExpression(root) {}
  ~FileNode() {}
  void accept(NodeVisitor &visitor);
};

// Abstract
class ExpressionNode: public Node {

};

// Abstract
class LiteralNode: public ExpressionNode {

};

class FunctionCallNode: public ExpressionNode {
  ExpressionNode &functionExp;
  std::forward_list<ExpressionNode*> &arguments;

public:
  NodeType getType() { return NodeType::FunctionCall; }
  FunctionCallNode(
    ExpressionNode &funcExp,
    std::forward_list<ExpressionNode*> &args
  ): functionExp(funcExp), arguments(args) {}
  ~FunctionCallNode() {}
  void accept(NodeVisitor &visitor);
};

class NamespaceNode: public Node {
  NamespaceNode *parentNamespace;
  std::string &ident;

public:
  NodeType getType() { return NodeType::Namespace; }
  NamespaceNode(NamespaceNode &parent, std::string &value):
    parentNamespace(&parent), ident(value) {}
  NamespaceNode(std::string &value):
    parentNamespace(nullptr), ident(value) {}
  NamespaceNode():
    parentNamespace(nullptr), ident(*new std::string("")) {}
  ~NamespaceNode() {}
  void accept(NodeVisitor &visitor);

  std::string &getIdent() {
    return ident;
  }
};

class VariableRefNode: public ExpressionNode {
  NamespaceNode &refNamespace;
  std::string &localIdent;

public:
  NodeType getType() { return NodeType::VariableRef; }
  VariableRefNode(NamespaceNode &refName, std::string &ident):
    refNamespace(refName), localIdent(ident) {}
  VariableRefNode(std::string &ident):
    refNamespace(*new NamespaceNode()), localIdent(ident) {}
  ~VariableRefNode() {}
  void accept(NodeVisitor &visitor);

  const std::string &getLocalIdent() {
    return localIdent;
  }
};

class LambdaFunctionNode: public ExpressionNode {
  std::forward_list<FunctionParamNode*> &params;
  ExpressionNode &expression;

public:
  NodeType getType() { return NodeType::LambdaFunction; }
  LambdaFunctionNode(
    std::forward_list<FunctionParamNode*> &paramList,
    ExpressionNode &exp
  ): params(paramList), expression(exp) {}
  ~LambdaFunctionNode() {}
  void accept(NodeVisitor &visitor);
};

class ElvisNode: public ExpressionNode {
  ExpressionNode &expressionA;
  ExpressionNode &expressionB;

public:
  NodeType getType() { return NodeType::Elvis; }
  ElvisNode(ExpressionNode &expA, ExpressionNode &expB):
    expressionA(expA), expressionB(expB) {}
  ~ElvisNode() {}
  void accept(NodeVisitor &visitor);
};

class BlockNode: public ExpressionNode {
  DefinitionNode &definition;
  ExpressionNode &expression;

public:
  NodeType getType() { return NodeType::Block; }
  BlockNode(DefinitionNode &def, ExpressionNode &exp):
    definition(def), expression(exp) {}
  ~BlockNode() {}
  void accept(NodeVisitor &visitor);
};

class NumberNode: public LiteralNode {
  double val;

public:
  NodeType getType() { return NodeType::Number; }
  NumberNode(const double value): val(value) {}
  ~NumberNode() {}
  void accept(NodeVisitor &visitor);
};

class StringNode: public LiteralNode {
  std::string &val;

public:
  NodeType getType() { return NodeType::String; }
  StringNode(std::string &value): val(value) {}
  ~StringNode() {}
  void accept(NodeVisitor &visitor);
};

class AtomNode: public LiteralNode {
  std::string &val;

public:
  NodeType getType() { return NodeType::Atom; }
  AtomNode(std::string &value): val(value) {}
  ~AtomNode() {}
  void accept(NodeVisitor &visitor);
};

class TupleNode: public LiteralNode {
  std::forward_list<ExpressionNode*> &expressionList;

public:
  NodeType getType() { return NodeType::Tuple; }
  TupleNode(std::forward_list<ExpressionNode*> &value):
    expressionList(value) {}
  TupleNode(): expressionList(*new std::forward_list<ExpressionNode*>()) {}
  ~TupleNode() {}
  void accept(NodeVisitor &visitor);
};

class ListNode: public LiteralNode {
  std::forward_list<ExpressionNode*> &expressionList;

public:
  NodeType getType() { return NodeType::List; }
  ListNode(std::forward_list<ExpressionNode*> &value):
    expressionList(value) {}
  ListNode(): expressionList(*new std::forward_list<ExpressionNode*>()) {}
  ~ListNode() {}
  void accept(NodeVisitor &visitor);
};

class StructNode: public LiteralNode {
  std::forward_list<StructPairNode*> &structPairList;

public:
  NodeType getType() { return NodeType::Struct; }
  StructNode(std::forward_list<StructPairNode*> &value):
    structPairList(value) {}
  ~StructNode() {}
  void accept(NodeVisitor &visitor);
};

class StructPairNode: public Node {
  std::string &ident;
  ExpressionNode &expression;

public:
  NodeType getType() { return NodeType::StructPair; }
  StructPairNode(std::string &identVal, ExpressionNode &expVal):
    ident(identVal), expression(expVal) {}
  ~StructPairNode() {}
  void accept(NodeVisitor &visitor);
};

// Abstract
class DefinitionNode: public Node {

};

class VariableDefNode: public DefinitionNode {
  VariableRefNode &variableRef;
  TypeNode &variableType;
  ExpressionNode &expression;

public:
  NodeType getType() { return NodeType::VariableDef; }
  VariableDefNode(
    VariableRefNode &varRef,
    TypeNode &varType,
    ExpressionNode &exp
  ):  variableRef(varRef),
      variableType(varType),
      expression(exp) {}
  ~VariableDefNode() {}
  void accept(NodeVisitor &visitor);
};

class FunctionDefNode: public DefinitionNode {
  FunctionDefHeaderNode &header;
  std::forward_list<FunctionParamNode*> &params;
  ExpressionNode &expression;

public:
  NodeType getType() { return NodeType::FunctionDef; }
  FunctionDefNode(
    FunctionDefHeaderNode &defHeader,
    std::forward_list<FunctionParamNode*> &paramList,
    ExpressionNode &exp
  ):  header(defHeader),
      params(paramList),
      expression(exp) {}
  ~FunctionDefNode() {}
  void accept(NodeVisitor &visitor);
};

class TypeDefNode: public DefinitionNode {
  TypeRefNode &typeRef;
  TypeNode &typeVal;

public:
  NodeType getType() { return NodeType::TypeDef; }
  TypeDefNode(TypeRefNode &tRef, TypeNode &typeNode):
    typeRef(tRef), typeVal(typeNode) {}
  ~TypeDefNode() {}
  void accept(NodeVisitor &visitor);
};

class FunctionDefHeaderNode: public Node {
  VariableRefNode &variableRef;
  TypeNode &variableType;

public:
  NodeType getType() { return NodeType::FunctionDefHeader; }
  FunctionDefHeaderNode(VariableRefNode &varRef, TypeNode &varType):
    variableRef(varRef), variableType(varType) {}
  ~FunctionDefHeaderNode() {}
  void accept(NodeVisitor &visitor);
};

class FunctionParamNode: public Node {
  std::string &name;
  TypeNode &paramType;

public:
  NodeType getType() { return NodeType::FunctionParam; }
  FunctionParamNode(std::string &paramName, TypeNode &parameterType):
    name(paramName), paramType(parameterType) {}
  ~FunctionParamNode() {}
  void accept(NodeVisitor &visitor);
};

// Abstract
class TypeNode: public Node {

};

class TypeRefNode: public TypeNode {
  NamespaceNode &refNamespace;
  std::string &localIdent;

public:
  NodeType getType() { return NodeType::TypeRef; }
  TypeRefNode(NamespaceNode &refName, std::string &ident):
    refNamespace(refName), localIdent(ident) {}
  TypeRefNode(std::string &ident):
    refNamespace(*new NamespaceNode()), localIdent(ident) {}
  ~TypeRefNode() {}
  void accept(NodeVisitor &visitor);

  std::string &getLocalIdent() {
    return localIdent;
  }
};

class TupleTypeNode: public TypeNode {
  std::forward_list<TypeNode*> &typeMembers;

public:
  NodeType getType() { return NodeType::TupleType; }
  TupleTypeNode(std::forward_list<TypeNode*> &members):
    typeMembers(members) {}
  TupleTypeNode(): typeMembers(*new std::forward_list<TypeNode*>()) {}
  ~TupleTypeNode() {}
  void accept(NodeVisitor &visitor);
};

class MaybeTypeNode: public TypeNode {
  TypeNode &baseType;

public:
  NodeType getType() { return NodeType::MaybeType; }
  MaybeTypeNode(TypeNode &typeArg): baseType(typeArg) {}
  ~MaybeTypeNode() {}
  void accept(NodeVisitor &visitor);
};

class ListTypeNode: public TypeNode {
  TypeNode &baseType;

public:
  NodeType getType() { return NodeType::ListType; }
  ListTypeNode(TypeNode &typeArg): baseType(typeArg) {}
  ~ListTypeNode() {}
  void accept(NodeVisitor &visitor);
};

class StructTypeNode: public TypeNode {
  std::forward_list<StructTypePairNode*> &typePairs;

public:
  NodeType getType() { return NodeType::StructType; }
  StructTypeNode(std::forward_list<StructTypePairNode*> &pairs):
    typePairs(pairs) {}
  ~StructTypeNode() {}

  void accept(NodeVisitor &visitor);
};

class StructTypePairNode: public Node {
  std::string &ident;
  TypeNode &type;

public:
  NodeType getType() { return NodeType::StructTypePair; }
  StructTypePairNode(std::string &identVal, TypeNode &typeVal):
    ident(identVal), type(typeVal) {}
  ~StructTypePairNode() {}
  void accept(NodeVisitor &visitor);
};

#endif
