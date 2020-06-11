#include "libmx.h"

t_node *mx_new_node(void *data, t_node *parent) {
    t_node *node = malloc(sizeof(t_node));

    if (node) {
        node->data = data;
        node->parent = parent;
        node->left = node->right = NULL;
    }
    return node;
}
