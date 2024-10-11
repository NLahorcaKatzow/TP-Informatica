#include "libreria.h"

uint16_t f_leer_sens_color();
void f_error_archivo();
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color);
config f_load_config_txt(const char *filename, void(*puntero)(void));



uint16_t f_leer_sens_color(){
    return (uint16_t)leer_ADC(TCS3200);
}

void f_error_archivo(){
    printf("Error al cargar el archivo de configuracion\n");
    exit(1); // Salir del programa
}


// Calcula si una medida de color esta dentro de la tolerancia permitida
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color) {
    int limiteInferior = color - tolerancia;
    int limiteSuperior = color + tolerancia;

    if (current_color >= limiteInferior && current_color <= limiteSuperior) {
        return 1; // La medida esta dentro de la tolerancia
    } else {
        return 0; // La medida no esta dentro de la tolerancia
    }
}


config f_load_config_txt(const char *filename, void (*error_func)(void)) {
    config cfg;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo para lectura");
        return cfg;
    }

    // Leer cada valor desde el archivo
    fscanf(file, "colores: %hhu %hhu %hhu %hhu %hhu %hhu\n", 
           &cfg.colores[0], &cfg.colores[1], &cfg.colores[2], 
           &cfg.colores[3], &cfg.colores[4], &cfg.colores[5]);
    fscanf(file, "tolerancia: %hhu\n", &cfg.tolerancia);

    int indice_salida;
    fscanf(file, "indice_salida: %d\n", &indice_salida);
    cfg.indice_salida = (salidas_c)indice_salida;

    // Asigna la función de error proporcionada
    cfg.error_func = error_func;

    fclose(file);
    return cfg;
}