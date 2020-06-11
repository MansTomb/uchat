#pragma once

typedef struct s_tree_node t_node;

struct s_tree_node {
    void *data;         // storage for data
    t_node *left;       // left child
    t_node *right;      // right child
    t_node *parent;     // NULL for root element
};

typedef struct {
    size_t size;        // amount of elements
    t_node *root;       // root element
} t_tree;

t_tree *mx_create_tree(void);
void mx_clear_tree(t_tree *tree);
void mx_delete_tree(t_tree *tree);
t_node *mx_new_node(void *data, t_node *parent);

void mx_foreach_preorder(t_tree *tree, void (*f)(t_node *));
void mx_foreach_inorder(t_tree *tree, void (*f)(t_node *));
void mx_foreach_postorder(t_tree *tree, void (*f)(t_node *));

void mx_foreach_preorder_r(t_tree *tree, void (*f)(t_node *));
void mx_foreach_inorder_r(t_tree *tree, void (*f)(t_node *));
void mx_foreach_postorder_r(t_tree *tree, void (*f)(t_node *));
