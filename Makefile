SRC_DIR  = src
GEN_DIR  = generators
BIN_DIR  = bin
BIN_NAME = Stasyan
OBJ_DIR  = obj
CC       = clang++
LEX      = flex
OBJS     = main stasyan_flex StasFrontend


CFLAGS   = -Wall -g
LDFLAGS  = -g


mk_dir:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)
	

$(OBJS) :
	$(CC) $(CFLAGS) $(SRC_DIR)/$@.cpp -I$(GEN_DIR) -c -o $(OBJ_DIR)/$@.o

build :  mk_dir Stasyan-lexer.o $(OBJS)
	$(CC) $(LDFLAGS) $(OBJ_DIR)/*.o -o $(BIN_NAME)

Stasyan-lexer.cpp:
	mkdir -p $(GEN_DIR)
	$(LEX) -o $(GEN_DIR)/Stasyan-lexer.cpp $(GEN_DIR)/stasyan_flex.l

Stasyan-lexer.o: Stasyan-lexer.cpp
	$(CC) $(CFLAGS) $(GEN_DIR)/Stasyan-lexer.cpp -I$(GEN_DIR) -o $(OBJ_DIR)/Stasyan-lexer.o -c 
