SYNTAX_ANALYSIS_FILES = ../syntax-analysis/Lexer.c ../syntax-analysis/Parser.c
SRC_FILES = ./src/**.c
FILES = $(SYNTAX_ANALYSIS_FILES) $(SRC_FILES)

build: $(FILES)
	$(CC) $(CFLAGS) $(LLVM_CFLAGS) $(FILES) -o lush

../syntax-analysis/Parser.c:
	bison Parser.c

../syntax-analysis/Lexer.c:
	flex Lexer.c
