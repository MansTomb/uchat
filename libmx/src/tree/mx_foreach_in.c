#include "libmx.h"

static void inorder(t_node *node, void (*f)(t_node *)) {
    if (node->left)
        inorder(node->left, f);
    f(node);
    if (node->right)
        inorder(node->right, f);
}

void mx_foreach_inorder(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        inorder(tree->root, f);
}

static void inorder_r(t_node *node, void (*f)(t_node *)) {
    if (node->right)
        inorder_r(node->right, f);
    f(node);
    if (node->left)
        inorder_r(node->left, f);
}

void mx_foreach_inorder_r(t_tree *tree, void (*f)(t_node *)) {
    if (tree && tree->root && f)
        inorder_r(tree->root, f);
}
