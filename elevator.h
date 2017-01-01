#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>

//�洢�˿���Ϣ������ 
struct passenger
{
	int destination;
	struct passenger *nextPtr;
};
struct passenger *callPtr;//���������û�ָ�� 
struct passenger *currentPtr, *last1Ptr, *midPtr, *lastPtr, *last2Ptr;//���ڴ�������ʱ��ָ��

//��������״̬����ر��� 
clock_t startTime; //ϵͳʱ�ӣ���¼��������ʱ��
int timeCount;//��ǰʱ�� 
int runtime;//���л����е�����ʱ��
int stopTime;//����ͣ����ʱ��
char callrequest;//�û��Ļ�������
int State;//��ǰ״̬��ע��0��ʾ���У�1��ʾ���У�2��ʾ���У�3��ʾͣ��
int direction;//˳������д�����з���1��ʾ���ϣ�2��ʾ����
float currentFloor; //��ǰ¥��, ע��1.0~9.0 
int strategy, prestrategy; //��ǰ���ò��ԣ�ע��0��ʾ���ȷ�����ԣ�1��ʾ˳��������

int IsSecond[33];

HANDLE hMutex;
FILE *fPtr;

void state0(); 
void state1();
void state2();
void state3();
void FloorState();
void StopState();

void printState1andState2andState0(int);
void printState3(int);
void printDestination(void);
void printUnreactIndoorFloor(void);
void printUnreactOutdoorUpandDownFloor(void);

void countpresenttime();
void time_count(); 
 
void chooseStrategy();                                                                     

void createFCFSlist();
void createBTWSlist();
struct passenger *FTPPtr(struct passenger *currentPtr, struct passenger *callPtr, int State);






