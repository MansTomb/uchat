#include "libmx.h"

t_list *mx_create_list() {
    t_list *list = (t_list *)malloc(sizeof(t_list));

    if (list) {
        list->head = list->tail = NULL;;
        list->size = 0;
    }
    return list;
}
