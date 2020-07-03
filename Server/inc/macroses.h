#pragma once
#define MX_INE " IF NOT EXISTS "
#define MX_CREATE(NAME) "CREATE TABLE" MX_INE #NAME " ( "
#define MX_INT_PK(NAME) #NAME " INTEGER PRIMARY KEY AUTOINCREMENT, "
#define MX_TRIGGER(NAME, ACT) "CREATE TRIGGER" MX_INE #NAME " AFTER " #ACT " ON "
#define MX_INSERT(TABLE, ...) "INSERT INTO " #TABLE " (" #__VA_ARGS__ ") VALUES "
#define MX_DEL_WH(TABLE, COND) "DELETE FROM " #TABLE " WHERE " #COND "; "

#define MX_TYPE(x) (cJSON_GetObjectItem(x, "json_type")->valueint)
#define MX_PTYPE(x) (cJSON_GetObjectItem(x, "p_type")->valueint)
#define MX_SET_TYPE(x, y) (cJSON_SetNumberValue(cJSON_GetObjectItem(x, "json_type"), y))
#define MX_VINT(x, y) (cJSON_GetObjectItem(x, y)->valueint)
#define MX_VSTR(x, y) (cJSON_GetObjectItem(x, y)->valuestring)
#define MX_PIECE(x)   (cJSON_GetObjectItem(x, "piece")->valuestring)
// #define MX_DEL(x, y)    (cJSON_DeleteItemFromObject(x, y))
