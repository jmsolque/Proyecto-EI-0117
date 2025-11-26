#include "poteapp.h"
#include "pot.h"
#include <gtk/gtk.h>

// Esta función sirve para cerrar la ventana de potencia
// y volver a mostrar la ventana del menú principal.
void volver_al_menu_potencia(GtkWidget *widget, gpointer data)
{
    (void)widget;  

    GtkWindow *ventana_pot = GTK_WINDOW(data);

    // Recupera la ventana del menú 
    GtkWindow *menu_window =
        GTK_WINDOW(g_object_get_data(G_OBJECT(ventana_pot), "Menu"));

    // Cierro la ventana de potencia
    gtk_window_close(ventana_pot);

    // Si el menú existe, lo vuelvo a mostrar
    if (menu_window != NULL)
    {
        gtk_widget_set_visible(GTK_WIDGET(menu_window), TRUE);
        gtk_window_present(menu_window);
    }
}

// Aquí voy a ir armando toda la pantalla del módulo de potencia.

void activate_potencia_calculator(GApplication *app, gpointer user_data)
{
    GtkWidget *window;

    
    if (app != NULL)
    {
        window = gtk_application_window_new(GTK_APPLICATION(app));
    }
    else
    {
        window = gtk_window_new();
    }

    gtk_window_set_title(GTK_WINDOW(window), "Calculadora - Potencia");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 350);

    // Guardo la referencia al menú principal para poder regresar luego
    if (user_data != NULL)
    {
        g_object_set_data(G_OBJECT(window), "Menu", user_data);
    }

    // Contenedor principal vertical
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    
    //     Entradas de datos
  

    // Entrada Voltaje
    GtkWidget *hbox_v = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_v);

    GtkWidget *label_v = gtk_label_new("Voltaje (V):");
    gtk_box_append(GTK_BOX(hbox_v), label_v);

    entry_voltaje = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_voltaje), "Ingrese voltaje");
    gtk_box_append(GTK_BOX(hbox_v), entry_voltaje);

    // Entrada Corriente
    GtkWidget *hbox_i = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_i);

    GtkWidget *label_i = gtk_label_new("Corriente (A):");
    gtk_box_append(GTK_BOX(hbox_i), label_i);

    entry_corriente = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_corriente), "Ingrese corriente");
    gtk_box_append(GTK_BOX(hbox_i), entry_corriente);

    // Entrada Resistencia
    GtkWidget *hbox_r = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(main_box), hbox_r);

    GtkWidget *label_r = gtk_label_new("Resistencia (Ω):");
    gtk_box_append(GTK_BOX(hbox_r), label_r);

    entry_resistencia = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_resistencia), "Ingrese resistencia");
    gtk_box_append(GTK_BOX(hbox_r), entry_resistencia);

    
    //     ComboBox de fórmulas
  

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

   
    //     Resultado
    

    label_result = gtk_label_new("Resultado aparecerá aquí");
    gtk_box_append(GTK_BOX(main_box), label_result);

   
    //     Botones
 

    GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(main_box), hbox_buttons);

    GtkWidget *btn_calcular = gtk_button_new_with_label("Calcular");
    g_signal_connect(btn_calcular, "clicked", G_CALLBACK(calcular_potencia), NULL);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_calcular);

    GtkWidget *btn_limpiar = gtk_button_new_with_label("Limpiar");
    g_signal_connect(btn_limpiar, "clicked", G_CALLBACK(limpiar_campos_pot), NULL);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_limpiar);

    GtkWidget *btn_volver = gtk_button_new_with_label("Volver");
    // conecto el botón para que regrese al menú
    g_signal_connect(btn_volver, "clicked", G_CALLBACK(volver_al_menu_potencia), window);
    gtk_box_append(GTK_BOX(hbox_buttons), btn_volver);

    // Muestro la ventana en pantalla
    gtk_window_present(GTK_WINDOW(window));
}
