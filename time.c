#include"elevator.h"

void countpresenttime()//计算当前时间的函数 
{
	//声明全局变量 
	extern int timeCount;
	extern clock_t startTime;
	clock_t finishTime;//定义一个局部变量，用来求从程序开始运行到某一状态时的间隔时钟 
	
	finishTime=clock();//获得此刻的时钟 
	timeCount=((int)(finishTime - startTime) / CLOCKS_PER_SEC);//计算此时进程的运行时间,由于sleep(3000),所以要除以3 
}

void time_count()//使时间延时一秒的函数 
{
     clock_t start,end;
     int duration;
     
     start=clock();             //调用库函数 clock() 返回CPU时钟计时单元（clock tick）数  
     while(duration<=1)         //使循环持续运行 1秒钟 达到时间延迟作用 
    {
        end=clock();
        duration=(int)(end-start)/CLOCKS_PER_SEC;
    }
} 
