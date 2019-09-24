/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

#define AN_IN1_Pin GPIO_PIN_0
#define AN_IN1_GPIO_Port GPIOC
#define AN_IN2_Pin GPIO_PIN_1
#define AN_IN2_GPIO_Port GPIOC
#define AN_IN3_Pin GPIO_PIN_2
#define AN_IN3_GPIO_Port GPIOC
#define AN_IN4_Pin GPIO_PIN_3
#define AN_IN4_GPIO_Port GPIOC
#define S800_UART_TX_Pin GPIO_PIN_0
#define S800_UART_TX_GPIO_Port GPIOA
#define S800_UART_RX_Pin GPIO_PIN_1
#define S800_UART_RX_GPIO_Port GPIOA
#define S800_DTR_Pin GPIO_PIN_2
#define S800_DTR_GPIO_Port GPIOA
#define S800_PW_Pin GPIO_PIN_3
#define S800_PW_GPIO_Port GPIOA
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define EXP_PIN1_Pin GPIO_PIN_4
#define EXP_PIN1_GPIO_Port GPIOC
#define EXP_PIN3_Pin GPIO_PIN_5
#define EXP_PIN3_GPIO_Port GPIOC
#define EXP_PIN5_Pin GPIO_PIN_0
#define EXP_PIN5_GPIO_Port GPIOB
#define EXP_PIN7_Pin GPIO_PIN_1
#define EXP_PIN7_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define EXP_PIN9_Pin GPIO_PIN_7
#define EXP_PIN9_GPIO_Port GPIOE
#define EXP_PIN11_Pin GPIO_PIN_8
#define EXP_PIN11_GPIO_Port GPIOE
#define EXP_PIN10_Pin GPIO_PIN_9
#define EXP_PIN10_GPIO_Port GPIOE
#define EXP_PIN8_Pin GPIO_PIN_10
#define EXP_PIN8_GPIO_Port GPIOE
#define EXP_PIN6_Pin GPIO_PIN_11
#define EXP_PIN6_GPIO_Port GPIOE
#define EXP_PIN4_Pin GPIO_PIN_12
#define EXP_PIN4_GPIO_Port GPIOE
#define EXP_PIN2_Pin GPIO_PIN_13
#define EXP_PIN2_GPIO_Port GPIOE
#define RS485_RE_Pin GPIO_PIN_14
#define RS485_RE_GPIO_Port GPIOE
#define RS485_DE_Pin GPIO_PIN_15
#define RS485_DE_GPIO_Port GPIOE
#define RS485_TX_Pin GPIO_PIN_10
#define RS485_TX_GPIO_Port GPIOB
#define RS485_RX_Pin GPIO_PIN_11
#define RS485_RX_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_12
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_13
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_14
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_15
#define LED4_GPIO_Port GPIOB
#define IN_READ_Pin GPIO_PIN_8
#define IN_READ_GPIO_Port GPIOD
#define OUT6_Pin GPIO_PIN_9
#define OUT6_GPIO_Port GPIOD
#define OUT5_Pin GPIO_PIN_10
#define OUT5_GPIO_Port GPIOD
#define OUT4_Pin GPIO_PIN_11
#define OUT4_GPIO_Port GPIOD
#define OUT3_Pin GPIO_PIN_12
#define OUT3_GPIO_Port GPIOD
#define OUT2_Pin GPIO_PIN_13
#define OUT2_GPIO_Port GPIOD
#define OUT1_Pin GPIO_PIN_14
#define OUT1_GPIO_Port GPIOD
#define IN_CLK_Pin GPIO_PIN_15
#define IN_CLK_GPIO_Port GPIOD
#define DEBUG_UART_TX_Pin GPIO_PIN_6
#define DEBUG_UART_TX_GPIO_Port GPIOC
#define DEBUG_UART_RX_Pin GPIO_PIN_7
#define DEBUG_UART_RX_GPIO_Port GPIOC
#define uSD_D0_Pin GPIO_PIN_8
#define uSD_D0_GPIO_Port GPIOC
#define IN_P_S_Pin GPIO_PIN_9
#define IN_P_S_GPIO_Port GPIOC
#define OUT_EN_Pin GPIO_PIN_8
#define OUT_EN_GPIO_Port GPIOA
#define ESP_UART_TX_Pin GPIO_PIN_9
#define ESP_UART_TX_GPIO_Port GPIOA
#define ESP_UART_RX_Pin GPIO_PIN_10
#define ESP_UART_RX_GPIO_Port GPIOA
#define ESP_RESET_Pin GPIO_PIN_11
#define ESP_RESET_GPIO_Port GPIOA
#define uSD_DET_Pin GPIO_PIN_12
#define uSD_DET_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_10
#define SW1_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_11
#define SW2_GPIO_Port GPIOC
#define uSD_CK_Pin GPIO_PIN_12
#define uSD_CK_GPIO_Port GPIOC
#define uSD_CD_Pin GPIO_PIN_0
#define uSD_CD_GPIO_Port GPIOD
#define uSD_CMD_Pin GPIO_PIN_2
#define uSD_CMD_GPIO_Port GPIOD
#define A6_INT_Pin GPIO_PIN_3
#define A6_INT_GPIO_Port GPIOD
#define A6_PW_Pin GPIO_PIN_4
#define A6_PW_GPIO_Port GPIOD
#define A6_UART_TX_Pin GPIO_PIN_5
#define A6_UART_TX_GPIO_Port GPIOD
#define A6_UART_RX_Pin GPIO_PIN_6
#define A6_UART_RX_GPIO_Port GPIOD
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define CAN1_RX_Pin GPIO_PIN_8
#define CAN1_RX_GPIO_Port GPIOB
#define CAN1_TX_Pin GPIO_PIN_9
#define CAN1_TX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
