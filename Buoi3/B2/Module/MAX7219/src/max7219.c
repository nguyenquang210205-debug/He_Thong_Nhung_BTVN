#include "MAX7219.h"
#include "SPI.h"

#define MAX7219_CS_LOW()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define MAX7219_CS_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_4)

void MAX7219_Write(
    uint8_t address,
    uint8_t data
)
{
    MAX7219_CS_LOW();

    SPI1_SendReceiveByte(address);
    SPI1_SendReceiveByte(data);

    MAX7219_CS_HIGH();
}

void MAX7219_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    MAX7219_CS_HIGH();

    MAX7219_Write(
        MAX7219_REG_DECODEMODE,
        0x00
    );

    MAX7219_Write(
        MAX7219_REG_INTENSITY,
        0x03
    );

    MAX7219_Write(
        MAX7219_REG_SCANLIMIT,
        0x07
    );

    MAX7219_Write(
        MAX7219_REG_SHUTDOWN,
        0x01
    );

    MAX7219_Write(
        MAX7219_REG_DISPLAYTEST,
        0x00
    );

    MAX7219_Clear();
}

void MAX7219_Clear(void)
{
    uint8_t i;

    for (i = 1; i <= 8; i++)
    {
        MAX7219_Write(i, 0x00);
    }
}
