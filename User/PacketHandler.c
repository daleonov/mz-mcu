
#include <stdio.h>
#include <stdlib.h>

#include "PacketHandler.h"
#include "Rs485Commands.h"

/* Служебные функции */
static unsigned char PACKET_CalculateCheckSum(const char* sMessage);
static int PACKET_ExtractMessage(const char* sRawPacket, char* sMessage);
static int PACKET_ExtractCheckSum(const char * sRawPacket, char * sCheckSum);

int PACKET_GetId(char* sPacketString){
	/*!
	\brief Парсер входных пакетов.
	\details Выделяет из входного пакета команду и контрольную сумму,
	\details сравнивает с известными командами (см. Rs485Commands.h)
	\details и возвращает её ID.
	*/

	char sMessage[PACKET_MAXLEN + 1];
	char sCheckSum[PACKET_CHECKSUM_LEN + 1];
	int nMessageLength;
	unsigned char nCheckSum;
	int i;

	/* Извлечение из пакета сообщения и контрольной суммы */
	nMessageLength = PACKET_ExtractMessage(sPacketString, sMessage);
	if (nMessageLength == 0) return RS485_MESSAGE_ERROR;
	PACKET_ExtractCheckSum(sPacketString, sCheckSum);
	/* Проверка контрольной суммы */
	nCheckSum = strtol(sCheckSum, NULL, 16);
	if(nCheckSum != PACKET_CalculateCheckSum(sMessage)) return RS485_CHECKSUM_ERROR;

	for (i=0; i<RS485_COMMANDS_NUM; i++){
		if(!strncmp(asRs485Commands[i], sMessage, PACKET_MAXLEN)){
			/* Если команда совпадает с командой из списка, возвращаем её ID */
			return anRs485Ids[i];
		}
	}

	/* Если команда не найдена - возвращаем код ошибки */
	return RS485_UNKNOWN_COMMAND_ERROR;
}

static int PACKET_ExtractMessage(const char* sRawPacket, char* sMessage){
	/*!
	\brief Извлекает строку сообщение из пакета. 
	\param sRawPacket Указатель на исходный пакет. 
	\param sMessage Выходные данные - указатель на строку с сообщением. 
	\retval Длина сообщения (в символях ASCII). 
	*/

	char *sMessageStart = NULL;
	unsigned int nMessageLength = 0;
	sMessageStart = (char*) strstr(sRawPacket, PACKET_START_SEQUENCE) + strlen(PACKET_START_SEQUENCE);
	nMessageLength = strlen(sMessageStart) - PACKET_CHECKSUM_LEN - 1;
	strncpy(sMessage, sMessageStart, nMessageLength);
	sMessage[nMessageLength] = '\0';

	return nMessageLength;
}

static int PACKET_ExtractCheckSum(const char * sRawPacket, char * sCheckSum){
	/*!
	\brief Извлекает символы контрольной суммы из сообщения (в формате ASCII). 
	\param sRawPacket Указатель на исходный пакет. 
	\param sCheckSum Выходные данные - указатель на строку с контрольной суммой. 
	\retval 0. 
	*/
	
	char *sCheckSumStart = NULL;

	sCheckSumStart = (char*) sRawPacket + (strlen(sRawPacket) - PACKET_CHECKSUM_LEN - 1);
	strncpy(sCheckSum, sCheckSumStart, PACKET_CHECKSUM_LEN);
	sCheckSum[PACKET_CHECKSUM_LEN] = '\0';

	return 0;
}

static unsigned char PACKET_CalculateCheckSum(const char* sMessage){
	/*!
	\brief Вычисляет контрольную сумму путём побитового исключающего "или" всех байт в строке. 
	\param sMessage Исходная строка.
	\retval Котрольная сумма (1 байт). 
	*/

	char cCurrentChar = *sMessage;
	unsigned char nCheckSum = 0;
	unsigned int nCharCounter = 0;
	while ((cCurrentChar != '\0') && (nCharCounter <= PACKET_MAXLEN)){
		nCheckSum ^= cCurrentChar;
		cCurrentChar = *(sMessage++);
		nCharCounter ++;
	}

	return nCheckSum;
}
