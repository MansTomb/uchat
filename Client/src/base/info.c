#include "client.h"

t_info *create_info(GtkApplication *app) {
    t_info *new = malloc(sizeof(t_info));
    GdkDisplay *display;
    GdkScreen *screen;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    new->main_window = create_main_window(app);
    new->layout = mx_layout_constructor("main_layout", WIDTH, HEIGHT);
    gtk_container_add(GTK_CONTAINER(new->main_window), new->layout);
    new->back_image = mx_constructor_background_image(new->main_window, BACKIMAGE_PATH);
    new->css = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(new->css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    return new;
}
