#include "server.h"

void mx_prepare_to_send(cJSON *json) {
    char *root = cJSON_Print(json);

    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "p_type", 0);
    cJSON_AddStringToObject(obj, "piece", buff);

    char *root = cJSON_Print(obj);
    sprintf(buff, "%s", root);

}

void mx_prepare_to_send(char *buff) {

    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "p_type", 0);
    cJSON_AddStringToObject(obj, "piece", buff);

    char *root = cJSON_Print(obj);
    sprintf(buff, "%s", root);

}
