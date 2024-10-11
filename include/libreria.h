#ifndef LIBRERIA
#define LIBRERIA
#include <stdio.h>

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
  char colores[6];    // lista de colores a detectar
  int tolerancia;
  salidas_c contenedores;     // enum de salida de contenedores de los colores
  void (*error_func)(void); // Funcion de error en caso de no detectar colores
  salidas_c indice_salida; // indice a mover para redirigir
}config;


config f_inicio(void); // lee el archivo de configuración y carga las variables.

int sensor_ir1 = 0; //0 low, 1 high
int sensor_ir2 = 0; //0 low, 1 high
int sensor_color = 0; //0-225 color (cambiar por un char en un futuro)



#endif //LIBRERIA