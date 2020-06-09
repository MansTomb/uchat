#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub,
                        const char *replace) {
    if (str && sub && replace) {
        int len1 = strlen(sub);
        int len2 = strlen(replace);
        int cnt = mx_count_substr(str, sub);

        if (cnt > 0) {
            char *result = mx_strnew(strlen(str) + (len2 - len1) * cnt, 0);

            for (int i = 0; *str; )
                if (*str == *sub && strncmp(str, sub, len1) == 0) {
                    strncpy(result + i, replace, len2);
                    str += len1;
                    i += len2;
                }
                else
                    result[i++] = *str++;
            return result;
        }
    }
    return str && sub && replace ? mx_strdup(str) : NULL;
}
