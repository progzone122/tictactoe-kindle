#include "menu.h"
#include <iostream>
#include <vector>

menu::menu() {
    menu_bar = gtk_hbox_new(FALSE, 5);
}

menu::~menu() {
    gtk_widget_destroy(menu_bar);
}

GtkWidget* menu::draw() {
    return menu_bar;
}

void menu::set_items(const std::vector<menuItem>& items) {
    for (const auto& item : items) {
        GtkWidget *button = gtk_button_new_with_label(item.name.c_str());

        g_signal_connect_data(button, "clicked", item.callback, item.user_data, NULL, G_CONNECT_AFTER);

        gtk_box_pack_start(GTK_BOX(menu_bar), button, TRUE, TRUE, 5);
    }
    gtk_widget_show_all(menu_bar);
}