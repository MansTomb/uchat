#include "server.h"

void test_register(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", MX_MAKE_REGISTER);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_registration(db, obj);
    int type = cJSON_GetObjectItem(obj, "json_type")->valueint;

    if (type == MX_SUCCESS_REGISTER) {
        printf("SUCCESS!!!\n");
    } else {
        printf("FAILED!!!\n");
    }
    cJSON_Delete(obj);
}

int main() {
    sqlite3 *db = NULL;
    mx_init_db(&db);

    test_register(db);
    mx_close_db(db);
}
