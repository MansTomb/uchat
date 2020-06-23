#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *contact = cJSON_CreateObject();
    const char *fields[] = {"cid", "login", "fname", "sname", "email",
        "status", "gid", "gname"};

    for (uint32_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
        cJSON_AddStringToObject(contact, fields[i], argv[i] ? argv[i] : "");

    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "contacts"), contact);
    return 0;
}

cJSON *get_contact_list(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT cl.contact_id, u.login, up.first_name, "
            "up.second_name, up.email, up.status, cl.group_id, cg.name "
            "FROM contacts_lists AS cl "
            "JOIN users AS u ON cl.contact_id = u.id AND cl.user_id = %i "
            "JOIN users_profiles AS up ON cl.contact_id = up.user_id "
            "LEFT JOIN contacts_groups AS cg ON cl.group_id = cg.id;",
            cJSON_GetObjectItem(jsn, "uid")->valueint);
    cJSON_AddArrayToObject(jsn, "contacts");
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "get contact list") != SQLITE_OK) {
        // ???????????????????????????????????????
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_new_personal_chat);
    }
    free(query);
    return jsn;
}
