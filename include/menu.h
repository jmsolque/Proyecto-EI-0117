// En esta sección se tiene el header file para el menu principal de la app
#ifndef MENU_H
#define MENU_H
#include <gtk/gtk.h>

// Declara las funciones del menú principal
void on_menu(GtkApplication *app, gpointer user_data);   // Función que activa la ventana del menú principal
void apply_css_menu();   // Función que aplica el formato CSS al menú principal

// Declaración de funciones para abrir las diferentes calculadoras
void open_calcu_ohm(GtkWidget *widget, gpointer data);   // Abre la calculadora de ley de Ohm
void open_resistencia(GtkWidget *widget, gpointer data);   // Abre la calculadora de Resistencia por Colores
void open_calcu_potencia(GtkWidget *widget, gpointer data);   // Abre la calculadora de Potencia

// Declara las funciones para regresar al menú principal
void volver_menu(GtkWidget *widget, gpointer data);   // Hace que se devuelva al menu principal desde cualquier modulo 

// Declara las funciones de las calculadoras 
extern void on_activate_ohm(GtkApplication *app, gpointer user_data);   // Activar la calculadora de ley de Ohm
extern void on_activate_resistencia(GtkApplication *app, gpointer user_data);   // Activar la calculadora de Resistencia por colores
extern void on_activate_potencia(GtkApplication *app, gpointer user_data);   // Activar  la calculadora de Potencia

#endif

