#include "client.h"

static void attach_layout(t_info *info, t_profile *profile) {
    mx_layout_put(info->layout, profile->scrollable, 300, 100);

    mx_scrollable_container_add(profile->scrollable, profile->layout);

    mx_layout_put(profile->layout, profile->statuslb, 20, 80);
    mx_layout_put(profile->layout, profile->status, 20, 110);
    mx_layout_put(profile->layout, profile->namelb, 20, 150);
    mx_layout_put(profile->layout, profile->name, 20, 170);
    mx_layout_put(profile->layout, profile->fnamelb, 20, 210);
    mx_layout_put(profile->layout, profile->fname, 20, 230);
    mx_layout_put(profile->layout, profile->snamelb, 20, 270);
    mx_layout_put(profile->layout, profile->sname, 20, 290);
    mx_layout_put(profile->layout, profile->emaillb, 20, 330);
    mx_layout_put(profile->layout, profile->email, 20, 350);

    mx_layout_put(profile->layout, profile->edit, 350, 410);
    mx_layout_put(profile->layout, profile->save, 150, 410);
    mx_layout_put(profile->layout, profile->cancel, 550, 410);
}

static void attach_signals(t_info *info, t_profile *profile) {
    MX_GSIG_CON(profile->edit, "clicked", MX_CB(mx_on_click_profile_edit), info);
    MX_GSIG_CON(profile->save, "clicked", MX_CB(mx_on_click_profile_save), info);
    MX_GSIG_CON(profile->cancel, "clicked", MX_CB(mx_on_click_profile_cancel), info);
}

static void set_preferences(t_profile *profile) {
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
        new->edit = mx_button_constuctor("Edit", "profile_button_edit");
        new->save = mx_button_constuctor("Save", "profile_button_save");
        new->cancel = mx_button_constuctor("Cancel", "profile_button_cancel");

        mx_profile_create_labels(info, new);
        mx_profile_create_entrys(info, new);
        set_preferences(new);
        attach_signals(info, new);
        attach_layout(info, new);
    }
    return new;
}
