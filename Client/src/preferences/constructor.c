#include "client.h"

static void attach_layout(t_info *info, t_preferences *pref) {
    mx_layout_put(info->layout, pref->scroll, 300, 100);

    mx_scrollable_container_add(pref->scroll, pref->layout);

    mx_layout_put(pref->layout, pref->theme_label, 100, 20);
    mx_layout_put(pref->layout, pref->theme_switch, 100, 40);
    mx_layout_put(pref->layout, pref->s_notify_switch, 100, 120);
    mx_layout_put(pref->layout, pref->v_notify_switch, 100, 220);
    mx_layout_put(pref->layout, pref->e_notify_switch, 100, 320);
    mx_layout_put(pref->layout, pref->volume_label, 100, 400);
    mx_layout_put(pref->layout, pref->volume, 100, 420);
}

static void attach_signals(t_info *info, t_preferences *pref) {
    MX_GSIG_CON(pref->theme_switch, "state-set", MX_CB(mx_on_click_theme_switch), info);
    MX_GSIG_CON(pref->s_notify_switch, "toggled", MX_CB(mx_on_click_snoti_switch), info);
    MX_GSIG_CON(pref->v_notify_switch, "toggled", MX_CB(mx_on_click_vnoti_switch), info);
    MX_GSIG_CON(pref->e_notify_switch, "toggled", MX_CB(mx_on_click_enoti_switch), info);
}

static void set_preferences(t_info *info, t_preferences *pref) {
    t_profile_data *data = info->cl_data->profile;

    gtk_widget_set_size_request(pref->volume, 300, 50);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->s_notify_switch), data->sound_noty);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->v_notify_switch), data->vs_noty);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->e_notify_switch), data->email_noty);
}

t_preferences *mx_preferences_constructor(t_info *info) {
    t_preferences *new = malloc(sizeof(t_preferences));

    if (new) {
        new->scroll = mx_scrollable_constructor("preferences_scroll", 880, 520);
        new->layout = mx_layout_constructor("prefernces_layout", 880, 520);
        new->volume_label = mx_label_constructor("volume_label", "Sound notify volume");
        new->volume = mx_scale_horizotal_constructor("volume_scale", 0, 100, 1);
        new->theme_label = mx_label_constructor("theme_label", "Change theme(dark, light)");
        new->theme_switch = mx_switch_button_constuctor("switch_button");
        new->s_notify_switch = mx_check_button_constuctor("sound_switch", "Wanna be notified by sound?");
        new->v_notify_switch = mx_check_button_constuctor("visual_switch", "Wanna be notified visually notified?");
        new->e_notify_switch = mx_check_button_constuctor("email_switch", "Wanna be notified by email?");

        set_preferences(info, new);
        attach_signals(info, new);
        attach_layout(info, new);
    }
    return new;
}
