#include "poteapp.h"
#include "pot.h"
#include <gtk/gtk.h>

/*
   CSS estilo, colores 
*/
void apply_css_potencia(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    const char *css =
        " .main_window { "
        "     background: #203850ff;"
        " } "

        " .title_label { "
        "     font-size: 24px; "
        "     font-weight: bold; "
        "     color: #ECF0F1; "
        " } "

        " .input_label { "
        "     font-size: 14px; "
        "     color: #BDC3C7;"
        "     font-weight: bold; "
        " } "

        " .campo_entrada { "
        "     background: #34495E; "
        "     color: white; "
        "     border: 2px solid #4FA3D9; "
        "     border-radius: 8px; "
        "     padding: 8px; "
        " } "

        " .calculate_boton { "
        "     background:rgb(22, 156, 129); "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "

        " .clear_boton { "
        "     background:rgb(143, 145, 147); "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "

        " .back_boton { "
        "     background:rgb(41, 128, 185); "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        "     margin-top: 10px; "
        " } "

        " .result_frame { "
        "     background:rgb(22, 137, 114); "
        "     border-radius: 12px; "
        "     padding: 20px; "
        " } "

        " .result_label { "
        "     font-size: 20px; "
        "     font-weight: bold; "
        "     color: white; "
        " } ";

    gtk_css_provider_load_from_string(provider, css);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(provider);
}

/*
   
   Aquí solo llamo a la función que está en pot.c para que
   active/desactive las cajas según la fórmula que escoja la persona
*/
static void on_formula_combo_changed(GtkComboBox *combo, gpointer user_data)
{
    (void)combo;
    (void)user_data;

    // Esta función está implementada en pot.c
    actualizar_campos_segun_formula();
}

/*
   Esta función cierra la ventana de Potencia
   y vuelve a mostrar el menú principal.
*/
void volver_al_menu_potencia(GtkWidget *widget, gpointer data)
{
    (void)widget;

    GtkWindow *ventana_pot = GTK_WINDOW(data);

    GtkWindow *menu_window =
        GTK_WINDOW(g_object_get_data(G_OBJECT(ventana_pot), "Menu"));

    gtk_window_close(ventana_pot);

    if (menu_window != NULL)
    {
        gtk_widget_set_visible(GTK_WIDGET(menu_window), TRUE);
        gtk_window_present(menu_window);
    }
}

/*
   Aquí esta toda la ventana de la calculadora de Potencia.
   
   
*/
void activate_potencia_calculator(GApplication *app, gpointer user_data)
{
    GtkWindow *menu_window = GTK_WINDOW(user_data);
    GtkWidget *window;

    if (app != NULL)
        window = gtk_application_window_new(GTK_APPLICATION(app));
    else
        window = gtk_window_new();

    gtk_window_set_title(GTK_WINDOW(window), "Calculadora - Potencia");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 550);
    gtk_widget_add_css_class(window, "main_window");

    /* guardo el menú para poder regresar con el botón Volver */
    if (menu_window != NULL)
        g_object_set_data(G_OBJECT(window), "Menu", menu_window);

    /* Caja vertical principal */
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    /* Título grande */
    GtkWidget *title = gtk_label_new("Calculadora - Potencia");
    gtk_widget_add_css_class(title, "title_label");
    gtk_box_append(GTK_BOX(main_box), title);

    /* Grid para acomodar labels + entradas + combo */
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_box_append(GTK_BOX(main_box), grid);

    /* Voltaje*/
    GtkWidget *label_v = gtk_label_new("Voltaje (V):");
    gtk_widget_add_css_class(label_v, "input_label");
    entry_voltaje = gtk_entry_new();
    gtk_widget_add_css_class(entry_voltaje, "campo_entrada");

    gtk_grid_attach(GTK_GRID(grid), label_v,        0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_voltaje,  1, 0, 1, 1);

    /* corriente */
    GtkWidget *label_i = gtk_label_new("Corriente (A):");
    gtk_widget_add_css_class(label_i, "input_label");
    entry_corriente = gtk_entry_new();
    gtk_widget_add_css_class(entry_corriente, "campo_entrada");

    gtk_grid_attach(GTK_GRID(grid), label_i,          0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_corriente,  1, 1, 1, 1);

    /* resistencia */
    GtkWidget *label_r = gtk_label_new("Resistencia (Ω):");
    gtk_widget_add_css_class(label_r, "input_label");
    entry_resistencia = gtk_entry_new();
    gtk_widget_add_css_class(entry_resistencia, "campo_entrada");

    gtk_grid_attach(GTK_GRID(grid), label_r,            0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_resistencia,  1, 2, 1, 1);

    /* formula combo */
    GtkWidget *label_f = gtk_label_new("Fórmula:");
    gtk_widget_add_css_class(label_f, "input_label");
    combo_formula = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = V * I");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = V² / R");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_formula), "P = I² * R");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_formula), 0);

    gtk_grid_attach(GTK_GRID(grid), label_f,       0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), combo_formula, 1, 3, 1, 1);

    /* Botones de Calcular y Limpiar */
    GtkWidget *boton_calc = gtk_button_new_with_label("Calcular");
    gtk_widget_add_css_class(boton_calc, "calculate_boton");

    GtkWidget *boton_clear = gtk_button_new_with_label("Limpiar");
    gtk_widget_add_css_class(boton_clear, "clear_boton");

    GtkWidget *boton_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(boton_box), boton_calc);
    gtk_box_append(GTK_BOX(boton_box), boton_clear);
    gtk_box_append(GTK_BOX(main_box), boton_box);

    /* Botón de volver al menú principal */
    GtkWidget *back_boton = gtk_button_new_with_label("Volver al Menú Principal");
    gtk_widget_add_css_class(back_boton, "back_boton");
    g_signal_connect(back_boton, "clicked",
                     G_CALLBACK(volver_al_menu_potencia), window);
    gtk_box_append(GTK_BOX(main_box), back_boton);

    /* Espacio antes del resultado */
    GtkWidget *space = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_append(GTK_BOX(main_box), space);

    /* Cuadro de resultado  */
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_widget_add_css_class(frame, "result_frame");
    gtk_box_append(GTK_BOX(main_box), frame);

    label_result = gtk_label_new("Resultado aparecerá aquí");
    gtk_widget_add_css_class(label_result, "result_label");
    gtk_frame_set_child(GTK_FRAME(frame), label_result);

    /* Conexión de señales de botones */
    g_signal_connect(boton_calc,  "clicked",
                     G_CALLBACK(calcular_potencia), NULL);
    g_signal_connect(boton_clear, "clicked",
                     G_CALLBACK(limpiar_campos_pot), NULL);

    /* Enter en las cajas de texto */
    g_signal_connect(entry_voltaje,     "activate",
                     G_CALLBACK(enter_calcular_pot), NULL);
    g_signal_connect(entry_corriente,   "activate",
                     G_CALLBACK(enter_calcular_pot), NULL);
    g_signal_connect(entry_resistencia, "activate",
                     G_CALLBACK(enter_calcular_pot), NULL);

    /* Cuando cambia la fórmula del combo, actualizar campos */
    g_signal_connect(combo_formula, "changed",
                     G_CALLBACK(on_formula_combo_changed), NULL);

    
    apply_css_potencia();
    actualizar_campos_segun_formula();

    /* Muestra la ventana en pantalla */
    gtk_window_present(GTK_WINDOW(window));
}
