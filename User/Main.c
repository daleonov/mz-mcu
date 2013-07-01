#include "stm32f10x.h"	  
#include "periph.h"
#include "FIFO.h"
#include "Time.h"  
#include "PacketHandler.h"

/* Буфер последовательного порта */
CB_Structure cbRxBuffer; 

/* Флаг пришедшего пакета */
_BOOL bNewPacket = 0;
			 
void USART1_IRQHandler(void){
	/*!
	\brief Обработчик прерываний от последовательного порта.
	*/		 
	static char cChr;						

	/*
	Если в Rx появились данные, записываем их побайтно в буфер.
	Когда приходит символ конца пакета (в данном случае CR), 
	устанавливаем флаг конца пакета. 
	*/
	if((USART_GetITStatus(USART1, USART_IT_RXNE))){
		/* Считываем байт */
		cChr= USART_ReceiveData(USART1);
		/* Записываем в буфер */
		CB_Push(&cbRxBuffer, cChr);
		/* Если CR - выставляем соответствующий флаг */
		if((cChr=='\r')){
			bNewPacket = 1;	
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		 
	}	  
	 	 
}

int DEV_HandlePacket(void);

int main(void){  	

	/* Инициальзация системного таймера */
	DEV_SystemRCCInit();

	/* Инициализация приёмного буфера */
	CB_Wipe(&cbRxBuffer);

	/* Инициализация последовательного порта (RS485) */
	PERIRH_DefaultUSART1Config();

	while(1){
		if(bNewPacket){	  			 
			DEV_HandlePacket(); /* Обработка пакета */ 
			bNewPacket = 0;	 /* Сброс флага */
		}	   
		TIME_Delay_ms(10);
	}

}


int DEV_HandlePacket(void){
	/*!
	\brief Обработчик принятых пакетов.
	\details Вызывается после приёма каждого пакета.
	*/
	char sReceivedPacket[CB_SIZE];
	int nPacketId;

	/* Считываем данные из буфера */
	CB_ReadStr(sReceivedPacket, &cbRxBuffer);
	CB_Wipe(&cbRxBuffer); 	
	
	/* Анализ пакета */
	nPacketId = PACKET_GetId(sReceivedPacket);
	
	/* Действия в зависимости от входного пакета */
	switch(nPacketId){

	/* Обработка опознанных пакетов */
	case 1: /* Пакет 1 */
		/* Действие 1 */
		break;
	case 2:	/* Пакет 2 */
		/* Действие 1 */
		break;
		/* ... */
		
	/* Обработка ошибок */	
	case RS485_CHECKSUM_ERROR: /* Ошибка контрольной суммы */ 
		/* ... */
		break;
	case RS485_UNKNOWN_COMMAND_ERROR: /* Неизвестный пакет */ 
		/* ... */
		break;
	/* ... */

	}	

	return 0;
}


