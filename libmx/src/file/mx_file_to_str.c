#include "libmx.h"

char *mx_file_to_str(const char *file) {
    char *string = NULL;
    int length = file ? mx_get_file_length(file) : 0;

    if (file && length > 0 && (string = malloc(length + 1))) {
        int stream = open(file, 0);

        read(stream, string, length);
        string[length] = '\0';
        close(stream);
    }
    return string;
}
