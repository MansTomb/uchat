#include "client.h"

// static void attach_layout(t_info *info, t_chat *chat) {
//     mx_layout_put(info->layout, chat->stack, 300, 100);
//     mx_layout_put(info->layout, chat->stack_controller, 300, 50);
//     // mx_layout_put(info->layout, chat->scroll, 300, 50);
// }

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

    if (new) {
        new->scroll = mx_scrollable_constructor("scrollable", 880, 520);
        new->layout = mx_layout_constructor("chat_window", 880, 520);
        new->box = mx_box_constructor("chat_box", 880, 1, GTK_ORIENTATION_VERTICAL);

        gtk_widget_set_vexpand(new->layout, TRUE);
        gtk_widget_set_vexpand(new->scroll, TRUE);

        mx_scrollable_container_add(new->scroll, new->box);
 
        mx_css_from_file(info, "./Resources/css/chat.css");
    }
    return new;
}
