#include"elevator.h"
#include"egg.h"

void createFCFSlist()
{
	//ȫ�ֱ���������
	extern HEGG hEggs[];
	extern int IsSecond[];
	extern struct passenger *callPtr, *currentPtr, *last1Ptr;
	extern int State;
	extern float currentFloor;
	extern int prestrategy;
	
	struct passenger *runPtr, *prePtr;//�ֲ����������� 
	//�ֲ�������ʼ��
	if(prestrategy==0 || (prestrategy==1 && currentPtr==NULL))
	{
		if(prestrategy==1)
			prestrategy=0;
		runPtr=currentPtr;
		prePtr=currentPtr;
		
	} 
	else
	{
		runPtr=last2Ptr;
		prePtr=last2Ptr;
	}
	
	if(currentPtr==NULL && prestrategy==0)//�ýڵ��ǵ�һ���ڵ� 
	{
		currentPtr=callPtr;
		last1Ptr=callPtr;
	}
	else if(last2Ptr==NULL && prestrategy==1)
	{
		last2Ptr=callPtr;
		last2Ptr=callPtr->nextPtr;
	}
	else//�ýڵ㲻�ǵ�һ���ڵ㣬��������Ҫ�ж�����ڵ��Ƿ���Ҫ���� 
	{
		while(runPtr!=NULL && (runPtr->destination!=callPtr->destination))//������Ѱ�����Ƿ����ظ�¥�� 
		{
			if(runPtr==prePtr)//runPtr�ڵ�һ��ָ��������
				runPtr=runPtr->nextPtr;
			else
			{
				runPtr=runPtr->nextPtr;
				prePtr=prePtr->nextPtr;	
			}     		
		}
		//�ж�Ϊʲô������ѭ�����Ӷ�ȷ���Ƿ��ܹ������ýڵ� 
		if(runPtr!=NULL)//���ظ�¥�� 
		{
				//���л����еĹ����У���ǰ����С�ڰ�ȫ���룬����Ϊ��һ���ڲ����󣬴�ʱ���ܳ����ýڵ� 
				if((State==1 && fabs(currentFloor-(runPtr->destination%10))<1.1 && currentFloor<(runPtr->destination%10) && prePtr->destination==runPtr->destination)
	         	||(State==2 && fabs(currentFloor-(runPtr->destination%10))<1.1 && currentFloor>(runPtr->destination%10)&& prePtr->destination==runPtr->destination))
				{
					//�õ�ʼ�ձ������ŵ�״̬���ͷ��û�����Ľڵ� 
					SetActiveEgg(hEggs[23+(currentPtr->destination)]);
					ShowEgg(1);
                    IsSecond[23+(currentPtr->destination)]=1;
					free(callPtr);
					callPtr=NULL;
				}
				else//��������¿��Գ����ڵ� 
				{
					if(runPtr->nextPtr==NULL)//��������һ���ڵ㣬Ҫ��������һ���ڵ� 
				    	last1Ptr=prePtr;
					if(prePtr==runPtr)//���ȡ�����ǵ�һ���ڵ� 
					{
						if(prestrategy==0)
							currentPtr=prePtr->nextPtr;
						else
							last2Ptr=prePtr->nextPtr;
						free(runPtr);
					}
					else
					{
						prePtr->nextPtr=runPtr->nextPtr;
         				free(runPtr);
         				runPtr=NULL;
					}	
				}		
		}
		else//���µĽڵ���뵽ָ������ 
		{
			if(prestrategy==0)
			{
				last1Ptr->nextPtr=callPtr;
				last1Ptr=callPtr;	
			}
			else
			{
				last2Ptr->nextPtr=callPtr;
				last2Ptr=callPtr;
			}
		}
	}
	callPtr=NULL;
}


