/* Este header file correspondiente a la función para hacer los calculos relacionados 
a la ley de ohm utilizando botones para generar una interfaz grafica por medio de gtk */
#ifndef MATE_H
#define MATE_H
#include <gtk/gtk.h>

// Decalración de funciones generales para la calculadora, estos son los botones que hacen las acciones
void calcular_ohm(GtkWidget *widget, gpointer data);   //widget es u puntero que sigue la acción de tocar el botón
void limpiar_campos(GtkWidget *widget, gpointer data);  // data es un puntero generico que envia información adicional del botón
void enter_calcular(GtkWidget *widget, gpointer data);

// Definición de widgets globales, estos son los espacios donde se meten o salen datos
extern GtkWidget *tension_in;      
extern GtkWidget *corriente_in;
extern GtkWidget *resistencia_in;
extern GtkWidget *result_label;


#endif
