// En esta sección se tiene el header file para el menu principal de la app
#ifndef MENU_H
#define MENU_H
#include <gtk/gtk.h>

void on_menu(GtkApplication *app, gpointer user_data);
void apply_css_menu();
void open_calcu_ohm(GtkWidget *widget, gpointer data);
void open_resistencia(GtkWidget *widget, gpointer data);
void open_calcu_potencia(GtkWidget *widget, gpointer data);


#endif 