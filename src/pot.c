#include "pot.h"
#include <gtk/gtk.h>
#include <math.h>

// Aquí voy a ir guardando los valores que el usuario escribe.

GtkWidget *entry_voltaje;
GtkWidget *entry_corriente;
GtkWidget *entry_resistencia;
GtkWidget *combo_formula;
GtkWidget *label_result;

// Función para convertir texto a número 
static double leer_valor(GtkWidget *entry)
{
    const char *txt = gtk_editable_get_text(GTK_EDITABLE(entry));
    if (txt == NULL || txt[0] == '\0')
        return 0.0;
    return atof(txt);
}

//  la función que  hace los cálculos.
// de lo que escoja el usuario en el combo, uso la fórmula correspondiente.
void calcular_potencia(GtkWidget *widget, gpointer data)
{
    // Leo los valores de las entradas
    double V = leer_valor(entry_voltaje);
    double I = leer_valor(entry_corriente);
    double R = leer_valor(entry_resistencia);

    // Obtengo qué fórmula escogió el usuario
    int formula = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_formula));

    double P = 0.0;

    // Uso un switch porque es más fácil de ver después
    switch (formula)
    {
        case 0:
            // P = V * I
            P = V * I;
            break;

        case 1:
            // P = V^2 / R 
            if (R != 0)
                P = (V * V) / R;
            else
                P = 0;
            break;

        case 2:
            // P = I^2 * R
            P = (I * I) * R;
            break;
    }

    // Aquí ya se muestra el resultado en la etiqueta
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Potencia = %.2f W", P);
    gtk_label_set_text(GTK_LABEL(label_result), buffer);
}

// Función para limpiar las entradas y borrar el resultado
void limpiar_campos_pot(GtkWidget *widget, gpointer data)
{
    gtk_editable_set_text(GTK_EDITABLE(entry_voltaje), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_corriente), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_resistencia), "");

    gtk_label_set_text(GTK_LABEL(label_result), "Resultado aparecerá aquí");
}

// Para permitir que al presionar enter también calcule la potencia
void enter_calcular_pot(GtkWidget *entry, gpointer user_data)
{
    calcular_potencia(NULL, NULL);
}
