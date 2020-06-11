#include "libmx.h"

t_string *mx_copy_str(t_string *str) {
    t_string *new = mx_create_string(str->str);
    
    return new;
}
