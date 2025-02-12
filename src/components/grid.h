#include <gtk/gtk.h>
#include <tictactoe.hpp>

#ifndef GRID_H
#define GRID_H

class grid {
public:
    grid();
    ~grid();
    GtkWidget *draw();
    void update(int slot);
    static void button_clicked(GtkWidget *button, gpointer data);
    void buttons_set_state(bool state);
    void set_result_label(GtkWidget* label);
    TicTacToe *board;
private:
    GtkWidget *result_label;
    GtkWidget *buttons[3][3];
};

#endif