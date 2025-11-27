#include <gtk/gtk.h>
#include <math.h>
#include "resistor_calc.h"


// ----- Mapeos de Colores -----
const char *colores[] = {
    "Negro", "Marrón", "Rojo", "Naranja", "Amarillo",
    "Verde", "Azul", "Violeta", "Gris", "Blanco", "Oro", "Plata"
};


const double rgb_colores[12][3] = {
    {0.0, 0.0, 0.0}, {0.36, 0.17, 0.09}, {0.89, 0.0, 0.03}, {1.0, 0.36, 0.0},
    {1.0, 0.87, 0.0}, {0.0, 0.5, 0.25}, {0.0, 0.2, 0.65}, {0.42, 0.25, 0.63},
    {0.62, 0.62, 0.62}, {1.0, 1.0, 1.0}, {0.83, 0.68, 0.21}, {0.75, 0.75, 0.75}
};


const double multiplicadores[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 0.1, 0.01
};


const char *tolerancias_texto[] = {
    "Marrón ±1%", "Rojo ±2%", "Oro ±5%", "Plata ±10%"
};
const int tolerancia_indices[] = {1, 2, 10, 11};


// ----- Función para volver al menú -----
void volver_menu_resistor(GtkWidget *widget, gpointer user_data) {
    // CORRECCIÓN: Marcar parámetro no usado
    (void)widget;
   
    AppData *data = (AppData *)user_data;
    GtkWindow *menu_window = GTK_WINDOW(g_object_get_data(G_OBJECT(data->window), "Menu"));
   
    // Cerrar la ventana actual de resistencia
    gtk_window_close(GTK_WINDOW(data->window));
   
    // Mostrar el menú principal y re-aplicar sus estilos
    if (menu_window != NULL) {
        gtk_widget_set_visible(GTK_WIDGET(menu_window), TRUE);
        gtk_window_present(menu_window);
    }
}


// ----- Función de Cálculo -----
void actualizar_valor(AppData *data) {
    int digito1 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int digito2 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult_idx = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol_idx = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));


    double mult = multiplicadores[mult_idx];
    double valor = ((digito1 * 10) + digito2) * mult;


    const char *tol_text = tolerancias_texto[tol_idx];
    char texto[128];


    if (valor >= 1000000)
        snprintf(texto, sizeof(texto), "%.2f MΩ %s", valor / 1e6, tol_text);
    else if (valor >= 1000)
        snprintf(texto, sizeof(texto), "%.2f kΩ %s", valor / 1e3, tol_text);
    else
        snprintf(texto, sizeof(texto), "%.0f Ω %s", valor, tol_text);


    gtk_label_set_text(GTK_LABEL(data->label_resultado), texto);
    gtk_widget_queue_draw(data->drawing_area);
}


// ----- Dibujo Minimalista con Degradado -----
void draw_resistor(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    // CORRECCIÓN: Marcar parámetro no usado
    (void)area;
   
    AppData *data = (AppData *)user_data;
    cairo_set_source_rgb(cr, 0.06, 0.1, 0.17); // Fondo azul oscuro
    cairo_paint(cr);


    double body_width = width * 0.5;
    double body_height = height * 0.25;
    double body_x = (width - body_width) / 2;
    double body_y = (height - body_height) / 2;


    cairo_set_line_width(cr, 6);
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.8);
    cairo_move_to(cr, body_x - 40, body_y + body_height / 2);
    cairo_line_to(cr, body_x, body_y + body_height / 2);
    cairo_move_to(cr, body_x + body_width, body_y + body_height / 2);
    cairo_line_to(cr, body_x + body_width + 40, body_y + body_height / 2);
    cairo_stroke(cr);


    cairo_pattern_t *pat = cairo_pattern_create_linear(body_x, body_y, body_x, body_y + body_height);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.12, 0.18, 0.29);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.18, 0.26, 0.39);


    double radius = 10.0;
    cairo_new_sub_path(cr);
    cairo_arc(cr, body_x + body_width - radius, body_y + radius, radius, -M_PI / 2, 0);
    cairo_arc(cr, body_x + body_width - radius, body_y + body_height - radius, radius, 0, M_PI / 2);
    cairo_arc(cr, body_x + radius, body_y + body_height - radius, radius, M_PI / 2, M_PI);
    cairo_arc(cr, body_x + radius, body_y + radius, radius, M_PI, 3 * M_PI / 2);
    cairo_close_path(cr);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);


    int b1 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int b2 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol_idx = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));


    double posiciones_x[4] = {
        body_x + body_width * 0.2,
        body_x + body_width * 0.35,
        body_x + body_width * 0.5,
        body_x + body_width * 0.7
    };
    double banda_ancho = body_width * 0.06;
    double banda_alto = body_height * 1.1;


    int indices[4] = {b1, b2, mult, tolerancia_indices[tol_idx]};


    for (int i = 0; i < 4; i++) {
        double r = rgb_colores[indices[i]][0];
        double g = rgb_colores[indices[i]][1];
        double b = rgb_colores[indices[i]][2];


        cairo_set_source_rgb(cr, r, g, b);
        cairo_rectangle(cr, posiciones_x[i], body_y - banda_alto * 0.05, banda_ancho, banda_alto);
        cairo_fill(cr);
    }
}


// ----- Evento Cambio de ComboBox -----
void on_color_changed(GtkComboBox *widget, gpointer user_data) {
    // CORRECCIÓN: Marcar parámetro no usado
    (void)widget;
   
    AppData *data = (AppData *)user_data;
    actualizar_valor(data);
}


