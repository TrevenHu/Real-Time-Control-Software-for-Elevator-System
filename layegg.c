#include<stdio.h>
#include"egg.h"

//画动画背景的函数 
 void DrawBackgroud()
{	
	extern HEGG hEggs[33];
	
	int i,r,m=0;	

	EggStart(800,485);
			
	//画门内背景
	hEggs[2]=LayEgg(); 
	MovePen(286,340);
	DrawBitmap("门内.bmp");
	
	//画左门
	hEggs[3]=LayEgg(); 
	MovePen(285,342);
	DrawBitmap("左门.bmp");
	
	//画右门 
	hEggs[4]=LayEgg(); 
	MovePen(404,342);
	DrawBitmap("右门.bmp");
	
	//背景 抠出门的位置	
	hEggs[1]=LayEgg();
	MovePen(0,485);
	DrawBitmap("背景1.bmp");  
	MovePen(285,485);
	DrawBitmap("背景2.bmp");
	MovePen(513,485);
	DrawBitmap("背景3.bmp");
	//先来先服务策略的亮着的按钮	
	hEggs[6]=LayEgg();
	MovePen(690,436);
	DrawBitmap("先来先服务按钮.bmp");
	ShowEgg(0);

	//顺便服务策略的亮着的按钮
	hEggs[7]=LayEgg();
	MovePen(565,436);
	DrawBitmap("顺便服务按钮.bmp");
	ShowEgg(0); 
	
	//画亮的上行按钮 第8--15个蛋 分别表示8--1层 
	for(i=1;i<=8;i++)
	{
		hEggs[i+7]=LayEgg();
		MovePen(110,490-i*56);
		DrawBitmap("上行选择.bmp");
		ShowEgg(0);
	}
	
	//画亮的下行按钮 第16--23个egg分别表示9--2层 
	for(i=0;i<=7;i++)
	{
		if(i==0)
		{
			hEggs[16]=LayEgg();
			MovePen(138,485);
			DrawBitmap("下行选择.bmp");
			ShowEgg(0);
		}
		else
		{
	    	hEggs[i+16]=LayEgg();
			MovePen(138,490-i*56);
			DrawBitmap("下行选择.bmp");
			ShowEgg(0);	
		}
    }
	
	//内部亮的数字按钮，第24--32个egg 	
	hEggs[24]= LayEgg();
	MovePen(587,292);
	DrawBitmap("按钮1.bmp");
	ShowEgg(0);
	
	hEggs[25]= LayEgg();
	MovePen(650,292);
	DrawBitmap("按钮2.bmp");
	ShowEgg(0);
	
	hEggs[26]= LayEgg();
	MovePen(713,292);
	DrawBitmap("按钮3.bmp");
	ShowEgg(0);
	
	hEggs[27]= LayEgg();
	MovePen(590,226);
	DrawBitmap("按钮4.bmp");
	ShowEgg(0);
	
	hEggs[28]= LayEgg();
	MovePen(652,229);
	DrawBitmap("按钮5.bmp");
	ShowEgg(0);
	
	hEggs[29]= LayEgg();
	MovePen(718,228);
	DrawBitmap("按钮6.bmp");
	ShowEgg(0);
	
	hEggs[30]= LayEgg();
	MovePen(590,165);
	DrawBitmap("按钮7.bmp");
	ShowEgg(0);
	
	hEggs[31]= LayEgg();
	MovePen(655,165);
	DrawBitmap("按钮8.bmp");
	ShowEgg(0);
	
	hEggs[32]= LayEgg();
	MovePen(720,167);
	DrawBitmap("按钮9.bmp");
	ShowEgg(0);
}
    	

//DrawElevator()函数，画起始电梯，即空闲在1楼 
void DrawElevator()
{
	extern HEGG hEggs[];
	hEggs[5]= LayEgg();
	MovePen(53,53);//计算电梯在一楼的起始坐标 
    DrawBitmap("滑行电梯.bmp");//画移动的电梯
	 
} 
