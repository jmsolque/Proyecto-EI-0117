#include <gtk/gtk.h>
#include <math.h>


//ESTRUCTURA PRINCIPAL DE LA APLICACIÓN

typedef struct {
    GtkWidget *combo1;
    GtkWidget *combo2;
    GtkWidget *combo3;
    GtkWidget *combo4;
    GtkWidget *label_resultado;
    GtkWidget *drawing_area;
} AppData;


 //DATOS DEL SISTEMA: COLORES, VALORES, TOLERANCIAS

/* Nombre de colores */
static const char *colores[] = {
    "Negro", "Marrón", "Rojo", "Naranja", "Amarillo",
    "Verde", "Azul", "Violeta", "Gris", "Blanco", "Oro", "Plata"
};

/* Colores RGB normalizados */
static const double rgb_colores[12][3] = {
    {0.0, 0.0, 0.0},      // Negro
    {0.36, 0.17, 0.09},   // Marrón
    {0.89, 0.0, 0.03},    // Rojo
    {1.0, 0.36, 0.0},     // Naranja
    {1.0, 0.87, 0.0},     // Amarillo
    {0.0, 0.5, 0.25},     // Verde
    {0.0, 0.2, 0.65},     // Azul
    {0.42, 0.25, 0.63},   // Violeta
    {0.62, 0.62, 0.62},   // Gris
    {1.0, 1.0, 1.0},      // Blanco
    {0.83, 0.68, 0.21},   // Oro
    {0.75, 0.75, 0.75}    // Plata
};

/* Multiplicadores */
static const double multiplicadores[] = {
    1, 10, 100, 1000, 10000,
    100000, 1000000, 10000000, 100000000, 1000000000
};

/* Tolerancias permitidas */
static const char *tolerancias_texto[] = {
    "Marrón ±1%", "Rojo ±2%", "Oro ±5%", "Plata ±10%"
};

/* Índices RGB en nuestra tabla */
static const int tolerancia_indices[] = {
    1,  // Marrón
    2,  // Rojo
    10, // Oro
    11  // Plata
};


 //TEMA CSS OSCURO PERSONALIZADO

static void aplicar_tema_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    const char *css =
        "window { background-color: #0E1A2B; color: #FFFFFF; }"
        "label { color: #FFFFFF; font-weight: 500; }"
        ".resultado-label { font-size: 18px; font-weight: bold; }"
        "combobox, combobox * { background-color: #1E2A3A; color: #FFFFFF; }";

    gtk_css_provider_load_from_data(provider, css, -1);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

//CÁLCULO DEL VALOR DE LA RESISTENCIA

static void actualizar_valor(AppData *data)
{
    int b1   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int b2   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol  = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));

    double valor = (b1 * 10 + b2) * multiplicadores[mult];
    const char *tol_txt = tolerancias_texto[tol];

    char texto[128];
    if (valor >= 1e6)
        snprintf(texto, sizeof(texto), "%.2f MΩ %s", valor / 1e6, tol_txt);
    else if (valor >= 1e3)
        snprintf(texto, sizeof(texto), "%.2f kΩ %s", valor / 1e3, tol_txt);
    else
        snprintf(texto, sizeof(texto), "%.0f Ω %s", valor, tol_txt);

    gtk_label_set_text(GTK_LABEL(data->label_resultado), texto);
    gtk_widget_queue_draw(data->drawing_area);
}


// DIBUJO DEL RESISTOR CON CAIRO

