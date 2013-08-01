/*!
\file MCU_Peripherials.c
\brief Peripherial interfaces for MCU
\author Daniel Leonov
\date 01.08.2013 / Dec 2011 (T8_Schur legacy code)
*/

#include "stm32f10x.h"
#include "MCU_Serial.h"

//USART Rx & Tx FIFOs
CB_Structure cbTxBuffer;
CB_Structure cbRxBuffer;

//USART Interrupts handler
void USART1_IRQHandler(void)
{		 
	static char cChr;						

	//Rx is not empty
	/*if((USART_GetITStatus(USART1, USART_IT_RXNE)))	{
		cChr= USART_ReceiveData(USART1);
		CB_Push(&cbRxBuffer, cChr);
		if((cChr=='\n')||(cChr=='\r')){
			//stDevStatus.bNewCmd=1;	 	
			//ExecuteCmd();
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		 
	}	 */

	//Transmission complete
	if((USART_GetITStatus(USART1, USART_IT_TC))){ 
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		if(!(cbTxBuffer.bIsEmpty)){ 
			USART_SendData(USART1,(uint16_t)CB_Pop(&cbTxBuffer));
		} 
		if(cbTxBuffer.bIsEmpty)	{ //it's not "else"!  
			CB_Wipe(&cbTxBuffer);		//!!!
			SERIAL_DisableUSARTIRQ(USART_TX_IRQ);
		}				
	}	 	 
}

void SERIAL_InitUSART1(u32 nBaudRate, u16 mWordLength, u16 mParity, u16 mStopBits){
	GPIO_InitTypeDef  GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure;					   
	//Äëÿ UART1 ïî óìîë÷àíèþ Tx=PA9, Rx=PA10;
	//àëüòåðíàòèâíûå âûâîäû: Tx=PB6, Rx=PB7.
	//Çäåñü èñïîëüçóåñòÿ ïîðò A. 
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
	//Íàñòðîéêà UART1
	USART_InitStructure.USART_BaudRate = nBaudRate;
	USART_InitStructure.USART_WordLength=mWordLength;
	USART_InitStructure.USART_StopBits=mStopBits;
	USART_InitStructure.USART_Parity=mParity;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void SERIAL_ConfigUSART1Interrupts(){ 
	NVIC_InitTypeDef NVIC_InitStructure;
	//Âêëþ÷àåì ïðåðûâàíèÿ ïî ïðè¸ìó	 	
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	  
//	USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	//Íàñòðîéêà âåêòîðà ïðåðûâàíèé
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	 
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void SERIAL_DisableUSARTIRQ(SERIAL_IRQEnum eIRQFlags){	 
	if (eIRQFlags&USART_RX_IRQ){					 		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	}	
	if (eIRQFlags&USART_TX_IRQ){		
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);
	}
}

void SERIAL_EnableUSARTIRQ(SERIAL_IRQEnum eIRQFlags){	 
	if (eIRQFlags&USART_RX_IRQ){						
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	}	  
	if (eIRQFlags&USART_TX_IRQ){				 		
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);
	}
}


extern CB_Structure cbTxBuffer;

//Configs USART1 with defaul parameters (see Periph.h).
void SERIAL_DefaultUSART1Config(){ 
	//115200, 8, N, 1
	SERIAL_InitUSART1(
		DEFAULT_USART_BAUDRATE,
		DEFAULT_USART_WORDLENGTH,
		DEFAULT_USART_PARITY,
		DEFAULT_USART_STOPBITS);
	SERIAL_ConfigUSART1Interrupts(); 
}

//Extracts a single character from FIFO and sendsto USART.
void SERIAL_PushToUSART1(char cChr, CB_Structure* cbStructure){
	_BOOL bIsFirst= cbStructure->bIsEmpty;
	CB_Push(cbStructure, cChr);
	if(bIsFirst){  
		SERIAL_EnableUSARTIRQ(USART_TX_IRQ);
		USART_SendData(USART1,(uint16_t)CB_Pop(cbStructure));
	}
}  

//Dumps FIFO to USART.
_BOOL SERIAL_StrToUSART1(CB_Structure* cbStructure){  	
	if(!(cbStructure->bIsEmpty)){  		
		SERIAL_EnableUSARTIRQ(USART_TX_IRQ);  		
		USART_SendData(USART1,(uint16_t)CB_Pop(cbStructure));
	//	SERIAL_DisableUSARTIRQ(USART_RX_IRQ); 
	}
	return TRUE;
}

//Sends a string to USART. 
void SERIAL_Printf(const char *sStr){
   	CB_WriteStr(&cbTxBuffer, sStr);
	SERIAL_StrToUSART1(&cbTxBuffer);
}
