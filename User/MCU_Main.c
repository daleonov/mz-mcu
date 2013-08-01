#include "MCU_System.h"	 
#include "MCU_MarkZeroBsp.h"
#include "MCU_Serial.h"	 
void InitGPIO(void);   




int main(void){ 
 	
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
		SYS_Delay(100);
		SERIAL_Printf("xxx\n");	
		MZ_SetLedState(MZ_GreenLed, MZ_LedOff);
		MZ_SetLedState(MZ_BlueLed, MZ_LedOn);
		SYS_Delay(100);
	}
} 
