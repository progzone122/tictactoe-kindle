#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
#include <gtk/gtk.h>

using namespace std;

struct menuItem {
    string name;
    GCallback callback;
    gpointer user_data;
};

class menu {
public:
    menu();
    ~menu();

    GtkWidget *draw();
    void set_items(const vector<menuItem> &items);

private:
    vector<menuItem> items;
    GtkWidget *menu_bar;
};



#endif //MENU_H
