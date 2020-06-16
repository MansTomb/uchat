#pragma once
#include "server.h"

int check(int rc, char *err);

int mx_create_db(sqlite3 *db);
void mx_init_db(sqlite3 **db);
void mx_close_db(sqlite3 *db);

cJSON *mx_registration(sqlite3 *db, cJSON *reg);
