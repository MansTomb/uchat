#include "libmx.h"

void mx_foreach_vector_reverse(t_vector *v, void (*f)(void *)) {
    if (v && v->arr && v->size && f) {
        uint8_t *start = v->arr + (v->size - 1) * v->bytes;

        for (uint8_t *i = start; i >= v->arr; i -= v->bytes)
            f(i);
    }
}
