#include "server.h"

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "gid", atoi(argv[0]));
    return 0;
}

static void get_group_id(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT id FROM contacts_groups WHERE name = '%s';",
            MX_VSTR(jsn, "gname"));
    rc = sqlite3_exec(db, query, get_id, jsn, &err);

    if (mx_check(rc, err, "get id present contact group") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_contact_group);
    }
    else {
        MX_SET_TYPE(jsn, success_add_contact_group);
    }
    free(query);
}

static void get_created_group_id(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT last_insert_rowid();");
    rc = sqlite3_exec(db, query, get_id, jsn, &err);

    if (mx_check(rc, err, "get id created contact group") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_contact_group);
    }
    else {
        MX_SET_TYPE(jsn, success_add_contact_group);
    }
    free(query);
}

static void add_group(sqlite3 *db, cJSON *jsn) {
    if (MX_VINT(jsn, "json_type") == success_add_contact_group) {
        char *query = NULL;
        char *err = NULL;
        int rc = 0;

        asprintf(&query, "INSERT INTO users_groups VALUES (%i, %i);",
                MX_VINT(jsn, "uid"), MX_VINT(jsn, "gid"));
        rc = sqlite3_exec(db, query, NULL, NULL, &err);

        if (mx_check(rc, err, "add user contact group") != SQLITE_OK) {
            MX_SET_TYPE(jsn, failed_add_contact_group);
        }
        else {
            MX_SET_TYPE(jsn, success_add_contact_group);
        }
        free(query);
    }
}

cJSON *mx_create_contact_group(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO contacts_groups VALUES (NULL, '%s');",
            MX_VSTR(jsn, "gname"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "create contact group") != SQLITE_OK) {
        get_group_id(db, jsn);
        add_group(db, jsn);
    }
    else {
        get_created_group_id(db, jsn);
        add_group(db, jsn);
    }
    free(query);
    return jsn;
}
