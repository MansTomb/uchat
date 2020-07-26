#include "server.h"

static void add_defaults(sqlite3 *db) {
    char *query1 = "INSERT INTO users VALUES (1, 'root', "
        "'99adc231b045331e514a516b4b7680f588e3823213abe901738bc3ad67b2f6fc');"
        "INSERT INTO chats VALUES (1, 3, 'UCHAT'); INSERT INTO users_chats "
        "VALUES (1, 1, 2);";
    char *err = NULL;

    if (sqlite3_exec(db, query1, NULL, NULL, &err) != SQLITE_OK) {
        fprintf(stderr, "db defaults error: %s\n", err);
        free(err);
    }
}

int mx_init_db(sqlite3 **db) {
#ifdef TEST
    int rc = sqlite3_open("test.db", db);
#else
    int rc = sqlite3_open(MX_DB_PATH, db);
#endif

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        exit(EXIT_FAILURE);
    }
    else {
        printf("Opened database successfully\n");
        rc = mx_create_db(*db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Creation db error: %s\n", sqlite3_errmsg(*db));
            exit(EXIT_FAILURE);
        }
        else {
            add_defaults(*db);
        }
    }
    return rc;
}
