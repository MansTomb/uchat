#include "client.h"

static char *hash_to_str(unsigned char *hash) {
    char *str = (char *)malloc(sizeof(char) * SHA512_DIGEST_LENGTH + 1);
    int a;
    int count = 0;
    char mas[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                    'a', 'b', 'c', 'd', 'e', 'f'};

    for (int i = 0; i < 32; i++) {
        a = hash[i] / 16;
        str[count++] = mas[a];
        a = hash[i] % 16;
        str[count++] = mas[a];
    }
    str[SHA512_DIGEST_LENGTH] = '\0';
    return str;
}

char *mx_create_hash(const char *pass) {
    unsigned char sha512[SHA512_DIGEST_LENGTH];
    char *hash;

    asprintf(&hash, "%s", pass);
    SHA512((unsigned char *)hash, strlen(hash), sha512);
    free(hash);
    return hash_to_str(sha512);
}
