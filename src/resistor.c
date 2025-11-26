 #include <gtk/gtk.h>
#include <math.h>

//Estructura base App

typedef struct {
    GtkWidget *combo1;
    GtkWidget *combo2;
    GtkWidget *combo3;
    GtkWidget *combo4;
    GtkWidget *label_resultado;
} AppData;

//     Datos de la resistencia

const char *colores[] = {
    "Negro", "Marrón", "Rojo", "Naranja", "Amarillo",
    "Verde", "Azul", "Violeta", "Gris", "Blanco"
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
}

//Evento de cambio
void on_combo_changed(GtkComboBox *widget, gpointer user_data)
{
    actualizar_valor((AppData *)user_data);
}

// Creación de combo
GtkWidget *crear_combo_colores()
{
    GtkWidget *combo = gtk_combo_box_t_*

