#ifndef LIBRERIA
#define LIBRERIA

#include "conf.h"


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
estados f_cambiar_estado_a(estados new_estado); //cambia el valor de un estado al transicionar
void seleccionar_motor_redir(int motor_id, int value); //selecciona el motor de redireccion y lo activa;


//funciones de estado
estados f_espera(estados current_estado, config *config);
estados f_transportar(estados current_estado, config *config);
estados f_clasificar(estados current_estado, config *config);
estados f_redirigir(estados current_estado, config *config);
estados f_error(estados current_estado, config *config);



#endif // LIBRERIA