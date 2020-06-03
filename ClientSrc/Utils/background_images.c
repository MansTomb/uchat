#include "uchat.h"

t_background_image *mx_constructor_background_image(GtkWidget *window, char *image_path) {
    t_background_image *new = (t_background_image *)malloc(sizeof(t_background_image));

    if (new != NULL) {
        new->window = window;
        new->pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 1280, 720, FALSE, NULL);
        new->image = gtk_image_new_from_pixbuf(GDK_PIXBUF(new->pixbuf));
        new->layout = gtk_layout_new(NULL, NULL);
    }
    return new;
}

void mx_show_background_image(t_background_image *back_image) {
   gtk_container_add(GTK_CONTAINER (back_image->window), back_image->layout);
   gtk_layout_set_size(GTK_LAYOUT(back_image->layout), 1280, 720);
   gtk_layout_put(GTK_LAYOUT(back_image->layout), GTK_WIDGET(back_image->image), 0, 0);
   gtk_widget_show(GTK_WIDGET(back_image->layout));
}

void mx_delete_background_image(t_background_image *back_image) {
    gtk_widget_destroy(back_image->image);
    gtk_widget_destroy(back_image->layout);
    gtk_widget_destroy(back_image->pixbuf);
}
