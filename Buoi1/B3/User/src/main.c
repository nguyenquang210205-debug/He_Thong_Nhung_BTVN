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
    RCC_Enable_PortC();
    RCC_Enable_PortB();
    GPIO_Config(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP);
    GPIO_Config(GPIOB ,GPIO_PIN_0, GPIO_MODE_INPUT_PU);
    while (1)
    {
        GPIO_Write_Pin(GPIOC, GPIO_PIN_13, GPIO_Read_Pin(GPIOB, GPIO_PIN_0));
    }
}
