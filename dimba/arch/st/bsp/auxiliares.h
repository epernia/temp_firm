

#ifndef __AUXILIARES_H
#define __AUXILIARES_H

#include "stm32f407xx.h"

enum{GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H};

//#############################################################
//## UART Ports
//#############################################################

#define ESP_PORT    1
#define A6_PORT		2
#define RS485_PORT	3
#define SIM800_PORT 4
#define DEBUG_PORT	6

//#############################################################
//## LEDs
//#############################################################

#define LEDn                             4

#define LED1_PIN                         GPIO_PIN_12
#define LED1_GPIO_PORT                   GPIO_B

#define LED2_PIN                         GPIO_PIN_13
#define LED2_GPIO_PORT                   GPIO_B

#define LED3_PIN                         GPIO_PIN_14
#define LED3_GPIO_PORT                   GPIO_B
  
#define LED4_PIN                         GPIO_PIN_15
#define LED4_GPIO_PORT                   GPIO_B

// #############################################################
// ## Pines de expansión
// #############################################################


#define EXP2_PIN                         GPIO_PIN_13
#define EXP2_GPIO_PORT                   GPIO_E

#define EXP4_PIN                         GPIO_PIN_12
#define EXP4_GPIO_PORT                   GPIO_E

#define EXP6_PIN                         GPIO_PIN_11
#define EXP6_GPIO_PORT                   GPIO_E

#define EXP8_PIN                         GPIO_PIN_10
#define EXP8_GPIO_PORT                   GPIO_E

#define EXP10_PIN                         GPIO_PIN_9
#define EXP10_GPIO_PORT                   GPIO_E

#define EXP11_PIN                         GPIO_PIN_8
#define EXP11_GPIO_PORT                   GPIO_E

#define EXP9_PIN                         GPIO_PIN_7
#define EXP9_GPIO_PORT                   GPIO_E

#define EXP7_PIN                         GPIO_PIN_1
#define EXP7_GPIO_PORT                   GPIO_B

#define EXP5_PIN                         GPIO_PIN_0
#define EXP5_GPIO_PORT                   GPIO_B

#define EXP3_PIN                         GPIO_PIN_5
#define EXP3_GPIO_PORT                   GPIO_C

#define EXP1_PIN                         GPIO_PIN_4
#define EXP1_GPIO_PORT                   GPIO_C

// #############################################################
// ## Pines del SIM800
// #############################################################

#define S800_PW_PIN                      	GPIO_PIN_3
#define S800_PW_GPIO_PORT                   GPIO_A

#define S800_DTR_PIN						GPIO_PIN_2
#define S800_DTR_GPIO_PORT                  GPIO_A

//#############################################################
//## Digital In/Out Pins
//#############################################################

#define IN_P_S_Pin                  		GPIO_PIN_9
#define IN_P_S_Port							GPIO_C

#define OUT_EN_Pin							GPIO_PIN_8
#define OUT_EN_Port							GPIO_A

#define IN_READ_Pin							GPIO_PIN_8
#define IN_READ_Port						GPIO_D

#define IN_CLK_Pin							GPIO_PIN_15
#define IN_CLK_Port							GPIO_D

#define OUT6_Pin							GPIO_PIN_9
#define OUT6_Port							GPIO_D

#define OUT5_Pin							GPIO_PIN_10
#define OUT5_Port							GPIO_D

#define OUT4_Pin							GPIO_PIN_11
#define OUT4_Port							GPIO_D

#define OUT3_Pin							GPIO_PIN_12
#define OUT3_Port							GPIO_D

#define OUT2_Pin							GPIO_PIN_13
#define OUT2_Port							GPIO_D

#define OUT1_Pin							GPIO_PIN_14
#define OUT1_Port							GPIO_D

//#############################################################
//## Global functions
//#############################################################

void gpioConfig(uint32_t GPIO_Port, uint16_t GPIO_Pin, uint32_t Mode);
uint32_t GPIO_ReadPin(uint32_t GPIO_Port, uint16_t GPIO_Pin);
void GPIO_WritePin(uint32_t GPIO_Port, uint16_t GPIO_Pin, uint32_t Pin_State);
void GPIO_TogglePin(uint32_t GPIO_Port, uint16_t GPIO_Pin);


#endif
