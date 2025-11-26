#include "pot.h"
#include <gtk/gtk.h>

// Aquí voy a ir implementando el cálculo de la potencia,
// pero por ahora dejo las funciones listas para que el módulo compile sin errores.

// Variables globales 
GtkWidget *entry_voltaje = NULL;
GtkWidget *entry_corriente = NULL;
GtkWidget *entry_resistencia = NULL;
GtkWidget *combo_formula = NULL;
GtkWidget *label_result = NULL;

void calcular_potencia(GtkWidget *widget, gpointer data) {
    // Aquí más adelante se va a leer los datos y hacer las fórmulas de potencia.
    // por el momento solo lo dejo como una prueba para ver que la función se llama bien.
    g_print("calcular_potencia() todavía no está implementada\n");
}

void limpiar_campos_pot(GtkWidget *widget, gpointer data) {
   
    g_print("limpiar_campos_pot() todavía no está lista\n");
}

void enter_calcular_pot(GtkWidget *entry, gpointer user_data) {
    // Esta función permitirá calcular al presionar enter.
    
    g_print("ENTER presionado en módulo potencia (todavía sin lógica)\n");
}
