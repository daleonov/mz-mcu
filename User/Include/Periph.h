#ifndef __STM32F10x_PERIPH_H
#define __STM32F10x_PERIPH_H
#include "FIFO.h"
#include "stm32f10x.h"
//Параметры USART по умолчанию
//115200, 8, E, 1
#define DEFAULT_USART_BAUDRATE   115200
#define DEFAULT_USART_WORDLENGTH USART_WordLength_8b
#define DEFAULT_USART_PARITY     USART_Parity_Even
#define DEFAULT_USART_STOPBITS   USART_StopBits_1

typedef enum{
	USART_TX_IRQ=0x01,
	USART_RX_IRQ=0x02
}PERIPH_IRQEnum;

void PERIRH_DefaultUSART1Config(void);

void PREIPH_ConfigUSART1Interrupts(void);
void PERIPH_EnableUSARTIRQ(PERIPH_IRQEnum eIRQFlags);
void PERIPH_DisableUSARTIRQ(PERIPH_IRQEnum eIRQFlags);
void PERIPH_InitUSART1(uint32_t nBaudRate, uint16_t mWordLength, uint16_t mParity, uint16_t mStopBits);

void DEV_SystemRCCInit(void);
#endif
