#include "server.h"

static int send_check(t_sock *sock, t_peer *client, int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("Peer is not ready right now, try again later.\n");
        }
        else {
            perror("Send() from peer error");
            mx_handle_disconnect(sock, client);
        }
    }
    // we have read as many as possible
    // else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //     return -1;
    // }
    else if (n == 0) {
        printf("Peer can't accept data right now, try again later.\n");
        // return -1;
    }
    return 0;
}

static void send_one(t_sock *sock, t_peer *peer, int sd) {
    int n;

    n = send(sd, peer->send_buff, strlen(peer->send_buff), MSG_DONTWAIT);
    if (n <= 0) {
        send_check(sock, peer, n);
    }
}

static cJSON *create_piece_file(int type, char *str, int size) {
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddNumberToObject(obj, "p_type", type);
    cJSON_AddStringToObject(obj, "piece", str);
    if (size)
        cJSON_AddNumberToObject(obj, "n", size);
    else
        cJSON_AddNumberToObject(obj, "n", -1);

    return obj;
}

// static void send_large(t_sock *sock, t_peer *p, int sd, char *large_message) {
//     unsigned long i = 0;
//     char str[MX_MAX_SEND_SIZE / 2];

//     // bzero(str, strlen(str));
//     while (large_message[i]) {
//         strncpy(str, &large_message[i], MX_MAX_SEND_SIZE / 2 - 1);
//         i += strlen(str);
//         // printf("i = %lu\n", i);                    //// for test

//         if (i == strlen(large_message)) {
//             mx_json_to_sending_buffer(p->send_buff,
//                                       create_peice(big_msg_end, str));
//             send_one(sock, p, sd);
//             // puts(send_buff);                       //// for test
//             break;
//         }
//         else {
//             mx_json_to_sending_buffer(p->send_buff,
//                                       create_peice(big_msg, str));
//             send_one(sock, p, sd);
//         }
//         sleep(1);
//         // puts(send_buff);                       //// for test
//     }
// }

void mx_send_file(t_sock *sock, t_peer *peer, cJSON *bd, int sd) {
    // char *root = cJSON_Print(bd);

    // mx_print_serv_out(bd, root);

    // printf("root size = %lu\n", strlen(root));        //// for test
    // printf("%s\n", root);                     //// for test

    // if (MX_PTYPE(bd) == file) {

    // }
    // else if (MX_PTYPE(bd) == file_end) {

    // }
    // else
    //     printf("error file type\n");

    // char root[MX_MAX_SEND_SIZE];
    char buff[MX_MAX_SEND_SIZE / 2];

    char *path = cJSON_GetObjectItem(bd, "path")->valuestring;
    // printf("path = %s\n", path);

    FILE *fp;
    if ((fp = fopen(path, "r")) == NULL) {
        printf("Cannot open file.\n");
        // exit(1);
    }
    else {
        // FILE *new;
        // if ((new = fopen("Server/tmp/new.png", "w")) == NULL) {
        //     printf("Cannot open file new.\n");
        //     exit(1);
        // }

        mx_json_to_sending_buffer(peer->send_buff, create_peice(file, "0", 0));
        send_one(sock, peer, sd);
        printf("%s\n ---", peer->send_buff);
        sleep(1);

        while (1) {
            // memset(buff, 0x00, MX_MAX_SEND_SIZE / 2);
            int n = fread(buff, 1, MX_MAX_SEND_SIZE / 2 - 1, fp);
            buff[MX_MAX_SEND_SIZE / 2 - 1] = '\0';
            mx_json_to_sending_buffer(peer->send_buff, create_piece_file(4, buff, n));
            send_one(sock, peer, sd);

            // fwrite(buff, 1, n, new);

            if (n == EOF || n == 0) {   // file_read_len == 0.
                printf("finish file\n");
                mx_json_to_sending_buffer(peer->send_buff, create_peice(5, "0", 0));
                send_one(sock, peer, sd);
                sleep(1);
                printf("%s\n ---", peer->send_buff);
                break;
            }
            printf("%s\n ---", peer->send_buff);
            sleep(1);
        }

        // fclose (new);
        fclose (fp);
    }

    // mx_json_to_sending_buffer(peer->send_buff, create_peice(file, root));
    // send_one(sock, peer, sd);

   /* Seek to the beginning of the file */
//    fseek(fp, 0, SEEK_SET);



    // des_fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0700);
    //     if(!des_fd) {
    //         perror("file open error : ");
    //         break;
    //     }
    //     /* file save */
    //     while(1) {
    //         memset(buf, 0x00, MAXBUF);
    //         file_read_len = read(client_sockfd, buf, MAXBUF);
    //         write(des_fd, buf, file_read_len);
    //         if(file_read_len == EOF | file_read_len == 0) {
    //             printf("finish file\n");
    //             break;
    //         }


    //     }


    // if (strlen(root) < 3 * MX_MAX_SEND_SIZE / 2) {
    //     mx_json_to_sending_buffer(peer->send_buff, create_peice(one_msg, root));
    //     send_one(sock, peer, sd);
    // }
    // else {
    //     large_message = strdup(root);
    //     len = strlen(large_message);
    //     // printf("message = %s\n", large_message);             //// for test

    //     send_large(sock, peer, sd, large_message);

    //     mx_strdel(&large_message);
    // }
}
