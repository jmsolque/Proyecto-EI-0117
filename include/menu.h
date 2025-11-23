// En esta sección se tiene el header file para el menu principal de la app
#ifndef MENU_H
#define MENU_H
#include <gtk/gtk.h>

void on_activate_menu(GtkApplication *app, gpointer user_data);
void apply_css_menu();
void open_ohm_calculator(GtkWidget *widget, gpointer data);
void open_resistance_calculator(GtkWidget *widget, gpointer data);
void open_power_calculator(GtkWidget *widget, gpointer data);


#endif 