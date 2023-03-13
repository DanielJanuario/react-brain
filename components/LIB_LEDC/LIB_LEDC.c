#include "LIB_LEDC.h"

uint8_t ledc_ch_num = 0;
ledc_channel_config_t ledc_channel[16];
uint32_t ledc_fade_duty[16];
int ledc_time_to_fade[16];
SemaphoreHandle_t counting_sem;


static bool cb_ledc_fade_end_event(const ledc_cb_param_t *param, void *user_arg)
{
    portBASE_TYPE taskAwoken = pdFALSE;

    if (param->event == LEDC_FADE_END_EVT) {
        SemaphoreHandle_t counting_sem = (SemaphoreHandle_t) user_arg;
        xSemaphoreGiveFromISR(counting_sem, &taskAwoken);
    }

    return (taskAwoken == pdTRUE);
}

void vTask_LEDC(void * param){
    ESP_LOGI(LEDC_TASK_TAG, "Task iniciada");

    for (;;) {
        /*FADE ON*/
        for (uint8_t i = 0; i < ledc_ch_num; i++) {
            ledc_set_fade_with_time(ledc_channel[i].speed_mode,
                    ledc_channel[i].channel, ledc_fade_duty[i], ledc_time_to_fade[i]);
                    
            ledc_fade_start(ledc_channel[i].speed_mode,
                    ledc_channel[i].channel, LEDC_FADE_NO_WAIT);
        }

        for (int i = 0; i < ledc_ch_num; i++) {
            xSemaphoreTake(counting_sem, portMAX_DELAY);
        }

        /*FADE OFF*/
        for (uint8_t i = 0; i < ledc_ch_num; i++) {
            ledc_set_fade_with_time(ledc_channel[i].speed_mode,
                    ledc_channel[i].channel, 0, ledc_time_to_fade[i]);

            ledc_fade_start(ledc_channel[i].speed_mode,
                    ledc_channel[i].channel, LEDC_FADE_NO_WAIT);
        }

        for (int i = 0; i < ledc_ch_num; i++) {
            xSemaphoreTake(counting_sem, portMAX_DELAY);
        }
    }
    
    ESP_LOGE(LEDC_TASK_TAG, "Task finalizada");
    vTaskDelete(NULL);
}

void ledc_new_config(uint8_t id, uint32_t duty, int time_to_fade){
    ledc_fade_duty[id] = duty;
    ledc_time_to_fade[id] = time_to_fade;
}

void ledc_init(uint8_t *pin){
    ledc_ch_num = sizeof(pin);
    counting_sem = xSemaphoreCreateCounting(16, 0);

    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,                      // frequency of PWM signal
        .speed_mode = LEDC_HS_MODE,           // timer mode
        .timer_num = LEDC_HS_TIMER,            // timer index
        .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
    };  

    for(uint8_t i = 0; i < sizeof(pin); i++){
        ledc_time_to_fade[i] = 3000;
        ledc_fade_duty[i] = 4000;
        ledc_channel[i].channel = i;
        ledc_channel[i].duty = 0;
        ledc_channel[i].gpio_num = pin[0];
        ledc_channel[i].speed_mode = LEDC_HS_MODE;
        ledc_channel[i].hpoint = 0;
        ledc_channel[i].timer_sel = LEDC_HS_TIMER;
        ledc_channel[i].flags.output_invert = 0;
        ledc_channel_config(&ledc_channel[i]);
    }

    // Initialize fade service.
    ledc_fade_func_install(0);
    ledc_cbs_t callbacks = {
        .fade_cb = cb_ledc_fade_end_event
    };

    for (uint8_t i = 0; i < sizeof(pin); i++) {
        ledc_cb_register(ledc_channel[i].speed_mode, ledc_channel[i].channel, &callbacks, (void *) counting_sem);
    }

    xTaskCreate(vTask_LEDC,
                "LEDC TASK",
                LEDC_TASK_STACK,
                NULL,
                1,
                LEDC_TASK_HANDLE);
    configASSERT(&LEDC_TASK_HANDLE);
}



/*
for (int i = 0; i < ledc_ch_num; i++) {
            xSemaphoreTake(counting_sem, portMAX_DELAY);
        }

        printf("3. LEDC set duty = %d without fade\n", ledc_fade_duty[i]);
        for (i = 0; i < ledc_ch_num; i++) {
            ledc_set_duty(ledc_channel[i].speed_mode, ledc_channel[i].channel, ledc_fade_duty[i]);
            ledc_update_duty(ledc_channel[i].speed_mode, ledc_channel[i].channel);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        printf("4. LEDC set duty = 0 without fade\n");
        for (i = 0; i < ledc_ch_num; i++) {
            ledc_set_duty(ledc_channel[i].speed_mode, ledc_channel[i].channel, 0);
            ledc_update_duty(ledc_channel[i].speed_mode, ledc_channel[i].channel);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
*/
