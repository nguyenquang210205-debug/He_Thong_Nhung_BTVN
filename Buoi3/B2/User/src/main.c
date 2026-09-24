#include "RCC.h"
#include "SPI.h"
#include "MAX7219.h"

static const uint8_t smiley_face[8] = {
    0x3C,
    0x42,
    0xA5,
    0x81,
    0xA5,
    0x99,
    0x42,
    0x3C
};

int main(void)
{
    uint8_t i;

    RCC_Config_72Mhz();
    SPI1_Init();
    MAX7219_Init();

    for (i = 0; i < 8; i++)
    {
        MAX7219_Write(
            i + 1,
            smiley_face[i]
        );
    }

    while (1)
    {
    }
}
