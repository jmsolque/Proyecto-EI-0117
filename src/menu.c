// Aquí va el código correspondiente al menu principal 
#include "menu.h"
#include <stdio.h>

static GtkWindow *menu_principal = NULL;  // Guarda el "path" al menu principal 

void apply_css_menu() {
    GtkCssProvider *provider = gtk_css_provider_new();  // Aplica el estilo css 

    const char *css =
        " .main-window { "
              "background: #2C3E50;"   // Fondo de la ventana principal 
        " } "
        " .title-label { "   // Titulo principal de la app
              "font-size: 28px; "   // Tamaño de letra
              "font-weight: bold; "   // Letra negrita
              "color: #ECF0F1; "   // Color de letra
              "margin-bottom: 30px; "   
        " } "
        " .botones { "   // Caracterisiticas de los botones
              "background: rgb(22, 156, 129); "
              "color: white; "    // Clor del borde
              "border-radius: 8px; "   // Radio de las esquinas 
              "padding: 15px; "   // Relleno del botón 
              "font-size: 16px; "
              "font-weight: bold; "
              "margin: 10px; "  
              "min-width: 200px; "   // Ancho minimo del botón 
        " } "
        " .boton_clic { "   // Define el comportamiento de los botones al dar clic
              "background: rgb(18, 130, 108); "
        " } "
        " .regresar_menu { "
              "background: rgb(143, 145, 147); "
              "color: white; "
              "border-radius: 8px; "
              "padding: 10px; "
              "margin-top: 20px; "
        " } ";

    gtk_css_provider_load_from_string(provider, css);   // Aplica el estilo css a los botones definidos

    gtk_style_context_add_provider_for_display(   
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);    // Libera la memoria utilizada para implementar el esitlo css
}

// Función para volver al menú principal desde cualquier calculadora
void volver_menu(GtkWidget *widget, gpointer data) {
    (void)widget;
    
    GtkWindow *current_window = GTK_WINDOW(data);
    
    gtk_window_close(current_window);   // Cierra la ventana actual de la calculadora
    
    // Muestra el menú principal y asegura que los estilos se aplica para mentener los colores
    if (menu_principal != NULL) {
        gtk_widget_set_visible(GTK_WIDGET(menu_principal), TRUE);
        gtk_window_present(menu_principal);   // Imprime el vantana del menu princiapal 
        apply_css_menu();   // Fuerza que se vuelva a aplicar el estilo css por que sino muestra colores por defecto 
    } else {
        printf("Menú principal no encontrado\n");  // Si no hay menu escribe un mensaje 
    }
}

// Llama la función que abre la calculadora de Ohm
void open_calcu_ohm(GtkWidget *widget, gpointer data) {
    (void)widget;
    (void)data;
    
    if (menu_principal != NULL) {   // Oculta el menu mientras se usa la calculadora
        gtk_widget_set_visible(GTK_WIDGET(menu_principal), FALSE);
    }
 
    on_activate_ohm(NULL, menu_principal);   // Llama la función que abre la calculadora de Ohm
}

// Llama la función que abre la calculadora de Resistencia por colores
void open_resistencia(GtkWidget *widget, gpointer data) {
    (void)widget;
    (void)data;
    
    if (menu_principal != NULL) {   // Oculta el menu mientras se usa la calculadora
        gtk_widget_set_visible(GTK_WIDGET(menu_principal), FALSE);
    }

    on_activate_resistencia(NULL, menu_principal);   // Llama la función que abre la calculadora de Ohm
}

// Llama la función que abre la calculadora de Potencia
void open_calcu_potencia(GtkWidget *widget, gpointer data) {
    (void)widget;
    (void)data;
    
    if (menu_principal != NULL) {   // Oculta el menu mientras se usa la calculadora
        gtk_widget_set_visible(GTK_WIDGET(menu_principal), FALSE);
    }
    
    on_activate_potencia(NULL, menu_principal);  // Llama la función que abre la calculadora de Potencia
}


// En esta sección se configuran las capas de la aplicación 
void on_menu(GtkApplication *app, gpointer user_data) {
    (void)user_data;
    
    GtkWidget *window = gtk_application_window_new(app);   // Crea una ventana de aplicación 
    menu_principal = GTK_WINDOW(window);  
    
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora Electrónica");   // Define el titulo de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);   // Define el tamaño de la ventana
    gtk_widget_add_css_class(window, "main-window");  // Define que es la ventana principal 

    // Caja principal vertical
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);   // Crea una caja vertical para organizar elementos
    gtk_window_set_child(GTK_WINDOW(window), main_box);  // Hace que esta caja sea hijo de la caja principal

    // Titulo del programa
    GtkWidget *title = gtk_label_new("Calculadora Electrónica");
    gtk_widget_add_css_class(title, "title-label");   // Utiliza la configuración del titulo que se definio arriba
    gtk_box_append(GTK_BOX(main_box), title);   // Añade el titulo a la ventana principal main

    // Espacio  vacío entre el titulo y los botones
    GtkWidget *space1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_append(GTK_BOX(main_box), space1);

    // Botón Ley de Ohm
    GtkWidget *ohm_boton = gtk_button_new_with_label("Ley de Ohm");  // Crea el botón que invoca la función de la ley de Ohm
    gtk_widget_add_css_class(ohm_boton, "botones");   // Le da el formato al botón
    g_signal_connect(ohm_boton, "clicked", G_CALLBACK(open_calcu_ohm), NULL); // Hace que el botón se active al darle clic
    gtk_box_append(GTK_BOX(main_box), ohm_boton);   // Abre la caluladora en la ventana principal 

    // Botón Resistencia por Colores
    GtkWidget *res_boton = gtk_button_new_with_label("Resistencia por Colores");
    gtk_widget_add_css_class(res_boton, "botones");
    g_signal_connect(res_boton, "clicked", G_CALLBACK(open_resistencia), NULL);
    gtk_box_append(GTK_BOX(main_box), res_boton);

    // Botón Calculadora de Potencia
    GtkWidget *potencia_boton = gtk_button_new_with_label("Calculadora de Potencia");
    gtk_widget_add_css_class(potencia_boton, "botones");  
    g_signal_connect(potencia_boton, "clicked", G_CALLBACK(open_calcu_potencia), NULL);
    gtk_box_append(GTK_BOX(main_box), potencia_boton);

    // Espacio entre los botones de las funciones y los botones inferirores 
    GtkWidget *space2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 50);
    gtk_box_append(GTK_BOX(main_box), space2);

    apply_css_menu();   // Invoca el estilo css a la ventana 
    gtk_window_present(GTK_WINDOW(window));  //Muestra la ventana al usuario 
}