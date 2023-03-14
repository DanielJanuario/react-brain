#ifndef LIB_LEDC_H
#define LIB_LEDC_H

#define LEDC_CHANNEL_COUNT 16

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "math.h"

/*RIGHT BRAIN DEFINES*/
#define RIGHT_VISUAL_CORTEX_1_PIN GPIO_NUM_2
#define RIGHT_VISUAL_CORTEX_2_PIN GPIO_NUM_4
#define RIGHT_AUDITORY_CORTEX_1_PIN GPIO_NUM_5
#define RIGHT_AUDITORY_CORTEX_2_PIN GPIO_NUM_12
#define RIGHT_STANDART_1_PIN GPIO_NUM_13 //PNP
#define RIGHT_STANDART_2_PIN GPIO_NUM_14
#define RIGHT_STANDART_3_PIN GPIO_NUM_15
#define RIGHT_STANDART_4_PIN GPIO_NUM_18

/*LEFT BRAIN DEFINES*/
#define LEFT_VISUAL_CORTEX_1_PIN GPIO_NUM_19
#define LEFT_VISUAL_CORTEX_2_PIN GPIO_NUM_21
#define LEFT_AUDITORY_CORTEX_1_PIN GPIO_NUM_22
#define LEFT_AUDITORY_CORTEX_2_PIN GPIO_NUM_23
#define LEFT_STANDART_1_PIN GPIO_NUM_25
#define LEFT_STANDART_2_PIN GPIO_NUM_26
#define LEFT_STANDART_3_PIN GPIO_NUM_17
#define LEFT_STANDART_4_PIN GPIO_NUM_16

static int ledc_pin[16] = {
                    RIGHT_VISUAL_CORTEX_1_PIN,
                    RIGHT_VISUAL_CORTEX_2_PIN,
                    LEFT_VISUAL_CORTEX_1_PIN,
                    LEFT_VISUAL_CORTEX_2_PIN,
                    RIGHT_AUDITORY_CORTEX_1_PIN,
                    RIGHT_AUDITORY_CORTEX_2_PIN,
                    LEFT_AUDITORY_CORTEX_1_PIN,
                    LEFT_AUDITORY_CORTEX_2_PIN,
                    RIGHT_STANDART_1_PIN,
                    RIGHT_STANDART_2_PIN,
                    RIGHT_STANDART_3_PIN,
                    RIGHT_STANDART_4_PIN,
                    LEFT_STANDART_1_PIN,
                    LEFT_STANDART_2_PIN,
                    LEFT_STANDART_3_PIN,
                    LEFT_STANDART_4_PIN,
                };

/*COMMUM DEFINES*/
#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#define MAX_PINS               16
#define DUTY_MAX               16


/*TASK DEFINES*/
#define LEDC_TASK_TAG "LIB_LEDC TASK"
#define LEDC_TASK_STACK 1024*2
static TaskHandle_t LEDC_TASK_HANDLE = NULL;

/*FUNCTIONS*/
void ledc_init();
void ledc_new_config(uint8_t, uint32_t, int);
#endif
