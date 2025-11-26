/* Este header file correspondiente a la activacion de la interfaz gráfica de la 
sección de la calculador */
#ifndef APP_H
#define APP_H
#include <gtk/gtk.h>

// Se declara la función que activa la app
void on_activate(GtkApplication *app, gpointer user_data);

// Se declara la función para aplicar CSS
void apply_css_ohm(void);  // CAMBIAR NOMBRE

void volver_al_menu(GtkWidget *widget, gpointer data);
#endif 