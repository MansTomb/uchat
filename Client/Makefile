CC = clang
LIB = libmx.a
NAME = uchat

base = main socket info close \
	client_receive_message_handler client_send_message_handler \
	receive_file send_file

handlers = read_non_requested_jsons handle_del_msg handle_edit_msg            \
	handle_send_msg

login = login validate callbacks json

register = register validate json

admin = admin

chat = chat interface callbacks get_json_chat_list_login callbacks_2          \
	json_send_msg_1 get_json_history

ban = callbacks ban

invite = callbacks invite

message = message callbacks interface edit_json delete_json

message_img = message_img callbacks interface

room_creation = room_creation validate callbacks json

change_pass = change_pass callbacks validate

main_chat_screen = main_screen

contacts = contacts callbacks json create_table get_json_list_contacts \
	save_json_groups del_cnt_json start_chat_json create_menus

profile = profile json callbacks

other_profile = other_profile

delete_profile = delete_profile callbacks json

preferences = preferences callbacks chg_pass_json

add_contact = add_contact callbacks add_json_user_to_contacts add_group

create_group = create_group callbacks

utils = css wait_for_json create_hash json_get_type dialog entry toggle       \
	set_vnotify find_something validate_chars

dirs = base login register admin add_contact chat create_group main_chat_screen \
	profile preferences contacts message message_img room_creation utils      \
	change_pass handlers delete_profile other_profile ban invite

FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = ../libmx/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

LFLAGS = -Iinc -I$(LIB_DIR)inc -I/usr/local/opt/openssl/include \
	-L/usr/local/opt/openssl/lib -lssl -lcrypto

CFLAGS = -Os -march=native -fomit-frame-pointer -flto

CFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address    \
	-fsanitize=undefined

PKGCONFIG = `pkg-config --libs --cflags gtk+-3.0`
PGKCONFIGFLAGS = `pkg-config --cflags gtk+-3.0`

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
PRINT = printf
MKDIR = mkdir -p
RM = /bin/rm -rf
TARGET = debug

R = \033[1;91m
G = \033[1;92m
Y = \033[1;93m
B = \033[1;94m
M = \033[1;95m
C = \033[1;96m
S = \033[38;5;45;1m
D = \033[0m
F = \033[5m
A = \033[A
K = \033[K

all: $(LIB) $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(LIB):
	@$(EXEC_LD)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) $(CFLAGS) $(PGKCONFIGFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(COMPILE) $(CFLAGS) $(PKGCONFIG) $(LIB_PATH) $(OBJ) -o $(NAME)
	@$(PRINT) "$K"

clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
