#ifndef __STM32F10x_FIFO_H
#define __STM32F10x_FIFO_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define _BOOL unsigned char
#define CB_SIZE 64u

//Структура кольцевого буфера.
//Элементы добавляются в Tail, читаются из Head.
//Обход по возрастанию индекса.
typedef struct{
	unsigned char nHead;
	unsigned char nTail;
	char sData[CB_SIZE];
	_BOOL bIsEmpty;
}CB_Structure;

//Сброс буфера. nHead и nTail указывают на одну и ту же ячейку.
void CB_Reset(CB_Structure* cbStructure);

//Добавление элемента в буфер.
_BOOL CB_Push(CB_Structure* cbStructure, unsigned char cSym);
//Заполняет буфер символами из строки.
void CB_WriteStr(CB_Structure* cbStructure, const char* sStr);

//Чтение элемента из буфера
char CB_Pop(CB_Structure* cbStructure);
//Чтение строки из буфера
void CB_ReadStr(char* sStr, CB_Structure* cbStructure);
//Размер очереди
int CB_GetSize(CB_Structure* cbStructure);

//Функции для отладки.

//Очистка буфера. nHead и nTail указывают на начало масиива.
void CB_Wipe(CB_Structure* cbStructure);
//Заполняет буфер символами "0".
void __CB_Fill(CB_Structure* cbStructure);

#endif


