// En esta sección a el código correspondiente a la interfaz gráfica del modulo de ley de Ohm
#include "app.h"
#include "mate.h"

// Aplicar el formato CSS
void apply_css(){
    GtkCssProvider *provider = gtk_css_provider_new();   // Aplica el estilo a los widgets con una sintaxis similar a Css

    const char *css =
      " .main-window { "    // Fondo de la ventana principal
        "     background: #2C3E50;"
        " } "
        " .title-label { "   // Titulo
        "     font-size: 24px; "    // Tamaño de la fuente el px
        "     font-weight: bold; "  // Texto en negrita
        "     color: #ECF0F1; "
        " } "
        " .section-title { "    // Titulo de las subsecciones 
        "     font-size: 18px; "
        "     font-weight: bold; "  
        "     color: #3498DB; "
        " } "
        " .input-label { "   // Etiqueta de cuadros para ingresar datos
        "     font-size: 14px; "
        "     color: #BDC3C7;"
        "     font-weight: bold; "
        " } "
        " .entry-field { "    // Campos para ingresar datos
        "     background: #34495E; "  // Fondo de la pagina
        "     color: white; "   // Color del texto 
        "     border: 2px solid #4FA3D9;"  // Borde con grosot y color
        "     border-radius: 8px; "   // Redio de los bordes redondos 
        "     padding: 8px; "   // Espacio dentro de un widget
        " } "
        " .calculate-button { "  // Botón calcular
        "     background: #1ABC9C; "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "
        " .clear-button { "   // Botón limpiar 
        "     background: #BDC3C7; "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "
        " .result-frame { "   // Cuadro que da el resultado 
        "     background: #16A085; "
        "     border-radius: 12px; "
        "     padding: 20px; "
        " } "
        " .result-label { "   // Etiqueta resultado 
        "     font-size: 20px; "
        "     font-weight: bold; "
        "     color: white; "
        " } ";

    gtk_css_provider_load_from_string(provider, css);   // Carga el formato css configurado arriba
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),    // Obtiene el display en la pantalla que se abre como una ventana
        GTK_STYLE_PROVIDER(provider),    // Hace la conversión para que sea compatible con GTK
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );   // Asegura que se aplique el estilo
    g_object_unref(provider);   // Elimina el puntero para no guardar todas sus reiteraciones al ejecutar el programa

}

// Configuración de la ventana que se despliega al ejecutar el programa
