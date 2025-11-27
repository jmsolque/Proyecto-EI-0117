#include "poteapp.h"
#include "pot.h"
#include <gtk/gtk.h>

/*
    Css
*/
void apply_css_potencia(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    const char *css =
        ".pot_window {"
        "   background: #2C3E50;"   /* color de fondo */
        "}"
        ".pot_label {"
        "   color: white;"
        "   font-weight: bold;"
        "}"
        ".pot_entry {"
        "   background: #34495E;"
        "   color: white;"
        "   border-radius: 6px;"
        "   padding: 4px;"
        "}"
        ".pot_button {"
        "   background: #1ABC9C;"
        "   color: white;"
        "   border-radius: 8px;"
        "   padding: 6px;"
        "}";

    gtk_css_provider_load_from_data(provider, css, -1);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}


/*
    Esta función sirve para cerrar la ventana del módulo de potencia
    y volver a mostrar la ventana del menú principal.
*/
void volver_al_menu_potencia(GtkWidget *widget, gpointer data)
{
    (void)widget;  

    GtkWindow *ventana_pot = GTK_WINDOW(data);

    // Aquí recupero la ventana del menú que guardamos en la ventana
    GtkWindow *menu_window =
        GTK_WINDOW(g_object_get_data(G_OBJECT(ventana_pot), "Menu"));

    // Cierro esta ventana
    gtk_window_close(ventana_pot);

    // Si el menú existe, lo muestro otra vez
    if (menu_window != NULL)
    {
        gtk_widget_set_visible(GTK_WIDGET(menu_window), TRUE);
        gtk_window_present(menu_window);
    }
}


/*
    Aquí arme toda la ventana de la calculadora de potencia.
    Esta es la estructura básica entradas, combo de fórmulas,
    resultado y botones.
*/
void activate_potencia_calculator(GApplication *app, gpointer user_data)
{
    GtkWidget *window;

    
    if (app != NULL)
        window = gtk_application_window_new(GTK_APPLICATION(app));
    else
        window = gtk_window_new();

    gtk_window_set_title(GTK_WINDOW(window), "Calculadora - Potencia");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);

  
    if (user_data != NULL)
        g_object_set_data(G_OBJECT(window), "Menu", user_data);

    // Caja vertical principal
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);


    /*  ENTRADA: VOLTAJE  */
    GtkWidget *hbox_v = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_v);

    GtkWidget *label_v = gtk_label_new("Voltaje (V):");
    gtk_box_append(GTK_BOX(hbox_v), label_v);

    entry_voltaje = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_voltaje), "Ingrese voltaje");
    gtk_box_append(GTK_BOX(hbox_v), entry_voltaje);


    /*  ENTRADA: CORRIENTE  */
    GtkWidget *hbox_i = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_i);

    GtkWidget *label_i = gtk_label_new("Corriente (A):");
    gtk_box_append(GTK_BOX(hbox_i), label_i);

    entry_corriente = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_corriente), "Ingrese corriente");
    gtk_box_append(GTK_BOX(hbox_i), entry_corriente);


    /*  ENTRADA: RESISTENCIA  */
    GtkWidget *hbox_r = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_r);

    GtkWidget *label_r = gtk_label_new("Resistencia (Ω):");
    gtk_box_append(GTK_BOX(hbox_r), label_r);

    entry_resistencia = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_resistencia), "Ingrese resistencia");
    gtk_box_append(GTK_BOX(hbox_r), entry_resistencia);


    /*   COMBOBOX DE FÓRMULAS  */
    GtkWidget *hbox_combo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_combo);

    GtkWidget *label_f = gtk_label_new("Fórmula:");
    gtk_box_append(GTK_BOX(hbox_combo), label_f);

    combo_formula = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = V * I");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = V² / R");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = I² * R");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_formula), 0);
    gtk_box_append(GTK_BOX(hbox_combo), combo_formula);


    /* ---  RESULTADO  ---*/
    label_result = gtk_label_new("Resultado aparecerá aquí");
    gtk_box_append(GTK_BOX(main_box), label_result);


    /* -- BOTONES ---*/
    GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(main_box), hbox_buttons);

    GtkWidget *btn_calcular = gtk_button_new_with_label("Calcular");
    g_signal_connect(btn_calcular, "clicked", G_CALLBACK(calcular_potencia), NULL);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_calcular);

    GtkWidget *btn_limpiar = gtk_button_new_with_label("Limpiar");
    g_signal_connect(btn_limpiar, "clicked", G_CALLBACK(limpiar_campos_pot), NULL);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_limpiar);

    GtkWidget *btn_volver = gtk_button_new_with_label("Volver");
    g_signal_connect(btn_volver, "clicked", G_CALLBACK(volver_al_menu_potencia), window);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_volver);


    /* Mostrar todo */
    gtk_window_present(GTK_WINDOW(window));
}
