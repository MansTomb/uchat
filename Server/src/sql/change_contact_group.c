#include "server.h"

cJSON *mx_change_contact_group(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE contacts_lists SET group_id = %i WHERE user_id = "
            "%i AND group_id = %i AND contact_id = %i;", MX_VINT(jsn, "gid2"),
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "gid1"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "change contact group") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_change_contact_group);
    }
    else {
        MX_SET_TYPE(jsn, success_change_contact_group);
    }
    free(query);
    return jsn;
}
