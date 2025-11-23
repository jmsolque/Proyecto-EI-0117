/* Este header file correspondiente a la activacion de la interfaz gráfica de la 
sección de la calculador */
#ifndef APP_H
#define APP_H
#include <gtk/gtk.h>

// Se declara la función que activa la app
void on_activate(GtkApplication *app, gpointer user_data);  // Esto define la señal para activar el programa

// Se declara la función para aplicar CSS
void apply_css();   // Esto define el formato css que se utiliza en aplicaciones gráficas, las segmenta por capas
void volver_al_menu(GtkWidget *widget, gpointer data);
#endif
