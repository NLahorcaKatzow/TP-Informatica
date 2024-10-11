#include "libreria.h"
#include "funcs.c"
// Declaración de las funciones de estado que conforman la máquina de estados
void f_espera(estados current_estado, config *config);
void f_transportar(estados current_estado, config *config);
void f_clasificar(estados current_estado, config *config);
void f_redirigir(estados current_estado, config *config);
void f_error(estados current_estado, config *config);


// Definición de la función `f_espera`, que representa el estado "ESPERA"
void f_espera(estados current_estado, config *config){
    // Si se presiona el boton de arranque, cambia al estado "TRANSPORTAR"
    if (BUTTON != 0) {
        current_estado = TRANSPORTAR;
    }
}

// Definición de la función `f_transportar`, que representa el estado "TRANSPORTAR"
void f_transportar(estados current_estado, config *config){
    printf("Transportando\n");
    // Inicia el motor de la cinta transportadora
    i_set_motor_trans(HIGH); // se enciende el motor

    // Si el sensor infrarrojo de la cinta (SENS_IR_TRANS) detecta algo,
    // se detiene el motor y se pasa al estado "CLASIFICAR"
    if (SENS_IR_TRANS != 0) {
        i_set_motor_trans(LOW); // apaga el motor
        current_estado = CLASIFICAR;
    }
}

// Definición de la función `f_clasificar`, que representa el estado "CLASIFICAR"
void f_clasificar(estados current_estado, config *config){
    printf("Clasificando\n");
    // Ciclo para comprobar cada uno de los colores definidos en `config->colores`
    for (int i = 0; i < 6; i++) {
        // Si el color leído está dentro de la tolerancia especificada, asigna `indice_salida` y cambia al estado "REDIRIGIR"
        if (f_tolerancia(f_leer_sens_color(), config->tolerancia, config->colores[i])) {
            config->indice_salida = i;
            current_estado = REDIRIGIR;
            return; // Termina la función después de encontrar un color válido
        }
    }
    // Si no se encontró un color válido, pasa al estado "ERROR"
    current_estado = ERROR; 
}

// Definición de la función `f_redirigir`, que representa el estado "REDIRIGIR"
void f_redirigir(estados current_estado, config *config){
    printf("Redirigiendo\n");
    // Activa el motor para mover la cinta de redirección
    i_set_motor_redir(HIGH);

    // Si el sensor infrarrojo de la cinta de redirección (SENS_IR_REDIR) detecta algo,
    // se detiene el motor y se regresa al estado "TRANSPORTAR"
    if (SENS_IR_REDIR != 0) {
        i_set_motor_redir(LOW);
        current_estado = TRANSPORTAR;
    }
}

// Definición de la función `f_error`, que representa el estado "ERROR"
void f_error(estados current_estado, config *config){
    printf("Error\n");
    // Asigna el valor `ERRORC` al índice de salida, indicando que hubo un error en la clasificación
    config->indice_salida = ERRORC;

    // Intenta redirigir el flujo a el contenedor ERRORC después de un error
    current_estado = REDIRIGIR; 
}