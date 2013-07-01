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

//��������� ���������� ������.
//�������� ����������� � Tail, �������� �� Head.
//����� �� ����������� �������.
typedef struct{
	unsigned char nHead;
	unsigned char nTail;
	char sData[CB_SIZE];
	_BOOL bIsEmpty;
}CB_Structure;

//����� ������. nHead � nTail ��������� �� ���� � �� �� ������.
void CB_Reset(CB_Structure* cbStructure);

//���������� �������� � �����.
_BOOL CB_Push(CB_Structure* cbStructure, unsigned char cSym);
//��������� ����� ��������� �� ������.
void CB_WriteStr(CB_Structure* cbStructure, const char* sStr);

//������ �������� �� ������
char CB_Pop(CB_Structure* cbStructure);
//������ ������ �� ������
void CB_ReadStr(char* sStr, CB_Structure* cbStructure);
//������ �������
int CB_GetSize(CB_Structure* cbStructure);

//������� ��� �������.

//������� ������. nHead � nTail ��������� �� ������ �������.
void CB_Wipe(CB_Structure* cbStructure);
//��������� ����� ��������� "0".
void __CB_Fill(CB_Structure* cbStructure);

#endif


