#include <stdint.h>

#include "RCC.h"
#include "GPIO.h"
#include "I2C.h"
#include "UART.h"

#define DS1307_ADDR 0xD0

uint8_t rtc[7];
char buffer[20];

uint8_t BCD_To_Dec(uint8_t x)
{
    return (x >> 4) * 10 + (x & 0x0F);
}

uint8_t Dec_To_BCD(uint8_t x)
{
    return (x / 10) * 16 + (x % 10);
}

void DS1307_Read(void)
{
    uint8_t reg = 0x00;

    I2C_Write(DS1307_ADDR, &reg, 1);
    I2C_Read(DS1307_ADDR, rtc, 7);
}

void DS1307_Set(uint8_t h, uint8_t m, uint8_t s)
{
    uint8_t data[4];

    data[0] = 0x00;
    data[1] = Dec_To_BCD(s) & 0x7F;
    data[2] = Dec_To_BCD(m);
    data[3] = Dec_To_BCD(h) & 0x3F;

    I2C_Write(DS1307_ADDR, data, 4);
}

void Send_Time(void)
{
    uint8_t h;
    uint8_t m;
    uint8_t s;

    DS1307_Read();

    s = BCD_To_Dec(rtc[0] & 0x7F);
    m = BCD_To_Dec(rtc[1]);
    h = BCD_To_Dec(rtc[2] & 0x3F);

    UART_SendString("TIME ");

    UART_SendChar('0' + h / 10);
    UART_SendChar('0' + h % 10);
    UART_SendChar(':');

    UART_SendChar('0' + m / 10);
    UART_SendChar('0' + m % 10);
    UART_SendChar(':');

    UART_SendChar('0' + s / 10);
    UART_SendChar('0' + s % 10);

    UART_SendString("\n\r");
}

uint8_t Get_Number(char *p)
{
    return (p[0] - '0') * 10 + (p[1] - '0');
}

void Process_Command(void)
{
    uint8_t h;
    uint8_t m;
    uint8_t s;

    if (buffer[0] == 'S' &&
        buffer[1] == 'E' &&
        buffer[2] == 'T')
    {
        h = Get_Number(&buffer[4]);
        m = Get_Number(&buffer[7]);
        s = Get_Number(&buffer[10]);

        if (h < 24 && m < 60 && s < 60)
        {
            DS1307_Set(h, m, s);
            UART_SendString("SET OK\n\r");
        }
        else
        {
            UART_SendString("ERROR\n\r");
        }
    }

    if (buffer[0] == 'R' &&
        buffer[1] == 'E' &&
        buffer[2] == 'A' &&
        buffer[3] == 'D')
    {
        Send_Time();
    }
}

int main(void)
{
    uint8_t index = 0;
    char c;

    RCC_Config_72Mhz();

    RCC_Enable_PortB();
    RCC_Enable_I2C1();

    GPIO_Config(GPIOB, GPIO_PIN_6, GPIO_MODE_AF_OD);
    GPIO_Config(GPIOB, GPIO_PIN_7, GPIO_MODE_AF_OD);

    I2C_Init();
    UART1_Init(115200);

    UART_SendString("DS1307 READY\n\r");

    while (1)
    {
        if (UART_Available())
        {
            c = UART_ReadChar();

            if (c == '\r' || c == '\n')
            {
                buffer[index] = '\0';

                if (index > 0)
                {
                    Process_Command();
                }

                index = 0;
            }
            else if (index < 19)
            {
                buffer[index++] = c;
            }
        }
    }
}
