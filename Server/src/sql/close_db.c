#include "server.h"

void mx_close_db(sqlite3 *db) {
    sqlite3_close(db);
}
