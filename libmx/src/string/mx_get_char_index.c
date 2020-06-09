#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str) {
        for (int i = 0; str && str[i]; ++i)
            if (str[i] == c)
                return i;
        return -1;
    }
    return -2;
}
