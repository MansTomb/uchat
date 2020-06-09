#include "libmx.h"

void mx_pop_backward(t_vector *v) {
    if (v && v->arr && v->size) {
        --v->size;
        if ((float)v->cap / v->size > 4 && v->cap > MX_VECTOR_DEFAULT_SIZE) {
            v->cap /= 2;
            v->arr = realloc(v->arr, v->bytes * v->cap);
        }
    }
}
