#include <stdio.h>
#include "libreria.h"



int main(int argc, char const *argv[])
{
    config init_data;
    estados current_estado = ESPERA;
    void (*fsm[])(estados, config) = {f_espera, f_transportar, f_clasificar, f_redirigir, f_error};

    while (1) fsm[current_estado](current_estado, init_data);
    

    return 0;
}


void f_espera(estados current_estado, config config){

    printf("En espera\n");
    //leer pin de sensor infrarrojo
    if(sensor_ir1 == 0) current_estado = TRANSPORTAR;
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
        if(f_tolerancia(sensor_color, config->tolerancia, config->colores[i])){
            config->indice_salida = i;
            current_estado = REDIRIGIR;
            }
    }
    current_estado = ERROR; //no encontro un color dentro de las especificaciones
    
}

void f_redirigir(estados current_estado, config config){
    printf("Redirigiendo\n");
    //accionar el motor para mover la cinta de redireccion
    if(sensor_ir2 != 0) current_estado = TRANSPORTAR;
    
}

void f_error(estados current_estado, config config){
    printf("Error\n");
    //accionar accion de error
    current_estado = ESPERA;
}


// Calcula si una medida de color esta dentro de la tolerancia permitida
int f_tolerancia(int color, int tolerancia, int current_color) {
    int limiteInferior = color - tolerancia;
    int limiteSuperior = color + tolerancia;

    if (current_color >= limiteInferior && current_color <= limiteSuperior) {
        return 1; // La medida esta dentro de la tolerancia
    } else {
        return 0; // La medida no esta dentro de la tolerancia
    }
}