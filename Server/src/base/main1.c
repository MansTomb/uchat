#include "server.h"

// char *mx_strjoin_free(char *s1, char const *s2) {
//      char *p = NULL;

//     if (!s1 && !s2)
//         return NULL;
//     else if (!s1)
//         p = mx_strdup(s2);
//     else if (!s2)
//         p = mx_strdup(s1);
//     else {
//         p = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
//         if (!p)
//             return NULL;
//         p = mx_strcpy(p, s1);
//         p = mx_strcat(p, s2);
//     }
//     mx_strdel(&s1);
//     return p;
// }

static int check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s\n", error_ptr);
            return 1;
        }
    return 0;
}

int main() {
    cJSON *get;
    char buff[16];
    bzero(buff, strlen(buff));
    char *str = "{ \"json_type\": 37, \"uid\": 2, \"con\": \"Hello!\"}";
    // char *ptr = str;
    char *ptr = strdup(str);
    // printf("str = %s\n", str);

    char *all = NULL;

    strncpy(buff, ptr, 15);
    all = strdup(buff);
    ptr += 15;
    // write(0, buff, 16);
    write(0, all, strlen(all));

    const char **return_parse_end = NULL;
    cJSON_bool isnullterm = 0;

    get = cJSON_ParseWithOpts(buff, return_parse_end, isnullterm);
    if (check_err_json(get)) {
        // return 1;
    }
    else {
        char *res = cJSON_Print(get);
        printf("res = %s\n", res);
    }

    strncpy(buff, ptr, 15);
    all = mx_strjoin(all, buff);
    ptr += 15;
    // write(0, buff, 16);
    write(0, all, strlen(all));


    get = cJSON_ParseWithOpts(all, return_parse_end, isnullterm);
    if (check_err_json(get)) {
        // return 1;
    }
    else {
        char *res = cJSON_Print(get);
        printf("\nres = %s\n", res);
    }

    strncpy(buff, ptr, 15);
    all = mx_strjoin(all, buff);
    ptr += 15;
    // write(0, buff, 16);
    write(0, all, strlen(all));


    get = cJSON_ParseWithOpts(all, return_parse_end, isnullterm);
    if (check_err_json(get)) {
        // return 1;
    }
    else {
        char *res = cJSON_Print(get);
        printf("res = %s\n", res);
    }

    cJSON_Delete(get);

    return 0;
}
