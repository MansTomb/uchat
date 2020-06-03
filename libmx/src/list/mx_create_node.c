#include "libmx.h"

t_list_node *mx_create_node(void *data, t_list_node *prev, t_list_node *next) {
    t_list_node *node = (t_list_node *)malloc(sizeof(t_list_node));

    if (node) {
        node->data = data;
        node->next = next;
        node->prev = prev;
    }
    return node;
}
