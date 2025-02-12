#include "grid.h"
#include <stdio.h>

grid::grid() {
    board = new TicTacToe();
    result_label = nullptr;
}

grid::~grid() {
    delete board;
    delete result_label;
}

GtkWidget* grid::draw() {
    GtkWidget *table = gtk_table_new(3, 3, TRUE);
    auto grid = board->getGrid();

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            GtkWidget *button = gtk_button_new_with_label("");

            int index = row * 3 + col;
            gtk_widget_set_name(button, std::to_string(index).c_str());

            gtk_button_set_label(GTK_BUTTON(button), std::string(1, grid[row][col]).c_str());

            g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), this);

            buttons[row][col] = button;

            gtk_table_attach_defaults(GTK_TABLE(table), button, col, col + 1, row, row + 1);
        }
    }

    return table;
}

void grid::button_clicked(GtkWidget *button, gpointer data) {
    grid *instance = static_cast<grid*>(data);

    const char* name = gtk_widget_get_name(button);
    int index = stoi(name);

    if (DEBUG) {
        std::cout << "[DEBUG] button_clicked: " << index << std::endl;
    }

    if (!instance->board->placeMarker(index + 1)) {
        return;
    }

    if (instance->result_label) {
        int winner = instance->board->checkWinner();

        if (winner == 1) {
            gtk_label_set_text(GTK_LABEL(instance->result_label), "Player 1 (X) wins!");
            instance->buttons_set_state(FALSE);
        } else if (winner == 2) {
            gtk_label_set_text(GTK_LABEL(instance->result_label), "Player 2 (O) wins!");
            instance->buttons_set_state(FALSE);
        } else {
            gtk_label_set_text(GTK_LABEL(instance->result_label), "");
            instance->buttons_set_state(TRUE);
        }
    }

    instance->update(index);

    instance->board->switchPlayer();
}

void grid::update(int index) {
    int row = index / 3;
    int col = index % 3;

    auto grid = board->getGrid();
    gtk_button_set_label(GTK_BUTTON(buttons[row][col]), std::string(1, grid[row][col]).c_str());
}

void grid::set_result_label(GtkWidget* label) {
    result_label = label;
}

void grid::buttons_set_state(bool state) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            gtk_widget_set_sensitive(buttons[row][col], state);
        }
    }
}