static void draw_resistor(GtkDrawingArea *area, cairo_t *cr,
                          int width, int height, gpointer user_data)
{
    AppData *data = (AppData *)user_data;

    cairo_set_source_rgb(cr, 0.06, 0.10, 0.17);
    cairo_paint(cr);

    double body_w = width * 0.5;
    double body_h = height * 0.25;
    double x = (width - body_w) / 2;
    double y = (height - body_h) / 2;

    /* Terminales */
    cairo_set_line_width(cr, 6);
    cairo_set_source_rgb(cr, 0.0, 0.88, 0.70);
    cairo_move_to(cr, x - 40, y + body_h / 2);
    cairo_line_to(cr, x, y + body_h / 2);
    cairo_move_to(cr, x + body_w, y + body_h / 2);
    cairo_line_to(cr, x + body_w + 40, y + body_h / 2);
    cairo_stroke(cr);

    /* Cuerpo con degradado */
    cairo_pattern_t *pat = cairo_pattern_create_linear(x, y, x, y + body_h);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.15, 0.22, 0.35);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.20, 0.30, 0.45);

    double r = 12.0;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x + body_w - r, y + r, r, -M_PI/2, 0);
    cairo_arc(cr, x + body_w - r, y + body_h - r, r, 0, M_PI/2);
    cairo_arc(cr, x + r, y + body_h - r, r, M_PI/2, M_PI);
    cairo_arc(cr, x + r, y + r, r, M_PI, 3*M_PI/2);
    cairo_set_source(cr, pat);
    cairo_fill(cr);
    cairo_pattern_destroy(pat);

    /* Bandas */
    int b1   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo1));
    int b2   = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo2));
    int mult = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo3));
    int tol  = gtk_combo_box_get_active(GTK_COMBO_BOX(data->combo4));

    int band_idx[4] = {
        b1,
        b2,
        mult,
        tolerancia_indices[tol]
    };

    double bx[4] = {
        x + body_w * 0.20,
        x + body_w * 0.35,
        x + body_w * 0.50,
        x + body_w * 0.70
    };

    double bw = body_w * 0.06;
    double bh = body_h * 1.10;

    for (int i = 0; i < 4; i++) {
        int c = band_idx[i];
        cairo_set_source_rgb(cr,
            rgb_colores[c][0],
            rgb_colores[c][1],
            rgb_colores[c][2]
        );
        cairo_rectangle(cr, bx[i], y - bh * 0.05, bw, bh);
        cairo_fill(cr);
    }
}

/* Evento de combo */
static void on_combo_changed(GtkComboBox *combo, gpointer user_data)
{
    actualizar_valor((AppData *)user_data);
}


// CREACIÓN DE COMBOBOX

static GtkWidget *crear_combo_colores(void)
{
    GtkWidget *c = gtk_combo_box_text_new();
    for (int i = 0; i < 10; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(c), colores[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(c), 0);
    return c;
}

static GtkWidget *crear_combo_multiplicador(void)
{
    GtkWidget *c = gtk_combo_box_text_new();
    for (int i = 0; i < 10; i++) {
        char txt[32];
        sprintf(txt, "x%.0f", multiplicadores[i]);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(c), txt);
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(c), 0);
    return c;
}

static GtkWidget *crear_combo_tolerancia(void)
{
    GtkWidget *c = gtk_combo_box_text_new();
    for (int i = 0; i < 4; i++)
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(c), tolerancias_texto[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(c), 0);
    return c;
}

//ACTIVACIÓN DE LA APLICACIÓN

static void app_activate(GApplication *app, gpointer user_data)
{
    AppData *data = g_new0(AppData, 1);

    aplicar_tema_css();

    GtkWidget *win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "Calculadora de Resistencias");
    gtk_window_set_default_size(GTK_WINDOW(win), 900, 450);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 16);
    gtk_window_set_child(GTK_WINDOW(win), hbox);

    GtkWidget *left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(hbox), left);

    /* Controles */
    gtk_box_append(GTK_BOX(left), gtk_label_new("1.ª banda de color"));
    data->combo1 = crear_combo_colores();
    gtk_box_append(GTK_BOX(left), data->combo1);

    gtk_box_append(GTK_BOX(left), gtk_label_new("2.ª banda de color"));
    data->combo2 = crear_combo_colores();
    gtk_box_append(GTK_BOX(left), data->combo2);

    gtk_box_append(GTK_BOX(left), gtk_label_new("Multiplicador"));
    data->combo3 = crear_combo_multiplicador();
    gtk_box_append(GTK_BOX(left), data->combo3);

    gtk_box_append(GTK_BOX(left), gtk_label_new("Tolerancia"));
    data->combo4 = crear_combo_tolerancia();
    gtk_box_append(GTK_BOX(left), data->combo4);

    data->label_resultado = gtk_label_new("Resultado: ");
    gtk_widget_add_css_class(data->label_resultado, "resultado-label");
    gtk_box_append(GTK_BOX(left), data->label_resultado);

    /* Área de dibujo */
    GtkWidget *right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(hbox), right);

    data->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_hexpand(data->drawing_area, TRUE);
    gtk_widget_set_vexpand(data->drawing_area, TRUE);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(data->drawing_area),
                                   draw_resistor, data, NULL);

    gtk_box_append(GTK_BOX(right), data->drawing_area);

    /* Señales */
    g_signal_connect(data->combo1, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo2, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo3, "changed", G_CALLBACK(on_combo_changed), data);
    g_signal_connect(data->combo4, "changed", G_CALLBACK(on_combo_changed), data);

    actualizar_valor(data);
    gtk_window_present(GTK_WINDOW(win));
}

//MAIN

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("org.gtk.resistorcalc",
                                              G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
