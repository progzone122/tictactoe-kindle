#include <iostream>
#include <gtk/gtk.h>
#include <string>

#include "config.hpp"

using namespace std;

#include "components/grid.h"
#include "components/menu.h"

void reset_board(GtkWidget *widget, gpointer user_data) {
    if (!user_data) {
        cerr << "Error: user_data == nullptr via reset_board!" << endl;
        return;
    }

    auto* board = static_cast<grid*>(user_data);

    board->board->reset();

    // Update the state of all buttons
    for (int i = 0; i < 9; ++i) {
        board->update(i);
    }

    board->buttons_set_state(TRUE);
}


int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window, DESKTOP_W_SIZE, DESKTOP_H_SIZE);
    gtk_window_set_title(GTK_WINDOW(window), TITLE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    menu menu;
    grid game_grid;

    GtkWidget *vbox_main = gtk_vbox_new(FALSE, 5);
    GtkWidget *vbox_menu = gtk_vbox_new(FALSE, 5);

    GtkWidget *hbox_result = gtk_hbox_new(FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox_result), 15);

    GtkWidget *result_label = gtk_label_new("");
    game_grid.set_result_label(result_label);

    GtkWidget *alignment_result = gtk_alignment_new(0.5, 0, 1, 0);
    gtk_container_add(GTK_CONTAINER(alignment_result), result_label);

    gtk_box_pack_start(GTK_BOX(hbox_result), alignment_result, TRUE, TRUE, 0);

    GtkWidget *table = game_grid.draw();
    gtk_widget_set_size_request(table, 400, 400);

    menu.set_items({
    {"Exit",  G_CALLBACK(gtk_main_quit), NULL},
    {"Restart",  G_CALLBACK(reset_board), &game_grid}
    });

    GtkWidget *top_menu = menu.draw();

    GtkWidget *alignment = gtk_alignment_new(0.5, 0.3, 0, 0);
    gtk_container_add(GTK_CONTAINER(alignment), table);

    gtk_box_pack_start(GTK_BOX(vbox_menu), top_menu, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox_main), hbox_result, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_main), alignment, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox_main), vbox_menu, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox_main);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}