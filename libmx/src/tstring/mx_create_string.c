#include "libmx.h"

t_string *mx_create_string(char *str) {
    t_string *string = malloc(sizeof(t_string));
    
    if (str != NULL) {
        string->str = mx_strdup(str);
        string->size = strlen(str);
        string->cap = strlen(str) + 1;
    }
    else {
        string->str = malloc(sizeof(char) * MX_STRING_DEFAULT_SIZE);
        string->cap = MX_STRING_DEFAULT_SIZE;
        string->size = 0;
        memset(string->str, 0, MX_STRING_DEFAULT_SIZE);
    }

    return string;
}
