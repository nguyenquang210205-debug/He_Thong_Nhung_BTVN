#include "TIM.h"

#define TIM2_BASE       0x40000000

#define TIM2_CR1        *((volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_SR         *((volatile uint32_t *)(TIM2_BASE + 0x10))
#define TIM2_EGR        *((volatile uint32_t *)(TIM2_BASE + 0x14))
#define TIM2_CNT        *((volatile uint32_t *)(TIM2_BASE + 0x24))
#define TIM2_PSC        *((volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR        *((volatile uint32_t *)(TIM2_BASE + 0x2C))
#define TIM2_DIER       *((volatile uint32_t *)(TIM2_BASE + 0x0C))

#define RCC_APB1ENR     *((volatile uint32_t *)0x4002101C)

#define NVIC_ISER0      *((volatile uint32_t *)0xE000E100)

void TIM2_init_IT(void)
{
    RCC_APB1ENR |= (1 << 0);

    TIM2_PSC = 71999;
    TIM2_ARR = 999;

    TIM2_EGR |= (1 << 0);

    TIM2_DIER |= (1 << 0);

    TIM2_CR1 |= (1 << 0);

    NVIC_ISER0 |= (1 << 28);
}

void TIM2_IRQHandler(void)
{
    if (TIM2_SR & 0x01)
    {
        TIM2_SR &= ~(uint32_t)(1 << 0);
    }
}

void delay_ms(uint32_t ms)
{
    RCC_APB1ENR |= (1 << 0);

    TIM2_CR1 &= ~(uint32_t)(1 << 0);

    TIM2_PSC = 71999;
    TIM2_ARR = ms - 1;
    TIM2_CNT = 0;

    TIM2_EGR |= (1 << 0);

    TIM2_SR &= ~(uint32_t)(1 << 0);

    TIM2_CR1 |= (1 << 0);

    while (!(TIM2_SR & (1 << 0)))
    {
    }

    TIM2_CR1 &= ~(uint32_t)(1 << 0);

    TIM2_SR &= ~(uint32_t)(1 << 0);

    TIM2_CNT = 0;
}