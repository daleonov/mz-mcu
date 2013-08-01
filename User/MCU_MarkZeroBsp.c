/*!
\file MCU_MarkZeroBsp.c
\brief MCU LEDs interface module
\author Daniel Leonov
\date 01.08.2013
*/

#include "MCU_MarkZeroBsp.h"
#include "MCU_Serial.h"

void MZ_InitLedGpio(void){
	/*!
	\brief Inits LEDs' GPIO.
	*/
	GPIO_InitTypeDef GPIO_InitStructure;
  
	MZ_GREEN_LED_BUS_CLOCK_CMD_FUNC(MZ_GREEN_LED_BUS_GPIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MZ_GREEN_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MZ_GREEN_LED_GPIO, &GPIO_InitStructure); 	

	MZ_BLUE_LED_BUS_CLOCK_CMD_FUNC(MZ_GREEN_LED_BUS_GPIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MZ_BLUE_LED_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MZ_BLUE_LED_GPIO, &GPIO_InitStructure);    

   return;		   
}

void MZ_SetLedState(MZ_TLedId mLedId, MZ_TLedState mLedState){
	/*!
	\brief Sets LED state.
	\param mLedId LED ID (see \ref __MZ_TLedId).
	\param mLedState LED state (see \ref __MZ_TLedState).
	*/
	GPIO_TypeDef* mLedGpio;
	uint16_t nLedPin;
	BitAction mLedBitState;

	switch(mLedId){
		case MZ_GreenLed:
			mLedGpio = MZ_GREEN_LED_GPIO;
			nLedPin = MZ_GREEN_LED_PIN;
			break;
		case MZ_BlueLed:
			mLedGpio = MZ_BLUE_LED_GPIO;
			nLedPin = MZ_BLUE_LED_PIN;
			break;
	}
	mLedBitState = (mLedState == MZ_LedOn) ? Bit_SET : Bit_RESET;
	GPIO_WriteBit(mLedGpio, nLedPin, mLedBitState);
}


void MZ_InitBluetoothSerial(void){
	
	SERIAL_DefaultUSART1Config();   
}
