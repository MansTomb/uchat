#include "libmx.h"

t_vector *mx_copy_vector(t_vector *copy) {
    t_vector *v = copy ? (t_vector *)malloc(sizeof(t_vector)) : NULL;

    if (v) {
        v->cap = copy->cap;
        v->size = copy->size;
        v->bytes = copy->bytes;
        v->arr = copy->arr ? mx_memdup(copy->arr, v->cap * v->bytes) : NULL;
    }
    return v;
}
