#ifndef LIB_LEDC_H
#define LIB_LEDC_H

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
void ledc_init(uint8_t *pin);
void ledc_new_config(uint8_t, uint32_t, int);
#endif
