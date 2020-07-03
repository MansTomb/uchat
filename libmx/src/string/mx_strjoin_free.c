#include "libmx.h"

char *mx_strjoin_free(const char *s1, const char *s2) {
    char *result;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        result = mx_strdup(s2);
    else if (!s2)
        result = mx_strdup(s1);
    else if ((result = malloc(strlen(s1) + strlen(s2) + 1))) {
        strcpy(result, s1);
        strcat(result, s2);
    }
    if (s1)
        mx_strdel((char **)&s1);
    return result;
}
