#include"elevator.h"
#include"egg.h"

void printState1andState2andState0 (int State)//���С����кͿ���״̬��������� 
{
	//ȫ�ֱ��������� 
	extern float currentFloor;
	extern FILE *fPtr;
	extern int strategy;
	
	if(State==1 || State==2)//���л�����״̬ʱ 
	{
		//�ļ���� 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
		if(fPtr!=NULL)//�ɹ����ļ��� 
		{
			//��ͬ����״̬�������ͬ������״̬���ű�ʾ 
			if(State==1)
				fputs("Elevator state: ��",fPtr);
			else
				fputs("Elevator state: ��",fPtr);
			//�����ǰ����¥�� 
			fprintf(fPtr," arriving at %.1f\n",currentFloor);
			//�����ǰ���ò��� 
			if(strategy==0)
				fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
			else
				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);//�ر��ļ� 
		}
		
		//��Ļ��� 
		if(State==1)
			printf("Elevator state: �� arriving at %.1f\n",currentFloor);
		else
			printf("Elevator state: �� arriving at %.1f\n",currentFloor);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
	//����ǰ״̬Ϊ���� 
	else if(State==0)
	{
		//�ļ���� 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
		if(fPtr!=NULL)//�ɹ����ļ��������Ӧ��״̬ 
		{
			fprintf(fPtr,"Elevator state: on the %.1f floor, vacant.\n",currentFloor);
			fclose(fPtr);//�ر��ļ� 
		}
		//��Ļ��� 
		printf("Elevator state: on the %.1f floor, vacant.\n",currentFloor);
	}
}

void printState3 (int State)//ͣ��״̬��������� 
{
	//ȫ�ֱ��������� 
	extern float currentFloor;
	extern int stopTime;
	extern int strategy;
	extern char callrequest;
	extern struct passenger *callPtr, *currentPtr;
	extern FILE *fPtr;
	//������Ҫ�ж�ͣ��ʱ�� 
	if(stopTime==0)//�ոյ���ĳ��¥�㣬�������״̬�� ͣ����ͣ�ڼ�¥���ոյ����¥�� 
	{
		//�ļ���� 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"Elevator state: stops at %.1f floor just now.\n",currentFloor);
			if(strategy==0)
		    	fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
  			else
  				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);
		}
		//��Ļ��� 
		printf("Elevator state: stops at %.1f floor just now.\n",currentFloor);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
	else  //ͣ����ĳ��¥��һ��ʱ�䣬�������״̬��ͣ���ڼ�¥��ͣ��ʱ�� 
	{
		//�ļ���� 
		fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
		if(fPtr!=NULL)
		{
			fprintf(fPtr,"Elevator state: stops at %.1f floor, the stop time is %d.\n",currentFloor,stopTime);
			if(strategy==0)
		    	fputs("The current strategy is Fist Come Fist Serve.\n",fPtr);
  			else
  				fputs("The current strategy is Serve By The Way.\n",fPtr);
			fclose(fPtr);
		}
		//��Ļ��� 
		printf("Elevator state: stops at %.1f floor, the stop time is %d.\n",currentFloor,stopTime);
		if(strategy==0)
		    printf("The current strategy is Fist Come Fist Serve.\n");
  		else
  			printf("The current strategy is Serve By The Way.\n");
	}
}

void printDestination()//��ӡĿ��¥��ĺ��� 
{
	//ȫ�ֱ��������� 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	extern int State;
	
	if(currentPtr!=NULL)//��ǰ�ڵ㲻Ϊ�գ�����Ŀ��¥�� 
	{
		if(State==3 && currentPtr->nextPtr!=NULL)//ͣ��״̬ʱ����Ӧ��ǰĿ��¥�㣬��δɾ��������Ŀ��¥��Ϊ��ǰ�ڵ��nextPtr��destination 
		{
			//�ļ���� 
			fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
			if(fPtr!=NULL)
			{
				fprintf(fPtr,"The next destination is %d.\n",((currentPtr->nextPtr)->destination)%10);
				fclose(fPtr);
			}
			//��Ļ��� 
			printf("The next destination is %d.\n",((currentPtr->nextPtr)->destination)%10);
		}
		else if(State==1 || State==2)//������״̬Ŀ��¥�㼴Ϊ��ǰ�ڵ�� destination
		{
			//�ļ���� 
			fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
			if(fPtr!=NULL)
			{
				fprintf(fPtr,"The next destination is %d.\n",(currentPtr->destination)%10);
				fclose(fPtr);
			}
			//��Ļ���
			printf("The next destination is %d.\n",(currentPtr->destination)%10);	
		}
	}
}


