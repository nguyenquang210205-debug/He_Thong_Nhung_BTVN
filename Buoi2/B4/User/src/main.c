#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"

int main(void)
{
    RCC_Config_72Mhz();
    RCC_Enable_PortA();
    RCC_Enable_TIM2();
    TIM2_PWM_Init();
    GPIO_Config(GPIOA, GPIO_PIN_0, GPIO_MODE_AF_PP);
    GPIO_Config(GPIOA, GPIO_PIN_1, GPIO_MODE_AF_PP);
    GPIO_Config(GPIOA, GPIO_PIN_2, GPIO_MODE_AF_PP);
    GPIO_Config(GPIOA, GPIO_PIN_3, GPIO_MODE_AF_PP);
    TIM2_PWM_SetDuty(TIM2_CH1, 10);
    TIM2_PWM_SetDuty(TIM2_CH2, 50);
    TIM2_PWM_SetDuty(TIM2_CH3, 70);
    TIM2_PWM_SetDuty(TIM2_CH4, 100);
    while (1)
    {
    }
}