#include "GPIO.h"
#include "RCC.h"
#include <stdint.h>

void mdelay(volatile uint32_t s);
void mdelay(volatile uint32_t s)
{
    for (volatile uint32_t i = 0; i < s; i++)
    {
        for (volatile uint32_t j = 0; j < 800; j++)
        {
        }
    }
}

int main(void)
{
    RCC_Enable_PortA();
    RCC_Enable_PortB();
    GPIO_Config(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 , GPIO_MODE_OUTPUT_PP);
    GPIO_Config(GPIOB , GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_MODE_INPUT_FLOATING);
    while (1)
    {
        GPIO_Write_Pin(GPIOA, GPIO_PIN_0, !GPIO_Read_Pin(GPIOB, GPIO_PIN_8));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_1, !GPIO_Read_Pin(GPIOB, GPIO_PIN_9));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_2, !GPIO_Read_Pin(GPIOB, GPIO_PIN_10));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_3, !GPIO_Read_Pin(GPIOB, GPIO_PIN_11));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_4, !GPIO_Read_Pin(GPIOB, GPIO_PIN_12));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_5, !GPIO_Read_Pin(GPIOB, GPIO_PIN_13));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_6, !GPIO_Read_Pin(GPIOB, GPIO_PIN_14));
        GPIO_Write_Pin(GPIOA, GPIO_PIN_7, !GPIO_Read_Pin(GPIOB, GPIO_PIN_15));
    }
}
