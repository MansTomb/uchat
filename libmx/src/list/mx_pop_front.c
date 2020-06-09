#include "libmx.h"

void mx_pop_front(t_list *list) {
    if (list && list->head) {
        t_list_node *temp = list->head;

        list->head = list->head->next;
        --list->size;
        free(temp);
        if (list->head == NULL)
            list->tail = NULL;
    }
}
