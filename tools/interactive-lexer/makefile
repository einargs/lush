LEXER_FILES = ../../syntax-analysis/Lexer.c
FILES = $(LEXER_FILES) main.c

export LEXER_FLAGS = -I

build: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o interactive-lexer.build

../../syntax-analysis/Lexer.c: ../../syntax-analysis/Lexer.l
	$(MAKE) Lexer.c -C ../../syntax-analysis

clean:
	rm ./interactive-lexer.build
	$(MAKE) clean-Lexer -C ../../syntax-analysis
