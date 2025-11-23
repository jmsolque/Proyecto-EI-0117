// Aquí va el código correspondiente al menu principal 
#include "menu.h"
#include <stdio.h>

void apply_css_menu() {
    GtkCssProvider *provider = gtk_css_provider_new();

    const char *css =
        " .main-window { "
        "     background: #2C3E50;"
        " } "
        " .title-label { "
        "     font-size: 28px; "
        "     font-weight: bold; "
        "     color: #ECF0F1; "
        "     margin-bottom: 30px; "
        " } "
        " .menu-button { "
        "     background: rgb(22, 156, 129); "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 15px; "
        "     font-size: 16px; "
        "     font-weight: bold; "
        "     margin: 10px; "
        "     min-width: 200px; "
        " } "
        " .menu-button:hover { "
        "     background: rgb(18, 130, 108); "
        " } ";

    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void open_calcu_ohm(GtkWidget *widget, gpointer data) {
    printf("Abriendo calculadora de Ley de Ohm...\n");
    // Aquí llamarás a la función que abre la calculadora de Ohm
}

void open_resistencia(GtkWidget *widget, gpointer data) {
    printf("Abriendo calculadora de Resistencia por Colores...\n");
    // Aquí llamarás a la función que abre la calculadora de Resistencia
}

void open_calcu_potencia(GtkWidget *widget, gpointer data) {
    printf("Abriendo calculadora de Potencia...\n");
    // Aquí llamarás a la función que abre la calculadora de Potencia
}

void on_menu(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora Electrónica - Menú Principal");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_add_css_class(window, "main-window");

    // Caja principal vertical
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // Título
    GtkWidget *title = gtk_label_new("Calculadora Electrónica");
    gtk_widget_add_css_class(title, "title-label");
    gtk_box_append(GTK_BOX(main_box), title);

    // Espacio
    GtkWidget *space1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_append(GTK_BOX(main_box), space1);

    // Botón Ley de Ohm
    GtkWidget *ohm_button = gtk_button_new_with_label("Ley de Ohm");
    gtk_widget_add_css_class(ohm_button, "menu-button");
    g_signal_connect(ohm_button, "clicked", G_CALLBACK(open_calcu_ohm), NULL);
    gtk_box_append(GTK_BOX(main_box), ohm_button);

    // Botón Resistencia por Colores
    GtkWidget *res_button = gtk_button_new_with_label("Resistencia por Colores");
    gtk_widget_add_css_class(res_button, "menu-button");
    g_signal_connect(res_button, "clicked", G_CALLBACK(open_resistencia), NULL);
    gtk_box_append(GTK_BOX(main_box), res_button);

    // Botón Calculadora de Potencia
    GtkWidget *power_button = gtk_button_new_with_label("Calculadora de Potencia");
    gtk_widget_add_css_class(power_button, "menu-button");
    g_signal_connect(power_button, "clicked", G_CALLBACK(open_calcu_potencia), NULL);
    gtk_box_append(GTK_BOX(main_box), power_button);

    // Espacio inferior
    GtkWidget *space2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    gtk_box_append(GTK_BOX(main_box), space2);

    apply_css_menu();
    gtk_window_present(GTK_WINDOW(window));
}