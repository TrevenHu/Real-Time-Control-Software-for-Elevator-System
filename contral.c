#include"elevator.h"
#include"egg.h"

void createFCFSlist()
{
	//全局变量的声明
	extern HEGG hEggs[];
	extern int IsSecond[];
	extern struct passenger *callPtr, *currentPtr, *last1Ptr;
	extern int State;
	extern float currentFloor;
	extern int prestrategy;
	
	struct passenger *runPtr, *prePtr;//局部变量的声明 
	//局部变量初始化
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
	
	if(currentPtr==NULL && prestrategy==0)//该节点是第一个节点 
	{
		currentPtr=callPtr;
		last1Ptr=callPtr;
	}
	else if(last2Ptr==NULL && prestrategy==1)
	{
		last2Ptr=callPtr;
		last2Ptr=callPtr->nextPtr;
	}
	else//该节点不是第一个节点，则首先需要判断这个节点是否需要撤销 
	{
		while(runPtr!=NULL && (runPtr->destination!=callPtr->destination))//遍历搜寻，看是否有重复楼层 
		{
			if(runPtr==prePtr)//runPtr在第一个指针上运行
				runPtr=runPtr->nextPtr;
			else
			{
				runPtr=runPtr->nextPtr;
				prePtr=prePtr->nextPtr;	
			}     		
		}
		//判断为什么会跳出循环，从而确定是否能够撤销该节点 
		if(runPtr!=NULL)//有重复楼层 
		{
				//上行或下行的过程中，当前距离小于安全距离，并且为第一个内部请求，此时不能撤销该节点 
				if((State==1 && fabs(currentFloor-(runPtr->destination%10))<1.1 && currentFloor<(runPtr->destination%10) && prePtr->destination==runPtr->destination)
	         	||(State==2 && fabs(currentFloor-(runPtr->destination%10))<1.1 && currentFloor>(runPtr->destination%10)&& prePtr->destination==runPtr->destination))
				{
					//让灯始终保持亮着的状态，释放用户请求的节点 
					SetActiveEgg(hEggs[23+(currentPtr->destination)]);
					ShowEgg(1);
                    IsSecond[23+(currentPtr->destination)]=1;
					free(callPtr);
					callPtr=NULL;
				}
				else//其余情况下可以撤销节点 
				{
					if(runPtr->nextPtr==NULL)//如果是最后一个节点，要保存好最后一个节点 
				    	last1Ptr=prePtr;
					if(prePtr==runPtr)//如果取消的是第一个节点 
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
		else//将新的节点插入到指针的最后 
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


//顺便服务创建链表函数 
void createBTWSlist()
{
	//全局变量的声明 
	extern struct passenger *callPtr;
	extern struct passenger *currentPtr, *midPtr, *lastPtr, *last2Ptr;
	extern int State;
	extern int direction;
	extern float currentFloor;
	extern int prestrategy;
	//局部变量的声明 
	struct passenger *runPtr, *prePtr, *putinPtr, *preputinPtr, *rPtr;
	
	if(currentPtr==NULL)//第一个指针 
	{
		currentPtr=callPtr;
		lastPtr=callPtr;
		last2Ptr=callPtr;
	}
	else
	{
		runPtr=currentPtr;         //局部变量初始化 
		prePtr=currentPtr;	
		
		//遍历搜寻，判断是否是需要消除的节点
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
		//判断出循环的条件，以此判断是撤销节点还是插入节点
		if(runPtr!=NULL)//需要撤销节点
		{
			//小于安全距离，不能撤销 
			if((State==1 && fabs(currentFloor-(runPtr->destination))<1.1 && currentFloor<runPtr->destination && runPtr==prePtr)
    		 ||(State==2 && fabs(currentFloor-(runPtr->destination))<1.1 && currentFloor>runPtr->destination && runPtr==prePtr))
		 	{
		 		//让灯始终保持亮着的状态，释放用户请求的节点
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
 		    else//能删除节点
			{
				if(runPtr==midPtr)//要保存好中间一个指针的地址
					midPtr=runPtr->nextPtr;
				if(runPtr->nextPtr==NULL)//保护好最后一个指针的地址
			 		lastPtr=prePtr;
	 			if(currentPtr->nextPtr==NULL)//只有一个节点还要删掉
	 			{
			 		free(runPtr);
			 		runPtr=NULL;
			 		currentPtr=NULL;
			 		callPtr=NULL;
			 	}
			 	else
			 	{	
					if(prePtr==runPtr)//如果取消的是第一个节点 
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
		else//需要插入节点 
		{
			if(direction==0)//电梯的整体运行方向是向上的
			{
				//在运行方向上 
				if(currentFloor<(callPtr->destination%10) && callPtr->destination<20)
				{ 
					//调用函数找到插入节点的位置 
					preputinPtr=FTPPtr(currentPtr,callPtr,1);
					putinPtr=preputinPtr->nextPtr;
					//插入节点 
					if((preputinPtr->destination%10)<(callPtr->destination%10))
					{
						preputinPtr->nextPtr=callPtr;
						callPtr->nextPtr=putinPtr;
					}
					else//是第一个大于当前楼层的目标楼层，插入到第一个节点 
					{
						callPtr->nextPtr=currentPtr;
						currentPtr=callPtr;
					}
					if(putinPtr==NULL)//保存好最后一个指针 
					{
						lastPtr=preputinPtr->nextPtr;
						last2Ptr=preputinPtr->nextPtr;
					}	
				}
				else //不在运行方向上 
				{
					if(midPtr==NULL)
					{
						midPtr=callPtr;
						lastPtr->nextPtr=midPtr;
						last2Ptr=midPtr;
					}
					else
					{
						//下行请求 
						if(callPtr->destination>20)
						{
							//调用函数找到插入位置
							preputinPtr=FTPPtr(midPtr,callPtr,2);
							putinPtr=preputinPtr->nextPtr;
							//插入结点
							if((callPtr->destination%10)<(preputinPtr->destination%10))
							{
								callPtr->nextPtr=putinPtr;
								preputinPtr->nextPtr=callPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;	
							}
							else//是第一个小于当前楼层的目标楼层，插入到不同方向上的第一个节点
							{ 
								callPtr->nextPtr=midPtr;
								lastPtr->nextPtr=callPtr;
								midPtr=callPtr;
							}		
						}
						else
						{
							//调用函数找到插入节点的位置 
							preputinPtr=FTPPtr(last2Ptr,callPtr,1);
							putinPtr=preputinPtr->nextPtr;
							//插入节点 
							if((preputinPtr->destination%10)<(callPtr->destination%10))
							{
								preputinPtr->nextPtr=callPtr;
								callPtr->nextPtr=putinPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;
							}
							else//是第一个大于不同方向楼层的目标楼层，插入到最后一个节点 
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
			 else//电梯的整体运行方向是向下的
			 {
			 	 //在运行方向上 
 			     if(currentFloor>(callPtr->destination%10) && (callPtr->destination>20 || callPtr->destination<10))
				 {
 				 	 //调用函数找到插入节点的位置 
					preputinPtr=FTPPtr(currentPtr,callPtr,2);
					putinPtr=preputinPtr->nextPtr;
					//插入节点 
					if((preputinPtr->destination%10)>(callPtr->destination%10))
					{
						preputinPtr->nextPtr=callPtr;
						callPtr->nextPtr=putinPtr;
					}
					else//是第一个大于当前楼层的目标楼层，插入到第一个节点 
					{
						callPtr->nextPtr=currentPtr;
						currentPtr=callPtr;
					}
					if(putinPtr==NULL)//保存好最后一个指针 
					{
						lastPtr=preputinPtr->nextPtr;
						last2Ptr=preputinPtr->nextPtr;
					}		
 				 }
				 else//不在运行方向上
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
							//调用函数找到插入位置
							preputinPtr=FTPPtr(midPtr,callPtr,1);
							putinPtr=preputinPtr->nextPtr;
							//插入结点
							if((callPtr->destination%10)>(preputinPtr->destination%10))
							{
								callPtr->nextPtr=putinPtr;
								preputinPtr->nextPtr=callPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;	
							}
							else//是第一个大于当前楼层的目标楼层，插入到不同方向上的第一个节点
							{ 
								callPtr->nextPtr=midPtr;
								lastPtr->nextPtr=callPtr;
								midPtr=callPtr;
							}			
						}
						else
						{
							//调用函数找到插入节点的位置 
							preputinPtr=FTPPtr(last2Ptr,callPtr,2);
							putinPtr=preputinPtr->nextPtr;
							//插入节点 
							if((preputinPtr->destination%10)>(callPtr->destination%10))
							{
								preputinPtr->nextPtr=callPtr;
								callPtr->nextPtr=putinPtr;
								if(callPtr->nextPtr==NULL)
									last2Ptr=callPtr;
							}
							else//是第一个大于不同方向楼层的目标楼层，插入到最后一个节点 
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


//寻找插入节点位置的函数
struct passenger *FTPPtr(struct passenger *currentPtr, struct passenger *callPtr, int State)
{
	
 	//局部变量的声明和初始化 
 	struct passenger *runPtr, *prePtr;
 	runPtr=currentPtr;
 	prePtr=currentPtr;
 	
 	//电梯处于上行状态 
 	if(State==1)
 	{
 		//遍历搜寻，找到需要插入节点的位置。 
	 	while(runPtr!=NULL && (runPtr->destination%10)<(callPtr->destination%10) && runPtr->destination<20)//遍历搜寻，找到插入节点的位置 
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
 	//电梯处于下行状态 
 	else 
	{
		//遍历搜寻，找到需要插入节点的位置。 
		while(runPtr!=NULL && ((runPtr->destination%10)>(callPtr->destination%10)) && (runPtr->destination>20 || runPtr->destination<10))//遍历搜寻，找到插入节点的位置
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
