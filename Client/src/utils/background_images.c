#include "client.h"

t_background_image *mx_background_image_constructor(t_info *info,
                                                    char *image_path) {
    t_background_image *new = malloc(sizeof(t_background_image));

    if (new != NULL) {
        new->window = info->main_window;
        new->pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 1280, 720, FALSE, NULL);
        new->image = gtk_image_new_from_pixbuf(new->pixbuf);
        gtk_layout_put(GTK_LAYOUT(info->layout), new->image, 0, 0);
    }
    return new;
}

void mx_background_image_show(t_background_image *backimg) {
    gtk_widget_show(backimg->image);
}

void mx_background_image_hide(t_background_image *backimg) {
    gtk_widget_hide(backimg->image);
}

void mx_background_image_delete(t_background_image *backimg) {
    gtk_widget_destroy(backimg->image);
    g_object_unref(backimg->pixbuf);
    free(backimg);
}
