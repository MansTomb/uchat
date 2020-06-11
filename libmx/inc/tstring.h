#pragma once

#define MX_STRING_DEFAULT_SIZE 16

typedef struct s_string {
    char *str;              // the str itself
    size_t cap;             // malloced memory to this string !!! NEVER CHANGE IT IN FUNCS
    size_t size;            // currest strlen
} t_string;

/*
 * creates base struct.
 * copies base struct and the string itself
 * deletes base struct
 */

// P.S If you give some str as parameter it initialize struct with same str(strdup) else if given NULL create str with default size
t_string *mx_create_string(char *str);
t_string *mx_copy_str(t_string *str);
void mx_delete_str(t_string *str);

/*
 * strcat which can realloc str by himself, so dont worry about segfault, also dont use standart strcat with this struct
 * removes chars in range. Example tstr_remove("privet", 1, 6) -> "p". rivet was deleted
 * insert chars(or char *) starting from some index
 */
void mx_tstrcat(t_string *dst, char *src);
void mx_tstr_remove(t_string *str, int start, int end);
void mx_tstr_insert(t_string *dst, size_t from, char *src);

/*
 * replaces all finded substring by replace str !!! DONT RETURN NEWSTR IT EDIT STR IN STRUCT
 * trim str in struct                           !!! DONT RETURN NEWSTR IT EDIT STR IN STRUCT
 * delete all extra spaces is str               !!! DONT RETURN NEWSTR IT EDIT STR IN STRUCT
 */
void mx_treplace_substr(t_string *str, char *substr, char *replace);
void mx_tstrtrim(t_string *str);
void mx_tdel_extra_spaces(t_string *str);
