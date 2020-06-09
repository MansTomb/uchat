#pragma once

#define MX_VECTOR_DEFAULT_SIZE 16

typedef struct s_vector {
    size_t cap;     // capacity
    size_t size;    // current size
    size_t bytes;   // size of item
    uint8_t *arr;   // array of items
} t_vector;

/*
 * creates base struct
 * copies base struct and all objects in container
 * deletes base struct
 */

t_vector *mx_create_vector(size_t size, size_t bytes);
t_vector *mx_copy_vector(t_vector *v);
void mx_delete_vector(t_vector *v);

/*
 * replaces the contents of container with count copies of value item
 * adds element to the end of container
 * deletes last item of the container
 */

void mx_assign_vector(t_vector *v, size_t count, const void *item);
void mx_push_backward(t_vector *v, const void *item);
void mx_pop_backward(t_vector *v);

/*
 * inserts value before pos
 * removes the element at pos
 * erases all elements from the container
 */

void mx_insert(t_vector *v, size_t pos, const void *item);
void mx_erase(t_vector *v, size_t pos);
void mx_clear_vector(t_vector *v);

/*
 * returns a pointer to element at location pos with bounds checking
 * returns a pointer to the first element in the container
 * returns a pointer to the last element in the container
 * returns a pointer to empty data place after last element
 */

void *mx_at(t_vector *v, size_t pos);
void *mx_get_front(t_vector *v);
void *mx_get_back(t_vector *v);
void *mx_end(t_vector *v);

/*
 * applies function f to every element of the container
 * reverse the order of elements
 */

void mx_foreach_vector(t_vector *v, void (*f)(void *));
void mx_foreach_vector_reverse(t_vector *v, void (*f)(void *));
void mx_reverse_vector(t_vector *v);
