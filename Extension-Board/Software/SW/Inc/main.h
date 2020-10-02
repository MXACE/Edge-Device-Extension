/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#define LED_6_Pin GPIO_PIN_13
#define LED_6_GPIO_Port GPIOC
#define LED_5_Pin GPIO_PIN_14
#define LED_5_GPIO_Port GPIOC
#define LED_4_Pin GPIO_PIN_15
#define LED_4_GPIO_Port GPIOC
#define seg___phase_Pin GPIO_PIN_0
#define seg___phase_GPIO_Port GPIOC
#define seg___A_Pin GPIO_PIN_1
#define seg___A_GPIO_Port GPIOC
#define seg___D_Pin GPIO_PIN_2
#define seg___D_GPIO_Port GPIOC
#define seg___B_Pin GPIO_PIN_3
#define seg___B_GPIO_Port GPIOC
#define seg___C_Pin GPIO_PIN_0
#define seg___C_GPIO_Port GPIOA
#define seg___latch_Pin GPIO_PIN_1
#define seg___latch_GPIO_Port GPIOA
#define seg_DP_Pin GPIO_PIN_2
#define seg_DP_GPIO_Port GPIOA
#define seg_L1L2_Pin GPIO_PIN_3
#define seg_L1L2_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_5
#define LED_3_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_6
#define LED_2_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_7
#define LED_1_GPIO_Port GPIOA
#define Button_3_Pin GPIO_PIN_4
#define Button_3_GPIO_Port GPIOC
#define Button_2_Pin GPIO_PIN_5
#define Button_2_GPIO_Port GPIOC
#define Button_1_Pin GPIO_PIN_0
#define Button_1_GPIO_Port GPIOB
#define Relay_3_Pin GPIO_PIN_1
#define Relay_3_GPIO_Port GPIOB
#define Relay_2_Pin GPIO_PIN_2
#define Relay_2_GPIO_Port GPIOB
#define Relay_1_Pin GPIO_PIN_10
#define Relay_1_GPIO_Port GPIOB
#define seg_L3_Pin GPIO_PIN_12
#define seg_L3_GPIO_Port GPIOB
#define DIG1_Pin GPIO_PIN_13
#define DIG1_GPIO_Port GPIOB
#define DIG2_Pin GPIO_PIN_14
#define DIG2_GPIO_Port GPIOB
#define DIG3_Pin GPIO_PIN_15
#define DIG3_GPIO_Port GPIOB
#define DIG4_Pin GPIO_PIN_8
#define DIG4_GPIO_Port GPIOC
#define RGB_B_Pin GPIO_PIN_8
#define RGB_B_GPIO_Port GPIOA
#define RGB_R_Pin GPIO_PIN_11
#define RGB_R_GPIO_Port GPIOA
#define RGB_G_Pin GPIO_PIN_12
#define RGB_G_GPIO_Port GPIOA
#define Relay_4_Pin GPIO_PIN_2
#define Relay_4_GPIO_Port GPIOD
#define Relay_5_Pin GPIO_PIN_4
#define Relay_5_GPIO_Port GPIOB
#define Relay_6_Pin GPIO_PIN_5
#define Relay_6_GPIO_Port GPIOB
#define LED_8_Pin GPIO_PIN_8
#define LED_8_GPIO_Port GPIOB
#define LED_7_Pin GPIO_PIN_9
#define LED_7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
