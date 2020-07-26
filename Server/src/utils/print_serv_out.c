#include "server.h"

static void print_yel(char *s) {
    printf("\x1B[33m%s\x1B[0m\n", s);
}
static void print_grn(char *s) {
    printf("\x1B[32m%s\x1B[0m\n", s);
}
static void print_red(char *s) {
    printf("\x1B[31m%s\x1B[0m\n", s);
}
static void print_blue(char *s) {
    printf("\x1B[34m%s\x1B[0m\n", s);
}

void mx_print_serv_out(cJSON *json, char *s) {
    print_blue(s);
}
