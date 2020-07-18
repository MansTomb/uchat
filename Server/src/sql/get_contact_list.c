#include "server.h"

static void add_others(cJSON *jsn) {
    cJSON *group = cJSON_CreateObject();
    cJSON_AddNumberToObject(group, "gid", 0);
    cJSON_AddStringToObject(group, "gname", "Others");
    cJSON_AddItemToArray(cJSON_GetObjectItem(jsn, "groups"), group);
}

static int get_groups(void *data, int argc, char **argv, char **cols) {
    cJSON *group = cJSON_CreateObject();

    cJSON_AddNumberToObject(group, "gid", atoi(argv[1]));
    cJSON_AddStringToObject(group, "gname", argv[2]);
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "groups"), group);
    return 0;
}

static int get_contacts(void *data, int argc, char **argv, char **cols) {
    cJSON *contact = cJSON_CreateObject();

    cJSON_AddNumberToObject(contact, "coid", atoi(argv[0]));
    cJSON_AddStringToObject(contact, "login", argv[1]);
    cJSON_AddStringToObject(contact, "fname", argv[2]);
    cJSON_AddStringToObject(contact, "sname", argv[3]);
    cJSON_AddStringToObject(contact, "email", argv[4]);
    cJSON_AddStringToObject(contact, "status", argv[5]);
    cJSON_AddNumberToObject(contact, "gid", atoi(argv[6]));
    cJSON_AddBoolToObject(contact, "active", false);
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "contacts"), contact);
    return 0;
}

static int get_group_list(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    int check = 0;

    asprintf(&query, "SELECT ug.group_id, cg.name FROM users_groups AS ug "
            "JOIN contacts_groups AS cg ON ug.user_id = %i AND cg.id = "
            "ug.group_id;", MX_VINT(jsn, "uid"));
    cJSON_AddArrayToObject(jsn, "groups");
    add_others(jsn);

    rc = sqlite3_exec(db, query, get_groups, jsn, &err);
    check = mx_check(rc, err, "get group list");

    if (check != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_client_contacts);
    }
    return check;
}

cJSON *mx_get_contact_list(sqlite3 *db, cJSON *jsn) {
    if (get_group_list(db, jsn) == SQLITE_OK) {
        char *query = NULL;
        char *err = NULL;
        int rc = 0;

        asprintf(&query, "SELECT cl.contact_id, u.login, up.first_name, "
                "up.second_name, up.email, up.status, cl.group_id FROM "
                "contacts_lists AS cl JOIN users AS u ON cl.contact_id = u.id "
                "AND cl.user_id = %i JOIN users_profiles AS up ON "
                "cl.contact_id = up.user_id;", MX_VINT(jsn, "uid"));
        cJSON_AddArrayToObject(jsn, "contacts");
        rc = sqlite3_exec(db, query, get_contacts, jsn, &err);
        if (mx_check(rc, err, "get contact list") != SQLITE_OK) {
            MX_SET_TYPE(jsn, failed_client_contacts);
        } else {
            MX_SET_TYPE(jsn, success_client_contacts);
        }
        free(query);
    }
    return jsn;
}
