#include "libmx.h"

void mx_treplace_substr(t_string *str, char *substr, char *replace) {
    if (substr && replace) {
        int pos = mx_get_substr_index(str->str, substr);

        for (; pos >= 0; pos = mx_get_substr_index(str->str, substr)) {
            if (pos >= 0) {
                mx_tstr_remove(str, pos, strlen(substr) + pos);
                mx_tstr_insert(str, pos, replace);
            }
        }
    }
}
