#include "server.h"

static void test_register(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", mx_make_register);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_registration(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    printf("%i\n", type);

    if (type == mx_success_register) {
        printf("SUCCESS = %i!!!\n", cJSON_GetObjectItem(obj, "id")->valueint);
    } else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

static void test_autorization(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", mx_make_authorization);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_authorization(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    printf("%i\n", type);

    if (type == mx_success_authorization) {
        printf("SUCCESS = %i!!!\n", cJSON_GetObjectItem(obj, "id")->valueint);
    } else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

int main() {
    sqlite3 *db = NULL;
    mx_init_db(&db);

    test_register(db);
    test_autorization(db);
    mx_close_db(db);
}
