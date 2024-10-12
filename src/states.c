#include "libreria.h"

void f_espera(estados current_estado, config *config){
    uart_puts("EnEspera\n");
    //i_set_motor_redir(BUTTON);
    if(BUTTON == HIGH) current_estado = TRANSPORTAR;
}

void f_transportar(estados current_estado, config *config){
    //printf("Transportando\n");
    uart_puts("Transportando\n");
    //mover la cinta
    i_set_motor_trans(HIGH);
    //accionar el motor para mover cinta
    
    if(SENS_IR_TRANS == HIGH) {
        i_set_motor_trans(LOW);
        current_estado = CLASIFICAR;
        }
}

void f_clasificar(estados current_estado, config *config){
    int i = 0;
    //printf("Clasificando\n");
    uart_puts("Clasificando\n");
    //leer datos de la cinta
    //accionar el algoritmo para clasificar
    
    for (i = 0; i < 6; i++)
    {
        if(f_tolerancia(f_leer_sens_color(), config->tolerancia, config->colores[i])){
            config->indice_salida = i;
            current_estado = REDIRIGIR;
            return;
            }
    }
    current_estado = ERROR; //no encontro un color dentro de las especificaciones
    
}

void f_redirigir(estados current_estado, config *config){
    //printf("Redirigiendo\n");
    uart_puts("Redirigiendo\n");
    //accionar el motor para mover la cinta de redireccion
    i_set_motor_redir(HIGH);
    if(SENS_IR_REDIR != 0) {
        i_set_motor_redir(LOW);
        current_estado = TRANSPORTAR;
        }
    
}

void f_error(estados current_estado, config *config){
    //printf("Error\n");
    uart_puts("Error\n");
    config->indice_salida = ERRORC;
    current_estado = REDIRIGIR; //

    current_estado = ESPERA;
}

