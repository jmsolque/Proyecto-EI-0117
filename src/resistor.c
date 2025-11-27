#include <gtk/gtk.h>
#include <math.h>

//Estructura base App

typedef struct {
    GtkWidget *combo1;
    GtkWidget *combo2;
    GtkWidget *combo3;
    GtkWidget *combo4;
    GtkWidget *label_resultado;
    GtkWidget *drawing_area;  // NUEVO: área de dibujo
} AppData;

//Datos del sistema


const char *colores[] = {
    "Negro", "Marrón", "Rojo", "Naranja", "Amarillo",
    "Verde", "Azul", "Violeta", "Gris", "Blanco"
};

// Colores RGB normalizados 
const double rgb_colores[10][3] = {
    {0.0, 0.0, 0.0},   // Negro
    {0.36, 0.17, 0.09},// Marrón
    {0.89, 0.0, 0.03}, // Rojo
    {1.0, 0.36, 0.0},  // Naranja
    {1.0, 0.87, 0.0},  // Amarillo
    {0.0, 0.5, 0.25},  // Verde
    {0.0, 0.2, 0.65},  // Azul
    {0.42, 0.25, 0.63},// Violeta
    {0.62, 0.62, 0.62},// Gris
    {1.0, 1.0, 1.0}    // Blanco
};

const double multiplicadores[] = {
    1, 10, 100, 1000, 10000,
    100000, 1000000, 10000000, 100000000, 1000000000
};

const char *tolerancias_texto[] = {
    "±1%", "±2%", "±5%", "±10%"
};

const double tolerancias_valores[] = {
    1, 2, 5, 10
};


//Función de Cálculo

void actualizar_valor(AppData *data)
{
    int b1 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int b2 = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol  = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));

    int dig1 = b1;
    int dig2 = b2;
    double mul = multiplicadores[mult];
    double resultado = (dig1 * 10 + dig2) * mul;

    const char *tol_txt = tolerancias_texto[tol];

    char buffer[128];

    if (resultado >= 1000000)
        snprintf(buffer, sizeof(buffer), "%.2f MΩ %s", resultado / 1e6, tol_txt);
    else if (resultado >= 1000)
        snprintf(buffer, sizeof(buffer), "%.2f kΩ %s", resultado / 1e3, tol_txt);
    else
        snprintf(buffer, sizeof(buffer), "%.0f Ω %s", resultado, tol_txt);

    gtk_label_set_text(GTK_LABEL(data->label_resultado), buffer);


    gtk_widget_queue_draw(data->drawing_area);
}

//Dibujo del resistor

static void draw_resistor(GtkDrawingArea *area,
                          cairo_t        *cr,
                          int             width,
                          int             height,
                          gpointer        user_data)
{
    AppData *data = (AppData *)user_data;


    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);


    double body_width  = width * 0.5;
    double body_height = height * 0.25;
    double body_x      = (width  - body_width)  / 2.0;
    double body_y      = (height - body_height) / 2.0;


    cairo_set_line_width(cr, 6);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, body_x - 40, body_y + body_height / 2.0);
    cairo_line_to(cr, body_x,       body_y + body_height / 2.0);
    cairo_move_to(cr, body_x + body_width, body_y + body_height / 2.0);
    cairo_line_to(cr, body_x + body_width + 40, body_y + body_height / 2.0);
    cairo_stroke(cr);


    double radius = 10.0;

    cairo_new_sub_path(cr);
    cairo_arc(cr, body_x + body_width - radius, body_y + radius,
              radius, -M_PI / 2, 0);
    cairo_arc(cr, body_x + body_width - radius,
              body_y + body_height - radius,
              radius, 0, M_PI / 2);
    cairo_arc(cr, body_x + radius,
              body_y + body_height - radius,
              radius, M_PI / 2, M_PI);
    cairo_arc(cr, body_x + radius, body_y + radius,
              radius, M_PI, 3 * M_PI / 2);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);  // gris claro
    cairo_fill(cr);


    int b1   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int b2   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol  = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));


    double posiciones_x[4] = {
        body_x + body_width * 0.20,
        body_x + body_width * 0.35,
        body_x + body_width * 0.50,
        body_x + body_width * 0.70
    };
    double banda_ancho = body_width * 0.06;
    double banda_alto  = body_height * 1.10;


    int indices[4] = { b1, b2, mult, tol };

    for (int i = 0; i < 4; i++) {
        int idx = indices[i];
        if (idx < 0 || idx > 9) continue;

        double r = rgb_colores[idx][0];
        double g = rgb_colores[idx][1];
        double b = rgb_colores[idx][2];

        cairo_set_source_rgb(cr, r, g, b);
        cairo_rectangle(cr,
                        posiciones_x[i],
                        body_y - banda_alto * 0.05,
                        banda_ancho,
                        banda_alto);
        cairo_fill(cr);
    }
}

