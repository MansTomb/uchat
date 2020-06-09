#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int words = 0;

    if (str) {
        while (*str) {
            for (; *str && *str == c; ++str);
            if (*str && *str != c) {
                for (; *str && *str != c; ++str);
                ++words;
            }
        }
    }
    return str ? words : -1;
}
