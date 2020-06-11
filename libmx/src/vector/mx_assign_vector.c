#include "libmx.h"

void mx_assign_vector(t_vector *v, size_t count, const void *item) {
    if (v && count && item) {
        if (count > v->cap) {
            mx_clear_vector(v);
            for (size_t i = 0; i < count; ++i)
                mx_push_backward(v, item);
        }
        else {
            uint8_t *end = v->arr + count * v->bytes;

            for (uint8_t *i = v->arr; i < end; i += v->bytes)
                memcpy(i, item, v->bytes);
        }
    }
}
