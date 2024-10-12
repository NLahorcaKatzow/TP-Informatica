#include "libreria.h"

int main(int argc, char const *argv[])
{
    
    config init_data;
    estados current_estado = ESPERA;
    
    init_data = f_load_config_txt();
    f_init_avr();
    uart_puts("Iniciando sistemas\n");
    void (*fsm[])(estados, config*) = {f_espera, f_transportar, f_clasificar, f_redirigir, f_error};
    uart_putc('c');
    while (1) fsm[current_estado](current_estado, &init_data);
    
    return 0;
}
