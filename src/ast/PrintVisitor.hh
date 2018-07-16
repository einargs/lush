#ifndef SRC_AST_PRINT_VISITOR_HH
#define SRC_AST_PRINT_VISITOR_HH

#include <sstream>

class PrintVisitor: public NodeVisitor {
  int level;
  std::ostringstream &strBuilder;

  PrintVisitor &nextLevel() {
    return *new PrintVisitor(level+1, strBuilder);
  }

public:
  PrintVisitor(int start, std::ostringstream &strStream):
    level(start), strBuilder(strStream) {}
  PrintVisitor():
    level(0), strBuilder(*new std::ostringstream()) {}
  ~PrintVisitor() {}

  PrintVisitor &visit(FileNode &node) {
    strBuilder << std::string(level, '\t');
    strBuilder << "file";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionCallNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "function_call";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(NamespaceNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "namespace (" << node.getIdent() << ")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(VariableRefNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "variable_ref (" << node.getLocalIdent() << ")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(LambdaFunctionNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "lambda_function";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ElvisNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "elvis";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(BlockNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "block";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(NumberNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "number";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StringNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "string";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(AtomNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "atom";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TupleNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "tuple";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ListNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "list";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "struct";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructPairNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "struct_pair";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(VariableDefNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "variable_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionDefNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "function_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TypeDefNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "type_def";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionDefHeaderNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "function_def_header";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(FunctionParamNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "function_param";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TypeRefNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "type_ref ("<<node.getLocalIdent()<<")";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(TupleTypeNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "tuple_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(MaybeTypeNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "maybe_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(ListTypeNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "list_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructTypeNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "struct_type";
    strBuilder << "\n";
    return nextLevel();
  }

  PrintVisitor &visit(StructTypePairNode &node)  {
    strBuilder << std::string(level, '\t');
    strBuilder << "struct_type_pair";
    strBuilder << "\n";
    return nextLevel();
  }

  std::string to_string() {
    return strBuilder.str();
  }
};

#endif
