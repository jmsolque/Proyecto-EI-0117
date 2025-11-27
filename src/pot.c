#include "pot.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
    Aquí defino las variables globales que vienen declaradas en pot.h.
    Estas son básicamente los campos de texto y el label de resultado.
*/
GtkWidget *entry_voltaje = NULL;
GtkWidget *entry_corriente = NULL;
GtkWidget *entry_resistencia = NULL;
GtkWidget *combo_formula = NULL;
GtkWidget *label_result = NULL;


/*
    Esta función hace todos los cálculos de potencia según lo que el usuario meta.
    También detecta si hacen falta datos o si hay errores como seria dividir entre cero.
*/
void calcular_potencia(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;

    // Primero leo el texto que escribió el usuario en cada cuadro
    const char *txt_v = gtk_editable_get_text(GTK_EDITABLE(entry_voltaje));
    const char *txt_i = gtk_editable_get_text(GTK_EDITABLE(entry_corriente));
    const char *txt_r = gtk_editable_get_text(GTK_EDITABLE(entry_resistencia));

    // Convierto esos textos a números
    double V = 0, I = 0, R = 0;
    int count = 0;

    if (strlen(txt_v) > 0) { V = atof(txt_v); count++; }
    if (strlen(txt_i) > 0) { I = atof(txt_i); count++; }
    if (strlen(txt_r) > 0) { R = atof(txt_r); count++; }

    // Si el usuario  llenó un solo  valor, no se puede calcular nada
    if (count < 2)
    {
        gtk_label_set_text(GTK_LABEL(label_result),
                           "Debe ingresar al menos 2 valores.");
        return;
    }

    // Aquí voy a calcular P
    double P = 0.0;
    char buffer[256];

    // Fórmula seleccionada por el usuario
    int opcion = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_formula));

    // Opción 0 = P = V * I
    if (opcion == 0)
    {
        if (strlen(txt_v) == 0 || strlen(txt_i) == 0)
        {
            gtk_label_set_text(GTK_LABEL(label_result),
                               "Para P = V * I debe llenar Voltaje y Corriente.");
            return;
        }
        P = V * I;
        snprintf(buffer, sizeof(buffer), "P = %.3f W (P = V × I)", P);
    }

    // Opción 1 = P = V² / R
    else if (opcion == 1)
    {
        if (strlen(txt_v) == 0 || strlen(txt_r) == 0)
        {
            gtk_label_set_text(GTK_LABEL(label_result),
                               "Para P = V² / R debe llenar Voltaje y Resistencia.");
            return;
        }
        if (R == 0)
        {
            gtk_label_set_text(GTK_LABEL(label_result),
                               "Error: la resistencia no puede ser 0");
            return;
        }

        P = (V * V) / R;
        snprintf(buffer, sizeof(buffer), "P = %.3f W (P = V² / R)", P);
    }

    // Opción 2 = P = I² * R
    else if (opcion == 2)
    {
        if (strlen(txt_i) == 0 || strlen(txt_r) == 0)
        {
            gtk_label_set_text(GTK_LABEL(label_result),
                               "Para P = I² × R debe llenar Corriente y Resistencia.");
            return;
        }
        P = I * I * R;
        snprintf(buffer, sizeof(buffer), "P = %.3f W (P = I² × R)", P);
    }

    // Aca es para mostrar el resultado final
    gtk_label_set_text(GTK_LABEL(label_result), buffer);
}


/*
    Esta función hace lo mismo que darle clic a "Calcular",
    solo que funciona cuando el usuario presiona enter.
*/
void enter_calcular_pot(GtkWidget *entry, gpointer user_data)
{
    (void)entry;
    (void)user_data;

    calcular_potencia(NULL, NULL);
}


/*
    Esta función deja todo vacío como si fuera la primera vez que se abre.
*/
void limpiar_campos_pot(GtkWidget *widget, gpointer data)
{
    (void)widget;
    (void)data;

    gtk_editable_set_text(GTK_EDITABLE(entry_voltaje), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_corriente), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_resistencia), "");

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_formula), 0);

    gtk_label_set_text(GTK_LABEL(label_result),
                       "Ingrese al menos dos valores y presione Calcular");
}
