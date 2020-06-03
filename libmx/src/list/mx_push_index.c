#include "libmx.h"

void mx_push_index(t_list *list, void *data, size_t index) {
    if (list) {
        if (index == 0)
            mx_push_front(list, data);
        else if (index == list->size)
            mx_push_back(list, data);
        else if (index < list->size) {
            t_list_node *prev_node = list->head;
            t_list_node *new_node = NULL;

            for (size_t pos = 0; ++pos < index; prev_node = prev_node->next);
            if ((new_node = mx_create_node(data, prev_node, prev_node->next)))
                prev_node->next = new_node, new_node->next->prev = new_node;
        }
    }
}
