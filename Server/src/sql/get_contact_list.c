#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *contact = cJSON_CreateObject();
    const char *fields[] = {"contact_id", "login", "first_name", "second_name",
        "email", "status"};

    cJSON_AddNumberToObject(contact, fields[0], atoi(argv[0]));
    for (uint32_t i = 1; i < sizeof(fields) / sizeof(fields[0]); ++i)
        cJSON_AddStringToObject(contact, fields[i], argv[i]);

    cJSON_AddNumberToObject(contact, "group_id", argv[6] ? atoi(argv[6]) : 0);
    cJSON_AddStringToObject(contact, "group_name", argv[7] ? argv[7] : "");
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "contacts"), contact);
    return 0;
}

cJSON *mx_get_contact_list(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT cl.contact_id, u.login, up.first_name, "
            "up.second_name, up.email, up.status, cl.group_id, cg.name "
            "FROM contacts_lists AS cl "
            "JOIN users AS u ON cl.contact_id = u.id AND cl.user_id = %i "
            "JOIN users_profiles AS up ON cl.contact_id = up.user_id "
            "LEFT JOIN contacts_groups AS cg ON cl.group_id = cg.id;",
            MX_VINT(jsn, "uid"));
    cJSON_AddArrayToObject(jsn, "contacts");
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "get contact list") != SQLITE_OK) {
        // ???????????????????????????????????????
    }
    else {
        MX_SET_TYPE(jsn, send_client_contacts);
    }
    free(query);
    return jsn;
}
