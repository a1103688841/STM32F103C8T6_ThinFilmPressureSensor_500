/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "stm32f103xb.h"
#include "usart.h"
#include <stdint.h>
#include <stdbool.h>
#include "../../User/hc4051.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId          defaultTaskHandle;
uint32_t            defaultTaskBuffer[128];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId          scanADCHandle;
osThreadId          bleSendHandle;
uint32_t            myTask03Buffer[128];
osStaticThreadDef_t myTask03ControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const* argument);
void StartTask02(void const* argument);
void StartTask03(void const* argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t  xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of scanADC */
    osThreadDef(scanADC, StartTask02, osPriorityIdle, 0, 128);
    scanADCHandle = osThreadCreate(osThread(scanADC), NULL);

    /* definition and creation of bleSend */
    osThreadStaticDef(bleSend, StartTask03, osPriorityIdle, 0, 128, myTask03Buffer, &myTask03ControlBlock);
    bleSendHandle = osThreadCreate(osThread(bleSend), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const* argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the scanADC thread.
 * @param argument: Not used
 * @retval None
 */
void set_ic1_s0(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic1_s1(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic1_s2(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
//
void set_ic2_s0(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic2_s1(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic2_s2(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
//
void set_ic3_s0(bool state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic3_s1(bool state)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic3_s2(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
//
void set_ic4_s0(bool state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic4_s1(bool state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic4_s2(bool state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
//
void set_ic5_s0(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic5_s1(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void set_ic5_s2(bool state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
/* USER CODE END Header_StartTask02 */
void StartTask02(void const* argument)
{
    /* USER CODE BEGIN StartTask02 */

    // 初始化HC4051
    hc4051_init(&HC4051_ic1, set_ic1_s0, set_ic1_s1, set_ic1_s2, NULL);
    hc4051_init(&HC4051_ic2, set_ic2_s0, set_ic2_s1, set_ic2_s2, NULL);
    hc4051_init(&HC4051_ic3, set_ic3_s0, set_ic3_s1, set_ic3_s2, NULL);
    hc4051_init(&HC4051_ic4, set_ic4_s0, set_ic4_s1, set_ic4_s2, NULL);
    hc4051_init(&HC4051_ic5, set_ic5_s0, set_ic5_s1, set_ic5_s2, NULL);

    /* Infinite loop */
    for (;;)
    {
        // 将DMA数据转换为ADC值
        machine_state.hc4051_ic1_current_ADC                                             = machine_state.dma_adc[0];
        machine_state.hc4051_ic2_current_ADC                                             = machine_state.dma_adc[1];
        machine_state.hc4051_ic3_current_ADC                                             = machine_state.dma_adc[2];
        machine_state.hc4051_ic4_current_ADC                                             = machine_state.dma_adc[3];
        machine_state.hc4051_ic5_current_ADC                                             = machine_state.dma_adc[4];
        machine_state.thinFilePressSensor_ADC[machine_state.hc4051_ic1_channel]          = machine_state.hc4051_ic1_current_ADC;
        machine_state.thinFilePressSensor_ADC[machine_state.hc4051_ic2_channel + 8 - 1]  = machine_state.hc4051_ic2_current_ADC;
        machine_state.thinFilePressSensor_ADC[machine_state.hc4051_ic3_channel + 16 - 1] = machine_state.hc4051_ic3_current_ADC;
        machine_state.thinFilePressSensor_ADC[machine_state.hc4051_ic4_channel + 24 - 1] = machine_state.hc4051_ic4_current_ADC;
        machine_state.thinFilePressSensor_ADC[machine_state.hc4051_ic5_channel + 32 - 1] = machine_state.hc4051_ic5_current_ADC;
        // 通道号
        machine_state.hc4051_ic1_channel++;
        if (machine_state.hc4051_ic1_channel > 7)
        {
            machine_state.hc4051_ic1_channel = 0;
        }
        machine_state.hc4051_ic2_channel++;
        if (machine_state.hc4051_ic2_channel > 7)
        {
            machine_state.hc4051_ic2_channel = 0;
        }
        machine_state.hc4051_ic3_channel++;
        if (machine_state.hc4051_ic3_channel > 7)
        {
            machine_state.hc4051_ic3_channel = 0;
        }
        machine_state.hc4051_ic4_channel++;
        if (machine_state.hc4051_ic4_channel > 7)
        {
            machine_state.hc4051_ic4_channel = 0;
        }
        machine_state.hc4051_ic5_channel++;
        if (machine_state.hc4051_ic5_channel > 7)
        {
            machine_state.hc4051_ic5_channel = 0;
        }
        hc4051_selectChannel(&HC4051_ic1, machine_state.hc4051_ic1_channel);
        hc4051_selectChannel(&HC4051_ic2, machine_state.hc4051_ic2_channel);
        hc4051_selectChannel(&HC4051_ic3, machine_state.hc4051_ic3_channel);
        hc4051_selectChannel(&HC4051_ic4, machine_state.hc4051_ic4_channel);
        hc4051_selectChannel(&HC4051_ic5, machine_state.hc4051_ic5_channel);
        HAL_ADC_Start_DMA(&hadc1, (uint32_t*)machine_state.dma_adc, 5);
        osDelay(pdMS_TO_TICKS(100));
    }
    /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the bleSend thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void const* argument)
{
    /* USER CODE BEGIN StartTask03 */
    /* Infinite loop */
    for (;;)
    {
        if (machine_state.ble_select == 1)
        {
            machine_state.ble_data_select = machine_state.ble_data_bin1;
            machine_state.ble_data_other  = machine_state.ble_data_bin2;
        }
        else
        {
            machine_state.ble_data_select = machine_state.ble_data_bin2;
            machine_state.ble_data_other  = machine_state.ble_data_bin1;
        }
        HAL_UART_Transmit_IT(&huart3, machine_state.ble_data_select, 1024);
        sprintf(
            machine_state.ble_data_other, "1:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",  //
            machine_state.thinFilePressSensor_ADC[0], machine_state.thinFilePressSensor_ADC[1], machine_state.thinFilePressSensor_ADC[2], machine_state.thinFilePressSensor_ADC[3],
            machine_state.thinFilePressSensor_ADC[4], machine_state.thinFilePressSensor_ADC[5], machine_state.thinFilePressSensor_ADC[6], machine_state.thinFilePressSensor_ADC[7],
            machine_state.thinFilePressSensor_ADC[8], machine_state.thinFilePressSensor_ADC[9], machine_state.thinFilePressSensor_ADC[10], machine_state.thinFilePressSensor_ADC[11],
            machine_state.thinFilePressSensor_ADC[12], machine_state.thinFilePressSensor_ADC[13], machine_state.thinFilePressSensor_ADC[14], machine_state.thinFilePressSensor_ADC[15],
            machine_state.thinFilePressSensor_ADC[16], machine_state.thinFilePressSensor_ADC[17], machine_state.thinFilePressSensor_ADC[18], machine_state.thinFilePressSensor_ADC[19],
            machine_state.thinFilePressSensor_ADC[20], machine_state.thinFilePressSensor_ADC[21], machine_state.thinFilePressSensor_ADC[22], machine_state.thinFilePressSensor_ADC[23],
            machine_state.thinFilePressSensor_ADC[24], machine_state.thinFilePressSensor_ADC[25], machine_state.thinFilePressSensor_ADC[26], machine_state.thinFilePressSensor_ADC[27],
            machine_state.thinFilePressSensor_ADC[28], machine_state.thinFilePressSensor_ADC[29], machine_state.thinFilePressSensor_ADC[30], machine_state.thinFilePressSensor_ADC[31],
            machine_state.thinFilePressSensor_ADC[32], machine_state.thinFilePressSensor_ADC[33], machine_state.thinFilePressSensor_ADC[34], machine_state.thinFilePressSensor_ADC[35]);

        osDelay(pdMS_TO_TICKS(10));
    }
    /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
