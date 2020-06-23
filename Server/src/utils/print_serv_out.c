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
    printf("\x1B[33m%s\x1B[0m\n", s);
}

void mx_print_serv_out(cJSON *json, char *s) {
    // print_yel(buff);

    switch (MX_TYPE(json)) {

        case failed_register:
            print_red(s);
            break;
        case failed_authorization:
            print_red(s);
            break;
        case failed_deletion:
            print_red(s);
            break;
        case failed_change_password:
            print_red(s);
            break;
        case failed_add_new_contact:
            print_red(s);
            break;
        case failed_del_contact:
            print_red(s);
            break;
        case failed_new_personal_chat:
            print_red(s);
            break;
        case failed_send_message:
            print_red(s);
            break;


        case success_register:
            print_grn(s);
            break;
        case success_authorization:
            print_grn(s);
            break;
        case success_deletion:
            print_grn(s);
            break;
        case success_change_password:
            print_grn(s);
            break;
        case success_add_new_contact:
            print_grn(s);
            break;
        case success_del_contact:
            print_grn(s);
            break;
        case success_new_personal_chat:
            print_grn(s);
            break;


        case send_message:
            print_blue(s);
            break;
        case logout:
            print_blue(s);
            break;


        default:
            print_blue("unknown type of message\n");
            break;
    }

}
