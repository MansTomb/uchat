#include "client.h"

static void attach_layout(t_info *info, t_chat *chat) {
    mx_layout_put(info->layout, chat->stack, 300, 100);
    mx_layout_put(info->layout, chat->stack_controller, 300, 50);
    // mx_layout_put(info->layout, chat->, 300, 50);
}

// static t_background_image *msx_background_image_constructor(t_info *info,
//                                                     char *image_path, GtkWidget *layout) {
//     t_background_image *new = malloc(sizeof(t_background_image));

//     if (new != NULL) {
//         new->window = info->main_window;
//         new->pixbuf = gdk_pixbuf_new_from_file_at_scale(image_path, 1280, 720, FALSE, NULL);
//         new->image = gtk_image_new_from_pixbuf(new->pixbuf);
//         gtk_layout_put(GTK_LAYOUT(layout), new->image, 0, 0);
//     }
//     return new;
// }

t_chat *mx_chat_constructor(t_info *info) {
    t_chat *new = malloc(sizeof(t_chat));

    if (info) {};
    if (new) {
        new->scroll = mx_scrollable_constructor("scrollable", NULL, NULL);
        new->layout = mx_layout_constructor("chat_window", 880, 1020);
        new->stack = gtk_stack_new();
        new->stack_controller = gtk_stack_switcher_new();
        gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(new->stack_controller), GTK_STACK(new->stack));
        gtk_stack_add_titled(GTK_STACK(new->stack), new->scroll, "stack", "Chat");
        gtk_container_add(GTK_CONTAINER(new->scroll), new->layout);
        gtk_widget_set_size_request(new->scroll, 880, 520);
        // new->scroll = gtk_scrolled_window_new(NULL, NULL);
        // gtk_widget_set_hexpand(new->scroll, TRUE);
        // gtk_widget_set_vexpand(new->scroll, TRUE);
        // new->layout = mx_layout_constructor("chat_window", 1280, 720);
        // gtk_layout_put(GTK_LAYOUT(info->layout), new->layout, 0, 0);
        // gtk_layout_put(GTK_LAYOUT(new->layout), bt, 320, 320);
        // gtk_widget_set_name(new->scroll, "alo");
        // new->back_image = msx_background_image_constructor(info, BACKIMAGE_PATH, new->layout);   
        new->back_image = mx_background_image_constructor(info, BACKIMAGE_PATH);
        mx_css_from_file(info, "./Resources/css/chat.css");
        attach_layout(info, new);
    }
    return new;
}
