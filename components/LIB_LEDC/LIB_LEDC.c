#include "LIB_LEDC.h"

uint8_t ledc_ch_num = 0;
ledc_channel_config_t ledc_channel[MAX_PINS];
int max_duty[MAX_PINS];
int target_duty[MAX_PINS];
int ledc_time_to_fade[MAX_PINS];

void vTask_LEDC(void * param){
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    ESP_LOGI(LEDC_TASK_TAG, "Task iniciada");
    

    
    for (;;) {
        /*FADE ON*/
        for(uint8_t i = 0; i < ledc_ch_num; i++){
            ESP_LOGI(LEDC_TASK_TAG, "MAX_DUTY: %d | TARGET_DUTY: %d | TIME_TO_FADE: %d", max_duty[i], target_duty[i], ledc_time_to_fade[i]);


        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    
    ESP_LOGE(LEDC_TASK_TAG, "Task finalizada");
    vTaskDelete(NULL);
}

void ledc_new_config(uint8_t id, uint32_t duty, int time_to_fade){
    max_duty[id] = 15;
    target_duty[id] = 10;
    ledc_time_to_fade[id] = 150;
}

void ledc_init(uint8_t pin[]){
    ledc_ch_num = sizeof(pin);
    ESP_LOGW(LEDC_TASK_TAG, "NUMB OF CHANNELS: %d", ledc_ch_num);
   
    ledc_timer_config_t timer_conf = {
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));


    for(uint8_t i = 0; i < ledc_ch_num; i++){
        ledc_channel[i].channel = i;
        ledc_channel[i].duty = 0;
        ledc_channel[i].gpio_num = pin[i];
        ledc_channel[i].speed_mode = LEDC_HS_MODE;
        ledc_channel[i].hpoint = 0;
        ledc_channel[i].timer_sel = LEDC_HS_TIMER;
        ledc_channel[i].flags.output_invert = 1;
        ledc_channel_config(&ledc_channel[i]);
    }

    xTaskCreate(vTask_LEDC,
                "LEDC TASK",
                LEDC_TASK_STACK,
                NULL,
                0,
                LEDC_TASK_HANDLE);
    configASSERT(&LEDC_TASK_HANDLE);
}



