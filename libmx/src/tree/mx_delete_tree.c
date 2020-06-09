#include "libmx.h"

void mx_delete_tree(t_tree *tree) {
    if (tree) {
        mx_clear_tree(tree);
        if (MX_MALLOC_SIZE(tree))
            free(tree);
    }
}
