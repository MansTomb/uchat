#include "server.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; ++i) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    (void)data;
    return 0;
}

#define H "SELECT * from "

void print_db(sqlite3 *db) {
    char *err = 0;
    char *q[] = {
        H "users", H "users_profiles", H "contact_groups",
        H "contact_lists", H "chats", H "user_chats",
        H "messages", H"block_lists"
    };

    for (uint32_t i = 0; i < sizeof(q) / sizeof(q[0]); ++i) {
        int rc = sqlite3_exec(db, q[i], callback, NULL, &err);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);
        }
    }
}

void mx_init_db(sqlite3 *db) {
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
    else {
        printf("Opened database successfully\n");
        rc = mx_create_db(db);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "Creation db error: %s\n", sqlite3_errmsg(db));
            exit(EXIT_FAILURE);
        }

        print_db(db);
    }
}
