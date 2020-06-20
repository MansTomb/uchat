#include "server.h"

int mx_check(int rc, char *err, char *desc) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error [%s]: %s\n", desc, err);
        sqlite3_free(err);
    }
    return rc;
}
