CC = clang
LIB = libmx.a
NAME = uchatserver

base = main

sockets = create_and_init init_2 loop sockets loop_utils handle_new_connection \
		handle_incoming_data

utils = initialize_zero

#$(addprefix parse/, $(parse))
RAW = $(addprefix base/, $(base)) 	\
		$(addprefix sockets/, $(sockets)) $(addprefix utils/, $(utils)) \

SRC_DIR = ./src/
OBJ_DIR = ./obj/
LIB_DIR = ../libmx/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(RAW)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(RAW)))
LIB_PATH = $(addprefix $(LIB_DIR), $(LIB))

WFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LFLAGS = -I../inc -I../libmx/inc
CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -fsanitize=address
PKGCONFIG = `pkg-config --libs --cflags gtk+-3.0`
PGKCONFIGFLAGS = `pkg-config --cflags gtk+-3.0`

all: install

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/base \
			$(OBJ_DIR)/sockets $(OBJ_DIR)/utils

# $(LIB):
# 	@make -sC $(LIB_DIR) -f Makefile install

# install
# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(PGKCONFIGFLAGS) $(CFLAGS) -o $@ -c $<

# $(NAME): $(OBJ_DIR) $(OBJ)
# 	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(PKGCONFIG) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB_PATH)

# debug
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(PGKCONFIGFLAGS) $(DFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(PKGCONFIG) $(DFLAGS) $(OBJ) -o $(NAME) $(LIB_PATH)

install: $(NAME)

clean:
	@make -sC $(LIB_DIR) -f Makefile clean
	@rm -rf $(OBJ_DIR)

uninstall:
	@make -sC $(LIB_DIR) -f Makefile uninstall
	@rm -rf $(NAME)

reinstall: uninstall install