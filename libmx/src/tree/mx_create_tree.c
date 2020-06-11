#include "libmx.h"

t_tree *mx_create_tree(void) {
    t_tree *tree = (t_tree *)malloc(sizeof(t_tree));

    if (tree) {
        tree->size = 0;
        tree->root = NULL;
    }
    return tree;
}
