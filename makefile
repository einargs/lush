export CC = clang-6.0
export CFLAGS = -g -O3
export LLVM_CFLAGS = `llvm-config-6.0 --cflags --ldflags --system-libs --libs core`

export PROJ_DIR = `pwd`
export COMPILER_DIR = $(PROJ_DIR)/compiler
export SYNTAX_ANALYSIS_DIR = $(PROJ_DIR)/syntax-analysis
export TOOLS_DIR = $(PROJ_DIR)/tools
export INTERACTIVE_LEXER_DIR = $(TOOLS_DIR)/interactive-lexer

compiler:
	$(MAKE) -C $(COMPILER_DIR)

run-interactive-lexer: interactive-lexer
	$(INTERACTIVE_LEXER_DIR)/interactive-lexer.build

interactive-lexer:
	$(MAKE) -C $(INTERACTIVE_LEXER_DIR)
