#include "libmx.h"

void mx_push_back(t_list *list, void *data) {
    t_list_node *node = NULL;

    if (list && (node = mx_create_node(data, list->tail, NULL))) {
        if (list->tail)
            list->tail = list->tail->next = node;
        else
            list->head = list->tail = node;
        ++list->size;
    }
}
