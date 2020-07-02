#include "server.h"

static void test_register(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_register);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_registration(db, obj);
    int type = MX_VINT(obj, "json_type");

    printf("TYPE = %i\n", type);

    if (type == success_register) {
        printf("SUCCESS: id = %i\n", MX_VINT(obj, "uid"));
    } else {
        printf("FAILED register\n");
    }
    cJSON_Delete(obj);
}

static void test_authorization(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_authorization);
    cJSON_AddStringToObject(obj, "login", "LOGIN");
    cJSON_AddStringToObject(obj, "hash", "HASH");

    cJSON *res = mx_authorization(db, obj);
    int type = MX_VINT(obj, "json_type");

    printf("TYPE = %i\n", type);

    if (type == success_authorization) {
        printf("SUCCESS: id = %i\n", MX_VINT(obj, "uid"));
    } else {
        printf("FAILED authorization\n");
    }
    cJSON_Delete(obj);
}

static void test_new_pchat(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", make_new_personal_chat);
    cJSON_AddNumberToObject(obj, "uid1", 1);
    cJSON_AddNumberToObject(obj, "uid2", 2);

    cJSON *res = mx_create_personal_chat(db, obj);
    int type = MX_VINT(obj, "json_type");

    printf("TYPE = %i\n", type);

    if (type == success_new_personal_chat) {
        printf("SUCCESS: id = %i\n", MX_VINT(obj, "uid"));
    }
    else {
        printf("FAILED creating new chat\n");
    }
    cJSON_Delete(obj);
}

static void test_contact_list(sqlite3 *db) {
    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(obj, "uid", 1);

    cJSON *res = get_contact_list(db, obj);
    int type = MX_VINT(obj, "json_type");

    printf("TYPE = %i\n", type);

    char *jsn = cJSON_Print(res);
    printf("%s", jsn);

    free(jsn);
    cJSON_Delete(obj);
}

int main() {
    sqlite3 *db = NULL;
    mx_init_db(&db);

    // test_register(db);
    // test_authorization(db);
    // test_new_pchat(db);

    test_contact_list(db);

    mx_close_db(db);
}
