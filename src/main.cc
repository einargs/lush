#include "ast/Node.hh"
#include "ast/PrintVisitor.hh"
#include "../generated/Parser.hh"
#include "../generated/Lexer.hh"

#include <iostream>
#include <string>

int yyparse(FileNode** rootNode, yyscan_t scanner);

FileNode* getAst(const char* programText) {
  FileNode *rootNode;
  yyscan_t scanner;
  YY_BUFFER_STATE state;

  if (yylex_init(&scanner)) {
    return NULL;
  }
  //printf("yylex_init\n");

  state = yy_scan_string(programText, scanner);
  //printf("yy_scan_string\n");

  if (yyparse(&rootNode, scanner)) {
    return NULL;
  }
  //printf("yyparse\n");

  yy_delete_buffer(state, scanner);
  //printf("yy_delete_buffer\n");

  yylex_destroy(scanner);
  //printf("yylex_destroy\n");

  return rootNode;
}

int main() {
  std::string name;

  std::getline(std::cin, name, '\0');

  //printf("<input>\n%s\n</input>", name.c_str());

  FileNode* node = getAst(name.c_str());
  //printf("getAst\n");

  PrintVisitor printVisitor;
  node->accept(printVisitor);
  std::cout << printVisitor.to_string();

  return 0;
}
