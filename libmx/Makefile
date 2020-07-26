CC = clang
NAME = libmx.a

file = get_file_length file_to_str read_line

json = cJSON

ALAC = ag_dec ag_enc alac_decoder alac_encoder ALACBitUtilities dp_dec dp_enc \
	matrix_dec matrix_enc

G72x = g723_24 g72x_test g72x g721 g723_16 g723_40

GSM610 = add code decode gsm_create gsm_decode gsm_destroy gsm_encode \
	gsm_option long_term lpc preprocess rpe short_term table

libsnddirs = ALAC G72x GSM610
libsndfiles = $(foreach dir, $(libsnddirs), $($(dir):%=$(dir)/%)) \
	dither aiff alac alaw au audio_detect avr broadcast caf cart chanmap \
	chunk command common double64 dwd dwvw file_io flac float32 g72x gsm610 \
	htk id3 ima_adpcm ima_oki_adpcm interleave ircam macos mat4 mat5 mpc2k \
	ms_adpcm nist ogg_opus ogg_pcm ogg_speex ogg_vorbis ogg paf pcm pvf raw \
	rf64 rx2 sd2 sds sndfile strings svx test_audio_detect \
	test_binheader_writef test_broadcast_var test_cart_var test_conversions \
	test_endswap test_file_io test_float test_ima_oki_adpcm test_log_printf \
	test_main test_strncpy_crlf txw ulaw voc vox_adpcm w64 wav wavlike \
	windows wve xi

libsnd = $(libsndfiles:%=libsnd/%)

list = clear_list create_list create_node delete_list foreach_list_reverse \
	foreach_list get_index list_to_array pop_back pop_front pop_index \
	push_back push_front push_index

memory = memdup memrchr

print = print_strarr print_unicode printchar printnum printstr printstrlen \
	printunum

string = count_substr count_words del_extra_spaces del_strarr get_char_index \
	get_substr_index lltoa_s lltoa replace_substr str_reverse strdel strdup \
	strjoin strjoin_free strndup strnew strsplit strtrim \
	ulltoa_s ulltoa ulltoh_s ulltoh itoa

utils = factorial foreach isprime numlen sigma sum_digits swap unumlen

dirs = file json list memory print string utils
FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/mx_%)) $(libsnd)

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-zero-length-array

LFLAGS = -Iinc
# -Isrc/libsnd/ALAC -Isrc/libsnd/G72x -Isrc/libsnd/GSM610
# -Isrc/libsnd/obj

# CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto

CFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address \
	-fsanitize=undefined

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
PRINT = printf
MKDIR = mkdir -p
AR = ar rcs
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
K = \033[K

all: $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir)) $(foreach dir, $(libsnddirs), $(dir:%=$@/libsnd/$(dir)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G ARCHIVING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(AR) $(NAME) $(OBJ)
	@$(PRINT) "$K"

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
