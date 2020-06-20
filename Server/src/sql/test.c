#include "server.h"

static void test_register(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_register);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_registration(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    printf("%i\n", type);

    if (type == success_register) {
        printf("SUCCESS = %i!!!\n", cJSON_GetObjectItem(obj, "id")->valueint);
    } else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

static void test_autorization(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_authorization);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_authorization(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    printf("%i\n", type);

    if (type == success_authorization) {
        printf("SUCCESS = %i!!!\n", cJSON_GetObjectItem(obj, "id")->valueint);
    } else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

static void test_new_pchat(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_new_personal_chat);
    cJSON_AddStringToObject(obj, "uid1", "1");
    cJSON_AddStringToObject(obj, "uid2", "2");

    cJSON *res = mx_create_personal_chat(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    printf("%i\n", type);

    if (type == success_new_personal_chat) {
        printf("SUCCESS = %i!!!\n", cJSON_GetObjectItem(obj, "id")->valueint);
    }
    else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

int main() {
    sqlite3 *db = NULL;
    mx_init_db(&db);

    // test_register(db);
    // test_autorization(db);
    test_new_pchat(db);
    mx_close_db(db);
}
