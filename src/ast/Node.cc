#include "Node.hh"

void FileNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  rootExpression.accept(nuVisitor);
}

void FunctionCallNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  functionExp.accept(nuVisitor);
  for (ExpressionNode *argument : arguments) {
    argument->accept(nuVisitor);
  }
}

void NamespaceNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  if (parentNamespace != nullptr) {
    parentNamespace->accept(visitor);
  }
}

void VariableRefNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  refNamespace.accept(nuVisitor);
}

void LambdaFunctionNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  expression.accept(nuVisitor);
  for (FunctionParamNode *param : params) {
    param->accept(nuVisitor);
  }
}

void ElvisNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  expressionA.accept(nuVisitor);
  expressionB.accept(nuVisitor);
}

void BlockNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  definition.accept(nuVisitor);
  expression.accept(nuVisitor);
}

void NumberNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
}

void StringNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
}

void AtomNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
}

void TupleNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  for (ExpressionNode *exp : expressionList) {
    exp->accept(nuVisitor);
  }
}

void ListNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  for (ExpressionNode *exp : expressionList) {
    exp->accept(nuVisitor);
  }
}

void StructNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  for (StructPairNode *pair : structPairList) {
    pair->accept(nuVisitor);
  }
}

void StructPairNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  expression.accept(nuVisitor);
}

void VariableDefNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  variableRef.accept(nuVisitor);
  variableType.accept(nuVisitor);
  expression.accept(nuVisitor);
}

void FunctionDefNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  header.accept(nuVisitor);
  for (FunctionParamNode *param : params) {
    param->accept(nuVisitor);
  }
  expression.accept(nuVisitor);
}

void TypeDefNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  typeRef.accept(nuVisitor);
  typeVal.accept(nuVisitor);
}

void FunctionDefHeaderNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  variableRef.accept(nuVisitor);
  variableType.accept(nuVisitor);
}

void FunctionParamNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  paramType.accept(nuVisitor);
}

void TypeRefNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  refNamespace.accept(nuVisitor);
}

void TupleTypeNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  for (TypeNode *mem : typeMembers) {
    mem->accept(nuVisitor);
  }
}

void MaybeTypeNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  baseType.accept(nuVisitor);
}

void ListTypeNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  baseType.accept(nuVisitor);
}

void StructTypeNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  for (StructTypePairNode *pair : typePairs) {
    pair->accept(nuVisitor);
  }
}

void StructTypePairNode::accept(NodeVisitor &visitor) {
  NodeVisitor &nuVisitor = visitor.visit(*this);
  type.accept(nuVisitor);
}
