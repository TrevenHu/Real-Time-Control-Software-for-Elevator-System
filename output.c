#include"elevator.h"
#include"egg.h"

void printState1andState2andState0 (int State)//上行、下行和空闲状态的输出函数 
{
	//全局变量的声明 
	extern float currentFloor;
	extern FILE *fPtr;
	extern int strategy;
	
	if(State==1 || State==2)//上行或下行状态时 
	{
		//文件输出 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
		if(fPtr!=NULL)//成功打开文件后 
		{
			//不同运行状态下输出不同的运行状态符号表示 
			if(State==1)
				fputs("Elevator state: ↑",fPtr);
			else
				fputs("Elevator state: ↓",fPtr);
			//输出当前所在楼层 
			fprintf(fPtr," arriving at %.1f\n",currentFloor);
			//输出当前所用策略 
			if(strategy==0)
				fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
			else
				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);//关闭文件 
		}
		
		//屏幕输出 
		if(State==1)
			printf("Elevator state: ↑ arriving at %.1f\n",currentFloor);
		else
			printf("Elevator state: ↓ arriving at %.1f\n",currentFloor);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
	//若当前状态为空闲 
	else if(State==0)
	{
		//文件输出 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
		if(fPtr!=NULL)//成功打开文件后，输出相应的状态 
		{
			fprintf(fPtr,"Elevator state: on the %.1f floor, vacant.\n",currentFloor);
			fclose(fPtr);//关闭文件 
		}
		//屏幕输出 
		printf("Elevator state: on the %.1f floor, vacant.\n",currentFloor);
	}
}

void printState3 (int State)//停靠状态的输出函数 
{
	//全局变量的声明 
	extern float currentFloor;
	extern int stopTime;
	extern int strategy;
	extern char callrequest;
	extern struct passenger *callPtr, *currentPtr;
	extern FILE *fPtr;
	//首先需要判断停靠时间 
	if(stopTime==0)//刚刚到达某个楼层，输出电梯状态： 停靠，停在几楼，刚刚到达该楼层 
	{
		//文件输出 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"Elevator state: stops at %.1f floor just now.\n",currentFloor);
			if(strategy==0)
		    	fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
  			else
  				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);
		}
		//屏幕输出 
		printf("Elevator state: stops at %.1f floor just now.\n",currentFloor);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
	else  //停靠在某个楼层一段时间，输出电梯状态：停靠在几楼，停靠时间 
	{
		//文件输出 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"Elevator state: stops at %.1f floor, the stop time is %d.\n",currentFloor,stopTime);
			if(strategy==0)
		    	fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
  			else
  				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);
		}
		//屏幕输出 
		printf("Elevator state: stops at %.1f floor, the stop time is %d.\n",currentFloor,stopTime);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
}

void printDestination()//打印目标楼层的函数 
{
	//全局变量的声明 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	extern int State;
	
	if(currentPtr!=NULL)//当前节点不为空，即有目标楼层 
	{
		if(State==3 && currentPtr->nextPtr!=NULL)//停靠状态时已响应当前目标楼层，还未删除，所以目标楼层为当前节点的nextPtr的destination 
		{
			//文件输出 
			fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
			if(fPtr!=NULL)
			{
				fprintf(fPtr,"The next destination is %d.\n",((currentPtr->nextPtr)->destination)%10);
				fclose(fPtr);
			}
			//屏幕输出 
			printf("The next destination is %d.\n",((currentPtr->nextPtr)->destination)%10);
		}
		else if(State==1 || State==2)//上下行状态目标楼层即为当前节点的 destination
		{
			//文件输出 
			fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
			if(fPtr!=NULL)
			{
				fprintf(fPtr,"The next destination is %d.\n",(currentPtr->destination)%10);
				fclose(fPtr);
			}
			//屏幕输出
			printf("The next destination is %d.\n",(currentPtr->destination)%10);	
		}
	}
}


