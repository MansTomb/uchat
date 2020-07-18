#include "client.h"

gboolean mx_validate_chars(char *text) {
    size_t len = strlen(text);

    for (size_t i = 0; i < len; ++i) {
        if (!isprint(text[i]) || text[i] == '\'' || text[i] == '"' ||
                     text[i] == '`')
            return false;
    }
    return true;
}
