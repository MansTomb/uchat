#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 && s2) {
        char *str = mx_strnew(strlen(s1) + strlen(s2), '\0');

        return str ? strcat(strcat(str, s1), s2) : NULL;
    }
    return (s1 || s2) ? (s1 ? mx_strdup(s1) : mx_strdup(s2)) : NULL;
}
