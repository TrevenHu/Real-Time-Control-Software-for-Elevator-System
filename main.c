#include "elevator.h"
#include"egg.h"

DWORD WINAPI input(LPVOID lpParameter);
int main()
{
	//全局变量的声明和初始化
	extern HEGG hEggs[33];
	extern int IsSecond[];
	extern struct passenger *callPtr, *currentPtr, *last1Ptr;
	callPtr=NULL;
	currentPtr=NULL;
	last1Ptr=NULL;
	midPtr=NULL;
	lastPtr=NULL;
	
	extern int strategy, prestrategy;
	strategy=0;prestrategy=0;
	extern int State;
	State=0;
	extern int direction;
	direction=0;
	extern char callrequest;
	extern float currentFloor;
	currentFloor=1.0;
	
	extern clock_t startTime;
	extern int timeCount;
	timeCount=0;
	extern int runtime;
	runtime=0;
	extern int stopTime;
	stopTime=0;
		
	extern FILE *fPtr;
	
	memset(IsSecond,0,33);
		
	//输出乘坐电梯的提示信息，分为文件输出和屏幕输出
    fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
    if(fPtr!=NULL)
    {    
    	fputs("o(∩_∩)o Dear passengers,welcome to our elevator!\n",fPtr);
		fputs("-------------------------------------------------------------------------\n",fPtr);
		fputs("Z represent first come first serve.\nX represent serve by the way.\n",fPtr);
		fputs("Interior request:enter 1--9 to represent 1--9 floors.\n",fPtr);
		fputs("Exterior upward request:enter Q W E R T Y U I to represent 1--8 floors.\n",fPtr);
		fputs("Exterior downward request:enter A S D F G H J K to represent 2--9 floors.\n",fPtr);
		fputs("Enter '#' to represent closing door.\n",fPtr);
		fputs("Please press the key Enter after input request.\n",fPtr);
		fputs("--------------------------------------------------------------------------\n",fPtr);
    	fclose(fPtr);
    }
    printf("o(∩_∩)o Dear passengers,welcome to our elevator!\n");
   	printf("------------------------------------------------------------------------\n"); 
   	printf("Z represent first come first serve.\nX represent serve by the way.\n");
	printf("Interior request:enter 1--9 to represent 1--9 floors.\n");
	printf("Exterior upward request:enter Q W E R T Y U I to represent 1--8 floors.\n");
	printf("Exterior downward request:enter A S D F G H J K to represent 2--9 floors.\n"); 
	printf("Enter '#' to represent closing door.\n"); 
	printf("Please press the key Enter after input request.\n");
	printf("-------------------------------------------------------------------------\n");
	
	//输出动画界面 
	DrawBackgroud();
 	DrawElevator(); 
	
	//开始计时	
	startTime=clock();
	 
	//创建线程
	DWORD ThreadID;
	HANDLE hThread;
	extern HANDLE hMutex;
	//创建互斥对象 
	hMutex=CreateMutex(NULL, TRUE, NULL);
	hThread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)input, NULL, 0, &ThreadID);
	CloseHandle(hThread);
    
    while(1)
    {
    	WaitForSingleObject(hMutex, INFINITE);
    	//有新用户请求时，根据策略的不同创建不同的链表。 
        if(callPtr!=NULL)
		{
 			if(strategy==0)
    			createFCFSlist();
   			else 
   				createBTWSlist();
		}
			
    	if(currentPtr!=NULL)
    	{
	    	if(fabs(currentFloor-(currentPtr->destination%10))<0.1)//当前楼层等于目标楼层,电梯进入停靠状态
	    	{
	    		//相同目的地时，灭灯和撤销节点的操作 
	    		while(currentPtr->nextPtr!=NULL && fabs(currentFloor-(currentPtr->nextPtr->destination%10))<0.1)
	    		{
	    			//相同的内部请求 
	    			if(currentPtr->destination<10)
	    			{
			    		SetActiveEgg(hEggs[23+(currentPtr->destination)]);
						ShowEgg(0);
                    	IsSecond[23+(currentPtr->destination)]=0;
			    	}
			    	//相同的外部上行请求 
			    	else if(currentPtr->destination>10 && currentPtr->destination<20)
			    	{
	    				SetActiveEgg(hEggs[16-(currentPtr->destination%10)]);
	    				ShowEgg(0);
	    				IsSecond[16-(currentPtr->destination)%10]=0;
	    			}
	    			else//相同的外部下行请求 
	    			{
			    		SetActiveEgg(hEggs[25-(currentPtr->destination%10)]);
	    				ShowEgg(0);
	    				IsSecond[25-(currentPtr->destination)%10]=0;
			    	}
					//删除目的地相同的节点 
    				currentPtr=currentPtr->nextPtr;
		    	}
	    		//在停靠状态下完成动作
	    		state3();
	    		//说明应该进入转向
			    if(strategy==1&&currentPtr!=NULL&&currentPtr==midPtr)
				{
					//完成上行下行的转换
					direction=1-direction;
					//完成上下行的转换后要再转换指针
					if(direction==0)//上行的转换指针 
					{
						//将midPtr移动到不同方向的第一个节点上，若无不同方向，则为NULL 
						while(midPtr!=NULL && midPtr->destination<20)
							midPtr=midPtr->nextPtr;
							
						//将lastPtr移动到相同方向的最后一个节点上。 
						lastPtr=currentPtr;
						while(lastPtr!=NULL&&lastPtr->nextPtr==NULL&&lastPtr->nextPtr!=midPtr)
							lastPtr=lastPtr->nextPtr;
					}
					else//下行的转换指针 
					{
						//将midPtr移动到不同方向的第一个节点上，若无不同方向，则为NULL
						while(midPtr!=NULL && midPtr->destination>20)
							midPtr=midPtr->nextPtr;
							
						//将lastPtr移动到相同方向的最后一个节点上。 
						lastPtr=currentPtr;
						while(lastPtr!=NULL&&lastPtr->nextPtr==NULL&&lastPtr->nextPtr!=midPtr)
							lastPtr=lastPtr->nextPtr;
					}	
				} 
	    	}
	    	else if(currentFloor<(currentPtr->destination%10))//当前楼层小于目标楼层,电梯处于上行状态
	    	{
	    	    if(State==2 && runtime%5!=0)//若处于非安全距离内，待到达安全距离以后再转向 
 	                state2();
          		else
	    	    	state1();	
	    	}
      
 	        else//当前楼层大于目标楼层,电梯处于下行状态
 	        {
     			if(State==1 && runtime%5!=0)//若处于非安全距离内，待到达安全距离以后再转向 
        			state1();
     			else
 	            	state2();
    	    }
	    }
	    else if(currentPtr==NULL)//当此时没有乘客的呼叫请求时
	    {
	    	//用于在非整数楼层撤销请求后使其运行到整数楼层后在改变状态。
			if(runtime%5!=0&&State==1)
				state1();
			else if(runtime%5!=0&&State==2)
				state2();
			else if(runtime%5==0)
				state0();			
    	}
    	//处理数据变化
    	switch(State)
    	{
	    	case 0:break;//空闲时刻无操作
			case 1:FloorState();runtime++;break;//上行时刻需要改变的数据floorstate
			case 2:FloorState();runtime++;break;//下行时刻需要改变的数据floorstate
			case 3:StopState();break;//停靠状态需要改变的数据stopTime
			default:printf("This is a bug.The elevator is very dangerous!Please flee away quickly!o(>﹏<)o!\n"); 
		            break;
	    }
	    //延时一秒 
 		Sleep(1000);
		 //释放钥匙 
		ReleaseMutex(hMutex);	
    }
	return 0;	
}
