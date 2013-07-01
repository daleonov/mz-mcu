#include "Periph.h"
#include "Time.h"

void PERIRH_DefaultUSART1Config(){ 
	/*!
	\brief Настройка USART1 параметрами по умолчанию (см. Periph.h).
	*/
	//115200, 8, N, 1
	PERIPH_InitUSART1(
		DEFAULT_USART_BAUDRATE,
		DEFAULT_USART_WORDLENGTH,
		DEFAULT_USART_PARITY,
		DEFAULT_USART_STOPBITS);
	PREIPH_ConfigUSART1Interrupts(); 
}

//Настройка UART1 для приёма-передачи.
//Tx=PA9, Rx=PA10, без Hardware Flow Control.
void PERIPH_InitUSART1(uint32_t nBaudRate, uint16_t mWordLength, uint16_t mParity, uint16_t mStopBits){
	/*!
	\brief Инициализация USART
	\param nBaudRate Скорость передачи (бод/с).
	\param mWordLength Длина посылки (бит).
	\param mParity Контроль чётности.
	\param mStopBits Длина стопового бита.
	*/

	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;					   
	//Для UART1 по умолчанию Tx=PA9, Rx=PA10;
	//альтернативные выводы: Tx=PB6, Rx=PB7.
	//Здесь используестя порт A. 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
	//PA9 - Tx
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//PA10 - Rx
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//Настройка UART1
	USART_InitStructure.USART_BaudRate = nBaudRate;
	USART_InitStructure.USART_WordLength=mWordLength;
	USART_InitStructure.USART_StopBits=mStopBits;
	USART_InitStructure.USART_Parity=mParity;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void PREIPH_ConfigUSART1Interrupts(){ 
	/*!
	\brief Настройка вектора прерываний	USART. 
	*/

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void PERIPH_DisableUSARTIRQ(PERIPH_IRQEnum eIRQFlags){
	/*!
	\brief Отключение прерываний USART.
	\param eIRQFlags Флаги прерывания (Rx/Tx)
	*/ 
	if (eIRQFlags&USART_RX_IRQ){					 		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	}	
	if (eIRQFlags&USART_TX_IRQ){		
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);
	}
}

void PERIPH_EnableUSARTIRQ(PERIPH_IRQEnum eIRQFlags){		
	/*!
	\brief Разрешение прерываний USART.
	\param eIRQFlags Флаги прерывания (Rx/Tx)
	*/ 
	if (eIRQFlags&USART_RX_IRQ){						
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}	  
	if (eIRQFlags&USART_TX_IRQ){				 		
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	}
}

void DEV_SystemRCCInit(){
	/*!
	\brief Настройка системного таймера.
	*/
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

