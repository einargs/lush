#ifndef SRC_AST_PRINT_VISITOR_HH
#define SRC_AST_PRINT_VISITOR_HH

#include <sstream>

class PrintVisitor: public NodeVisitor {
  int level;
  char* indentCharStr = "| ";
  std::ostringstream &strBuilder;

  PrintVisitor &nextLevel() {
    return *new PrintVisitor(level+1, strBuilder);
  }

  void indent() {
    for (int i = 0; i < level; i++) {
      strBuilder << indentCharStr;
    }
  }

public:
  PrintVisitor(int start, std::ostringstream &strStream):
    level(start), strBuilder(strStream) {}
  PrintVisitor():
    level(0), strBuilder(*new std::ostringstream()) {}
  ~PrintVisitor() {}

  PrintVisitor &visit(FileNode &node) {
    indent();
    strBuilder << "file";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionCallNode &node)  {
    indent();
    strBuilder << "function_call";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(NamespaceNode &node)  {
    indent();
    strBuilder << "namespace (" << node.getIdent() << ")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(VariableRefNode &node)  {
    indent();
    strBuilder << "variable_ref (" << node.getLocalIdent() << ")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(LambdaFunctionNode &node)  {
    indent();
    strBuilder << "lambda_function";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ElvisNode &node)  {
    indent();
    strBuilder << "elvis";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(BlockNode &node)  {
    indent();
    strBuilder << "block";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(NumberNode &node)  {
    indent();
    strBuilder << "number";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StringNode &node)  {
    indent();
    strBuilder << "string";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(AtomNode &node)  {
    indent();
    strBuilder << "atom";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TupleNode &node)  {
    indent();
    strBuilder << "tuple";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ListNode &node)  {
    indent();
    strBuilder << "list";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructNode &node)  {
    indent();
    strBuilder << "struct";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructPairNode &node)  {
    indent();
    strBuilder << "struct_pair";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(VariableDefNode &node)  {
    indent();
    strBuilder << "variable_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionDefNode &node)  {
    indent();
    strBuilder << "function_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TypeDefNode &node)  {
    indent();
    strBuilder << "type_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionDefHeaderNode &node)  {
    indent();
    strBuilder << "function_def_header";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionParamNode &node)  {
    indent();
    strBuilder << "function_param";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TypeRefNode &node)  {
    indent();
    strBuilder << "type_ref ("<<node.getLocalIdent()<<")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TupleTypeNode &node)  {
    indent();
    strBuilder << "tuple_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(MaybeTypeNode &node)  {
    indent();
    strBuilder << "maybe_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ListTypeNode &node)  {
    indent();
    strBuilder << "list_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructTypeNode &node)  {
    indent();
    strBuilder << "struct_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructTypePairNode &node)  {
    indent();
    strBuilder << "struct_type_pair";
    strBuilder << "\n";
    return nextLevel();
  }

  std::string to_string() {
    return strBuilder.str();
  }
};

#endif
