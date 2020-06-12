#include "server.h"

// static int callback(void *data, int argc, char **argv, char **azColName) {
//     // fprintf(stderr, "%s: ", (const char *)data);

//     for (int i = 0; i < argc; ++i) {
//         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }

//     printf("\n");
//     (void)data;
//     return 0;
// }

// int open_db(sqlite3 **db) {
//     int rc = sqlite3_open("test.db", db);

//     if (rc) {
//         fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
//     } else {
//         fprintf(stdout, "Opened database successfully\n");
//     }
//     return rc;
// }

// int create(sqlite3 *db) {
//     char *zErrMsg = NULL;
//     char *sql = "CREATE TABLE IF NOT EXISTS COMPANY ("
//                 "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
//                 "NAME TEXT NOT NULL UNIQUE,"
//                 "AGE INT NOT NULL,"
//                 "ADDRESS CHAR(50),"
//                 "SALARY REAL);";

//     int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

//     if (rc != SQLITE_OK) {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     } else {
//         fprintf(stdout, "Table created successfully\n");
//     }
//     return rc;
// }

// int insert(sqlite3 *db) {
//     char *zErrMsg = NULL;

//     char *sql = "INSERT INTO COMPANY (NAME,AGE,ADDRESS,SALARY) VALUES"
//                 "('Paul', 32, 'California', 20000.00),"
//                 "('Allen', 25, 'Texas', 15000.00),"
//                 "('Teddy', 23, 'Norway', 20000.00),"
//                 "('Mark', 25, 'Rich-Mond ', 65000.00);";

//     int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

//     if (rc != SQLITE_OK) {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     } else {
//         fprintf(stdout, "Records created successfully\n");
//     }
//     return rc;
// }

// int select_db(sqlite3 *db) {
//     char *zErrMsg = 0;
//     char *sql = "SELECT * from COMPANY";

//     int rc = sqlite3_exec(db, sql, callback, NULL, &zErrMsg);

//     if (rc != SQLITE_OK) {
//         fprintf(stderr, "SQL error: %s\n", zErrMsg);
//         sqlite3_free(zErrMsg);
//     } else {
//         fprintf(stdout, "Operation done successfully\n");
//     }
//     return rc;
// }

// void test() {
//     sqlite3 *db = NULL;

//     int rc = open_db(&db);
//     if (rc == 0) {
//         rc = create(db);

//         if (rc == 0) {
//             rc = insert(db);
//             rc = select_db(db);
//         }
//     }

//     sqlite3_close(db);
// }
