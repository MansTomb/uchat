#include "libmx.h"

void mx_push_backward(t_vector *v, const void *item) {
    if (v && v->arr && item) {
        if (v->size == v->cap) {
            v->cap *= 2;
            v->arr = realloc(v->arr, v->bytes * v->cap);
        }
        memcpy(v->arr + (v->size * v->bytes), item, v->bytes);
        ++v->size;
    }
}
