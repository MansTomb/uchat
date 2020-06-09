#include "libmx.h"

t_vector *mx_create_vector(size_t size, size_t bytes) {
    t_vector *v = bytes > 0 ? (t_vector *)malloc(sizeof(t_vector)) : NULL;

    if (v) {
        size_t cap = MX_VECTOR_DEFAULT_SIZE;

        for (size_t max = SIZE_MAX / 16; cap < size && cap < max; cap *= 2);
        v->cap = cap;
        v->size = size;
        v->bytes = bytes;
        v->arr = malloc(bytes * cap);
    }
    return v;
}
