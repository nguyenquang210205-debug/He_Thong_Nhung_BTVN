#include <stdint.h>

#include "RCC.h"
#include "UART.h"

#define MA_LOP  "He Thong Nhung"
#define MA_NHOM  " Nhom 03"

#define RX_BUFFER_SIZE 128

int main(void)
{
    char rx_buffer[RX_BUFFER_SIZE];
    char c;
    uint32_t index;

    RCC_Config_72Mhz();

    UART1_Init(9600);

    UART1_SendString("\r\nSTM32 UART READY\r\n");

    while (1)
    {
        index = 0;

        while (1)
        {
            c = UART1_ReadChar();

            if (c == '!')
            {
                break;
            }

            if (index < RX_BUFFER_SIZE - 1)
            {
                rx_buffer[index++] = c;
            }
        }

        rx_buffer[index] = '\0';

        UART1_SendString(MA_LOP);
        UART1_SendString(MA_NHOM);
        UART1_SendString(": ");
        UART1_SendString(rx_buffer);
        UART1_SendString("\n\r");
    }
}
