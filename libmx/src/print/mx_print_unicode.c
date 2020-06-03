#include "libmx.h"

void mx_print_unicode(wchar_t c, const int fd) {
    char parts[5] = {0};

    if (c < 0x80) 
        parts[0] = c & 0x7F;
    else if (c < 0x0800) {
        parts[0] = (c >> 6 & 0x1F) | 0xC0;
        parts[1] = (c & 0x3F) | 0x80;
    }
    else if (c < 0x010000) {
        parts[0] = (c >> 12 & 0x0F) | 0xE0;
        parts[1] = (c >> 6 & 0x3F) | 0x80;
        parts[2] = (c & 0x3F) | 0x80;
    }
    else {
        parts[0] = (c >> 18 & 0x07) | 0xF0;
        parts[1] = (c >> 12 & 0x3F) | 0x80;
        parts[2] = (c >> 6 & 0x3F) | 0x80;
        parts[3] = (c & 0x3F) | 0x80;
    }
    write(fd, parts, strlen(parts));
}
