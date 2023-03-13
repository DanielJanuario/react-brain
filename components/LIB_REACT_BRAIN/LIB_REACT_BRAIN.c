#include "LIB_REACT_BRAIN.h"

int *ledc_pin = {RIGHT_VISUAL_CORTEX_1_PIN,
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
                    LEFT_STANDART_4_PIN
                    };

void vTask_React_Brain(void * param){
    ESP_LOGI(REACT_BRAIN_TASK_TAG, "Task iniciada");
    for(;;){
        // VERIFICA SENSORES

        // REAGE DE ACORDO
    }

    ESP_LOGE(REACT_BRAIN_TASK_TAG, "Task finalizada");
    vTaskDelete(NULL);
}

void react_brain_init(){
    xTaskCreate(vTask_React_Brain,
                "LEDC TASK",
                REACT_BRAIN_TASK_STACK,
                NULL,
                1,
                REACT_BRAIN_TASK_HANDLE);
    configASSERT(&REACT_BRAIN_TASK_HANDLE);
}
