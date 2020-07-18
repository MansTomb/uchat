#include "client.h"

static void set_editables(t_profile *profile, gboolean is_editable) {
    // gtk_editable_set_editable(GTK_EDITABLE(profile->login), is_editable);
    gtk_editable_set_editable(GTK_EDITABLE(profile->fname), is_editable);
    gtk_editable_set_editable(GTK_EDITABLE(profile->lname), is_editable);
    gtk_editable_set_editable(GTK_EDITABLE(profile->email), is_editable);
    // gtk_editable_set_editable(GTK_EDITABLE(profile->status), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->login), is_editable);
    gtk_entry_set_has_frame(GTK_ENTRY(profile->fname), is_editable);
    gtk_entry_set_has_frame(GTK_ENTRY(profile->lname), is_editable);
    gtk_entry_set_has_frame(GTK_ENTRY(profile->email), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->status), is_editable);
}

static int validate(t_profile *profile) {
    if (mx_entry_text_exist(profile->fname) &&
        mx_entry_text_exist(profile->lname) &&
        mx_entry_text_exist(profile->email)) {
        if (mx_validate_chars((char *)mx_entry_get_text(profile->fname)) &&
            mx_validate_chars((char *)mx_entry_get_text(profile->lname)) &&
            mx_validate_chars((char *)mx_entry_get_text(profile->email))) {
            return true;
        }
        else
            mx_dialog_warning_create(NULL, "Wrong character in fields!");
    }
    else 
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}

void mx_on_click_profile_edit(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->prof;

printf("mx_on_click_profile_edit\n");
    set_editables(profile, TRUE);

    gtk_widget_hide(profile->edit);
    gtk_widget_show(profile->save);
    gtk_widget_show(profile->cancel);
}

void mx_on_click_profile_save(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->prof;

    if (validate(profile)) {
        mx_upd_prof_build_json_wrapper((t_info *)data);
        // Send data to server mx_make_update_profile estimated return mx_success_update_profile
        set_editables(profile, FALSE);
        gtk_widget_hide(profile->save);
        gtk_widget_hide(profile->cancel);
        gtk_widget_show(profile->edit);
    }
}

void mx_on_click_profile_cancel(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->prof;

printf("mx_on_click_profile_cancel\n");
    // Cancel changes data from server
    // Load data again, data must be stored at profile structure
    set_editables(profile, FALSE);
    gtk_widget_hide(profile->save);
    gtk_widget_hide(profile->cancel);
    gtk_widget_show(profile->edit);
}
