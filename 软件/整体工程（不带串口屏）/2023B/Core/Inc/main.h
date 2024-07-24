/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOF
#define Relays_Pin GPIO_PIN_12
#define Relays_GPIO_Port GPIOD
#define ADS_RST_Pin GPIO_PIN_9
#define ADS_RST_GPIO_Port GPIOC
#define ADS_DAISY_Pin GPIO_PIN_8
#define ADS_DAISY_GPIO_Port GPIOA
#define ADS_SDO_Pin GPIO_PIN_11
#define ADS_SDO_GPIO_Port GPIOA
#define ADS_SDI_Pin GPIO_PIN_12
#define ADS_SDI_GPIO_Port GPIOA
#define ADS_nCS_Pin GPIO_PIN_15
#define ADS_nCS_GPIO_Port GPIOA
#define ADS_SCLK_Pin GPIO_PIN_10
#define ADS_SCLK_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOB
#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
