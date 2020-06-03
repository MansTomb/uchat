#include "libmx.h"

void mx_delete_str(t_string *str) {
    if (str) {
        if (MX_MALLOC_SIZE(str->str))
            mx_strdel(&str->str);
        if (MX_MALLOC_SIZE(str))
            free(str);
    }
}
