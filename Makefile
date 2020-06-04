CC = clang

client = Client/uchatclient
server = Server/uchatserver

LIB_DIR = ./libmx/
CLIENT_DIR = ./Client/
SERVER_DIR = ./Server/

all: install

install:
	@make -sC $(LIB_DIR) -f Makefile install
	@make -sC $(CLIENT_DIR) -f Makefile install
#@make -sC $(SERVER_DIR) -f Makefile install
	@mv $(client) .
#@mv $(server) .

clean:
	@rm -rf uchatclient uchatserver obj Client/obj

reinstall:

uninstall:
