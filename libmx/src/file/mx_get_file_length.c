#include "libmx.h"

int64_t mx_get_file_length(const char *filename) {
    int stream = open(filename, 0);

    if (stream > -1) {
        int64_t length = 0;
        char buffer[1024];

        for (int64_t delta = 1; delta; delta -= length) {
            delta = length;
            length += read(stream, buffer, 1024);
        }
        close(stream);
        return length;
    }
    return -1;
}
