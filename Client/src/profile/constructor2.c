#include "client.h"

static GtkWidget *create_field(char *name, char *placeholder, char *text) {
    GtkWidget *field = mx_entry_constructor(name);

    gtk_entry_set_placeholder_text(GTK_ENTRY(field), placeholder);
    gtk_entry_set_has_frame(GTK_ENTRY(field), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(field), FALSE);
    gtk_entry_set_text(GTK_ENTRY(field), text);
    gtk_entry_set_width_chars(GTK_ENTRY(field), 16);
    gtk_entry_set_max_length(GTK_ENTRY(field), 0);

    return field;
}

static GtkWidget *create_label(char *name, char *text) {
    GtkWidget *label = mx_label_constructor(name, text);

    return label;
}

void mx_profile_create_entrys(t_info *info, t_profile *new) {
    t_profile_data *data = info->cl_data->profile;

    new->name = create_field("profile_field", "Login", data->login);
    new->fname = create_field("profile_field", "First Name", data->first_name);
    new->sname = create_field("profile_field", "Second Name", data->sec_name);
    new->email = create_field("profile_field", "Email", data->user_email);
    new->status = create_field("profile_status", "Status", data->status);
}

void mx_profile_create_labels(t_info *info, t_profile *new) {
    new->namelb = create_label("profile_label", "Login");
    new->fnamelb = create_label("profile_label", "First Name");
    new->snamelb = create_label("profile_label", "Second Name");
    new->emaillb = create_label("profile_label", "Email");
    new->statuslb = create_label("profile_statuslb", "Status");
}
