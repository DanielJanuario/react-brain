#include "LIB_REACT_BRAIN.h"

esp_adc_cal_characteristics_t adc1_chars;


int ledc_pin[] = {
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

uint8_t adc_pin[] = {
                        ADC1_CHANNEL_4,
                        ADC1_CHANNEL_5,
                        ADC1_CHANNEL_6,
                        ADC1_CHANNEL_7,
                    };
                    

uint16_t get_light_sensor_percentage(uint8_t id){
    uint16_t raw = esp_adc_cal_raw_to_voltage(adc1_get_raw(adc_pin[id]), &adc1_chars);
    float value = (raw*100)/4096;
    // ESP_LOGI(REACT_BRAIN_TASK_TAG, "SENSOR: %d | VALUE: %f", id, value);
    return (uint16_t) value;
}

uint16_t get_sound_sensor_percentage(uint8_t id){
    uint16_t raw = esp_adc_cal_raw_to_voltage(adc1_get_raw(adc_pin[id]), &adc1_chars);
    float value = (raw*100)/4096;
    // ESP_LOGI(REACT_BRAIN_TASK_TAG, "SENSOR: %d | VALUE: %f", id, value);
    return (uint16_t) value;
}

void vTask_React_Brain(void * param){
    ESP_LOGI(REACT_BRAIN_TASK_TAG, "Task iniciada");
    uint16_t l1, l2, s1, s2;

    for(;;){
        // VERIFICA SENSORES
        l1 = get_light_sensor_percentage(0);
        l2 = get_light_sensor_percentage(1);
        s1 = get_sound_sensor_percentage(2);
        s2 = get_sound_sensor_percentage(3);

        ESP_LOGI(REACT_BRAIN_TASK_TAG, "L1: %d | L2: %d | S1: %d | S2: %d", l1, l2, s1, s2);

        if(l1 > LIGHT_SENSE || l2 > LIGHT_SENSE || s1 > SOUND_SENSE || s2 > SOUND_SENSE){
            if(l1 > LIGHT_SENSE){
                ESP_LOGI(REACT_BRAIN_TASK_TAG, "L1");
                ledc_new_config(0, DUTY_HIGH, 150/portTICK_PERIOD_MS);
                for(uint8_t i = 4; i < sizeof(ledc_pin); i++)
                    ledc_new_config(i, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }
            else{
                ledc_new_config(0, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }

            if(l2 > LIGHT_SENSE){
                ESP_LOGI(REACT_BRAIN_TASK_TAG, "L2");
                ledc_new_config(1, DUTY_HIGH, 150/portTICK_PERIOD_MS);
                for(uint8_t i = 4; i < sizeof(ledc_pin); i++)
                    ledc_new_config(i, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }
            else{
                ledc_new_config(1, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }

            if(s1 > SOUND_SENSE){
                ESP_LOGI(REACT_BRAIN_TASK_TAG, "S1");
                ledc_new_config(2, DUTY_HIGH, 150/portTICK_PERIOD_MS);
                for(uint8_t i = 4; i < sizeof(ledc_pin); i++)
                    ledc_new_config(i, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }
            else{
                ledc_new_config(2, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }

            if(s2 > SOUND_SENSE){
                ESP_LOGI(REACT_BRAIN_TASK_TAG, "S2");
                ledc_new_config(3, DUTY_HIGH, 150/portTICK_PERIOD_MS);
                for(uint8_t i = 4; i < sizeof(ledc_pin); i++)
                    ledc_new_config(i, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }
            else{
                ledc_new_config(3, DUTY_LOW, 150/portTICK_PERIOD_MS);
            }
        }
        else{
            for(uint8_t i = 0; i < sizeof(ledc_pin); i++)
                ledc_new_config(i, DUTY_HIGH, 150);
        }

        // REAGE DE ACORDO
        vTaskDelay(100/portTICK_PERIOD_MS);
    }

    ESP_LOGE(REACT_BRAIN_TASK_TAG, "Task finalizada");
    vTaskDelete(NULL);
}

void react_brain_init(){
    ledc_init(ledc_pin);

    for(uint8_t i = 0; i < sizeof(adc_pin); i++)
        adc1_config_channel_atten(adc_pin[i], ADC_ATTEN_DB_11);

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    xTaskCreate(vTask_React_Brain,
                "REACT BRAIN TASK",
                REACT_BRAIN_TASK_STACK,
                NULL,
                1,
                REACT_BRAIN_TASK_HANDLE);
    configASSERT(&REACT_BRAIN_TASK_HANDLE);
}
