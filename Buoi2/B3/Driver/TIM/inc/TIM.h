#ifndef __TIM_H
#define __TIM_H

#include <stdint.h>

void TIM2_init_IT(void);
void TIM2_IRQHandler(void);
void delay_ms(uint32_t ms);

#endif