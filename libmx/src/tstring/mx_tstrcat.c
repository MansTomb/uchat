#include "libmx.h"

void mx_tstrcat(t_string *dst, char *src) {
    if (dst->cap > dst->size + strlen(src)) {
        strcat(dst->str, src);
        dst->size = strlen(dst->str);
    }
    else {
        dst->str = realloc(dst->str, dst->cap *= 2);
        mx_tstrcat(dst, src);
    }
}
