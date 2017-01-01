#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>

//存储乘客信息的链表 
struct passenger
{
	int destination;
	struct passenger *nextPtr;
};
struct passenger *callPtr;//用于输入用户指令 
struct passenger *currentPtr, *last1Ptr, *midPtr, *lastPtr, *last2Ptr;//用于创建链表时的指针

//电梯运行状态的相关变量 
clock_t startTime; //系统时钟，记录电梯启动时间
int timeCount;//当前时刻 
int runtime;//上行或下行的运行时间
int stopTime;//电梯停靠的时间
char callrequest;//用户的基本请求
int State;//当前状态，注：0表示空闲，1表示上行，2表示下行，3表示停靠
int direction;//顺便服务中大的运行方向，1表示向上，2表示向下
float currentFloor; //当前楼层, 注：1.0~9.0 
int strategy, prestrategy; //当前采用策略，注：0表示优先服务策略，1表示顺便服务策略

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






