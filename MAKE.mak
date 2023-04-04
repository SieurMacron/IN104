CC = gcc
CFLAGS = -Wall -Werror `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

INC = -I include
SRC_DIR = source

SRCS = $(SRC_DIR)/Entites_du_jeu.c main.c
OBJS = $(SRCS:.c=.o)

all: program

program: $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS) program