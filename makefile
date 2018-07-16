TEMP_CFLAGS = -Wno-unused-private-field

export CC = clang++-6.0
export CFLAGS = -g -O3 -fcxx-exceptions $(TEMP_CFLAGS)
export LLVM_CFLAGS = `llvm-config-6.0 --cxxflags --ldflags --system-libs --libs core`

LEXER_FILE = src/Lexer.l
PARSER_FILE = src/Parser.y

GENERATED_DIR = generated
GENERATED_SRC_FILES = generated/Lexer.cc generated/Parser.cc

SRC_FILES = src/*.cc src/ast/*.cc

FILES = $(SRC_FILES) $(GENERATED_SRC_FILES)

build: $(FILES)
	$(CC) $(CFLAGS) $(LLVM_CFLAGS) $(FILES) -o build/lush

generated/Lexer.cc: $(LEXER_FILE)
	flex $(LEXER_FILE)

generated/Parser.cc: $(PARSER_FILE)
	bison $(PARSER_FILE)

clean:
	rm $(GENERATED_DIR)/*
