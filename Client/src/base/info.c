#include "client.h"

static t_windows *create_windows() {
    t_windows *new = malloc(sizeof(t_windows));
    
    if (new) {
        new->adm = NULL;
        new->log = NULL;
        new->reg = NULL;
        new->ms = NULL;
        new->rc = NULL;
        new->ac = NULL;
        new->cg = NULL;
        new->pref = NULL;
        new->prof = NULL;
        new->cont = NULL;
    }
    return new;
}

t_info *mx_create_info() {
    t_info *new = malloc(sizeof(t_info));
    // GdkDisplay *display;
    // GdkScreen *screen;

    // display = gdk_display_get_default();
    // screen = gdk_display_get_default_screen(display);
    new->timer = NULL;
    new->json = NULL;
    new->wchange = 0;
    new->windows = create_windows();
    new->chat_list = mx_create_list();
    new->css = gtk_css_provider_new();
    new->cl_data = (t_data *)malloc(sizeof(t_data));
    new->cl_data->profile = (t_profile_data *)malloc(sizeof(t_profile_data));
    // gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(new->css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    return new;
}
