#include "client.h"

void mx_register_screen_build(t_info *info, t_register *reg) {
    if (reg == NULL)
        info->windows->reg = reg = malloc(sizeof(t_register));

    reg->builder = gtk_builder_new();
    gtk_builder_add_from_file(reg->builder, "./Resources/glade/register_screen.glade", NULL);

    reg->password_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "password_entry"));
    reg->passwordc_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "passwordc_entry"));
    reg->username_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "username_entry"));
    reg->window = GTK_WIDGET(gtk_builder_get_object(reg->builder, "register_window"));
    gtk_builder_connect_signals(reg->builder, info);

    gtk_widget_show(reg->window);
}

void mx_register_screen_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->reg->window);
    free(info->windows->reg);
    info->windows->reg = NULL;
}

void mx_on_click_back(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_register_screen_destroy(info);
    mx_login_screen_build(info, info->windows->log);
}

static gboolean validate_entry(t_register *reg) {
    if (mx_entry_text_exist(reg->username_entry)
        && mx_entry_text_exist(reg->password_entry)
        && mx_entry_text_exist(reg->passwordc_entry))
        return true;
    mx_dialog_warning_create(NULL, "All fields must not be empty!");
    return false;
}

static gboolean validate_entry_chars(GtkWidget *entry) {
    const char *text = mx_entry_get_text(entry);
    size_t len = strlen(text);

    for (size_t i = 0; i < len; ++i) {
        if (!isprint(text[i]))
            return false;
    }
    return true;
}

static gboolean password_match(t_register *reg) {
    const char *text1 = mx_entry_get_text(reg->password_entry);
    const char *text2 = mx_entry_get_text(reg->passwordc_entry);

    if (!strcmp(text1, text2))
        return true;
    mx_dialog_warning_create(NULL, "Password must match!");
    return false;
}

static gboolean validate_entryes(t_register *reg) {
    if (validate_entry_chars(reg->username_entry) 
            && validate_entry_chars(reg->password_entry)
            && validate_entry_chars(reg->passwordc_entry))
            return true;
    mx_dialog_warning_create(NULL, "Username and password must be printable!");
    return false;
}

gboolean mx_reg_data_validate(t_register *reg) {
    if (validate_entry(reg))
        if (validate_entryes(reg))
            if (password_match(reg))
                return true;
    return false;
}

static void free_wrapper(char **str, char **hash_pass, cJSON **jlogin) {
    cJSON_Delete(*jlogin);
    if (MX_MALLOC_SIZE(*str))
        free(*str);
    if (MX_MALLOC_SIZE(*hash_pass))
        free(*hash_pass);
}

static void reg_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *str = NULL;
    char *hash_pass = mx_create_hash(password);

    cJSON_AddNumberToObject(jlogin, "json_type", make_register);
    cJSON_AddStringToObject(jlogin, "login", login);
    cJSON_AddStringToObject(jlogin, "hash", hash_pass);

    str = cJSON_Print(jlogin);
    if (!str || send(s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "register: 'send' error occured\n");
    free_wrapper(&str, &hash_pass, &jlogin);
}

void mx_register_build_json_wrapper(t_info *info) {
    reg_bld_json(mx_entry_get_text(info->windows->reg->username_entry),
                 mx_entry_get_text(info->windows->reg->password_entry),
                 info->sock->sock);
}


void mx_reg_user_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;

    if(app && info){};
    // action "mx_make_register" estimated return mx_success_register
    if (mx_reg_data_validate(info->windows->reg)) {
        mx_register_build_json_wrapper(info);
        mx_wait_for_json(info, failed_register, success_register);
        if (mx_get_jtype(info, success_register)) {
            
        }
        else if (mx_get_jtype(info, failed_register))
            mx_dialog_warning_create(NULL, "Username already on use!");
    }
}
