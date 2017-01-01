#include "elevator.h"
#include"egg.h"

DWORD WINAPI input(LPVOID lpParameter);
int main()
{
	//ȫ�ֱ����������ͳ�ʼ��
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
		
	//����������ݵ���ʾ��Ϣ����Ϊ�ļ��������Ļ���
    fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
    if(fPtr!=NULL)
    {    
    	fputs("o(��_��)o Dear passengers,welcome to our elevator!\n",fPtr);
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
    printf("o(��_��)o Dear passengers,welcome to our elevator!\n");
   	printf("------------------------------------------------------------------------\n"); 
   	printf("Z represent first come first serve.\nX represent serve by the way.\n");
	printf("Interior request:enter 1--9 to represent 1--9 floors.\n");
	printf("Exterior upward request:enter Q W E R T Y U I to represent 1--8 floors.\n");
	printf("Exterior downward request:enter A S D F G H J K to represent 2--9 floors.\n"); 
	printf("Enter '#' to represent closing door.\n"); 
	printf("Please press the key Enter after input request.\n");
	printf("-------------------------------------------------------------------------\n");
	
	//����������� 
	DrawBackgroud();
 	DrawElevator(); 
	
	//��ʼ��ʱ	
	startTime=clock();
	 
	//�����߳�
	DWORD ThreadID;
	HANDLE hThread;
	extern HANDLE hMutex;
	//����������� 
	hMutex=CreateMutex(NULL, TRUE, NULL);
	hThread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)input, NULL, 0, &ThreadID);
	CloseHandle(hThread);
    
    while(1)
    {
    	WaitForSingleObject(hMutex, INFINITE);
    	//�����û�����ʱ�����ݲ��ԵĲ�ͬ������ͬ������ 
        if(callPtr!=NULL)
		{
 			if(strategy==0)
    			createFCFSlist();
   			else 
   				createBTWSlist();
		}
			
    	if(currentPtr!=NULL)
    	{
	    	if(fabs(currentFloor-(currentPtr->destination%10))<0.1)//��ǰ¥�����Ŀ��¥��,���ݽ���ͣ��״̬
	    	{
	    		//��ͬĿ�ĵ�ʱ����ƺͳ����ڵ�Ĳ��� 
	    		while(currentPtr->nextPtr!=NULL && fabs(currentFloor-(currentPtr->nextPtr->destination%10))<0.1)
	    		{
	    			//��ͬ���ڲ����� 
	    			if(currentPtr->destination<10)
	    			{
			    		SetActiveEgg(hEggs[23+(currentPtr->destination)]);
						ShowEgg(0);
                    	IsSecond[23+(currentPtr->destination)]=0;
			    	}
			    	//��ͬ���ⲿ�������� 
			    	else if(currentPtr->destination>10 && currentPtr->destination<20)
			    	{
	    				SetActiveEgg(hEggs[16-(currentPtr->destination%10)]);
	    				ShowEgg(0);
	    				IsSecond[16-(currentPtr->destination)%10]=0;
	    			}
	    			else//��ͬ���ⲿ�������� 
	    			{
			    		SetActiveEgg(hEggs[25-(currentPtr->destination%10)]);
	    				ShowEgg(0);
	    				IsSecond[25-(currentPtr->destination)%10]=0;
			    	}
					//ɾ��Ŀ�ĵ���ͬ�Ľڵ� 
    				currentPtr=currentPtr->nextPtr;
		    	}
	    		//��ͣ��״̬����ɶ���
	    		state3();
	    		//˵��Ӧ�ý���ת��
			    if(strategy==1&&currentPtr!=NULL&&currentPtr==midPtr)
				{
					//����������е�ת��
					direction=1-direction;
					//��������е�ת����Ҫ��ת��ָ��
					if(direction==0)//���е�ת��ָ�� 
					{
						//��midPtr�ƶ�����ͬ����ĵ�һ���ڵ��ϣ����޲�ͬ������ΪNULL 
						while(midPtr!=NULL && midPtr->destination<20)
							midPtr=midPtr->nextPtr;
							
						//��lastPtr�ƶ�����ͬ��������һ���ڵ��ϡ� 
						lastPtr=currentPtr;
						while(lastPtr!=NULL&&lastPtr->nextPtr==NULL&&lastPtr->nextPtr!=midPtr)
							lastPtr=lastPtr->nextPtr;
					}
					else//���е�ת��ָ�� 
					{
						//��midPtr�ƶ�����ͬ����ĵ�һ���ڵ��ϣ����޲�ͬ������ΪNULL
						while(midPtr!=NULL && midPtr->destination>20)
							midPtr=midPtr->nextPtr;
							
						//��lastPtr�ƶ�����ͬ��������һ���ڵ��ϡ� 
						lastPtr=currentPtr;
						while(lastPtr!=NULL&&lastPtr->nextPtr==NULL&&lastPtr->nextPtr!=midPtr)
							lastPtr=lastPtr->nextPtr;
					}	
				} 
	    	}
	    	else if(currentFloor<(currentPtr->destination%10))//��ǰ¥��С��Ŀ��¥��,���ݴ�������״̬
	    	{
	    	    if(State==2 && runtime%5!=0)//�����ڷǰ�ȫ�����ڣ������ﰲȫ�����Ժ���ת�� 
 	                state2();
          		else
	    	    	state1();	
	    	}
      
 	        else//��ǰ¥�����Ŀ��¥��,���ݴ�������״̬
 	        {
     			if(State==1 && runtime%5!=0)//�����ڷǰ�ȫ�����ڣ������ﰲȫ�����Ժ���ת�� 
        			state1();
     			else
 	            	state2();
    	    }
	    }
	    else if(currentPtr==NULL)//����ʱû�г˿͵ĺ�������ʱ
	    {
	    	//�����ڷ�����¥�㳷�������ʹ�����е�����¥����ڸı�״̬��
			if(runtime%5!=0&&State==1)
				state1();
			else if(runtime%5!=0&&State==2)
				state2();
			else if(runtime%5==0)
				state0();			
    	}
    	//�������ݱ仯
    	switch(State)
    	{
	    	case 0:break;//����ʱ���޲���
			case 1:FloorState();runtime++;break;//����ʱ����Ҫ�ı������floorstate
			case 2:FloorState();runtime++;break;//����ʱ����Ҫ�ı������floorstate
			case 3:StopState();break;//ͣ��״̬��Ҫ�ı������stopTime
			default:printf("This is a bug.The elevator is very dangerous!Please flee away quickly!o(>�n<)o!\n"); 
		            break;
	    }
	    //��ʱһ�� 
 		Sleep(1000);
		 //�ͷ�Կ�� 
		ReleaseMutex(hMutex);	
    }
	return 0;	
}
