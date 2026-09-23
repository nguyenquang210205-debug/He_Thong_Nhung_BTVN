#include "I2C.h"

void I2C_Init(void)
{
    RCC_APB2ENR |= (1U << 3);
    
    GPIOB_CRL &= ~((0xFU << 24) | (0xFU << 28));
    GPIOB_CRL |=  ((0xFU << 24) | (0xFU << 28));

    RCC_APB1ENR |= (1U << 21);

    I2C1_CR1 &= ~(1U << 0);

    I2C1_CR2 &= ~0x3FU;
    I2C1_CR2 |= 36U;

    I2C1_CCR = 180U;
    I2C1_TRISE = 37U;

    I2C1_CR1 |= (1U << 0);
}

void I2C_Start(void)
{
    I2C1_CR1 |= (1U << 8);
    while (!(I2C1_SR1 & (1U << 0)));
}

void I2C_Stop(void)
{
    I2C1_CR1 |= (1U << 9);
}

void I2C_SendAddr(uint8_t addr, uint8_t is_read)
{
    uint32_t temp;
    if (is_read)
    {
        I2C1_DR = addr | 0x01U;
    }
    else
    {
        I2C1_DR = addr & ~0x01U;
    }
    while (!(I2C1_SR1 & (1U << 1)));
    temp = I2C1_SR1;
    temp = I2C1_SR2;
    (void)temp;
}

void I2C_WriteData(uint8_t data)
{
    while (!(I2C1_SR1 & (1U << 7)));
    I2C1_DR = data;
    while (!(I2C1_SR1 & (1U << 2)));
}

uint8_t I2C_ReadData_Ack(void)
{
    uint8_t data;
    I2C1_CR1 |= (1U << 10);
    while (!(I2C1_SR1 & (1U << 6)));
    data = (uint8_t)I2C1_DR;
    return data;
}

uint8_t I2C_ReadData_Nack(void)
{
    uint8_t data;
    I2C1_CR1 &= ~(1U << 10);
    while (!(I2C1_SR1 & (1U << 6)));
    data = (uint8_t)I2C1_DR;
    return data;
}

void I2C_Write(uint8_t dev_addr, uint8_t *pData, uint16_t size)
{
    uint16_t i;
    I2C_Start();
    I2C_SendAddr(dev_addr, 0);
    for (i = 0; i < size; i++)
    {
        I2C_WriteData(pData[i]);
    }
    I2C_Stop();
}

void I2C_Read(uint8_t dev_addr, uint8_t *pData, uint16_t size)
{
    uint16_t i;
    I2C_Start();
    I2C_SendAddr(dev_addr, 1);
    for (i = 0; i < size; i++)
    {
        if (i == size - 1)
        {
            pData[i] = I2C_ReadData_Nack();
        }
        else
        {
            pData[i] = I2C_ReadData_Ack();
        }
    }
    I2C_Stop();
}
