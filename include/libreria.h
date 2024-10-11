#ifndef LIBRERIA
#define LIBRERIA 1
#include <stdio.h>

#include "avr_api.h"

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
  ERROR
}salidas_c;


//datos 
typedef struct {
  uint8_t colores[6];    // lista de colores a detectar
  uint8_t tolerancia;
  salidas_c contenedores;     // enum de salida de contenedores de los colores
  void (*error_func)(void); // Funcion de error en caso de no detectar colores
  salidas_c indice_salida; // indice a mover para redirigir
}config;


config f_inicio(void); // lee el archivo de configuración y carga las variables.


#define SENS_IR_PORT avr_GPIO_C

#define SENS_IR_TRANS_PIN avr_GPIO_PIN_0
#define SENS_IR_TRANS avr_GPIOC_IN_0

#define SENS_IR_REDIR_PIN avr_GPIO_PIN_1
#define SENS_IR_REDIR avr_GPIOC_IN_1

#define TCS3200 avr_ADC_canal0



#endif //LIBRERIA