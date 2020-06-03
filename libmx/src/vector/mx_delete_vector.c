#include "libmx.h"

void mx_delete_vector(t_vector *v) {
    if (v) {
        if (MX_MALLOC_SIZE(v->arr))
            free(v->arr);
        if (MX_MALLOC_SIZE(v))
            free(v);
    }
}
