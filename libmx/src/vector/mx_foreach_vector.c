#include "libmx.h"

void mx_foreach_vector(t_vector *v, void (*f)(void *)) {
    if (v && v->arr && v->size && f) {
        uint8_t *end = v->arr + v->size * v->bytes;

        for (uint8_t *i = v->arr; i < end; i += v->bytes)
            f(i);
    }
}
