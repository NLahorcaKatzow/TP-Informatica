#include "libreria.h"

estados f_espera(estados current_estado, config *current_config){
    //uart_puts("EnEspera\n");
    //i_set_motor_trans(BUTTON);
    
    if(BUTTON == HIGH) return f_cambiar_estado_a(TRANSPORTAR);
    return ESPERA;
}

estados f_transportar(estados current_estado, config *current_config){
    //printf("Transportando\n");
    //uart_puts("Transportando\n");
    //mover la cinta
    i_set_motor_trans(HIGH);
    //accionar el motor para mover cinta
    
    if(SENS_IR_TRANS == HIGH) {
        return f_cambiar_estado_a(CLASIFICAR);
        }
     return TRANSPORTAR;
}

estados f_clasificar(estados current_estado, config *current_config){
    int i = 0;
    //printf("Clasificando\n");
    //uart_puts("Clasificando\n");
    //leer datos de la cinta
    //accionar el algoritmo para clasificar
    
    for (i = 0; i < 6; i++)
    {
        if(f_tolerancia(f_leer_sens_color(), current_config->tolerancia, current_config->colores[i])){
            current_config->indice_salida = i;
            return f_cambiar_estado_a(REDIRIGIR);
            
            }
    }
    return f_cambiar_estado_a(ERROR); //no encontro un color dentro de las especificaciones
}

estados f_redirigir(estados current_estado, config *current_config){
    //printf("Redirigiendo\n");
    //uart_puts("Redirigiendo\n");
    //accionar el motor para mover la cinta de redireccion
    seleccionar_motor_redir(current_config->indice_salida, HIGH);
    if(SENS_IR_REDIR != 0) {
        return f_cambiar_estado_a(TRANSPORTAR);
        }
    return REDIRIGIR;
}

estados f_error(estados current_estado, config *current_config){
    //printf("Error\n");
    uart_puts("Error\n");
    current_config->indice_salida = ERRORC;
    return f_cambiar_estado_a(REDIRIGIR); //retorna la nueva configuracion para volver a redirigir

}

