#include "libmx.h"

void **mx_list_to_array(t_list *list) {
    t_list_node *node = list && list->size ? list->head : NULL;
    void **array = NULL;

    if (node && (array = (void **)malloc(sizeof(void *) * list->size)))
        for (size_t i = 0; node; ++i, node = node->next)
            array[i] = node->data;
    return array;
}
