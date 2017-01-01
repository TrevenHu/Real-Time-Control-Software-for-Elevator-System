#include "elevator.h"
#include"egg.h"

void state0()
{
	extern int State;
	State=0;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //����ʱ�亯�����㵱ǰʱ�� 
	
	//�ļ���� 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	printState1andState2andState0(State);            //��ӡ����״̬ 
	
}

void state1()
{
	extern int State;
	State=1;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //���㵱ǰʱ�� 
	
    //�ļ��������Ļ��� 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	 
	printState1andState2andState0(State);   //��ӡ����״̬ 
	printDestination();            //��ӡĿ��¥�� 
	printUnreactIndoorFloor();           //��ӡ�ڲ�δ��Ӧ¥�� 
 	printUnreactOutdoorUpandDownFloor();//��ӡδ��Ӧ���Ϻ��к����º�������¥�� 
}

void state2()
{
	extern int State;
	State=2;
	extern int timeCount;
	extern FILE *fPtr;
	
	countpresenttime();            //���㵱ǰʱ�� 
	
	//�ļ��������Ļ��� 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	printState1andState2andState0(State);   //��ӡ����״̬ 
	printDestination();            //��ӡĿ��¥�� 
	printUnreactIndoorFloor();           //��ӡ�ڲ�δ��Ӧ¥�� 
	printUnreactOutdoorUpandDownFloor();//��ӡδ��Ӧ���Ϻ��к����º�������¥��
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
	
	countpresenttime();          //���㵱ǰʱ�� 
	
	//�ļ��������Ļ��� 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	{
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"\nThe time is:%d\n",timeCount);
			fclose(fPtr);
		}
	}
	printf("\nThe time is:%d\n",timeCount);
	
	DrawState3(); 
	
	printState3(State);          //��ӡͣ��״̬ 
	printDestination();          //��ӡĿ��¥�� 
	printUnreactIndoorFloor();         //��ӡ�ڲ�δ��Ӧ¥�� 
	printUnreactOutdoorUpandDownFloor();//��ӡδ��Ӧ���Ϻ��к����º�������¥��

    if(callrequest=='#'||stopTime==5)//���ﵽͣ��ʱ�����ܵ����ż�ָʾ 
    {
    	
    	headPtr=currentPtr;
    	if(currentPtr==NULL || currentPtr->nextPtr==NULL)     //û����һ��Ŀ��¥�� �������״̬
        {
        	State=0;
        	free(headPtr);//�ͷŷ�����ɵĽڵ� 
        	currentPtr=NULL;
        	headPtr=NULL;
        }
        else
		{
			currentPtr=currentPtr->nextPtr;//������һλ�˿�
			free(headPtr);
			headPtr=NULL; 		
			if(currentFloor<(currentPtr->destination%10))//��ǰ¥��С��Ŀ��¥�� ���ݴ�������״̬ 
        		State=1;   
        	else                     //��ǰ¥�����Ŀ��¥�� ���ݴ�������״̬ 
        		State=2;
		}
   
     	stopTime=0;              //��ͣ��ʱ������ 
     	//���¹��ż���callrequest���㡣 
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
     	        //����ÿ���� 1�� ��ǰ¥������ 0.2 
        currentFloor+=0.2;
		SetActiveEgg(hEggs[5]);
       	OffsetEgg(0,10.8);//10.8Ϊ1s �����еľ��� 
     }        
     else if(State==2)    {
     	//����ÿ���� 1��  ��ǰ¥����� 0.2 
        currentFloor-=0.2;
        SetActiveEgg(hEggs[5]);
		OffsetEgg(0,-10.8);//10.8Ϊ1s �����еľ���
     }       
        
}
void StopState()
{
    extern int stopTime;   
	
    stopTime++;                   //ͣ��ʱ������ 1�� 
}

