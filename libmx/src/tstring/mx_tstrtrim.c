#include "libmx.h"

void mx_tstrtrim(t_string *str) {
    while (isspace(*str->str))
        mx_tstr_remove(str, 0, 1);
    while (isspace(*(str->str + str->size - 1)))
        mx_tstr_remove(str, str->size - 1, str->size);
}
