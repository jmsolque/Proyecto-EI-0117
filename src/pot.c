#include "pot.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Variables globales donde guardo las entradas de la ventana
GtkWidget *entry_voltaje = NULL;
GtkWidget *entry_corriente = NULL;
GtkWidget *entry_resistencia = NULL;
GtkWidget *combo_formula = NULL;
GtkWidget *label_result = NULL;

// Aquí hago el cálculo  de la potencia.

void calcular_potencia(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;

    // Primero leo lo que el usuario escribió en los cuadros
    const char *txt_v = gtk_editable_get_text(GTK_EDITABLE(entry_voltaje));
    const char *txt_i = gtk_editable_get_text(GTK_EDITABLE(entry_corriente));
    const char *txt_r = gtk_editable_get_text(GTK_EDITABLE(entry_resistencia));

    // Convierto el texto a número 
    double V = (strlen(txt_v) > 0) ? atof(txt_v) : 0;
    double I = (strlen(txt_i) > 0) ? atof(txt_i) : 0;
    double R = (strlen(txt_r) > 0) ? atof(txt_r) : 0;

    int opcion = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_formula));
    double P = 0.0;
    char buffer[128];

    // Dependiendo de lo que el usuario escoja
    if (opcion == 0) {  // P = V * I
        P = V * I;
        snprintf(buffer, sizeof(buffer), "P = %.4f W (usando V * I)", P);
    }
    else if (opcion == 1) {  // P = V² / R
        if (R == 0) {
            gtk_label_set_text(GTK_LABEL(label_result), "No se puede dividir entre 0");
            return;
        }
        P = (V * V) / R;
        snprintf(buffer, sizeof(buffer), "P = %.4f W (usando V² / R)", P);
    }
    else if (opcion == 2) {  // P = I² * R
        P = (I * I) * R;
        snprintf(buffer, sizeof(buffer), "P = %.4f W (usando I² * R)", P);
    }

    // mostrando el resultado final en el label
    gtk_label_set_text(GTK_LABEL(label_result), buffer);
}

// Esta función limpia todo de nuevo
void limpiar_campos_pot(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;

    gtk_editable_set_text(GTK_EDITABLE(entry_voltaje), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_corriente), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_resistencia), "");
    gtk_label_set_text(GTK_LABEL(label_result), "Todo limpio :)");
}

// Esta función permite calcular al presionar enter
void enter_calcular_pot(GtkWidget *entry, gpointer user_data)
{
    (void)entry;
    (void)user_data;

    calcular_potencia(NULL, NULL);
}
