#ifndef POT_H
#define POT_H

#include <gtk/gtk.h>

// Aquí van las entradas donde el usuario mete los datos
extern GtkWidget *entry_voltaje;
extern GtkWidget *entry_corriente;
extern GtkWidget *entry_resistencia;

// Combo para seleccionar qué fórmula usar
extern GtkWidget *combo_formula;

// Label donde se va a mostrar la potencia calculada
extern GtkWidget *label_result;

// Función que hace el cálculo 
void calcular_potencia(GtkWidget *widget, gpointer data);

// Limpia todos los campos, por si el usuario quiere empezar de cero
void limpiar_campos_pot(GtkWidget *widget, gpointer data);

// Esta función sirve para calcular cuando se presiona enter
void enter_calcular_pot(GtkWidget *entry, gpointer user_data);

// Esta función activa/desactiva las cajas según la fórmula que el usuario escoja
void actualizar_campos_segun_formula(void);

#endif
