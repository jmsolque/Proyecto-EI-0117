#include <gtk/gtk.h>

//Estructura base app
typedef struct {
    GtkWidget *main_window;
} AppData;


//Funcion principal 
void app_activate(GApplication *app, gpointer user_data)
{
    AppData *data = g_new0(AppData, 1);

    // Crear la ventana
   data->main_window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(data->main_window), "Calculadora de Resistencias");
    gtk_window_set_default_size(GTK_WINDOW(data->main_window), 600, 400);

    // Un label placeholder
    GtkWidget *label = gtk_label_new("Interfaz inicial lista...");
    gtk_window_set_child(GTK_WINDOW(data->main_window), label);

    gtk_window_present(GTK_WINDOW(data->main_window));
}


// Funcion main
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.resistorcalc", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
