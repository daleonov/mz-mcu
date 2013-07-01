#ifndef __PACKET_HANDLER_H
#define __PACKET_HANDLER_H
#include <string.h>

/* Структура пакета */
#define PACKET_START_SEQUENCE "EEE:" // Начало пакета - последовательность символов
#define PACKET_END_CHAR 0x0D // Конец пакета - символ "CR" ('\r')
#define PACKET_MAXLEN 64 // Максимально допустимая длина пакета в символах
#define PACKET_CHECKSUM_LEN 2 // Длина контрольной суммы в символах ASCII

/* Коды ошибок */
#define RS485_UNKNOWN_ERROR -1
#define RS485_NO_START_SEQUENCE_ERROR -2
#define RS485_NO_END_CHAR_ERROR -3
#define RS485_CHECKSUM_ERROR -4
#define RS485_MESSAGE_ERROR -5
#define RS485_UNKNOWN_COMMAND_ERROR -6

int PACKET_GetId(char* sPacketString);

#endif //__PACKET_HANDLER_H
