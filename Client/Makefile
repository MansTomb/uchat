CC = clang
LIB = libmx.a
NAME = uchat

base = main socket info main_window windows_constructor

login = login callbacks errors constructor

register = register callbacks errors constructor

chat = chat callbacks errors constructor

chat_switcher = chat_switcher callbacks errors constructor

message = message callbacks errors constructor

utils = background_images buttons grids input_labels layouts css labels       \
	widget dialog scrollable stack stack_switcher fixed frame box listbox

json =

dirs = base login register chat chat_switcher message utils json
FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = ../libmx/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -Iinc -I$(LIB_DIR)inc
CFLAGS = -Os -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address    \
	-fsanitize=undefined

PKGCONFIG = `pkg-config --libs --cflags gtk+-3.0`
PGKCONFIGFLAGS = `pkg-config --cflags gtk+-3.0`

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

all: debug

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

# silent installing
install: check
	@$(EXEC_LD) $@
	@$(EXEC_IT) $(NAME)

clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

# silent rebuilding
reinstall: uninstall install

.PHONY: all build debug check clean install uninstall reinstall
