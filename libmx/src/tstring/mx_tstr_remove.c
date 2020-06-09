#include "libmx.h"

void mx_tstr_remove(t_string *str, int start, int end) {
    if (start >= 0 && start < end) {
        int j = 0;

        for (int i = start; end != i; ++i) {
            for (j = start; str->str[j + 1]; ++j)
                str->str[j] = str->str[j + 1];
            str->str[j] = '\0';
        }
        str->size -= end - start;
    }
}
