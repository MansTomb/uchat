CC = clang
LIB = libmx.a
NAME = uchatclient

base = main socket info main_window windows_constructor

login = login callbacks errors constructor

register = register callbacks errors constructor

chat = chat callbacks errors constructor

chat_switcher = chat_switcher chat_switcher_hide callbacks errors constructor \
				chat_switcher_show

message = message callbacks errors constructor

main_menu = main_menu callbacks callbacks2 errors constructor

profile = profile callbacks errors constructor

contacts = contacts callbacks errors constructor

room_creation = room_creation callbacks errors constructor

mainchatscreen = main_chat_screen

utils = background_images buttons grids input_labels layouts css labels widget \
	dialog scrollable stack stack_switcher fixed frame box listbox


json-build-login = build

#$(addprefix parse/, $(parse))
RAW = $(addprefix base/, $(base)) 	\
	  $(addprefix login/, $(login)) $(addprefix utils/, $(utils)) \
	  $(addprefix json-build-login/, $(json-build-login)) \
	  $(addprefix register/, $(register)) $(addprefix chat/, $(chat)) \
	  $(addprefix message/, $(message)) \
	  $(addprefix chat_switcher/, $(chat_switcher)) \
	  $(addprefix main_chat_screen/, $(mainchatscreen)) \
	  $(addprefix main_menu/, $(main_menu)) \
	  $(addprefix profile/, $(profile)) $(addprefix contacts/, $(contacts)) \
	  $(addprefix room_creation/, $(room_creation))

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
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/base $(OBJ_DIR)/login \
				$(OBJ_DIR)/utils $(OBJ_DIR)/json-build-login \
				$(OBJ_DIR)/register $(OBJ_DIR)/chat $(OBJ_DIR)/message \
				$(OBJ_DIR)/chat_switcher $(OBJ_DIR)/main_chat_screen \
				$(OBJ_DIR)/main_menu $(OBJ_DIR)/profile $(OBJ_DIR)/contacts \
				$(OBJ_DIR)/room_creation
#$(OBJ_DIR)/parse
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
	@rm -rf $(OBJ_DIR)

reinstall: uninstall install