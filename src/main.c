#include <stdio.h>
#include "libreria.h"



int main(int argc, char const *argv[])
{
    config init_data;
    estados current_estado = ESPERA;

    init_data = f_load_config_txt("config.txt", f_error_archivo);
    init_avr();

    void (*fsm[])(estados, config) = {f_espera, f_transportar, f_clasificar, f_redirigir, f_error};

    while (1) fsm[current_estado](current_estado, init_data);
    

    return 0;
}

void f_init_avr(){
    //Inicializacion de pines de entrada de sensores de proximidad IR
    GpioInitStructure_AVR sensores_ir;

    sensores_ir.port = SENS_IR_PORT;
    sensores_ir.modo = avr_GPIO_mode_Input;
    sensores_ir.pines = SENS_IR_TRANS_PIN | SENS_IR_REDIR_PIN;
    init_gpio(sensores_ir);

    //Inicializacion de pin de entrada de sensor de color
    AdcInitStructure_AVR tcs3200;
    tcs3200.mode = avr_ADC_MODE_Single_Conversion;
    tcs3200.reference = avr_ADC_REF_Internal;
    tcs3200.resolution = avr_ADC_RES_8Bit;
    tcs3200.prescaler = avr_ADC_Prescaler_64;
    tcs3200.channel = TCS3200;
    init_adc(tcs3200);

}

uint16_t f_leer_sens_color(){
    return (uint16_t)leer_ADC(TCS3200);
}


void f_espera(estados current_estado, config config){

    printf("En espera\n");
    //leer pin de sensor infrarrojo
    if(SENS_IR_TRANS_PIN == 0) current_estado = TRANSPORTAR;
    else current_estado = CLASIFICAR;
}

void f_transportar(estados current_estado, config config){
    printf("Transportando\n");
    //mover la cinta
    //accionar el motor para mover cinta
    current_estado = CLASIFICAR;
}

void f_clasificar(estados current_estado, config *config){
    printf("Clasificando\n");
    //leer datos de la cinta
    //accionar el algoritmo para clasificar
    for (size_t i = 0; i < 6; i++)
    {
        if(f_tolerancia(f_leer_sens_color(), config->tolerancia, config->colores[i])){
            config->indice_salida = i;
            current_estado = REDIRIGIR;
            return;
            }
    }
    current_estado = ERROR; //no encontro un color dentro de las especificaciones
    
}

void f_redirigir(estados current_estado, config config){
    printf("Redirigiendo\n");
    //accionar el motor para mover la cinta de redireccion
    
    if(SENS_IR_REDIR_PIN != 0) current_estado = TRANSPORTAR;
    
}

void f_error(estados current_estado, config config){
    printf("Error\n");
    
    current_estado = REDIRIGIR; //

    current_estado = ESPERA;
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

    int contenedores;
    fscanf(file, "contenedores: %d\n", &contenedores);
    cfg.contenedores = (salidas_c)contenedores;

    int indice_salida;
    fscanf(file, "indice_salida: %d\n", &indice_salida);
    cfg.indice_salida = (salidas_c)indice_salida;

    // Asigna la función de error proporcionada
    cfg.error_func = error_func;

    fclose(file);
    return cfg;
}