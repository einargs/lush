#ifndef SRC_AST_NODE_VISITOR_HH
#define SRC_AST_NODE_VISITOR_HH

#include "./Node.hh"
class FileNode;
class FunctionCallNode;
class NamespaceNode;
class VariableRefNode;
class LambdaFunctionNode;
class ElvisNode;
class BlockNode;
class NumberNode;
class StringNode;
class AtomNode;
class TupleNode;
class ListNode;
class StructNode;
class StructPairNode;
class VariableDefNode;
class FunctionDefNode;
class TypeDefNode;
class FunctionDefHeaderNode;
class FunctionParamNode;
class TypeRefNode;
class TupleTypeNode;
class MaybeTypeNode;
class ListTypeNode;
class StructTypeNode;
class StructTypePairNode;

class NodeVisitor {
public:
  virtual NodeVisitor &visit(FileNode &node) = 0;
  virtual NodeVisitor &visit(FunctionCallNode &node) = 0;
  virtual NodeVisitor &visit(NamespaceNode &node) = 0;
  virtual NodeVisitor &visit(VariableRefNode &node) = 0;
  virtual NodeVisitor &visit(LambdaFunctionNode &node) = 0;
  virtual NodeVisitor &visit(ElvisNode &node) = 0;
  virtual NodeVisitor &visit(BlockNode &node) = 0;
  virtual NodeVisitor &visit(NumberNode &node) = 0;
  virtual NodeVisitor &visit(StringNode &node) = 0;
  virtual NodeVisitor &visit(AtomNode &node) = 0;
  virtual NodeVisitor &visit(TupleNode &node) = 0;
  virtual NodeVisitor &visit(ListNode &node) = 0;
  virtual NodeVisitor &visit(StructNode &node) = 0;
  virtual NodeVisitor &visit(StructPairNode &node) = 0;
  virtual NodeVisitor &visit(VariableDefNode &node) = 0;
  virtual NodeVisitor &visit(FunctionDefNode &node) = 0;
  virtual NodeVisitor &visit(TypeDefNode &node) = 0;
  virtual NodeVisitor &visit(FunctionDefHeaderNode &node) = 0;
  virtual NodeVisitor &visit(FunctionParamNode &node) = 0;
  virtual NodeVisitor &visit(TypeRefNode &node) = 0;
  virtual NodeVisitor &visit(TupleTypeNode &node) = 0;
  virtual NodeVisitor &visit(MaybeTypeNode &node) = 0;
  virtual NodeVisitor &visit(ListTypeNode &node) = 0;
  virtual NodeVisitor &visit(StructTypeNode &node) = 0;
  virtual NodeVisitor &visit(StructTypePairNode &node) = 0;
};

#endif
