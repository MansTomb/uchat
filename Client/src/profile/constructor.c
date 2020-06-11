#include "client.h"

static void attach_layout(t_info *info, t_profile *profile) {
    mx_layout_put(info->layout, profile->scrollable, 300, 100);

    mx_scrollable_container_add(profile->scrollable, profile->layout);

    mx_layout_put(profile->layout, profile->namelabel, 360, 30);
    mx_layout_put(profile->layout, profile->name, 350, 50);
    mx_layout_put(profile->layout, profile->idlabel, 360, 90);
    mx_layout_put(profile->layout, profile->id, 350, 110);
    mx_layout_put(profile->layout, profile->edit, 350, 410);
    mx_layout_put(profile->layout, profile->save, 150, 410);
    mx_layout_put(profile->layout, profile->cancel, 550, 410);
}

static void attach_signals(t_info *info, t_profile *profile) {
    g_signal_connect(profile->edit, "clicked", G_CALLBACK(mx_on_click_profile_edit), info);
    g_signal_connect(profile->save, "clicked", G_CALLBACK(mx_on_click_profile_save), info);
    g_signal_connect(profile->cancel, "clicked", G_CALLBACK(mx_on_click_profile_cancel), info);
}

static void set_preferences(t_profile *profile) {
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile->name), "Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(profile->id), "id");

    gtk_entry_set_text(GTK_ENTRY(profile->name), "Loh228");
    gtk_entry_set_text(GTK_ENTRY(profile->id), "1");

    gtk_editable_set_editable(GTK_EDITABLE(profile->name), FALSE);
    gtk_editable_set_editable(GTK_EDITABLE(profile->id), FALSE);

    gtk_widget_set_size_request(profile->edit, 200, 100);
    gtk_widget_set_size_request(profile->save, 200, 100);
    gtk_widget_set_size_request(profile->cancel, 200, 100);
}

t_profile *mx_profile_constructor(t_info *info) {
    t_profile *new = malloc(sizeof(t_profile));

    if (new) {
        // new->image            Ава будущая
        new->scrollable = mx_scrollable_constructor("profile_scrollable", 880, 520);
        new->layout = mx_layout_constructor("profile_layout", 880, 520);
        new->namelabel = mx_label_constructor("profile_name_label", "Username");
        new->idlabel = mx_label_constructor("profile_id_label", "id");
        new->name = mx_entry_constructor("profile_name");
        new->id = mx_entry_constructor("profile_id");
        new->edit = mx_button_constuctor("Edit", "profile_button_edit");
        new->save = mx_button_constuctor("Save", "profile_button_save");
        new->cancel = mx_button_constuctor("Cancel", "profile_button_cancel");

        set_preferences(new);
        attach_signals(info, new);
        attach_layout(info, new);
    }
    return new;
}
