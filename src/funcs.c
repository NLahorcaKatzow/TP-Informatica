#include "libreria.h"
#include "conf.h"

// ImplementaciOn de las funciones

void f_init_avr(){
    //Inicializacion de pines de entrada de sensores de proximidad IR
    GpioInitStructure_AVR sensores_ir, motores;
    UartInitStructure uart;
    AdcInitStructure_AVR tcs3200;


    sensores_ir.port = SENS_IR_PORT;
    sensores_ir.modo = avr_GPIO_mode_Input;
    sensores_ir.pines = SENS_IR_TRANS_PIN | SENS_IR_REDIR_PIN | BUTTON_PIN;
    init_gpio(sensores_ir);

    //Inicializacion de pin de salida para los motores

    motores.port = MOTOR_PORT;
    motores.modo = avr_GPIO_mode_Output;
    motores.pines = MOTOR_TRANS_PIN | MOTOR_REDIR1_PIN | MOTOR_REDIR2_PIN | MOTOR_REDIR3_PIN | MOTOR_REDIR4_PIN | MOTOR_REDIR5_PIN | MOTOR_REDIR6_PIN;
    init_gpio(motores);

    //Inicializacion de pin de entrada de sensor de color
    tcs3200.mode = avr_ADC_MODE_Single_Conversion;  
    tcs3200.reference = avr_ADC_REF_Internal;
    tcs3200.resolution = avr_ADC_RES_10Bit; 
    tcs3200.prescaler = avr_ADC_Prescaler_64;
    tcs3200.channel = TCS3200;
    init_adc(tcs3200);
    
    //Inicializacion  de entrada de uart
    uart.baudrate = 9600;
    uart.uart_port = avr_uart0;
    init_uart_avr(uart);
    
    
    sei();
}


// FunciÃ³n para leer el valor del sensor de color
uint16_t f_leer_sens_color() {
    return (uint16_t)(leer_ADC(TCS3200)); // Llama a la funciÃ³n para leer el sensor TCS3200
}

// FunciÃ³n que se ejecuta si ocurre un error al cargar el archivo de configuraciÃ³n
void f_error_archivo() {
    //printf("Error al cargar el archivo de configuracion\n");
    //exit(1); // Termina el programa con un cÃ³digo de error
}

// FunciÃ³n que verifica si una medida de color estÃ¡ dentro de la tolerancia permitida
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color) {
    // Calcula el lÃ­mite inferior y superior para verificar si el color estÃ¡ dentro de la tolerancia
    int limiteInferior = color - tolerancia;
    int limiteSuperior = color + tolerancia;

    // Verifica si el valor del color actual estÃ¡ dentro del rango de tolerancia
    if (current_color >= limiteInferior && current_color <= limiteSuperior) {
        return HIGH; // La medida estÃ¡ dentro de la tolerancia
    } else {
        return LOW; // La medida no estÃ¡ dentro de la tolerancia
    }
}

// FunciÃ³n para cargar la configuraciÃ³n desde un archivo de texto
config f_load_init_data() {
    //CAMBIAR LUEGO (TODO)
    //Cargar variables de configuracion
    config new_config;
    new_config.colores[0] = 0;
    new_config.colores[1] = 150;
    new_config.colores[2] = 200;
    new_config.colores[3] = 255;
    new_config.colores[4] = 75;
    new_config.colores[5] = 50;
    new_config.tolerancia = 10;
    new_config.contenedores = ESPERA;
    new_config.indice_salida = 0;
    return new_config; // Retorna la nueva estructura
}

void f_set_motor_trans(int value) {
    MOTOR_TRANS = value;
}

estados f_cambiar_estado_a(estados new_estado){
    seleccionar_motor_redir(-1, LOW);
    f_set_motor_trans(LOW);
    uart_puts("cambiando estado"); 
    
    return new_estado;
}

void seleccionar_motor_redir(int motor_id, int value) {
    
    if(motor_id == -1){		//si id es -1, solamente va a desactivar todos los motores
    SELECT_MOTOR_OUT(1) = SELECT_MOTOR_OUT(2) = SELECT_MOTOR_OUT(3) = SELECT_MOTOR_OUT(4) = SELECT_MOTOR_OUT(5) = SELECT_MOTOR_OUT(6) = LOW;
    return;
    } 
    
    switch (motor_id + 1) {
        case 1:
            SELECT_MOTOR_OUT(1) = value;
            break;

        case 2:
            SELECT_MOTOR_OUT(2) = value;
            break;

        case 3:
            SELECT_MOTOR_OUT(3) = value;
            break;

        case 4:
            SELECT_MOTOR_OUT(4) = value;
            break;

        case 5:
            SELECT_MOTOR_OUT(5) = value;
            break;
	default:
	    //en caso haber una falla con el id, activa el motor6, el motor de errores de clasificacion
	    SELECT_MOTOR_OUT(6) = HIGH;
	break;
    }
}

estados f_clasificar(config *current_config){
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
    return f_error(current_config);
}


estados f_error(config *current_config){
    //printf("Error\n");
    uart_puts("Error\n");
    current_config->indice_salida = ERRORC;
    return f_cambiar_estado_a(REDIRIGIR); //retorna la nueva configuracion para volver a redirigir

}

int f_validate_sens_ir_trans(){
    return SENS_IR_TRANS == HIGH;
}
int f_validate_sens_ir_redir(){
    return SENS_IR_REDIR == HIGH;
}
int f_validate_button(){
    return BUTTON == HIGH;
}