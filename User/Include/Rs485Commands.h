
/*
����� ��������� ������ ����������� ������� � �� ID.
��������� ���� ���� ��� � ����� PacketHandler.h.
*/

#define RS485_COMMANDS_NUM 4 /* ���������� ��������� ������� ������� */

char asRs485Commands[RS485_COMMANDS_NUM][PACKET_MAXLEN] = {"Sample1", "Sample2", "12RS485", "Sample3"};
int anRs485Ids[RS485_COMMANDS_NUM] = {1, 2, 3, 4};

