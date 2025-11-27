#include <gtk/gtk.h>
#include "app.h"
#include "menu.h"
#include "resistor_calc.h"
#include "poteapp.h"

/*
    Esta función se encarga de abrir la calculadora de la Ley de Ohm
    
*/
void on_activate_ohm(GtkApplication *app, gpointer user_data) {
    on_activate(app, user_data);
}

/*
    Esta función abre la calculadora de resistencias por colores.
    
*/
void on_activate_resistencia(GtkApplication *app, gpointer user_data) {
    app_activate(G_APPLICATION(app), user_data);
}

/*
    Esta función abre la calculadora de Potencia.
    
*/
void on_activate_potencia(GtkApplication *app, gpointer user_data) {
    activate_potencia_calculator(G_APPLICATION(app), user_data);
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    /*
        Aquí se crea la aplicación principal GTK.
        
    */
    app = gtk_application_new("com.electronica.calculator", G_APPLICATION_DEFAULT_FLAGS);

    /*
        Cuando la aplicación se activa, queremos que aparezca el menú principal.
        Por eso conectamos la señal activate con la función on_menu().
    */
    g_signal_connect(app, "activate", G_CALLBACK(on_menu), NULL);

    /*
        Esta línea ejecuta toda la aplicación GTK.
        Aquí se queda esperando mientras el usuario usa el programa.
    */
    status = g_application_run(G_APPLICATION(app), argc, argv);

    /*
        Cuando la aplicación se cierra, liberamos la memoria de la app.
    */
    g_object_unref(app);

    return status;
}
