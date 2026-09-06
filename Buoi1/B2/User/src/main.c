#include "GPIO.h"
#include "RCC.h"
#include <stdint.h>

void mdelay(volatile uint32_t s){
    for (volatile uint32_t i = 0; i < s; i++){
        for (volatile uint32_t j = 0; j < 800; j++){
        }
    }
}

uint16_t led_pin[] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7};
int main(void)
{
    RCC_Enable_PortA();
    GPIO_Config( GPIOA,GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP
    );
    while (1)
    {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                GPIO_Write_Pin(GPIOA, led_pin[j], 0);
            }
            GPIO_Write_Pin(GPIOA, led_pin[i], 1);
            mdelay(1000);
        }
        for (int i = 7; i >= 0; i--){
            for (int j = 0; j < 8; j++){
                GPIO_Write_Pin(GPIOA, led_pin[j], 0);
            }
            GPIO_Write_Pin(GPIOA, led_pin[i], 1);
            mdelay(1000);
        }
    }
}