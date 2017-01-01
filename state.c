#include "elevator.h"
#include"egg.h"

void state0()
{
	extern int State;
	State=0;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //调用时间函数计算当前时间 
	
	//文件输出 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	printState1andState2andState0(State);            //打印空闲状态 
	
}

void state1()
{
	extern int State;
	State=1;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //计算当前时间 
	
    //文件输出和屏幕输出 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	 
	printState1andState2andState0(State);   //打印上行状态 
	printDestination();            //打印目的楼层 
	printUnreactIndoorFloor();           //打印内部未响应楼层 
 	printUnreactOutdoorUpandDownFloor();//打印未响应向上呼叫和向下呼叫所在楼层 
}

void state2()
{
	extern int State;
	State=2;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //计算当前时间 
	
	//文件输出和屏幕输出 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	printState1andState2andState0(State);   //打印下行状态 
	printDestination();            //打印目的楼层 
	printUnreactIndoorFloor();           //打印内部未响应楼层 
	printUnreactOutdoorUpandDownFloor();//打印未响应向上呼叫和向下呼叫所在楼层
}

void state3()
{
	extern int State;
	State=3;
	extern int timeCount;
	extern char callrequest;
	extern int stopTime;
	extern struct passenger *currentPtr;
	struct passenger *headPtr;
	extern float currentFloor;
	extern FILE *fPtr;
	
	countpresenttime();          //计算当前时间 
	
	//文件输出和屏幕输出 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	DrawState3(); 
	
	printState3(State);          //打印停靠状态 
	printDestination();          //打印目的楼层 
	printUnreactIndoorFloor();         //打印内部未响应楼层 
	printUnreactOutdoorUpandDownFloor();//打印未响应向上呼叫和向下呼叫所在楼层

    if(callrequest=='#'||stopTime==5)//当达到停靠时间或接受到关门键指示 
    {
    	
    	headPtr=currentPtr;
    	if(currentPtr==NULL || currentPtr->nextPtr==NULL)     //没有下一个目标楼层 进入空闲状态
        {
        	State=0;
        	free(headPtr);//释放服务完成的节点 
        	currentPtr=NULL;
        	headPtr=NULL;
        }
        else
		{
			currentPtr=currentPtr->nextPtr;//服务下一位乘客
			free(headPtr);
			headPtr=NULL; 		
			if(currentFloor<(currentPtr->destination%10))//当前楼层小于目标楼层 电梯处于上行状态 
        		State=1;   
        	else                     //当前楼层大于目标楼层 电梯处于下行状态 
        		State=2;
		}
   
     	stopTime=0;              //将停靠时间置零 
     	//按下关门键后，callrequest置零。 
     	if(callrequest=='#')
     		callrequest='0';
    }
}

void FloorState()
{
     extern HEGG hEggs[];
     extern int State;
     extern float currentFloor;
     
     if(State==1){
     	        //电梯每运行 1秒 当前楼层增加 0.2 
        currentFloor+=0.2;
		SetActiveEgg(hEggs[5]);
       	OffsetEgg(0,10.8);//10.8为1s 内上行的距离 
     }        
     else if(State==2)    {
     	//电梯每运行 1秒  当前楼层减少 0.2 
        currentFloor-=0.2;
        SetActiveEgg(hEggs[5]);
		OffsetEgg(0,-10.8);//10.8为1s 内下行的距离
     }       
        
}
void StopState()
{
    extern int stopTime;   
	
    stopTime++;                   //停靠时间增加 1秒 
}

