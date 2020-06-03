#include "libmx.h"

void mx_foreach_list(t_list *list, void (*f)(t_list_node *)) {
    t_list_node *node = f && list ? list->head : NULL;

    for (; node; node = node->next)
        f(node);
}
