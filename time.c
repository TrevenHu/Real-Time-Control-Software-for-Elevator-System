#include"elevator.h"

void countpresenttime()//���㵱ǰʱ��ĺ��� 
{
	//����ȫ�ֱ��� 
	extern int timeCount;
	extern clock_t startTime;
	clock_t finishTime;//����һ���ֲ�������������ӳ���ʼ���е�ĳһ״̬ʱ�ļ��ʱ�� 
	
	finishTime=clock();//��ô˿̵�ʱ�� 
	timeCount=((int)(finishTime - startTime) / CLOCKS_PER_SEC);//�����ʱ���̵�����ʱ��,����sleep(3000),����Ҫ����3 
}

void time_count()//ʹʱ����ʱһ��ĺ��� 
{
     clock_t start,end;
     int duration;
     
     start=clock();             //���ÿ⺯�� clock() ����CPUʱ�Ӽ�ʱ��Ԫ��clock tick����  
     while(duration<=1)         //ʹѭ���������� 1���� �ﵽʱ���ӳ����� 
    {
        end=clock();
        duration=(int)(end-start)/CLOCKS_PER_SEC;
    }
} 
