#include "client.h"

GdkPixbuf *mx_get_image(char *filepath, int width, int height) {
    return gdk_pixbuf_new_from_file_at_scale(filepath, width, height, 1, NULL);
}
