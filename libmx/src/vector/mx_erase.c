#include "libmx.h"

void mx_erase(t_vector *v, size_t pos) {
    if (v && v->size) {
        if (pos < v->size - 1)
            memmove(v->arr + pos, v->arr + pos + 1,
                    (v->size - pos - 1) * v->bytes);
        --v->size;
        if ((float)v->cap / v->size > 4 && v->cap > MX_VECTOR_DEFAULT_SIZE) {
            v->cap /= 2;
            v->arr = realloc(v->arr, v->bytes * v->cap);
        }
    }
}