//Evento de cambio

void on_combo_changed(GtkComboBox *widget, gpointer user_data)
{
    actualizar_valor((AppData *)user_data);
}

//Creación de combos

GtkWidget *crear_combo_colores()
{
    GtkWidget *combo = gtk_combo_box_text_new();
    for (int i = 0; i < 10; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), colores[i]);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    return combo;
}

GtkWidget *crear_combo_multiplicador()
{
    GtkWidget *combo = gtk_combo_box_text_new();
    for (int i = 0; i < 10; i++) {
        char texto[32];
        sprintf(texto, "x%.0f", multiplicadores[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), texto);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    return combo;
}

GtkWidget *crear_combo_tolerancia()
{
    GtkWidget *combo = gtk_combo_box_text_new();
    for (int i = 0; i < 4; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), tolerancias_texto[i]);

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    return combo;
}

//Activación de la App

void app_activate(GApplication *app, gpointer user_data)
{
    AppData *data = g_new0(AppData, 1);

    GtkWidget *ventana = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(ventana), "Calculadora de Resistencias");
    gtk_window_set_default_size(GTK_WINDOW(ventana), 800, 400);

    /* Layout principal: izquierda controles, derecha dibujo */
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_window_set_child(GTK_WINDOW(ventana), hbox);

    /* Columna izquierda: combos y resultado */
    GtkWidget *box_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(hbox), box_left);

    gtk_box_append(GTK_BOX(box_left), gtk_label_new("1.ª banda de color"));
    data->combo1 = crear_combo_colores();
    gtk_box_append(GTK_BOX(box_left), data->combo1);

    gtk_box_append(GTK_BOX(box_left), gtk_label_new("2.ª banda de color"));
    data->combo2 = crear_combo_colores();
    gtk_box_append(GTK_BOX(box_left), data->combo2);

    gtk_box_append(GTK_BOX(box_left), gtk_label_new("Multiplicador"));
    data->combo3 = crear_combo_multiplicador();
    gtk_box_append(GTK_BOX(box_left), data->combo3);

    gtk_box_append(GTK_BOX(box_left), gtk_label_new("Tolerancia"));
    data->combo4 = crear_combo_tolerancia();
    gtk_box_append(GTK_BOX(box_left), data->combo4);

    data->label_resultado = gtk_label_new("Resultado: ");
    gtk_box_append(GTK_BOX(box_left), data->label_resultado);

    GtkWidget *box_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(hbox), box_right);

    data->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(data->drawing_area, TRUE);
    gtk_widget_set_vexpand(data->drawing_area, TRUE);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawing_area),
                                   draw_resistor,
                                   data,
                                   NULL);
    gtk_box_append(GTK_BOX(box_right), data->drawing_area);


    g_signal_connect(data->combo1, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo2, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo3, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo4, "changed", G_CALLBACK(on_combo_changed), data);

    actualizar_valor(data);

    gtk_window_present(GTK_WINDOW(ventana));
}

// funcion main
int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.resistorcalc", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

    status = g_application_run(GTK_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