void printUnreactIndoorFloor(void)//����ڲ�δ��Ӧ��Ŀ��¥�� 
{
	//ȫ�ֱ��������� 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	extern int State;
	//�ֲ������ĳ�ʼ�� 
	struct passenger *theNewPtr=NULL;
	int button=0;

	if(State==1||State==2)              //������ʱ��һ��δ��Ӧ¥��Ϊ��ǰ�ڵ� 
         theNewPtr=currentPtr;  
     else if(State==3&&currentPtr!=NULL)
	     theNewPtr=currentPtr->nextPtr;    //ͣ��ʱ��һ��δ��Ӧ¥��Ϊ��ǰ�ڵ��nextPtr 
	//�ļ��������Ļ��� 
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	if(fPtr!=NULL)
	{
		//��ʱ���ڵ�Ϊ�գ���˵��û��δ��Ӧ������ 
		if(theNewPtr==NULL)
		{
			fputs("There is no unreact  indoor request.\n",fPtr);
			printf("There is no unreact  indoor request.\n");
		}
		else//��δ��Ӧ���� 
		{
			while(theNewPtr!=NULL)//���������ҳ�δ��Ӧ���ڲ����� 
			{
				if(theNewPtr->destination<=9)//���δ��Ӧ�ڲ����� 
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
			if(button==0)//��button=0,˵��û���ڲ����������Ӧ������ 
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

void printUnreactOutdoorUpandDownFloor(void)//���δ��Ӧ�����Ϻ��к����º������ڵ�¥�� 
{
	//�ⲿ���������� 
	extern struct passenger *currentPtr;
	extern FILE *fPtr;
	//�ڲ������������ͳ�ʼ�� 
	struct passenger *theNewPtr=NULL;
	int i=0, j=0, a=0;
	int downCall[100];
	if(State==1||State==2)              //������ʱ��һ��δ��Ӧ¥��Ϊ��ǰ�ڵ� 
         theNewPtr=currentPtr;  
 	else if(State==3&&currentPtr!=NULL)
	     theNewPtr=currentPtr->nextPtr;    //ͣ��ʱ��һ��δ��Ӧ¥��Ϊ��ǰ�ڵ��nextPtr 
	
	//�ļ��������Ļ���	
	fPtr=fopen("C:\\Users\\Administrator\\Desktop\\����ļ�.txt","a");
	if(fPtr!=NULL)
	{
		//��ʱ���ڵ�Ϊ�գ���˵��û��δ��Ӧ�����Ϻ��к����º�����
		if(theNewPtr==NULL)
		{
			fputs("There is no unreact outdoor request.\n",fPtr);
			printf("There is no unreact outoor request.\n");
		}
		else//��δ��Ӧ�����Ϻ��к����º��� 
		{
			while(theNewPtr!=NULL)//���������ҳ�δ��Ӧ�����Ϻ��к����º���
			{
				if((theNewPtr->destination)>10 && (theNewPtr->destination)<20)//���Ϻ��� 
				{
					//�ļ��������Ļ��� 
					if(i==0)
					{
						fputs("The unreact floors up are:<",fPtr);
						printf("The unreact floors up are:<");
					}	
					fprintf(fPtr,"%d ",theNewPtr->destination%10);
					printf("%d ",theNewPtr->destination%10);
					i++;
				}
				else if(theNewPtr->destination>20)//���º���,�Ƚ���Щ���º��е�����¥��洢�������� 
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
			else//��i=0,˵��û�����Ϻ��е�¥�� 
			{
				fputs("There is no unreact floor up.\n",fPtr);
				printf("There is no unreact floor up.\n");	
			}
			if(j!=0)//�����º��� 
			{
				//�ļ��������Ļ��� 
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
			else//��j=0,˵��û�����º��� 
			{
				fputs("There is no unreact floor down.\n",fPtr);
				printf("There is no unreact floor down.\n");
			}
		}
	} 
	fclose(fPtr);
}

//DrawState3()���� 
void DrawState3()
{
	 extern struct passenger *currentPtr;
     extern int stopTime; 
     extern char callrequest;
     int i;
     extern HEGG hEggs[33];
     extern int IsSecond[];
     //����
     if(stopTime==0)
     {		
          for(i=1;i<=20;i++)
	      {   
	          SetActiveEgg(hEggs[3]);
              OffsetEgg(-5.65,0); //���������ſ�ȵ�1/20
		      SetActiveEgg(hEggs[4]);
		      OffsetEgg(5.65,0); //���������ſ�ȵ�1/20 
	      }
	      //����Ŀ�ĵغ󣬽�����Ӧ����Ʋ���������IsSecond���㡣 
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
     //�� Go='#'(���˹���)��ͣ��ʱ�䵽��5S,���ݹ���
	 if(callrequest=='#'||stopTime==5)  
 	 {     
	      
 	      for(i=1;i<=20;i++)
	      {    
	         SetActiveEgg(hEggs[3]);
	         OffsetEgg(5.65,0); //���������ſ�ȵ�1/20
	       
	         SetActiveEgg(hEggs[4]);
		     OffsetEgg(-5.65,0); //���������ſ�ȵ�1/20
	      }
      }
} 
