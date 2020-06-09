#include "libmx.h"

static void clear_subtree(t_node *node) {
    if (node) {
        clear_subtree(node->left);
        clear_subtree(node->right);
        free(node);
    }
}

void mx_clear_tree(t_tree *tree) {
    if (tree) {
        clear_subtree(tree->root);
        tree->root = NULL;
    }
}
