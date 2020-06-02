CC = clang
NAME = client

client = ClientSrc/main.c
server = ServerSrc/main.c

INC = inc/uchat.h

WFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LFLAGS = -Iinc
CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -fsanitize=address -ftrapv

all: install

install:
	@$(CC) $(WFLAGS) $(client) -o client -I$(INC)
	@$(CC) $(WFLAGS) $(server) -o server -I$(INC)

clean:
	@rm -rf client server

reinstall:

uninstall: