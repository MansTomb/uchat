#pragma once

#if defined(__APPLE__)
#include <malloc/malloc.h>
#define MX_MALLOC_SIZE(x) malloc_size(x)
#elif defined(_WIN64) || defined(_WIN32)
#include <malloc.h>
#define MX_MALLOC_SIZE(x) _msize(x)
#elif defined(__linux__)
#include <malloc.h>
#define MX_MALLOC_SIZE(x) malloc_usable_size(x)
#endif

#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "macroses.h"

#include "list.h"
#include "tree.h"
#include "vector.h"
#include "tstring.h"
#include "json.h"
#include "json-builder.h"

/*
 * file
 */

int64_t mx_get_file_length(const char *filename);
char *mx_file_to_str(const char *file);
int64_t mx_read_line(char **lineptr, char delim, const int fd);

/*
 * memory
 */

void *mx_memdup(const void *src, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);

/*
 * print
 */

void mx_print_strarr(const char **arr, const char *delim, const int fd);
void mx_print_unicode(wchar_t c, const int fd);

void mx_printchar(char c, const int fd);
void mx_printnum(int64_t n, const int fd);
void mx_printstr(const char *s, const int fd);
void mx_printstrlen(const char *s, size_t len, const int fd);
void mx_printunum(uint64_t n, const int fd);

/*
 * string
 */

int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);

char *mx_del_extra_spaces(const char *str);
void mx_del_strarr(char ***arr);

int mx_get_char_index(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);

char *mx_lltoa_s(int64_t nbr, char *str, int len);
char *mx_lltoa(int64_t number);

char *mx_replace_substr(const char *str, const char *sub, const char *replace);
void mx_str_reverse(char *s);

void mx_strdel(char **str);
char *mx_strdup(const char *str);

char *mx_strjoin(const char *s1, const char *s2);
char *mx_strndup(const char *str, size_t n);

char *mx_strnew(const int size, char c);
char **mx_strsplit(const char *s, char c);
char *mx_strtrim(const char *str);

char *mx_ulltoa_s(uint64_t nbr, char *str, int len);
char *mx_ulltoa(uint64_t number);
char *mx_ulltoh_s(uint64_t nbr, char *str, int len);
char *mx_ulltoh(uint64_t nbr);

/*
 * utils
 */

uint64_t mx_factorial(uint64_t n);
void mx_foreach(void *arr, size_t size, size_t bytes, void (*f)(void *));

bool mx_isprime(uint64_t num);
int mx_numlen(int64_t num, uint32_t base);

uint64_t mx_sigma(uint64_t n);
int mx_sum_digits(uint64_t num);

void mx_swap(void *restrict v1, void *restrict v2, size_t size);
int mx_unumlen(uint64_t nbr, uint32_t base);
