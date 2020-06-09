#include "libmx.h"

void *mx_end(t_vector *v) {
    return v && v->arr && v->size ? v->arr + (v->bytes * v->size) : NULL;
}
