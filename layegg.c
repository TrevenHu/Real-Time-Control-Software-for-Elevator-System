#include<stdio.h>
#include"egg.h"

//�����������ĺ��� 
 void DrawBackgroud()
{	
	extern HEGG hEggs[33];
	
	int i,r,m=0;	

	EggStart(800,485);
			
	//�����ڱ���
	hEggs[2]=LayEgg(); 
	MovePen(286,340);
	DrawBitmap("����.bmp");
	
	//������
	hEggs[3]=LayEgg(); 
	MovePen(285,342);
	DrawBitmap("����.bmp");
	
	//������ 
	hEggs[4]=LayEgg(); 
	MovePen(404,342);
	DrawBitmap("����.bmp");
	
	//���� �ٳ��ŵ�λ��	
	hEggs[1]=LayEgg();
	MovePen(0,485);
	DrawBitmap("����1.bmp");  
	MovePen(285,485);
	DrawBitmap("����2.bmp");
	MovePen(513,485);
	DrawBitmap("����3.bmp");
	//�����ȷ�����Ե����ŵİ�ť	
	hEggs[6]=LayEgg();
	MovePen(690,436);
	DrawBitmap("�����ȷ���ť.bmp");
	ShowEgg(0);

	//˳�������Ե����ŵİ�ť
	hEggs[7]=LayEgg();
	MovePen(565,436);
	DrawBitmap("˳�����ť.bmp");
	ShowEgg(0); 
	
	//���������а�ť ��8--15���� �ֱ��ʾ8--1�� 
	for(i=1;i<=8;i++)
	{
		hEggs[i+7]=LayEgg();
		MovePen(110,490-i*56);
		DrawBitmap("����ѡ��.bmp");
		ShowEgg(0);
	}
	
	//���������а�ť ��16--23��egg�ֱ��ʾ9--2�� 
	for(i=0;i<=7;i++)
	{
		if(i==0)
		{
			hEggs[16]=LayEgg();
			MovePen(138,485);
			DrawBitmap("����ѡ��.bmp");
			ShowEgg(0);
		}
		else
		{
	    	hEggs[i+16]=LayEgg();
			MovePen(138,490-i*56);
			DrawBitmap("����ѡ��.bmp");
			ShowEgg(0);	
		}
    }
	
	//�ڲ��������ְ�ť����24--32��egg 	
	hEggs[24]= LayEgg();
	MovePen(587,292);
	DrawBitmap("��ť1.bmp");
	ShowEgg(0);
	
	hEggs[25]= LayEgg();
	MovePen(650,292);
	DrawBitmap("��ť2.bmp");
	ShowEgg(0);
	
	hEggs[26]= LayEgg();
	MovePen(713,292);
	DrawBitmap("��ť3.bmp");
	ShowEgg(0);
	
	hEggs[27]= LayEgg();
	MovePen(590,226);
	DrawBitmap("��ť4.bmp");
	ShowEgg(0);
	
	hEggs[28]= LayEgg();
	MovePen(652,229);
	DrawBitmap("��ť5.bmp");
	ShowEgg(0);
	
	hEggs[29]= LayEgg();
	MovePen(718,228);
	DrawBitmap("��ť6.bmp");
	ShowEgg(0);
	
	hEggs[30]= LayEgg();
	MovePen(590,165);
	DrawBitmap("��ť7.bmp");
	ShowEgg(0);
	
	hEggs[31]= LayEgg();
	MovePen(655,165);
	DrawBitmap("��ť8.bmp");
	ShowEgg(0);
	
	hEggs[32]= LayEgg();
	MovePen(720,167);
	DrawBitmap("��ť9.bmp");
	ShowEgg(0);
}
    	

//DrawElevator()����������ʼ���ݣ���������1¥ 
void DrawElevator()
{
	extern HEGG hEggs[];
	hEggs[5]= LayEgg();
	MovePen(53,53);//���������һ¥����ʼ���� 
    DrawBitmap("���е���.bmp");//���ƶ��ĵ���
	 
} 
