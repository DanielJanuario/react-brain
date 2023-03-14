#ifndef LIB_REACT_BRAIN
#define LIB_REACT_BRAIN

#include <LIB_LEDC.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <esp_log.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/gpio.h"

#define LIGHT_SENSOR_1_PIN ADC1_CHANNEL_4
#define LIGHT_SENSOR_2_PIN ADC1_CHANNEL_5
#define SOUND_SENSOR_1_PIN ADC1_CHANNEL_6
#define SOUND_SENSOR_2_PIN ADC1_CHANNEL_7

/*DUTY DEFINES*/
#define DUTY_LOW 50
#define DUTY_HIGH 8192-10

/*SENSORS DEFINES*/
#define LIGHT_SENSE 15
#define SOUND_SENSE 90

/*TASK DEFINES*/
#define REACT_BRAIN_TASK_TAG "LIB_REACT_BRAIN TASK"
#define REACT_BRAIN_TASK_STACK 1024*2
static TaskHandle_t REACT_BRAIN_TASK_HANDLE = NULL;

/*FUNCTIONS*/
void react_brain_init();


#endif