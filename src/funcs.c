#include "libreria.h"

// Declaración de las funciones
uint16_t f_leer_sens_color(); // Lee el valor del sensor de color
void f_error_archivo();       // Muestra un error al cargar un archivo y termina el programa
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color); // Verifica si un color está dentro de una tolerancia
config f_load_config_txt(const char *filename, void(*puntero)(void)); // Carga la configuración desde un archivo de texto

// Implementación de las funciones

// Función para leer el valor del sensor de color
uint16_t f_leer_sens_color() {
    return (uint16_t)leer_ADC(TCS3200); // Llama a la función para leer el sensor TCS3200
}

// Función que se ejecuta si ocurre un error al cargar el archivo de configuración
void f_error_archivo() {
    printf("Error al cargar el archivo de configuracion\n");
    exit(1); // Termina el programa con un código de error
}

// Función que verifica si una medida de color está dentro de la tolerancia permitida
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color) {
    // Calcula el límite inferior y superior para verificar si el color está dentro de la tolerancia
    int limiteInferior = color - tolerancia;
    int limiteSuperior = color + tolerancia;

    // Verifica si el valor del color actual está dentro del rango de tolerancia
    if (current_color >= limiteInferior && current_color <= limiteSuperior) {
        return 1; // La medida está dentro de la tolerancia
    } else {
        return 0; // La medida no está dentro de la tolerancia
    }
}

// Función para cargar la configuración desde un archivo de texto
config f_load_config_txt(const char *filename, void (*error_func)(void)) {
    config cfg; // Se declara una estructura de tipo config
    FILE *file = fopen(filename, "r"); // Abre el archivo en modo de lectura
    if (file == NULL) {
        perror("Error al abrir el archivo para lectura"); // Imprime un error si no se puede abrir el archivo
        error_func(); // Llama a la función de error proporcionada
        return cfg;
    }

    // Lee los valores de "colores" desde el archivo de texto
    fscanf(file, "colores: %hhu %hhu %hhu %hhu %hhu %hhu\n", 
           &cfg.colores[0], &cfg.colores[1], &cfg.colores[2], 
           &cfg.colores[3], &cfg.colores[4], &cfg.colores[5]);

    // Lee el valor de "tolerancia" desde el archivo
    fscanf(file, "tolerancia: %hhu\n", &cfg.tolerancia);

    // Lee el valor de "indice_salida" y lo convierte al tipo `salidas_c`
    int indice_salida;
    fscanf(file, "indice_salida: %d\n", &indice_salida);
    cfg.indice_salida = (salidas_c)indice_salida;

    // Asigna la función de error proporcionada a `cfg.error_func`
    cfg.error_func = error_func;

    fclose(file); // Cierra el archivo
    return cfg;   // Retorna la estructura de configuración cargada
}