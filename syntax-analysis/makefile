GENERATED_LEXER_FILES = Lexer.c Lexer.h
GENERATED_PARSER_FILES = Parser.c Parser.h
GENERATED_FILES = $(GENERATED_LEXER_FILES) $(GENERATED_PARSER_FILES)

build-all: Lexer.c Parser.c

Lexer.c:
	flex $(LEXER_FLAGS) Lexer.l

Parser.c:
	bison $(PARSER_FLAGS) Parser.y

clean:
	rm $(GENERATED_FILES)

clean-Lexer:
	rm $(GENERATED_LEXER_FILES)

clean-Parser:
	rm $(GENERATED_PARSER_FILES)
