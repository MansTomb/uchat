NAME = libmx.a
CC = clang

file = get_file_length file_to_str read_line

list = clear_list create_list create_node delete_list foreach_list_reverse    \
	foreach_list get_index list_to_array pop_back pop_front pop_index         \
	push_back push_front push_index

memory = memdup memrchr

print = print_strarr print_unicode printchar printnum printstr printstrlen    \
	printunum

string = count_substr count_words del_extra_spaces del_strarr get_char_index  \
	get_substr_index lltoa_s lltoa replace_substr str_reverse strdel strdup   \
	strjoin strndup strnew strsplit strtrim ulltoa_s ulltoa ulltoh_s ulltoh

tstring = copy_str create_string delete_str tdel_extra_spaces treplace_substr \
	tstr_insert tstr_remove tstrcat tstrtrim

tree = create_tree clear_tree delete_tree foreach_in foreach_post foreach_pre  \
	new_node

utils = factorial foreach isprime numlen sigma sum_digits swap unumlen

vector = assign_vector at clear_vector copy_vector create_vector              \
	delete_vector end erase foreach_vector foreach_vector_reverse get_back    \
	get_front insert pop_backward push_backward reverse_vector

json = json

RAW = $(addprefix file/mx_, $(file)) $(addprefix list/mx_, $(list))           \
	$(addprefix memory/mx_, $(memory)) $(addprefix print/mx_, $(print))       \
	$(addprefix string/mx_, $(string)) $(addprefix tree/mx_, $(tree))         \
	$(addprefix utils/mx_, $(utils)) $(addprefix vector/mx_, $(vector))       \
	$(addprefix tstring/mx_, $(tstring)) $(addprefix json/, $(json))

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(RAW)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(RAW)))

WFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LFLAGS = -Iinc
CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto
DFLAGS = -O0 -g3 -glldb -fsanitize=address

all: install

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/file $(OBJ_DIR)/list $(OBJ_DIR)/memory    \
	$(OBJ_DIR)/print $(OBJ_DIR)/string $(OBJ_DIR)/tree $(OBJ_DIR)/utils       \
	$(OBJ_DIR)/vector $(OBJ_DIR)/tstring $(OBJ_DIR)/json

# install
# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(CFLAGS) -o $@ -c $<

# debug
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -pipe $(WFLAGS) $(LFLAGS) $(DFLAGS) -o $@ -c $<

install: $(OBJ_DIR) $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)

uninstall:
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)

reinstall: uninstall install