/*!
\file MCU_Peripherials.h
\brief MCU_Peripherials module header
\author Daniel Leonov
\date 01.08.2013 / Dec 2011 (T8_Schur legacy code)
*/

#ifndef __MCU_SERIAL_H
#define __MCU_SERIAL_H

#include "MCU_Common.h"
#include "MCU_SerialFifo.h"

//Ïàðàìåòðû USART ïî óìîë÷àíèþ
//9600, 8, N, 1
#define DEFAULT_USART_BAUDRATE   9600
#define DEFAULT_USART_WORDLENGTH USART_WordLength_8b
#define DEFAULT_USART_PARITY     USART_Parity_No
#define DEFAULT_USART_STOPBITS   USART_StopBits_1
//
typedef enum{
	USART_TX_IRQ=0x01,
	USART_RX_IRQ=0x02
}SERIAL_IRQEnum;


void SERIAL_PushToUSART1(char cChr, CB_Structure* cbStructure);
_BOOL SERIAL_StrToUSART1(CB_Structure* cbStructure);
void SERIAL_Printf(const char *sStr);
void SERIAL_DefaultUSART1Config(void);

void SERIAL_ConfigUSART1Interrupts(void);
void SERIAL_EnableUSARTIRQ(SERIAL_IRQEnum eIRQFlags);
void SERIAL_DisableUSARTIRQ(SERIAL_IRQEnum eIRQFlags);
void SERIAL_InitUSART1(u32 nBaudRate, u16 mWordLength, u16 mParity, u16 mStopBits);

#endif // __MCU_SERIAL_H
