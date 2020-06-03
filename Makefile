# CC = clang
# NAME = client

# client = ClientSrc/main.c ClientSrc/LoginSrc/login.c ClientSrc/Utils/background_images.c
# server = ServerSrc/main.c

# INC = /Users/abalabin/Desktop/Work/uchatGit/inc/client.h /Users/abalabin/Desktop/Work/uchatGit/inc/uchat.h

# WFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
# LFLAGS = -Iinc
# CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
# DFLAGS = -O0 -g3 -glldb -fsanitize=address -ftrapv
# PKGFLAGS = `pkg-config --cflags gtk+-3.0`
# PKGFLAGS2 = `pkg-config --libs gtk+-3.0`

# all: install

# install:
# 	@$(CC) $(WFLAGS) $(PKGFLAGS) $(client) -o client $(PKGFLAGS2) -I$(INC)
# 	@$(CC) $(WFLAGS) $(PKGFLAGS) $(server) -o server $(PKGFLAGS2) -I$(INC)

# clean:
# 	@rm -rf client server

# reinstall:

# uninstall:


CC = clang
LIB = libmx.a
NAME = client

base = main

loginsrc = login

utils = background_images

#$(addprefix parse/, $(parse))
RAW = $(addprefix base/, $(base)) 	\
	$(addprefix LoginSrc/, $(loginsrc)) $(addprefix Utils/, $(utils)) \

SRC_DIR = ./ClientSrc/
OBJ_DIR = ./obj/
LIB_DIR = ./libmx/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(RAW)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(RAW)))
LIB_PATH = $(addprefix $(LIB_DIR), $(LIB))

WFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LFLAGS = -Iinc -Ilibmx/inc
CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -fsanitize=address
PKGFLAGS = `pkg-config --cflags gtk+-3.0`
PKGFLAGS2 = `pkg-config --libs gtk+-3.0`

all: install

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/base $(OBJ_DIR)/LoginSrc \
				$(OBJ_DIR)/Utils
#$(OBJ_DIR)/parse
$(LIB):
	@make -sC $(LIB_DIR) -f Makefile install

# install
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -pipe $(WFLAGS) $(PKGFLAGS) $(LFLAGS) $(CFLAGS) -o $@ $(PKGFLAGS2) $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) -pipe $(WFLAGS) $(PKGFLAGS) $(LFLAGS) $(CFLAGS) $(OBJ) -o $(NAME) $(PKGFLAGS2) $(LIB_PATH)

# debug
# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@$(CC) -pipe $(WFLAGS) $(PKGFLAGS) $(LFLAGS) $(DFLAGS) -o $@ $(PKGFLAGS2) $<

# $(NAME): $(OBJ_DIR) $(OBJ)
# 	@$(CC) -pipe $(WFLAGS) $(PKGFLAGS) $(LFLAGS) $(DFLAGS) $(OBJ) -o $(NAME) $(PKGFLAGS2) $(LIB_PATH)

install: $(LIB) $(NAME)

clean:
	@make -sC $(LIB_DIR) -f Makefile clean
	@rm -rf $(OBJ_DIR)

uninstall:
	@make -sC $(LIB_DIR) -f Makefile uninstall
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)

reinstall: uninstall install