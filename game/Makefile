INCLUDE = ../include
LIB = ../lib
MODULES = ../modules


CC = gcc

OBJS = game.o $(MODULES)/interface.o $(MODULES)/state.o $(MODULES)/ADTVector.o $(MODULES)/Snake.o $(LIB)/libraylib.a
EXEC = game
CFLAGS = -Wall -g -I$(INCLUDE) 
LDFLAGS = -lm

include $(LIB)/libraylib.mk

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

$(LIB)/%.a:
	$(MAKE) -C $(LIB) $*.a
	
run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)

valgrind: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

