#include "libmx.h"

void mx_pop_index(t_list *list, size_t index) {
    if (list && list->head) {
        if (index == 0)
            mx_pop_front(list);
        else if (index == list->size - 1)
            mx_pop_back(list);
        else if (index < list->size) {
            t_list_node *del_node = NULL;
            t_list_node *prev_node = list->head;

            for (size_t pos = 0; ++pos < index; prev_node = prev_node->next);
            del_node = prev_node->next;
            prev_node->next = del_node->next;
            del_node->next->prev = prev_node;
            free(del_node);
            --list->size;
        }
    }
}
