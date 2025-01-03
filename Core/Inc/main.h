/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
typedef struct
{
    int hc4051_ic1_channel;
    int hc4051_ic2_channel;
    int hc4051_ic3_channel;
    int hc4051_ic4_channel;
    int hc4051_ic5_channel;
    //
    int hc4051_ic1_current_ADC;
    int hc4051_ic2_current_ADC;
    int hc4051_ic3_current_ADC;
    int hc4051_ic4_current_ADC;
    int hc4051_ic5_current_ADC;
    //
    unsigned int dma_adc[5];
    int          thinFilePressSensor_ADC[40];
    //
    char* ble_data_select;
    char* ble_data_other;

    char  ble_data_bin1[1024];
    char  ble_data_bin2[1024];
    short ble_select;
} machine_state_t;
extern machine_state_t machine_state;
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

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
