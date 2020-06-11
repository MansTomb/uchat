#include "libmx.h"

static void preorder(t_node *node, void (*f)(t_node *)) {
    f(node);
    if (node->left)
        preorder(node->left, f);
    if (node->right)
        preorder(node->right, f);
}

void mx_foreach_preorder(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        preorder(tree->root, f);
}

static void preorder_r(t_node *node, void (*f)(t_node *)) {
    f(node);
    if (node->right)
        preorder_r(node->right, f);
    if (node->left)
        preorder_r(node->left, f);
}

void mx_foreach_preorder_r(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        preorder_r(tree->root, f);
}
