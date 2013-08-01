/*!
\file MCU_Main.c
\brief MZ_Mcu application level
\author Daniel Leonov
\date 01.08.2013
*/

#include <stdio.h>

#include "MCU_System.h"	 
#include "MCU_MarkZeroBsp.h"
#include "MCU_Serial.h"	 
void InitGPIO(void);   

int main(void){ 
 	char sStr[64];
	u32 nCounter = 0;
	
	/* System timer */
	SYS_InitRcc();
	/* LEDs */
	MZ_InitLedGpio();	
	/* UART/Bluetooth */
	MZ_InitBluetoothSerial();
	SERIAL_Printf("USART init complete.\n");	

	while(1){ 
		MZ_SetLedState(MZ_GreenLed, MZ_LedOn);
		MZ_SetLedState(MZ_BlueLed, MZ_LedOff);
		SYS_Delay(200);
		snprintf(sStr, 64, "Mark Zero array MCU %d\n", (int)nCounter++);
		SERIAL_Printf(sStr);	
		MZ_SetLedState(MZ_GreenLed, MZ_LedOff);
		MZ_SetLedState(MZ_BlueLed, MZ_LedOn);
		SYS_Delay(200);
	}
} 
