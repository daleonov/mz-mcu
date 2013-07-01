#include "stm32f10x.h"	  
#include "periph.h"
#include "FIFO.h"
#include "Time.h"  
#include "PacketHandler.h"

/* ����� ����������������� ����� */
CB_Structure cbRxBuffer; 

/* ���� ���������� ������ */
_BOOL bNewPacket = 0;
			 
void USART1_IRQHandler(void){
	/*!
	\brief ���������� ���������� �� ����������������� �����.
	*/		 
	static char cChr;						

	/*
	���� � Rx ��������� ������, ���������� �� �������� � �����.
	����� �������� ������ ����� ������ (� ������ ������ CR), 
	������������� ���� ����� ������. 
	*/
	if((USART_GetITStatus(USART1, USART_IT_RXNE))){
		/* ��������� ���� */
		cChr= USART_ReceiveData(USART1);
		/* ���������� � ����� */
		CB_Push(&cbRxBuffer, cChr);
		/* ���� CR - ���������� ��������������� ���� */
		if((cChr=='\r')){
			bNewPacket = 1;	
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		 
	}	  
	 	 
}

int DEV_HandlePacket(void);

int main(void){  	

	/* ������������� ���������� ������� */
	DEV_SystemRCCInit();

	/* ������������� �������� ������ */
	CB_Wipe(&cbRxBuffer);

	/* ������������� ����������������� ����� (RS485) */
	PERIRH_DefaultUSART1Config();

	while(1){
		if(bNewPacket){	  			 
			DEV_HandlePacket(); /* ��������� ������ */ 
			bNewPacket = 0;	 /* ����� ����� */
		}	   
		TIME_Delay_ms(10);
	}

}


int DEV_HandlePacket(void){
	/*!
	\brief ���������� �������� �������.
	\details ���������� ����� ����� ������� ������.
	*/
	char sReceivedPacket[CB_SIZE];
	int nPacketId;

	/* ��������� ������ �� ������ */
	CB_ReadStr(sReceivedPacket, &cbRxBuffer);
	CB_Wipe(&cbRxBuffer); 	
	
	/* ������ ������ */
	nPacketId = PACKET_GetId(sReceivedPacket);
	
	/* �������� � ����������� �� �������� ������ */
	switch(nPacketId){

	/* ��������� ���������� ������� */
	case 1: /* ����� 1 */
		/* �������� 1 */
		break;
	case 2:	/* ����� 2 */
		/* �������� 1 */
		break;
		/* ... */
		
	/* ��������� ������ */	
	case RS485_CHECKSUM_ERROR: /* ������ ����������� ����� */ 
		/* ... */
		break;
	case RS485_UNKNOWN_COMMAND_ERROR: /* ����������� ����� */ 
		/* ... */
		break;
	/* ... */

	}	

	return 0;
}


