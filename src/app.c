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
        "     background:rgb(22, 156, 129); "   // Aqui no se utiliza el codigo de color hexadeimal por que el color se modifico en el editor de codigo 
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "
        " .clear-button { "   // Botón limpiar 
        "     background:rgb(143, 145, 147); "
        "     color: white; "
        "     border-radius: 8px; "
        "     padding: 10px; "
        " } "
        " .result-frame { "   // Cuadro que da el resultado 
        "     background:rgb(22, 137, 114); "
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
void on_activate(GtkApplication *app, gpointer user_data) {

    GtkWidget *window = gtk_application_window_new(app);   // Crea una  nueva ventana asociada a la app
    
    // Esto es lo que esta en la capa mas baja
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora Ley de Ohm");  // Titulo de la app
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 550);   // Tamaño de la ventana
    gtk_widget_add_css_class(window, "main-window");   // Añade el estilo a la ventana

    // Genera la caja principal vertical para ordenar los widgets
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), main_box);  // Se establece esta ventana vertical como hijo de la ventana principal

    // Genera el titulo 
    GtkWidget *title = gtk_label_new("Calculadora Ley de Ohm");   // Crea una etiqueta con el titulo
    gtk_widget_add_css_class(title, "title-label");  // Aplica el estilo css a la etiqueta
    gtk_box_append(GTK_BOX(main_box), title);  // Añade la etiqueta a la ventana principal 

    // Genera el grid para ajustar los botones, titulos y cuadros 
    GtkWidget *grid = gtk_grid_new();    
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);  // Espacio entre column
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);    // Espacio entre filas
    gtk_box_append(GTK_BOX(main_box), grid);   // Annade la grid a la ventana principal 

    // Se crean los lugares para recibir y dar los valores de tensión, corrient ey resistencia
    GtkWidget *label_tension = gtk_label_new("Tensión (V):");   
    gtk_widget_add_css_class(label_tension, "input-label");
    tension_in = gtk_entry_new();   // Crea un espacio para que el ususario ingrese un numero 
    gtk_widget_add_css_class(tension_in, "entry-field");

    GtkWidget *label_corriente = gtk_label_new("Corriente (A):");
    gtk_widget_add_css_class(label_corriente, "input-label");
    corriente_in = gtk_entry_new();  
    gtk_widget_add_css_class(corriente_in, "entry-field");

    GtkWidget *label_resistencia = gtk_label_new("Resistencia (Ω):");
    gtk_widget_add_css_class(label_resistencia, "input-label");
    resistencia_in = gtk_entry_new();  
    gtk_widget_add_css_class(resistencia_in, "entry-field");

    // Coloca los cuadros y el texto basandose en la grid
    gtk_grid_attach(GTK_GRID(grid), label_tension, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), tension_in, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_corriente, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), corriente_in, 1, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), label_resistencia, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), resistencia_in, 1, 2, 1, 1);

    // Crea el boton calcular 
    GtkWidget *boton_calc = gtk_button_new_with_label("Calcular");
    gtk_widget_add_css_class(boton_calc, "calculate-button");

    // Crea el botn limpial 
    GtkWidget *boton_clear = gtk_button_new_with_label("Limpiar");
    gtk_widget_add_css_class(boton_clear, "clear-button");

    // Crea una caja horizontal para acomodar los botones calcular y limpiar
    GtkWidget *boton_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(boton_box), boton_calc);   // Añade calcular a al caja
    gtk_box_append(GTK_BOX(boton_box), boton_clear);   // Añade limpiar a la caja

    gtk_box_append(GTK_BOX(main_box), boton_box);  // Añade la caja a la ventana principal 

    // Espacio vacío entre los botones y los resultados
    GtkWidget *space = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); // 20px de espacio
    gtk_box_append(GTK_BOX(main_box), space);

    // Crea el marco donde se muestran los resultados 
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_widget_add_css_class(frame, "result-frame");
    gtk_box_append(GTK_BOX(main_box), frame);

    // Crea la etiqueta que se muestra en el cuadro
    result_label = gtk_label_new("Ingrese 2 valores para calcular");
    gtk_widget_add_css_class(result_label, "result-label");   // Le da el formato css a la etiqueta
    gtk_frame_set_child(GTK_FRAME(frame), result_label);   // Hace la etiqueta hija de la ventana resultado, osea que siempre que sale resultado sale la etiqueta

    // Cuando el ususuario hace clic en el boton, envia una señal
    g_signal_connect(boton_calc, "clicked", G_CALLBACK(calcular_ohm), NULL);
    g_signal_connect(boton_clear, "clicked", G_CALLBACK(limpiar_campos), NULL);

    // Cuando el usuario hace enter en el teclado, envia una señal 
    g_signal_connect(tension_in, "activate", G_CALLBACK(enter_calcular), NULL);
    g_signal_connect(corriente_in, "activate", G_CALLBACK(enter_calcular), NULL);
    g_signal_connect(resistencia_in, "activate", G_CALLBACK(enter_calcular), NULL);

    // Aplica css a la ventana principal y a todos los elementos 
    apply_css();

    // Muestra la ventana en la pantalla ya configurada 
    gtk_window_present(GTK_WINDOW(window));
}