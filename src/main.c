#include "libreria.h"

int main(int argc, char const *argv[])
{
    config init_data = f_load_init_data();
    estados current_estado = ESPERA;
    estados (*fsm[])(estados, config*) = {f_espera, f_transportar, f_redirigir};

    f_init_avr();
    uart_puts("Iniciando sistemas");
    uart_putc('c');
    while (1) current_estado = fsm[current_estado](current_estado, &init_data);
    
    return 0;
}