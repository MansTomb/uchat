#include "client.h"

static void set_group_names(t_contact_add *ac) {
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ac->combobox), "Loh228");
}

void mx_add_contact_build(t_info *info, t_contact_add *ac) {
    if (ac == NULL)
        info->windows->ac = ac = malloc(sizeof(t_contact_add));

    ac->builder = gtk_builder_new();
    gtk_builder_add_from_file(ac->builder, "./Resources/glade/add_contact.glade", NULL);

    ac->dialog = GTK_WIDGET(gtk_builder_get_object(ac->builder, "dialog"));
    ac->addbt = GTK_WIDGET(gtk_builder_get_object(ac->builder, "add"));
    ac->cancelbt = GTK_WIDGET(gtk_builder_get_object(ac->builder, "cancel"));
    ac->entry = GTK_WIDGET(gtk_builder_get_object(ac->builder, "entry"));
    ac->combobox = GTK_WIDGET(gtk_builder_get_object(ac->builder, "combo_box"));
    ac->nameslist = GTK_TREE_STORE(gtk_builder_get_object(ac->builder, "names"));
    gtk_builder_connect_signals(ac->builder, ac);

    set_group_names(ac);
    ac->info = info;

    gtk_widget_show(ac->dialog);
} 

void mx_add_contact_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->ac->dialog);
    free(info->windows->ac);
    info->windows->ac = NULL;
}
