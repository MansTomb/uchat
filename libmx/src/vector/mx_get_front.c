#include "libmx.h"

void *mx_get_front(t_vector *v) {
    return v && v->size ? v->arr : NULL;
}
