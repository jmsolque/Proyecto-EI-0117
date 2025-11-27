
#ifndef RESISTOR_CALC_H
#define RESISTOR_CALC_H


#include <gtk/gtk.h>
#include <math.h>


// Estructura principal de la aplicación
typedef struct {
    int banda1;
    int banda2;
    int multiplicador;
    int tolerancia;
    GtkWidget *label_resultado;
    GtkWidget *drawing_area;
    GtkWidget *combo1;
    GtkWidget *combo2;
    GtkWidget *combo3;
    GtkWidget *combo4;
    GtkWidget *window; // Nueva referencia a la ventana
} AppData;


// Declaración de funciones
void actualizar_valor(AppData *data);
void on_color_changed(GtkComboBox *widget, gpointer user_data);
GtkWidget* crear_combo_colores();
void aplicar_tema_css_resistor(); // Cambiado el nombre
void app_activate(GApplication *app, gpointer user_data);


// Dibujo del resistor
void draw_resistor(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data);


// Función para volver al menú (nueva)
void volver_menu_resistor(GtkWidget *widget, gpointer user_data);


#endif // RESISTOR_CALC_H
