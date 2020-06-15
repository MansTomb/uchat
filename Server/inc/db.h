#pragma once
#include "server.h"

int mx_create_db(sqlite3 *db);
void mx_init_db(sqlite3 *db);
void mx_close_db(sqlite3 *db);
