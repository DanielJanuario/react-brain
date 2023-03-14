#include "LIB_LEDC.h"

uint8_t ledc_ch_num = 0, direction[MAX_PINS];
ledc_channel_config_t ledc_channel[MAX_PINS];
int32_t max_duty[MAX_PINS], target_duty[MAX_PINS], step_fade[MAX_PINS], current_duty[MAX_PINS], new_duty[MAX_PINS];
int ledc_time_to_fade[MAX_PINS];

void vTask_LEDC(void * param){
    
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    ESP_LOGI(LEDC_TASK_TAG, "Task iniciada");
    
    for(uint8_t i = 0, j = 0; i < ledc_ch_num; i++){
        direction[i] = 0;
        current_duty[i] = (i%8 >= 0) ? (ledc_get_duty(LEDC_HIGH_SPEED_MODE, j)) : (ledc_get_duty(LEDC_LOW_SPEED_MODE, j));
        target_duty[i] = max_duty[i];
        step_fade[i] = (target_duty[i] - current_duty[i]) / ledc_time_to_fade[i];
        j++;
        if(j >= 8) j = 0;
    }
    
    
    for (;;) {
        /*FADE ON*/
        for(uint8_t i = 0, j = 0; i < ledc_ch_num; i++){
            // ESP_LOGI(LEDC_TASK_TAG, "MAX_DUTY: %d | TARGET_DUTY: %d | TIME_TO_FADE: %d", max_duty[i], target_duty[i], ledc_time_to_fade[i]);
            
            current_duty[i] = (i%8 >= 0) ? (ledc_get_duty(LEDC_HIGH_SPEED_MODE, j)) : (ledc_get_duty(LEDC_LOW_SPEED_MODE, j));
            new_duty[i] = current_duty[i] + step_fade[i];
            (i%8 >= 0) ? (ledc_set_duty(LEDC_HIGH_SPEED_MODE, j, new_duty[i])) : (ledc_set_duty(LEDC_LOW_SPEED_MODE, j, new_duty[i]));
            (i%8 >= 0) ? (ledc_update_duty(LEDC_HIGH_SPEED_MODE, j)) : (ledc_update_duty(LEDC_LOW_SPEED_MODE, j));

            if(((new_duty[i] >= target_duty[i]) && (direction[i] == 0)) || ((new_duty[i] < target_duty[i]) && (direction[i] == 1))){
                current_duty[i] = (i%8 >= 0) ? (ledc_get_duty(LEDC_HIGH_SPEED_MODE, j)) : (ledc_get_duty(LEDC_LOW_SPEED_MODE, j));
                target_duty[i] = (target_duty[i] != 0) ? (0) : (max_duty[i]);
                step_fade[i] = (target_duty[i] - current_duty[i]) / ledc_time_to_fade[i];
                direction[i] = 1 - direction[i];
            }
            ESP_LOGI(LEDC_TASK_TAG, "id = %d | target = %d | current_duty = %d | step_fade = %d | new_duty = %d | direction = %d", i, target_duty[i], current_duty[i], step_fade[i], new_duty[i], direction[i]);
            
            j++;
            if(j >= 8) j = 0;
        }
        vTaskDelay(1);
    }
    
    ESP_LOGE(LEDC_TASK_TAG, "Task finalizada");
    vTaskDelete(NULL);
}

void ledc_new_config(uint8_t id, uint32_t duty, int time_to_fade){
    max_duty[id] = duty;
    ledc_time_to_fade[id] = time_to_fade;
}

void ledc_init(){
    ledc_ch_num = sizeof(ledc_pin)/sizeof(ledc_pin[0]);
    // ESP_LOGW(LEDC_TASK_TAG, "NUMB OF CHANNELS: %d", ledc_ch_num);
   
    ledc_timer_config_t timer_conf = {
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 5000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = LEDC_TIMER_0
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));


    for(uint8_t i = 0, j = 0; i < ledc_ch_num; i++){
        ledc_channel[i].channel = j;
        ledc_channel[i].duty = 0;
        ledc_channel[i].gpio_num = ledc_pin[i];
        (i%8 >= 0) ? (ledc_channel[i].speed_mode = LEDC_HS_MODE) : (ledc_channel[i].speed_mode = LEDC_LS_MODE);
        ledc_channel[i].hpoint = 0;
        (i%8 >= 0) ? (ledc_channel[i].timer_sel = LEDC_HS_TIMER) : (ledc_channel[i].timer_sel = LEDC_LS_TIMER);
        ledc_channel[i].flags.output_invert = 0;
        ledc_channel_config(&ledc_channel[i]);
        j++;
        if(j >= 8) j = 0;
        // ESP_LOGW("TESTE", "CHANNEL = %d | GPIO = %d", ledc_channel[i].channel, ledc_pin[i]);
    }


    xTaskCreate(vTask_LEDC,
                "LEDC TASK",
                LEDC_TASK_STACK,
                NULL,
                0,
                LEDC_TASK_HANDLE);
    configASSERT(&LEDC_TASK_HANDLE);
}



