#include <stdint.h>

/* Các symbol được định nghĩa trong linker script */
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Hàm main */
extern int main(void);

/* =========================================================
 * Default Handler
 * ========================================================= */

void Default_Handler(void)
{
    while (1)
    {
    }
}

/* =========================================================
 * Reset Handler
 * ========================================================= */

void Reset_Handler(void)
{
    uint32_t *src;
    uint32_t *dst;

    /* -----------------------------------------
     * Copy .data từ Flash -> RAM
     * ----------------------------------------- */

    src = &_sidata;
    dst = &_sdata;

    while (dst < &_edata)
    {
        *dst++ = *src++;
    }

    /* -----------------------------------------
     * Clear .bss
     * ----------------------------------------- */

    dst = &_sbss;

    while (dst < &_ebss)
    {
        *dst++ = 0;
    }

    /* -----------------------------------------
     * Gọi main()
     * ----------------------------------------- */

    main();

    /* main không nên return */
    while (1)
    {
    }
}

/* =========================================================
 * Vector Table
 * ========================================================= */

__attribute__((section(".isr_vector")))
const void *g_pfnVectors[] =
{
    /* Initial Stack Pointer */
    &_estack,

    /* Reset */
    Reset_Handler,

    /* Cortex-M3 Exceptions */

    Default_Handler,    /* NMI */
    Default_Handler,    /* HardFault */
    Default_Handler,    /* MemManage */
    Default_Handler,    /* BusFault */
    Default_Handler,    /* UsageFault */

    0,
    0,

    Default_Handler,    /* SVCall */
    Default_Handler,    /* DebugMonitor */

    0,

    Default_Handler,    /* PendSV */
    Default_Handler,    /* SysTick */

    /* STM32F103 interrupt vectors */

    Default_Handler,    /* WWDG */
    Default_Handler,    /* PVD */
    Default_Handler,    /* TAMPER */
    Default_Handler,    /* RTC */
    Default_Handler,    /* FLASH */
    Default_Handler,    /* RCC */
    Default_Handler,    /* EXTI0 */
    Default_Handler,    /* EXTI1 */
    Default_Handler,    /* EXTI2 */
    Default_Handler,    /* EXTI3 */
    Default_Handler,    /* EXTI4 */
    Default_Handler,    /* DMA1_Channel1 */
    Default_Handler,    /* DMA1_Channel2 */
    Default_Handler,    /* DMA1_Channel3 */
    Default_Handler,    /* DMA1_Channel4 */
    Default_Handler,    /* DMA1_Channel5 */
    Default_Handler,    /* DMA1_Channel6 */
    Default_Handler,    /* DMA1_Channel7 */
    Default_Handler,    /* ADC1_2 */
    Default_Handler,    /* USB_HP_CAN1_TX */
    Default_Handler,    /* USB_LP_CAN1_RX0 */
    Default_Handler,    /* CAN1_RX1 */
    Default_Handler,    /* CAN1_SCE */
    Default_Handler,    /* EXTI9_5 */
    Default_Handler,    /* TIM1_BRK */
    Default_Handler,    /* TIM1_UP */
    Default_Handler,    /* TIM1_TRG_COM */
    Default_Handler,    /* TIM1_CC */
    Default_Handler,    /* TIM2 */
    Default_Handler,    /* TIM3 */
    Default_Handler,    /* TIM4 */
    Default_Handler,    /* I2C1_EV */
    Default_Handler,    /* I2C1_ER */
    Default_Handler,    /* I2C2_EV */
    Default_Handler,    /* I2C2_ER */
    Default_Handler,    /* SPI1 */
    Default_Handler,    /* SPI2 */
    Default_Handler,    /* USART1 */
    Default_Handler,    /* USART2 */
    Default_Handler,    /* USART3 */
    Default_Handler,    /* EXTI15_10 */
    Default_Handler,    /* RTCAlarm */
    Default_Handler,    /* USBWakeUp */
    Default_Handler     /* TIM8_BRK */
};