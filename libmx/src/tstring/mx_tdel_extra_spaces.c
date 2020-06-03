#include "libmx.h"

void mx_tdel_extra_spaces(t_string *str) {
    for (size_t i = 0; i < str->size; ++i) {
        if (isspace(str->str[i])) {
            while (isspace(str->str[i + 1]))
                mx_tstr_remove(str, i + 1, i + 2);
            str->str[i] = ' ';
        }
    }
}
