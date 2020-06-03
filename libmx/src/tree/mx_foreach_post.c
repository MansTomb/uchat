#include "libmx.h"

static void postorder(t_node *node, void (*f)(t_node *)) {
    if (node->left)
        postorder(node->left, f);
    if (node->right)
        postorder(node->right, f);
    f(node);
}

void mx_foreach_postorder(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        postorder(tree->root, f);
}

static void postorder_r(t_node *node, void (*f)(t_node *)) {
    if (node->right)
        postorder_r(node->right, f);
    if (node->left)
        postorder_r(node->left, f);
    f(node);
}

void mx_foreach_postorder_r(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        postorder_r(tree->root, f);
}
