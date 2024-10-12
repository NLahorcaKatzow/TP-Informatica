#include "libreria.h"



int main(int argc, char const *argv[])
{
    config init_data;
    estados current_estado = ESPERA;

    init_data = f_load_config_txt("config.txt", f_error_archivo);
    f_init_avr();

    void (*fsm[])(estados, config*) = {f_espera, f_transportar, f_clasificar, f_redirigir, f_error};

    while (1) fsm[current_estado](current_estado, &init_data);
    

    return 0;
}

void f_init_avr(){
    //Inicializacion de pines de entrada de sensores de proximidad IR
    GpioInitStructure_AVR sensores_ir, motores;
 
    AdcInitStructure_AVR tcs3200;


    sensores_ir.port = SENS_IR_PORT;
    sensores_ir.modo = avr_GPIO_mode_Input;
    sensores_ir.pines = SENS_IR_TRANS_PIN | SENS_IR_REDIR_PIN | BUTTON_PIN;
    init_gpio(sensores_ir);

    //Inicializacion de pin de salida para los motores

    motores.port = MOTOR_PORT;
    motores.modo = avr_GPIO_mode_Output;
    motores.pines = MOTOR_TRANS_PIN | MOTOR_REDIR_PIN;
    init_gpio(motores);

    //Inicializacion de pin de entrada de sensor de color
    tcs3200.mode = avr_ADC_MODE_Single_Conversion;  
    tcs3200.reference = avr_ADC_REF_Internal;
    tcs3200.resolution = avr_ADC_RES_10Bit;
    tcs3200.prescaler = avr_ADC_Prescaler_64;
    tcs3200.channel = TCS3200;
    init_adc(tcs3200);

}

