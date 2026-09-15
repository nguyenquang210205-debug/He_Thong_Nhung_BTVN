#include "GPIO.h"
#include "RCC.h"
#include <stdint.h>

void mdelay(volatile uint32_t s);
void mdelay(volatile uint32_t s)
{
    for(int i = 0 ; i < s ; i++){
      for(int j = 0 ; j < 800 ; j++);
    }
}

int main(void)
{
    RCC_Enable_PortC();
    GPIO_Config(GPIOA, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP);

    while (1)
    {
        GPIO_Write_Pin(GPIOA, GPIO_PIN_2, 1);
        mdelay(2000);

        GPIO_Write_Pin(GPIOA, GPIO_PIN_2, 0);
        mdelay(2000);
    }
}
