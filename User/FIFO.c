#include "FIFO.h"

/*
//��������� ���������� ������.
//�������� ����������� � Tail, �������� �� Head.
//����� �� ����������� �������.
typedef struct{
	unsigned char nHead;
	unsigned char nTail;
	char sData[CB_SIZE];
	_BOOL bIsEmpty;
}CB_Structure;
*/

//������� ������. nHead � nTail ��������� �� ������ �������.
void CB_Wipe(CB_Structure* cbStructure){
	cbStructure->nHead=0;
	cbStructure->nTail=0;
	cbStructure->bIsEmpty=1;   
}

//����� ������. nHead � nTail ��������� �� ���� � �� �� ������.
void CB_Reset(CB_Structure* cbStructure){
	cbStructure->nHead=cbStructure->nTail;
	cbStructure->bIsEmpty=1;
}

//���������� �������� � �����.
_BOOL CB_Push(CB_Structure* cbStructure, unsigned char cSym){
	cbStructure->sData[cbStructure->nTail]=cSym;
	if (++(cbStructure->nTail)==CB_SIZE) cbStructure->nTail=0;
	if (cbStructure->nHead==cbStructure->nTail) return FALSE;//cbStructure->nHead++; //������ ������������ ������
	cbStructure->bIsEmpty=0; //�������� �������� ��������?
	return TRUE;
}

//��������� ����� ��������� �� ������.
void CB_WriteStr(CB_Structure* cbStructure, const char* sStr){
	int i;
	for(i=0; (sStr[i]!='\0'); i++){CB_Push(cbStructure, sStr[i]);} //���������!
}

//������ �������� �� ������
char CB_Pop(CB_Structure* cbStructure){
	char cSym=0;
	cSym=cbStructure->sData[cbStructure->nHead];
	//���� ������ � ����� ������� - ����� ����.
	if (++(cbStructure->nHead)==CB_SIZE) cbStructure->nHead=0;
	//���� ������ � �����, �� ������ �����������.
	if (cbStructure->nHead==cbStructure->nTail) cbStructure->bIsEmpty=1;
	return cSym;
}
void CB_ReadStr(char* sStr, CB_Structure* cbStructure){
	int i;

	for(i=0; i<CB_SIZE; i++)
		sStr[i]=CB_Pop(cbStructure);

}
//������� ��� �������.
//��������� ����� ��������� "0".

void __CB_Fill(CB_Structure* cbStructure){
	int i;
	for(i=0; i<=CB_SIZE-1; i++) cbStructure->sData[i]='0';
}

int CB_GetSize(CB_Structure* cbStructure){
	if(cbStructure->nTail>=cbStructure->nHead) return cbStructure->nTail-cbStructure->nHead;
	else return (CB_SIZE-cbStructure->nHead+cbStructure->nTail);
}