void printUnreactIndoorFloor(void)//输出内部未相应的目标楼层 
{
	//全局变量的声明 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	extern int State;
	//局部变量的初始化 
	struct passenger *theNewPtr=NULL;
	int button=0;

	if(State==1||State==2)              //上下行时第一个未响应楼层为当前节点 
         theNewPtr=currentPtr;  
     else if(State==3&&currentPtr!=NULL)
	     theNewPtr=currentPtr->nextPtr;    //停靠时第一个未响应楼层为当前节点的nextPtr 
	//文件输出和屏幕输出 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	if(fPtr!=NULL)
	{
		//此时若节点为空，则说明没有未响应请求了 
		if(theNewPtr==NULL)
		{
			fputs("There is no unreact  indoor request.\n",fPtr);
			printf("There is no unreact  indoor request.\n");
		}
		else//有未响应请求 
		{
			while(theNewPtr!=NULL)//遍历链表，找出未响应的内部请求 
			{
				if(theNewPtr->destination<=9)//输出未响应内部请求 
				{
					if(button==0) 
					{
						fprintf(fPtr,"The unreact indoor request are:%d ",theNewPtr->destination);
						printf("The unreact indoor request are:%d ",theNewPtr->destination);
						button=1;
					}
					else
					{
						fprintf(fPtr,"%d ",theNewPtr->destination);
						printf("%d ",theNewPtr->destination);
					}
				}
				theNewPtr=theNewPtr->nextPtr;	
			}
			if(button==0)//若button=0,说明没有内部请求，输出相应的内容 
			{
				fputs("There is no unreact indoor request.\n",fPtr);
				printf("There is no unreact indoor request.\n");
			}
			else
			{
   				fputs("\n",fPtr);
				printf("\n");		
			}	
		}
	}
	fclose(fPtr);
}

void printUnreactOutdoorUpandDownFloor(void)//输出未响应的向上呼叫和向下呼叫所在的楼层 
{
	//外部变量的声明 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	//内部变量的声明和初始化 
	struct passenger *theNewPtr=NULL;
	int i=0, j=0, a=0;
	int downCall[100];
	if(State==1||State==2)              //上下行时第一个未响应楼层为当前节点 
         theNewPtr=currentPtr;  
 	else if(State==3&&currentPtr!=NULL)
	     theNewPtr=currentPtr->nextPtr;    //停靠时第一个未响应楼层为当前节点的nextPtr 
	
	//文件输出和屏幕输出	
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\输出文件.txt","a");
	if(fPtr!=NULL)
	{
		//此时若节点为空，则说明没有未响应的向上呼叫和向下呼叫了
		if(theNewPtr==NULL)
		{
			fputs("There is no unreact outdoor request.\n",fPtr);
			printf("There is no unreact outoor request.\n");
		}
		else//有未响应的向上呼叫和向下呼叫 
		{
			while(theNewPtr!=NULL)//遍历链表，找出未响应的向上呼叫和向下呼叫
			{
				if((theNewPtr->destination)>10 && (theNewPtr->destination)<20)//向上呼叫 
				{
					//文件输出和屏幕输出 
					if(i==0)
					{
						fputs("The unreact floors up are:<",fPtr);
						printf("The unreact floors up are:<");
					}	
					fprintf(fPtr,"%d ",theNewPtr->destination%10);
					printf("%d ",theNewPtr->destination%10);
					i++;
				}
				else if(theNewPtr->destination>20)//向下呼叫,先将这些向下呼叫的所在楼层存储到数组中 
				{
					downCall[j]=(theNewPtr->destination%10);
					j++;
				}
				theNewPtr=theNewPtr->nextPtr;
			}
			if(i!=0)
			{
				fputs(">.\n",fPtr);
				printf(">.\n");
			}
			else//若i=0,说明没有向上呼叫的楼层 
			{
				fputs("There is no unreact floor up.\n",fPtr);
				printf("There is no unreact floor up.\n");	
			}
			if(j!=0)//有向下呼叫 
			{
				//文件输出和屏幕输出 
				fputs("The unreact floor down is:[",fPtr);
				printf("The unreact floor down is:[");
				for(a=0;a<=j-1;a++)
				{
					fprintf(fPtr,"%d ",downCall[a]);
					printf("%d ",downCall[a]);
				}
			}
			if(j!=0)
			{
				fputs("].\n",fPtr);
				printf("].\n");
			}
			else//若j=0,说明没有向下呼叫 
			{
				fputs("There is no unreact floor down.\n",fPtr);
				printf("There is no unreact floor down.\n");
			}
		}
	} 
	fclose(fPtr);
}

