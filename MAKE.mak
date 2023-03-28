# Makefile for compiling and running a program with SDL2 library

# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -L./lib -lSDL2

# Source files and executable
SRC = main.c
OBJ = $(SRC:.c=.o)
EXEC = main

# Build rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning rule
clean:
	rm -f $(OBJ) $(EXEC)