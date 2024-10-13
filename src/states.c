#include "libreria.h"

estados f_espera(estados current_estado, config *current_config)
{
    // uart_puts("EnEspera\n");

    if (f_validate_button())
        return f_cambiar_estado_a(TRANSPORTAR);
    return ESPERA;
}

estados f_transportar(estados current_estado, config *current_config)
{
    // printf("Transportando\n");
    // uart_puts("Transportando\n");
    // mover la cinta
    f_set_motor_trans(HIGH);
    // accionar el motor para mover cinta

    if (f_validate_sens_ir_trans())
        return f_clasificar(current_config);

    return TRANSPORTAR;
}

estados f_redirigir(estados current_estado, config *current_config)
{
    // printf("Redirigiendo\n");
    // uart_puts("Redirigiendo\n");
    // accionar el motor para mover la cinta de redireccion
    seleccionar_motor_redir(current_config->indice_salida, HIGH);
    if (f_validate_sens_ir_redir())
    {
        return f_cambiar_estado_a(TRANSPORTAR);
    }
    return REDIRIGIR;
}
