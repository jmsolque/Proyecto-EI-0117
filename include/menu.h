// En esta sección se tiene el header file para el menu principal de la app
// En esta sección se tiene el header file para el menu principal de la app
#ifndef MENU_H
#define MENU_H
#include <gtk/gtk.h>

// Declaración de funciones del menú principal
void on_menu(GtkApplication *app, gpointer user_data);   // Función que activa la ventana del menú principal
void apply_css_menu();   // Función que aplica el formato CSS al menú principal

// Declaración de funciones para abrir las diferentes calculadoras
void open_calcu_ohm(GtkWidget *widget, gpointer data);   // Abre la calculadora de Ley de Ohm
void open_resistencia(GtkWidget *widget, gpointer data);   // Abre la calculadora de Resistencia por Colores
void open_calcu_potencia(GtkWidget *widget, gpointer data);   // Abre la calculadora de Potencia

// Declaración de función para regresar al menú principal
void volver_menu(GtkWidget *widget, gpointer data);   // Permite volver al menú principal desde cualquier calculadora

// Declaraciones externas de las funciones de las calculadoras 
extern void on_activate_ohm(GtkApplication *app, gpointer user_data);   // Función de activación de la calculadora de Ohm
extern void on_activate_resistencia(GtkApplication *app, gpointer user_data);   // Función de activación de la calculadora de Resistencia
extern void on_activate_potencia(GtkApplication *app, gpointer user_data);   // Función de activación de la calculadora de Potencia

#endif

