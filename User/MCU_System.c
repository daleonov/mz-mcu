/*!
\file MCU_System.c
\brief MCU hardware system-related routines
\author Daniel Leonov
\date 01.08.2013
*/

#include "MCU_System.h"

void SYS_InitRcc(){
	ErrorStatus hseStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON); //HSE is 8MHz
 
	//Waiting for HSE to start...
	hseStartUpStatus = RCC_WaitForHSEStartUp();
	
	if (hseStartUpStatus == SUCCESS){ 
		//Enabling flash buffer
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);	

		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	
		// APB2
		RCC_PCLK2Config(RCC_HCLK_Div4);	 	
		// APB1
		RCC_PCLK1Config(RCC_HCLK_Div4);			
		 	
		// PLLCLK = 8MHz * 8 = 64 MHz
		RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_4);	 	
		//Enabling the phase-locked loop
		RCC_PLLCmd(ENABLE);
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//Setting PLL output as system clock
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 	
		
	//	No macros for this one...
	//	0x00: HSI used as system clock 
	//	0x04: HSE used as system clock 
	//	0x08: PLL used as system clock
		while (RCC_GetSYSCLKSource() != 0x08);
	} 		
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

void SYS_Delay(__IO uint32_t nTime){
	/*!
	\brief Delay.
	\param nTime Delay time (in ms).
	*/	
	 
	uint32_t nTicks=(TIME_CPU_CLK/4000)*nTime;
	for(; nTicks != 0; nTicks--);
} 
