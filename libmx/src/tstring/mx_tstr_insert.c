#include "libmx.h"

void mx_tstr_insert(t_string *dst, size_t from, char *src) {
    if (src && from >= 0 && from <= dst->size) {
        size_t len = strlen(src);

        if (dst->cap > dst->size + len) {
            for (size_t i = from; i - from < len; ++i) {
                for (size_t j = dst->size + len; j > i; --j)
                    dst->str[j] = dst->str[j - 1];
                dst->str[i] = src[i - from];
            }
        }
        else {
            dst->str = realloc(dst->str, dst->cap *= 2);
            mx_tstr_insert(dst, from, src);
        }
        dst->size = strlen(dst->str);
    }
}
