#include "GPIO.h"
#include "RCC.h"
#include <stdint.h>

void mdelay(volatile uint32_t s){
    for (volatile uint32_t i = 0; i < s; i++){
        for (volatile uint32_t j = 0; j < 800; j++){
        }
    }
}


int main(void){
    RCC_Enable_PortB();
    RCC_Enable_PortC();
    GPIO_Config(GPIOB, GPIO_PIN_0, GPIO_MODE_INPUT_PU);
    GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP);
    GPIO_Write_Pin(GPIOC, GPIO_PIN_13, 0);
    uint8_t led_state = 0;
    while (1){
        if (GPIO_Read_Pin(GPIOB, GPIO_PIN_0) == 0){
            mdelay(50);
            if (GPIO_Read_Pin(GPIOB, GPIO_PIN_0) == 0){
                led_state = !led_state;
                GPIO_Write_Pin(GPIOC, GPIO_PIN_13, led_state);
                while (GPIO_Read_Pin(GPIOB, GPIO_PIN_0) == 0);
                mdelay(50);
            }
        }
    }
}