//˳����񴴽������� 
void createBTWSlist()
{
	//ȫ�ֱ��������� 
	extern struct passenger *callPtr;
	extern struct passenger *currentPtr, *midPtr, *lastPtr, *last2Ptr;
	extern int State;
	extern int direction;
	extern float currentFloor;
	extern int prestrategy;
	//�ֲ����������� 
	struct passenger *runPtr, *prePtr, *putinPtr, *preputinPtr, *rPtr;
	
	if(currentPtr==NULL)//��һ��ָ�� 
	{
		currentPtr=callPtr;
		lastPtr=callPtr;
		last2Ptr=callPtr;
	}
	else
	{
		runPtr=currentPtr;         //�ֲ�������ʼ�� 
		prePtr=currentPtr;	
		
		//������Ѱ���ж��Ƿ�����Ҫ�����Ľڵ�
		while(runPtr!=NULL && runPtr->destination!=callPtr->destination)
		{
			if(runPtr==prePtr)
				runPtr=runPtr->nextPtr;
			else
			{
				runPtr=runPtr->nextPtr;
				prePtr=prePtr->nextPtr;
			}
		}
		//�жϳ�ѭ�����������Դ��ж��ǳ����ڵ㻹�ǲ���ڵ�
		if(runPtr!=NULL)//��Ҫ�����ڵ�
		{
			//С�ڰ�ȫ���룬���ܳ��� 
			if((State==1 && fabs(currentFloor-(runPtr->destination))<1.1 && currentFloor<runPtr->destination && runPtr==prePtr)
    		 ||(State==2 && fabs(currentFloor-(runPtr->destination))<1.1 && currentFloor>runPtr->destination && runPtr==prePtr))
		 	{
		 		//�õ�ʼ�ձ������ŵ�״̬���ͷ��û�����Ľڵ�
		 		if(currentPtr->destination<10)
		 		{
					SetActiveEgg(hEggs[23+(currentPtr->destination)]);
					ShowEgg(1);
                    IsSecond[23+(currentPtr->destination)]=1;
		 		}
		 		else if(currentPtr->destination>20)
		 		{
		 			SetActiveEgg(hEggs[25-(currentPtr->destination%10)]);
	    			ShowEgg(1);
    				IsSecond[25-(currentPtr->destination)%10]=1;
		 		}
		 		else
			 	{
		 			SetActiveEgg(hEggs[16-(currentPtr->destination%10)]);
  					ShowEgg(1);
   					IsSecond[16-(currentPtr->destination)%10]=1;
		 		}
		 		printf("It can't be deleted!\n"); 
 		    	free(callPtr);
				callPtr=NULL;	
 		    }
 		    else//��ɾ���ڵ�
			{
				if(runPtr==midPtr)//Ҫ������м�һ��ָ��ĵ�ַ
					midPtr=runPtr->nextPtr;
				if(runPtr->nextPtr==NULL)//���������һ��ָ��ĵ�ַ
			 		lastPtr=prePtr;
	 			if(currentPtr->nextPtr==NULL)//ֻ��һ���ڵ㻹Ҫɾ��
	 			{
			 		free(runPtr);
			 		runPtr=NULL;
			 		currentPtr=NULL;
			 		callPtr=NULL;
			 	}
			 	else
			 	{	
					if(prePtr==runPtr)//���ȡ�����ǵ�һ���ڵ� 
					{
						currentPtr=prePtr->nextPtr;
						free(runPtr);
					}
					else
					{
						prePtr->nextPtr=runPtr->nextPtr;
         				free(runPtr);
         				runPtr=NULL;
					}
	 			}
			} 
		}
		else//��Ҫ����ڵ� 
		{
			if(direction==0)//���ݵ��������з��������ϵ�
			{
				//�����з����� 
				if(currentFloor<(callPtr->destination%10) && callPtr->destination<20)
				{ 
					//���ú����ҵ�����ڵ��λ�� 
					preputinPtr=FTPPtr(currentPtr,callPtr,1);
					putinPtr=preputinPtr->nextPtr;
					//����ڵ� 
					if((preputinPtr->destination%10)<(callPtr->destination%10))
					{
						preputinPtr->nextPtr=callPtr;
						callPtr->nextPtr=putinPtr;
					}
					else//�ǵ�һ�����ڵ�ǰ¥���Ŀ��¥�㣬���뵽��һ���ڵ� 
					{
						callPtr->nextPtr=currentPtr;
						currentPtr=callPtr;
					}
					if(putinPtr==NULL)//��������һ��ָ�� 
					{
						lastPtr=preputinPtr->nextPtr;
						last2Ptr=preputinPtr->nextPtr;
					}	
				}
				else //�������з����� 
				{
					if(midPtr==NULL)
					{
						midPtr=callPtr;
						lastPtr->nextPtr=midPtr;
						last2Ptr=midPtr;
					}
					else
					{
						//�������� 
						if(callPtr->destination>20)
						{
							//���ú����ҵ�����λ��
							preputinPtr=FTPPtr(midPtr,callPtr,2);
							putinPtr=preputinPtr->nextPtr;
							//������
							if((callPtr->destination%10)<(preputinPtr->destination%10))
							{
								callPtr->nextPtr=putinPtr;
								preputinPtr->nextPtr=callPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;	
							}
							else//�ǵ�һ��С�ڵ�ǰ¥���Ŀ��¥�㣬���뵽��ͬ�����ϵĵ�һ���ڵ�
							{ 
								callPtr->nextPtr=midPtr;
								lastPtr->nextPtr=callPtr;
								midPtr=callPtr;
							}		
						}
						else
						{
							//���ú����ҵ�����ڵ��λ�� 
							preputinPtr=FTPPtr(last2Ptr,callPtr,1);
							putinPtr=preputinPtr->nextPtr;
							//����ڵ� 
							if((preputinPtr->destination%10)<(callPtr->destination%10))
							{
								preputinPtr->nextPtr=callPtr;
								callPtr->nextPtr=putinPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;
							}
							else//�ǵ�һ�����ڲ�ͬ����¥���Ŀ��¥�㣬���뵽���һ���ڵ� 
							{
								if(preputinPtr->destination<20)
								{
									if(midPtr==NULL)
									{
										lastPtr->nextPtr=callPtr;
										callPtr->nextPtr=midPtr;
										midPtr=callPtr;
									}
									else
									{
										rPtr=midPtr;
										while(rPtr->nextPtr!=last2Ptr)
											rPtr=rPtr->nextPtr;
										rPtr->nextPtr=callPtr;
										callPtr->nextPtr=last2Ptr;
										last2Ptr=callPtr;
									}
									
								}
								else
								{
									last2Ptr->nextPtr=callPtr;
									last2Ptr=callPtr;
								}
								
							}	
						}				 
					 }		
				  } 
			 }
			 else//���ݵ��������з��������µ�
			 {
			 	 //�����з����� 
 			     if(currentFloor>(callPtr->destination%10) && (callPtr->destination>20 || callPtr->destination<10))
				 {
 				 	 //���ú����ҵ�����ڵ��λ�� 
					preputinPtr=FTPPtr(currentPtr,callPtr,2);
					putinPtr=preputinPtr->nextPtr;
					//����ڵ� 
					if((preputinPtr->destination%10)>(callPtr->destination%10))
					{
						preputinPtr->nextPtr=callPtr;
						callPtr->nextPtr=putinPtr;
					}
					else//�ǵ�һ�����ڵ�ǰ¥���Ŀ��¥�㣬���뵽��һ���ڵ� 
					{
						callPtr->nextPtr=currentPtr;
						currentPtr=callPtr;
					}
					if(putinPtr==NULL)//��������һ��ָ�� 
					{
						lastPtr=preputinPtr->nextPtr;
						last2Ptr=preputinPtr->nextPtr;
					}		
 				 }
				 else//�������з�����
				 {
					if(midPtr==NULL)
					{
						midPtr=callPtr;
						lastPtr->nextPtr=midPtr;
						last2Ptr=midPtr;
					}
					else
					{
						if(callPtr->destination<20)
						{
							//���ú����ҵ�����λ��
							preputinPtr=FTPPtr(midPtr,callPtr,1);
							putinPtr=preputinPtr->nextPtr;
							//������
							if((callPtr->destination%10)>(preputinPtr->destination%10))
							{
								callPtr->nextPtr=putinPtr;
								preputinPtr->nextPtr=callPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;	
							}
							else//�ǵ�һ�����ڵ�ǰ¥���Ŀ��¥�㣬���뵽��ͬ�����ϵĵ�һ���ڵ�
							{ 
								callPtr->nextPtr=midPtr;
								lastPtr->nextPtr=callPtr;
								midPtr=callPtr;
							}			
						}
						else
						{
							//���ú����ҵ�����ڵ��λ�� 
							preputinPtr=FTPPtr(last2Ptr,callPtr,2);
							putinPtr=preputinPtr->nextPtr;
							//����ڵ� 
							if((preputinPtr->destination%10)>(callPtr->destination%10))
							{
								preputinPtr->nextPtr=callPtr;
								callPtr->nextPtr=putinPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;
							}
							else//�ǵ�һ�����ڲ�ͬ����¥���Ŀ��¥�㣬���뵽���һ���ڵ� 
							{
								if(preputinPtr->destination>20)
								{
									if(midPtr==NULL)
									{
										lastPtr->nextPtr=callPtr;
										callPtr->nextPtr=midPtr;
										midPtr=callPtr;
									}
									else
									{
										rPtr=midPtr;
										while(rPtr->nextPtr!=last2Ptr)
											rPtr=rPtr->nextPtr;
										rPtr->nextPtr=callPtr;
										callPtr->nextPtr=last2Ptr;
										last2Ptr=callPtr;
									}
								}
								else 
								{
									last2Ptr->nextPtr=callPtr;
									last2Ptr=callPtr;
								}			
							}
								
						}			 
					 }		
				  } 		
 			 } 
		} 
	}
	callPtr=NULL;	
}


