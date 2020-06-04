#include "uchat.h"

t_background_image *mx_constructor_background_image(GtkWidget *window, char *image_path) {
    t_background_image *new = malloc(sizeof(t_background_image));

    if (new != NULL) {
        new->window = window;
        new->pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 1280, 720, FALSE, NULL);
        new->image = gtk_image_new_from_pixbuf(new->pixbuf);
    }
    return new;
}

void mx_background_image_show(t_info *info) {
    gtk_layout_put(GTK_LAYOUT(info->layout), info->back_image->image, 0, 0);
    gtk_widget_show_all(info->back_image->window);
}

void mx_background_image_delete(t_background_image *back_image) {
    gtk_widget_destroy(back_image->image);
    gtk_widget_destroy(GTK_WIDGET(back_image->pixbuf));
}
