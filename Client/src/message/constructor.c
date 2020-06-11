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

    g_signal_connect(items[0], "activate", G_CALLBACK(mx_callback_reply), message);
    g_signal_connect(items[1], "activate", G_CALLBACK(mx_callback_forward), message);
    g_signal_connect(items[2], "activate", G_CALLBACK(mx_callback_delete), message);
}

static GtkWidget *create_menu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    if(info) {};
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    return menu;
}

// static void label_settings(GtkWidget *lable, char *message) {
//     gtk_widget_set_size_request(lable, strlen(message) > 860 ? 860 : strlen(message), 1);
//     gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
//     gtk_label_set_selectable(GTK_LABEL(lable), TRUE);
//     gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
// }

t_message *mx_message_construct(t_info *info, char *message, char *username) {
    t_message *new = malloc(sizeof(t_message));
    GtkWidget *lable;

    if (new) {
        new->button = mx_button_constuctor(message, "message_text");
        new->lable = mx_label_constructor("username_inmsg", username);
        new->frame = mx_fixed_constructor("message_container", 300, MX_MSGHEIGHT(message));
        new->menu = create_menu(info);
        new->info = info;

        create_menu_items(new, new->menu);

        lable = gtk_bin_get_child(GTK_BIN(new->button));
        gtk_widget_set_size_request(new->button, 300, MX_MSGHEIGHT(message));
        gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(lable), PANGO_WRAP_CHAR);
        gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
        gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);
        
        g_signal_connect(new->button, "button-press-event", G_CALLBACK(mx_callback_menu_show), new);
        mx_fixed_put(new->frame, new->lable, 50, 0);
        mx_fixed_put(new->frame, new->button, 10, 20);
        // new->event = gtk_event_box_new();
        // new->layout = mx_fixed_constructor("messagebox", 840, 1);
        // new->frame = mx_frame_constructor("messageframe", username, 840, 1);
        // new->lable = mx_label_constructor("message_text", message);
        // new->menu = create_menu(info);
        // new->info = info;

        // gtk_widget_set_margin_start(new->frame, 10);
        // gtk_widget_set_margin_end(new->frame, 10);
        // gtk_widget_set_margin_top(new->frame, 5);
        // gtk_label_set_justify(GTK_LABEL(new->lable), GTK_JUSTIFY_LEFT);

        // create_menu_items(new, new->menu);

        // gtk_widget_set_vexpand(new->lable, TRUE);
        // gtk_widget_set_vexpand(new->frame, TRUE);

        // gtk_container_add(GTK_CONTAINER(new->frame), new->layout);
        // gtk_container_add(GTK_CONTAINER(new->event), new->lable);

        // label_settings(new->lable, message);

        // gtk_widget_set_events(new->event, GDK_BUTTON_PRESS_MASK);
        // g_signal_connect(G_OBJECT(new->event), "button-press-event", G_CALLBACK(mx_callback_menu_show), new);
        // mx_fixed_put(new->layout, new->event, 50, 0);
    }
    return new;
}
