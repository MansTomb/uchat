#include "server.h"

static int callback(void *data, int argc, char **argv, char **col) {
    for (int i = 0; i < argc; ++i) {
        printf("%s = %s\n", col[i], argv[i]);
    }

    printf("\n");
    return 0;
}

#define H "SELECT * from "

static void print_db(sqlite3 *db) {
    char *err = 0;
    char *q[] = {
        H "users", H "users_profiles", H "users_notify_settings",
        H "contacts_groups", H "contacts_lists", H "chats",
        H "users_chats", H "messages"
    };

    for (uint32_t i = 0; i < sizeof(q) / sizeof(q[0]); ++i) {
        int rc = sqlite3_exec(db, q[i], callback, NULL, &err);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);
        }
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

        // print_db(*db);
    }
    return rc;
}
