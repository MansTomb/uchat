#include "libmx.h"

void mx_delete_list(t_list *list) {
    if (list) {
        mx_clear_list(list);
        if (MX_MALLOC_SIZE(list))
            free(list);
    }
}