// ----- Creación de ComboBox -----
GtkWidget* crear_combo_colores() {
    GtkWidget *combo = gtk_combo_box_text_new();
    for (int i = 0; i < 12; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), colores[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    return combo;
}


// ----- Aplicar CSS personalizado SOLO para resistencia -----
void aplicar_tema_css_resistor() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        ".resistor_window { background: #3498DB; }"
        ".resistor_label { color: #FFFFFF; font-weight: bold; }"
        ".resistor_button { background:rgb(231, 220, 137); color: #00E0A1; border-radius: 6px; padding: 6px; }"
        ".resistor_button:hover { background: #00E0A1; color:rgb(191, 207, 229); }"
        ".resistor_combobox { background: #1E2A3A; color: #FFFFFF; border: 1px solid #00E0A1; border-radius: 5px; }"
        ".back_boton_resistor { background: rgb(41, 128, 185); color: white; border-radius: 8px; padding: 10px; margin-top: 10px; }",
        -1);


    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}


// ----- Función Principal de la App -----
void app_activate(GApplication *app, gpointer user_data) {
    AppData *data = g_new0(AppData, 1);
    aplicar_tema_css_resistor();


    GtkWidget *ventana;
   
    // CORRECCIÓN: Manejar tanto aplicación GTK como ventana simple
    if (app != NULL) {
        ventana = gtk_application_window_new(GTK_APPLICATION(app));
    } else {
        ventana = gtk_window_new();
    }
   
    data->window = ventana; // Guardar referencia a la ventana
   
    gtk_window_set_title(GTK_WINDOW(ventana), "Calculadora de Resistencias");
    gtk_window_set_default_size(GTK_WINDOW(ventana), 800, 500);
    gtk_widget_add_css_class(ventana, "resistor_window"); // Clase específica para resistencia


    // Guardar referencia al menú principal si está disponible
    if (user_data != NULL) {
        g_object_set_data(G_OBJECT(ventana), "Menu", user_data);
    }


    GtkWidget *caja_principal = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_window_set_child(GTK_WINDOW(ventana), caja_principal);


    GtkWidget *box_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_box_append(GTK_BOX(caja_principal), box_left);


    GtkWidget *titulo = gtk_label_new("<b>Bandas de colores</b>");
    gtk_label_set_use_markup(GTK_LABEL(titulo), TRUE);
    gtk_widget_add_css_class(titulo, "resistor_label");
    gtk_box_append(GTK_BOX(box_left), titulo);


    data->combo1 = crear_combo_colores();
    data->combo2 = crear_combo_colores();
    data->combo3 = crear_combo_colores();
    data->combo4 = gtk_combo_box_text_new();
    for (int i = 0; i < 4; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->combo4), tolerancias_texto[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(data->combo4), 0);


    // Aplicar clases específicas a los combobox
    gtk_widget_add_css_class(data->combo1, "resistor_combobox");
    gtk_widget_add_css_class(data->combo2, "resistor_combobox");
    gtk_widget_add_css_class(data->combo3, "resistor_combobox");
    gtk_widget_add_css_class(data->combo4, "resistor_combobox");


    GtkWidget *label1 = gtk_label_new("1.ª banda de color");
    GtkWidget *label2 = gtk_label_new("2.ª banda de color");
    GtkWidget *label3 = gtk_label_new("Multiplicador");
    GtkWidget *label4 = gtk_label_new("Tolerancia");


    gtk_widget_add_css_class(label1, "resistor_label");
    gtk_widget_add_css_class(label2, "resistor_label");
    gtk_widget_add_css_class(label3, "resistor_label");
    gtk_widget_add_css_class(label4, "resistor_label");


    gtk_box_append(GTK_BOX(box_left), label1);
    gtk_box_append(GTK_BOX(box_left), data->combo1);
    gtk_box_append(GTK_BOX(box_left), label2);
    gtk_box_append(GTK_BOX(box_left), data->combo2);
    gtk_box_append(GTK_BOX(box_left), label3);
    gtk_box_append(GTK_BOX(box_left), data->combo3);
    gtk_box_append(GTK_BOX(box_left), label4);
    gtk_box_append(GTK_BOX(box_left), data->combo4);


    // Botón para volver al menú principal
    GtkWidget *back_boton = gtk_button_new_with_label("Volver al Menú Principal");
    gtk_widget_add_css_class(back_boton, "back_boton_resistor");
    g_signal_connect(back_boton, "clicked", G_CALLBACK(volver_menu_resistor), data);
    gtk_box_append(GTK_BOX(box_left), back_boton);


    GtkWidget *box_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_box_append(GTK_BOX(caja_principal), box_right);


    data->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(data->drawing_area, TRUE);
    gtk_widget_set_vexpand(data->drawing_area, TRUE);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawing_area), draw_resistor, data, NULL);
    gtk_box_append(GTK_BOX(box_right), data->drawing_area);


    data->label_resultado = gtk_label_new("Valor de la resistencia: ");
    gtk_widget_add_css_class(data->label_resultado, "resistor_label");
    gtk_widget_set_halign(data->label_resultado, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(box_right), data->label_resultado);


    g_signal_connect(data->combo1, "changed", G_CALLBACK(on_color_changed), data);
    g_signal_connect(data->combo2, "changed", G_CALLBACK(on_color_changed), data);
    g_signal_connect(data->combo3, "changed", G_CALLBACK(on_color_changed), data);
    g_signal_connect(data->combo4, "changed", G_CALLBACK(on_color_changed), data);


    // Calcular valor inicial
    actualizar_valor(data);


    gtk_window_present(GTK_WINDOW(ventana));
}
