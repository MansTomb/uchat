#include "client.h"

void test() {
    printf("Nazal\n");
}

t_message *mx_message_construct(char *message, char *username) {
    t_message *new = malloc(sizeof(t_message));

    if (new) {
        new->event = gtk_event_box_new();
        new->layout = mx_fixed_constructor("messagebox", 860, 1);
        new->frame = mx_frame_constructor("messageframe", username, 860, 1);
        new->lable = mx_label_constructor("message_text", message);

        gtk_container_add(GTK_CONTAINER(new->frame), new->layout);
        gtk_container_add(GTK_CONTAINER(new->event), new->lable);

        gtk_widget_set_size_request(new->lable, 860, 1);
        gtk_label_set_line_wrap(GTK_LABEL(new->lable), TRUE);
        gtk_label_set_selectable(GTK_LABEL(new->lable), TRUE);
        gtk_label_set_max_width_chars(GTK_LABEL(new->lable), 100);


        gtk_widget_set_events(new->event, GDK_BUTTON_PRESS_MASK);
        g_signal_connect(G_OBJECT(new->event), "button-press-event", G_CALLBACK(test), NULL);
        mx_fixed_put(new->layout, new->event, 0, 0);
        gtk_widget_show(new->frame);
        gtk_widget_show(new->event);
        gtk_widget_show(new->lable);
        gtk_widget_show(new->layout);
    }
    return new;
}
