#include "client.h"

void mx_wait_for_json(t_info *info, int type1, int type2) {
    while (1) {
        if (info->json &&
           (mx_get_jtype(info, type1) || mx_get_jtype(info, type2))) {
               return;
           }
    }
}
