CODEGEN_FILES = codegen/codegen.c codegen/Context.c
LIB_FILES = lib/Map.c
AST_FILES = ast/Node.c
SYNTAX_ANALYSIS_FILES = syntax-analysis/Parser.c syntax-analysis/Lexer.c
ROOT_FILES = main.c

FILES = $(ROOT_FILES) $(SYNTAX_ANALYSIS_FILES) #$(CODEGEN_FILES) $(LIB_FILES) $(AST_FILES)
CC = clang-6.0
CFLAGS = -g -O3 `llvm-config-6.0 --cflags --ldflags --system-libs --libs core`

test: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o test

syntax-analysis/Lexer.c: syntax-analysis/Lexer.l
	flex syntax-analysis/Lexer.l

syntax-analysis/Parser.c: syntax-analysis/Parser.y syntax-analysis/Lexer.c
	bison syntax-analysis/Parser.y