//DrawState3()函数 
void DrawState3()
{
	 extern struct passenger *currentPtr;
     extern int stopTime; 
     extern char callrequest;
     int i;
     extern HEGG hEggs[33];
     extern int IsSecond[];
     //开门
     if(stopTime==0)
     {		
          for(i=1;i<=20;i++)
	      {   
	          SetActiveEgg(hEggs[3]);
              OffsetEgg(-5.65,0); //左门左移门宽度的1/20
		      SetActiveEgg(hEggs[4]);
		      OffsetEgg(5.65,0); //右门右移门宽度的1/20 
	      }
	      //到达目的地后，进行相应的灭灯操作，并将IsSecond置零。 
   		  switch(currentPtr->destination)
  		  {                           
			  case 1:SetActiveEgg(hEggs[24]);
                  ShowEgg(0);IsSecond[24]=0;break;
   		 	  case 2:SetActiveEgg(hEggs[25]);
    	  	      ShowEgg(0);IsSecond[25]=0;break;
              case 3:SetActiveEgg(hEggs[26]);
    	  	      ShowEgg(0);IsSecond[26]=0;break;
        	  case 4:SetActiveEgg(hEggs[27]);
                  ShowEgg(0);IsSecond[27]=0;break;
        	  case 5:SetActiveEgg(hEggs[28]);
    	  	      ShowEgg(0);IsSecond[28]=0;break;
        	  case 6:SetActiveEgg(hEggs[29]);
    	  	      ShowEgg(0);IsSecond[29]=0;break;
        	  case 7:SetActiveEgg(hEggs[30]);
    	  	      ShowEgg(0);IsSecond[30]=0;break;
        	  case 8:SetActiveEgg(hEggs[31]);
  	    		  ShowEgg(0);IsSecond[31]=0;break;
        	  case 9:SetActiveEgg(hEggs[32]);
    	  	      ShowEgg(0);IsSecond[32]=0;break;
			  case 11:SetActiveEgg(hEggs[15]);
    	  	      ShowEgg(0);IsSecond[15]=0;break;
    		  case 12:SetActiveEgg(hEggs[14]);
    	  	      ShowEgg(0);IsSecond[14]=0;break;
        	  case 13:SetActiveEgg(hEggs[13]);
    	  	      ShowEgg(0);IsSecond[13]=0;break;
        	  case 14:SetActiveEgg(hEggs[12]);
    	  	      ShowEgg(0);IsSecond[12]=0;break;
        	  case 15:SetActiveEgg(hEggs[11]);
    	  	      ShowEgg(0);IsSecond[11]=0;break;
        	  case 16:SetActiveEgg(hEggs[10]);
    	  	      ShowEgg(0);IsSecond[10]=0;break;
 			  case 17:SetActiveEgg(hEggs[9]);
    	  	      ShowEgg(0);IsSecond[9]=0;break;
	    	  case 18:SetActiveEgg(hEggs[8]);
    	  	      ShowEgg(0);IsSecond[8]=0;break;
	    	  case 22:SetActiveEgg(hEggs[23]);
    	  	      ShowEgg(0);IsSecond[23]=0;break;
	    	  case 23:SetActiveEgg(hEggs[22]);
    	  	      ShowEgg(0);IsSecond[22]=0;break;
     		  case 24:SetActiveEgg(hEggs[21]);
    	  	      ShowEgg(0);IsSecond[21]=0;break;
        	  case 25:SetActiveEgg(hEggs[20]);
    	  	      ShowEgg(0);IsSecond[20]=0;break;
	    	  case 26:SetActiveEgg(hEggs[19]);
    	  	      ShowEgg(0);IsSecond[19]=0;break;
	    	  case 27:SetActiveEgg(hEggs[18]);
    	  	      ShowEgg(0);IsSecond[18]=0;break;
	    	  case 28:SetActiveEgg(hEggs[17]);
    	  	      ShowEgg(0);IsSecond[17]=0;break;
    		  case 29:SetActiveEgg(hEggs[16]);
    	  	      ShowEgg(0);IsSecond[16]=0;break;	
     	}
     }
     //当 Go='#'(有人关门)或停靠时间到了5S,电梯关门
	 if(callrequest=='#'||stopTime==5)  
 	 {     
	      
 	      for(i=1;i<=20;i++)
	      {    
	         SetActiveEgg(hEggs[3]);
	         OffsetEgg(5.65,0); //左门右移门宽度的1/20
	       
	         SetActiveEgg(hEggs[4]);
		     OffsetEgg(-5.65,0); //右门左移门宽度的1/20
	      }
      }
} 
