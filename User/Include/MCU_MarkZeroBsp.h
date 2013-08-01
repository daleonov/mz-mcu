/*!
\file MCU_MarkZeroBsp.h
\brief Board suport package header
\author Daniel Leonov
\date 01.08.2013
*/

#ifndef __MCU_MARKZEROBSP_H
#define __MCU_MARKZEROBSP_H

#include "stm32f10x.h"
#include "MCU_Common.h"

/* MCU architecture-related macros */
#define MZ_GREEN_LED_BUS_CLOCK_CMD_FUNC RCC_APB2PeriphClockCmd
#define MZ_GREEN_LED_BUS_GPIO RCC_APB2Periph_GPIOC
#define MZ_BLUE_LED_BUS_CLOCK_CMD_FUNC RCC_APB2PeriphClockCmd
#define MZ_BLUE_LED_BUS_GPIO RCC_APB2Periph_GPIOC

/* GPIO-related macros */
#define MZ_GREEN_LED_GPIO GPIOC
#define MZ_GREEN_LED_PIN GPIO_Pin_9
#define MZ_BLUE_LED_GPIO GPIOC
#define MZ_BLUE_LED_PIN GPIO_Pin_8

/*! LED ID (name) */
typedef enum __MZ_TLedId{
	MZ_GreenLed = 1, /*!< Green LED */
	MZ_BlueLed = 2 /*!< BlueLed */
}MZ_TLedId;

/*! LED state */
typedef enum __MZ_TLedState{
	MZ_LedOff = 0, /*!< Off */
	MZ_LedOn = 1 /*!< On */
}MZ_TLedState;

void MZ_InitLedGpio(void);
void MZ_SetLedState(MZ_TLedId mLedId, MZ_TLedState mLedState);
void MZ_InitBluetoothSerial(void);

#endif // __MCU_MARKZEROBSP_H
