#ifndef __STM32F10x_PERIPH_H
#define __STM32F10x_PERIPH_H
#include "FIFO.h"
#include "stm32f10x.h"
#include "Convert.h"
//Параметры USART по умолчанию
//9600, 8, N, 1
#define DEFAULT_USART_BAUDRATE   9600
#define DEFAULT_USART_WORDLENGTH USART_WordLength_8b
#define DEFAULT_USART_PARITY     USART_Parity_No
#define DEFAULT_USART_STOPBITS   USART_StopBits_1
//
typedef enum{
	USART_TX_IRQ=0x01,
	USART_RX_IRQ=0x02
}PERIPH_IRQEnum;


//Параметры I2C	по умолчанию
#define DEFAULT_I2C_SPEED      100000
#define DEFAULT_I2C_ADDRESS    B8(0000001)<<1
#define DEFAULT_I2C_DUTY_CYCLE I2C_DutyCycle_16_9


void PERIPH_PushToUSART1(char cChr, CB_Structure* cbStructure);
_BOOL PERIPH_StrToUSART1(CB_Structure* cbStructure);
void PERIPH_Printf(const char *sStr);
void PERIRH_DefaultUSART1Config(void);

void PREIPH_ConfigUSART1Interrupts(void);
void PERIPH_EnableUSARTIRQ(PERIPH_IRQEnum eIRQFlags);
void PERIPH_DisableUSARTIRQ(PERIPH_IRQEnum eIRQFlags);
void PERIPH_InitUSART1(uint32_t nBaudRate, uint16_t mWordLength, uint16_t mParity, uint16_t mStopBits);

void PERIPH_InitI2C1(uint32_t nClockSpeed, uint16_t nOwnAddress1, uint16_t mDutyCycle);
void PERIPH_DefaultI2CConfig(void);
#endif
