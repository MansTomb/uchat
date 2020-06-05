#include "client.h"

t_background_image *mx_background_image_constructor(GtkWidget *window, char *image_path) {
    t_background_image *new = malloc(sizeof(t_background_image));

    if (new != NULL) {
        new->window = window;
        new->pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 1280, 720, FALSE, NULL);
        new->image = gtk_image_new_from_pixbuf(new->pixbuf);
    }
    return new;
}

void mx_background_image_show(GtkWidget *layout, t_background_image *image) {
    gtk_layout_put(GTK_LAYOUT(layout), image->image, 0, 0);
}

void mx_background_image_delete(t_background_image *back_image) {
    gtk_widget_destroy(back_image->image);
    g_object_unref(back_image->pixbuf);
    free(back_image);
}
