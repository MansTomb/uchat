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
        new->cp = NULL;
        new->pref = NULL;
        new->prof = NULL;
        new->cont = NULL;
    }
    return new;
}

void mx_info_create_css(t_info *new) {
    GdkDisplay *display;
    GdkScreen *screen;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    new->css = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(new->css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

t_info *mx_create_info() {
    t_info *new = malloc(sizeof(t_info));

    new->timer = NULL;
    new->json = NULL;
    new->wchange = 0;
    new->windows = create_windows();
    new->chat_list = mx_create_list();
    new->cl_data = (t_data *)malloc(sizeof(t_data));
    new->cl_data->contacts = mx_create_list();
    new->cl_data->profile = (t_profile_data *)malloc(sizeof(t_profile_data));
    new->cl_data->contacts = mx_create_list();
    return new;
}
