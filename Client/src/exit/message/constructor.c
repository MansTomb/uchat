#include "client.h"

static void create_menu_items(t_message *message, GtkWidget *menu) {
    GtkWidget *items[3];

    items[0] = gtk_menu_item_new_with_label("Reply");
    items[1] = gtk_menu_item_new_with_label("Forward");
    items[2] = gtk_menu_item_new_with_label("Delete");

    gtk_menu_attach(GTK_MENU(menu), items[0], 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(menu), items[1], 0, 1, 1, 2);
    gtk_menu_attach(GTK_MENU(menu), items[2], 0, 1, 2, 3);

    gtk_widget_show(items[0]);
    gtk_widget_show(items[1]);
    gtk_widget_show(items[2]);

    MX_GSIG_CON(items[0], "activate", MX_CB(mx_callback_reply), message);
    MX_GSIG_CON(items[1], "activate", MX_CB(mx_callback_forward), message);
    MX_GSIG_CON(items[2], "activate", MX_CB(mx_callback_delete), message);
}

static GtkWidget *create_menu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    return menu;
}

static void set_prefernces(t_message *new, int msgheight) {
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(new->button));
    gtk_widget_set_size_request(new->button, 300, msgheight);
    gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(lable), PANGO_WRAP_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);
}

t_message *mx_message_construct(t_info *info, char *message, char *username) {
    t_message *new = malloc(sizeof(t_message));
    char *name_a_date = mx_strjoin("21:47 ", username);

    if (new) {
        new->icon = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_scale("./Resources/images/online.png", 40, 40, TRUE, NULL));
        new->button = mx_button_constuctor(message, "message_text");
        new->lable = mx_label_constructor("username_inmsg", name_a_date);
        new->frame = mx_fixed_constructor("message_container", 300, MX_MSGHEIGHT(message));
        new->menu = create_menu(info);
        new->info = info;

        create_menu_items(new, new->menu);
        
        set_prefernces(new, MX_MSGHEIGHT(message));

        MX_GSIG_CON(new->button, "button-press-event", MX_CB(mx_callback_menu_show), new);
        mx_fixed_put(new->frame, new->icon, 0, 0);
        mx_fixed_put(new->frame, new->lable, 50, 0);
        mx_fixed_put(new->frame, new->button, 10, 20);
    }
    return new;
}
