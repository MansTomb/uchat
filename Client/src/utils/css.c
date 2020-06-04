#include "uchat.h"

void mx_css_from_file(t_info *info, char *filename) {
    gtk_css_provider_load_from_path(info->css, filename, NULL);
}

void mx_css_from_data(t_info *info, char *data) {
    gtk_css_provider_load_from_data(info->css, data, -1, NULL);
}