//Ѱ�Ҳ���ڵ�λ�õĺ���
struct passenger *FTPPtr(struct passenger *currentPtr, struct passenger *callPtr, int State)
{
	
 	//�ֲ������������ͳ�ʼ�� 
 	struct passenger *runPtr, *prePtr;
 	runPtr=currentPtr;
 	prePtr=currentPtr;
 	
 	//���ݴ�������״̬ 
 	if(State==1)
 	{
 		//������Ѱ���ҵ���Ҫ����ڵ��λ�á� 
	 	while(runPtr!=NULL && (runPtr->destination%10)<(callPtr->destination%10) && runPtr->destination<20)//������Ѱ���ҵ�����ڵ��λ�� 
	 	{
	 		if(runPtr==prePtr)
 		    	runPtr=runPtr->nextPtr;
   			else
   			{
			   	runPtr=runPtr->nextPtr;
			   	prePtr=prePtr->nextPtr;
	   		}
	 	}
	 	return prePtr;
 	}
 	//���ݴ�������״̬ 
 	else 
	{
		//������Ѱ���ҵ���Ҫ����ڵ��λ�á� 
		while(runPtr!=NULL && ((runPtr->destination%10)>(callPtr->destination%10)) && (runPtr->destination>20 || runPtr->destination<10))//������Ѱ���ҵ�����ڵ��λ��
	 	{
	 		if(runPtr==prePtr)
 		    	runPtr=runPtr->nextPtr;
   			else
   			{
			   	runPtr=runPtr->nextPtr;
			   	prePtr=prePtr->nextPtr;
	   		}
	 	}
	 	return prePtr;
	}	
}
