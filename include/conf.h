#ifndef CONF_H
#define CONF_H 1


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

#define MOTOR_REDIR1_PIN avr_GPIO_PIN_1
#define MOTOR_REDIR1 avr_GPIOA_OUT_1

#define MOTOR_REDIR2_PIN avr_GPIO_PIN_2
#define MOTOR_REDIR2 avr_GPIOA_OUT_2

#define MOTOR_REDIR3_PIN avr_GPIO_PIN_3
#define MOTOR_REDIR3 avr_GPIOA_OUT_3

#define MOTOR_REDIR4_PIN avr_GPIO_PIN_4
#define MOTOR_REDIR4 avr_GPIOA_OUT_4

#define MOTOR_REDIR5_PIN avr_GPIO_PIN_5
#define MOTOR_REDIR5 avr_GPIOA_OUT_5

#define MOTOR_REDIR6_PIN avr_GPIO_PIN_6
#define MOTOR_REDIR6 avr_GPIOA_OUT_6

#define TCS3200 avr_ADC_canal0

#define HIGH 1
#define LOW 0

#define SELECT_MOTOR_OUT(motor_id) MOTOR_REDIR##motor_id

#endif //CONF_H