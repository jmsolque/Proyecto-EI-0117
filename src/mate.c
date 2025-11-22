// En esta seccion va el codigo correspondiente a los calculos matematicos y acciones del modulo de ley de Ohm
#include "mate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Se definen las entradas y salidas de información 
GtkWidget *tension_in = NULL;       // Entrada de tensión
GtkWidget *corriente_in = NULL;     // Entrada de corriente
GtkWidget *resistencia_in = NULL;   // Entrada de resistencia
GtkWidget *result_label = NULL;     // Salida del resultado de la operación 

// Función que calcula la Ley de Ohm con los valores de entrada
void calcular_ohm(GtkWidget *widget, gpointer data){
    const char *tension_text = gtk_editable_get_text(tension_in);     // Aquí se guarda en _text lo que el usuario ingresa en _in
    const char *corriente_text = gtk_editable_get_text(corriente_in);
    const char *resistencia_text = gtk_editable_get_text(resistencia_in);

    double tension = 0, corriente = 0, resistencia = 0;  // Define las varibales y las inicializa en 0
    int campos_llenos = 0;   // Define el contador en 0

    // Conteo de campos llenos
    if (strlen(tension_text) > 0){
        tension = atof(tension_text);
        campos_llenos++;
    }
    if (strlen(corriente_text) > 0){
        corriente = atof(corriente_text);
        campos_llenos++;
    }
    if (strlen(resistencia_text) > 0){
        resistencia = atof(resistencia_text);
        campos_llenos++;
    }

    // Solo permitir que esten 2 campos llenos
    if (campos_llenos != 2){
        gtk_label_set_text(GTK_LABEL(result_label), "Debe ingresar 2 valores");  // Cambia el texto sale en el cuadro de resultados por el mensaje 
        return; 
    }
    double resultado = 0;  // Crea la variable para guardar el resultado de ley de Ohm
    char buffer[100];   // Convierte el resultado a texto antes de mostrarlo

    // Calculo de tension T = R * I
    if (strlen(tension_text) == 0){    // Si el campo es 0, el usuario no lo lleno enotnces calcula la tensión
        resultado = corriente * resistencia;   // Calcula la tensión 
        snprintf(buffer, sizeof(buffer), "Tensión = %.2f V", resultado);  // Modifica el texto del espacio resultado y coloca el valor de la operación
    }

    // Calculo de corriente I = V/R
    else if (strlen(corriente_text) == 0){
        if (resistencia == 0){     // Si se ingresa una R = 0, señala el error
            gtk_label_set_text(GTK_LABEL(result_label), "El valor de resistencia NO puede ser 0");
            return;
        }
        resultado = tension / resistencia;     // Hace el calculo de corriente
        sprintf(buffer, sizeof(buffer), "Corriente = %.4f A", resultado);
    }

    // Calculo de resistencia R = V/I
    else if (strlen(resistencia_text) == 0){
        if (corriente == 0){     // Si se ingresa una I = 0, indica el error
            gtk_label_set_text(GTK_LABEL(result_label), "El valor de corriente no puede ser 0");
            return;
        }
        resultado = tension / corriente;   // Calcula la resistencia 
        snprintf(buffer, sizeof(buffer), "Resistencia = %.2f Ω", resultado);
    }
    gtk_label_set_text(GTK_LABEL(result_label),buffer);   // Hace que el resultado se vea enn el cuadro que muestra el resultado
}

 // Ejecuta el calculo cuando se presiona el botón
    void enter_calcular(GtkWidget *entry, gpointer user_data){   // Al seleccionar el botón, ejecuta la función que calcula la ley de Ohm
        calcular_ohm(entry, user_data);
    }

// Limpia los espacios en los que el usuario ingresa los datos
void limpiar_campos(GtkWidget *widget, gpointer data) {
    gtk_editable_set_text(GTK_EDITABLE(tension_in), "");
    gtk_editable_set_text(GTK_EDITABLE(corriente_in), "");
    gtk_editable_set_text(GTK_EDITABLE(resistencia_in), "");
    gtk_label_set_text(GTK_LABEL(result_label), "Ingrese 2 valores para calcular el resultado");  
}
