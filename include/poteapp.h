#ifndef POTEAPP_H
#define POTEAPP_H

#include <gtk/gtk.h>

// Esta función es la que abre la ventana de potencia.

void activate_potencia_calculator(GApplication *app, gpointer user_data);

// Esta función sirve para aplicar un CSS sencillo al módulo de potencia.

void apply_css_potencia(void);

// Esta función sirve para volver al menú principal.

void volver_al_menu_potencia(GtkWidget *widget, gpointer data);

#endif
