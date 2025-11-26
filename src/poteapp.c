#include "poteapp.h"
#include "pot.h"
#include <gtk/gtk.h>

// Aquí viy a ir construyendo la pantalla del módulo de potencia


void activate_potencia_calculator(GApplication *app, gpointer user_data)
{
    // Creo la ventana principal del módulo de potencia
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora - Potencia");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Caja principal vertical donde luego voy a meter los campos y botones
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // Texto temporal solo para saber que sí abre la ventana
    GtkWidget *label_temp = gtk_label_new("Aquí irá el módulo de potencia :)");
    gtk_box_append(GTK_BOX(main_box), label_temp);

    gtk_widget_show(window);
}
