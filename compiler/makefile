SYNTAX_ANALYSIS_FILES = ../syntax-analysis/Lexer.c ../syntax-analysis/Parser.c
SRC_FILES = ./src/**.c
FILES = $(SYNTAX_ANALYSIS_FILES) $(SRC_FILES)

build: $(FILES)
	$(CC) $(CFLAGS) $(LLVM_CFLAGS) $(FILES) -o lush

../syntax-analysis/Parser.c:
	export PARSER_FLAGS = 
	$(MAKE) -C $(SYNTAX_ANALYSIS_DIR) Parser.c

../syntax-analysis/Lexer.c:
	export LEXER_FLAGS = --bison-bridge
	$(MAKE) -C $(SYNTAX_ANALYSIS_DIR) Lexer.c
