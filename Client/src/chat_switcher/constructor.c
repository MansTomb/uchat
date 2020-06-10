#include "client.h"

// t_switcher *mx_chat_switcher_constructor(t_info *info) {
//     t_switcher *new = malloc(sizeof(t_chat));

//     if (new) {
//         new->stack = mx_stack_constructor("chat_stack");
//         new->stack_controller = mx_stack_switcher_constructor("chat_switcher", new->stack);

//         mx_layout_put(info->layout, new->stack, 300, 100);
//         mx_layout_put(info->layout, new->stack_controller, 300, 50);
//         mx_css_from_file(info, "./Resources/css/chat_switcher.css");
//         gtk_widget_show(new->stack);
//         gtk_widget_show(new->stack_controller);
//     }
//     return new;
// }

t_chat_switcher *mx_chat_switcher_constructor(t_info *info) {
    t_chat_switcher *new = malloc(sizeof(t_chat));

    if (new) {
        new->box = mx_box_constructor("box_of_chat_buttons", 60, 40, GTK_ORIENTATION_VERTICAL);

        mx_layout_put(info->layout, new->box, 1180, 100);
        
        mx_css_from_file(info, "./Resources/css/chat_switcher.css");
    }
    return new;
}
