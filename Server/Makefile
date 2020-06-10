CC = clang
LIB = libmx.a
NAME = uchat_server

base = main

sockets = create_and_init handle_incoming_data handle_new_connection          \
	handle_read_from_stdin init_2 loop_handler loop peer_receive_message      \
	peer_send_message shutdown signals 

utils = initialize_zero message_queue message peer

dirs = base sockets utils
FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = ../libmx/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -Iinc -I$(LIB_DIR)inc
CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address    \
	-fsanitize=undefined

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
PRINT = printf
MKDIR = mkdir -p
RM = /bin/rm -rf
TARGET = build

# checking about debugging in current project
DEBUG_OBJ = $(shell nm $(OBJ) 2> /dev/null | grep -m1 asan)
DEBUG_BIN = $(shell nm $(NAME) 2> /dev/null | grep -m1 asan)
DEBUG_LIB = $(shell nm $(LIB_PATH) 2> /dev/null | grep -m1 asan)

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

all: build

# recursion call this make with initialized variables
debug:
	@make TARGET=debug CFLAGS='$(DFLAGS)' -s install

build: check $(LIB) $(NAME)

# check debug level collision during this compilation
check:
ifeq ($(TARGET),build)
ifneq ($(findstring asan,$(DEBUG_LIB)),)
	@$(EXEC_LD) uninstall
	@$(RM) $(NAME)
endif
ifneq ($(or $(findstring asan,$(DEBUG_OBJ)), $(findstring asan,$(DEBUG_BIN))),)
	@$(RM) $(OBJ_DIR) $(NAME)
endif
else
ifeq ($(findstring asan,$(DEBUG_LIB)),)
	@$(EXEC_LD) uninstall
	@$(RM) $(NAME)
endif
ifeq ($(and $(findstring asan,$(DEBUG_OBJ)), $(findstring asan,$(DEBUG_BIN))),)
	@$(RM) $(OBJ_DIR) $(NAME)
endif
endif

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(LIB):
	@$(EXEC_LD) $(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) $(CFLAGS) $(PGKCONFIGFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(COMPILE) $(CFLAGS) $(PKGCONFIG) $(LIB_PATH) $(OBJ) -o $(NAME)
	@$(PRINT) "$K"

# silent mode without printing LOGO
install: check
	@$(EXEC_LD) $@
	@$(EXEC_IT) $(NAME)

clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

# silent rebuild project
reinstall: uninstall install

.PHONY: all build debug check clean install uninstall reinstall
