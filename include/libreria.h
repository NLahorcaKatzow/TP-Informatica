#ifndef LIBRERIA
#define LIBRERIA

#include "avr_api.h"

//definiciones

#define SENS_IR_PORT avr_GPIO_C

#define SENS_IR_TRANS_PIN avr_GPIO_PIN_0
#define SENS_IR_TRANS avr_GPIOC_IN_0

#define SENS_IR_REDIR_PIN avr_GPIO_PIN_1
#define SENS_IR_REDIR avr_GPIOC_IN_1

#define BUTTON_PIN avr_GPIO_PIN_2
#define BUTTON avr_GPIOC_IN_2

#define MOTOR_PORT avr_GPIO_A

#define MOTOR_TRANS_PIN avr_GPIO_PIN_0
#define MOTOR_TRANS avr_GPIOA_OUT_0

#define MOTOR_REDIR_PIN avr_GPIO_PIN_1
#define MOTOR_REDIR avr_GPIOA_OUT_1



#define TCS3200 avr_ADC_canal0

#define HIGH 1
#define LOW 0


//estados
typedef enum{
  ESPERA,
  TRANSPORTAR,
  CLASIFICAR,
  REDIRIGIR,
  ERROR
}estados;

//salidas
typedef enum {
  S0,
  S1,
  S2,
  S3,
  S4,
  S5,
  ERRORC
}salidas_c;

//datos 
typedef struct {
  uint8_t colores[6];    // lista de colores a detectar
  uint8_t tolerancia;
  salidas_c contenedores;     // enum de salida de contenedores de los colores
  //void (*error_func)(estados current_estado, config *config); // Funcion de error en caso de no detectar colores
  salidas_c indice_salida; // indice a mover para redirigir
}config;

//funciones
void f_init_avr();
void i_set_motor_redir(int i);
void i_set_motor_trans(int i);
uint16_t f_leer_sens_color(); // Lee el valor del sensor de color
void f_error_archivo();       // Muestra un error al cargar un archivo y termina el programa
int f_tolerancia(uint16_t color, uint8_t tolerancia, uint8_t current_color); // Verifica si un color está dentro de una tolerancia
config f_load_config_txt(); // Carga la configuración desde un archivo de texto


//funciones de estado
void f_espera(estados current_estado, config *config);
void f_transportar(estados current_estado, config *config);
void f_clasificar(estados current_estado, config *config);
void f_redirigir(estados current_estado, config *config);
void f_error(estados current_estado, config *config);



#endif // LIBRERIA