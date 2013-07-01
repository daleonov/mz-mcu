#include "Periph.h"
#include "Binary.h"
#include "Time.h"
 /************/
 //Low-level functions for perirherial interfaces
 /************/

//Настройка UART1 для приёма-передачи.
//Tx=PA9, Rx=PA10, без Hardware Flow Control.
void PERIPH_InitUSART1(uint32_t nBaudRate, uint16_t mWordLength, uint16_t mParity, uint16_t mStopBits){
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
	NVIC_InitTypeDef NVIC_InitStructure;
	//Включаем прерывания по приёму	 	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	  
//	USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	//Настройка вектора прерываний
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
	if (eIRQFlags&USART_RX_IRQ){						
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}	  
	if (eIRQFlags&USART_TX_IRQ){				 		
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	}
}
