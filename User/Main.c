#include "stm32f10x.h"	 
#include "Time.h"  

void InitGPIO(void);   
void DEV_SystemRCCInit(void);

int main(void){  	

	/* Инициальзация системного таймера */
	DEV_SystemRCCInit();
	InitGPIO();	

	while(1){ 
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		TIME_Delay_ms(500);
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		TIME_Delay_ms(500);
	}
}


void InitGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 	   

   return;		   
} 


void DEV_SystemRCCInit(){
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
