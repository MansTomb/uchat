#include "libmx.h"

t_list_node *mx_get_index(t_list *list, size_t index) {
    if (list && list->head) {
        if (index == 0)
            return list->head;
        else if (index == list->size - 1)
            return list->tail;
        else if (index < list->size) {
            t_list_node *node = list->head->next;

            for (size_t pos = 1; pos < index; ++pos)
                node = node->next;
            return node;
        }
    }
    return NULL;
}
