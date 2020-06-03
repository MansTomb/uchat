#include "libmx.h"

void mx_foreach_list_reverse(t_list *list, void (*f)(t_list_node *)) {
    t_list_node *node = f && list ? list->tail : NULL;

    for (; node; node = node->prev)
        f(node);
}
