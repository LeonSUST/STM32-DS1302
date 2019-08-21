#include "stdio.h"
#include "ds1302.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

u8 read[] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};//读秒、分、时、日、月、周、年的寄存器地址
u8 write[] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};//写秒、分、时、日、月、周、年的寄存器地址
/*******************引脚配置******************************************/
void ds1302_GPIO_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOG, ENABLE);//使能时钟	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; //REST		
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;				  //E5-DATA，因为要求双向传输，所以设置为开漏
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;//DATA
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//SCLK 		
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
}
/*****************************************************************/
/********************发送八位数据*********************************/
void Sendchar(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SCLK = 0;//拉低时钟线，准备发送数据
				if(dat & 0x01)//判断数据最后一位是高还是低
					DATA=1;
				else
					DATA=0;
				dat >>= 1;//右移准备发送下一位
				SCLK = 1;//拉高时钟线，数据成功发送
	}
}
/********************************************************************/
/*************************************************读取八位数据******************************************************************/
u8 Readchar()
{
	u8 Return_dat,i;
	for(i=0;i<8;i++)
	{																						
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)//判断数据线状态是高还是低，注意一定是	GPIO_ReadInputDataBit，		
			Return_dat = Return_dat|0x80;//如果是高电平，取出数据，不是的话不需要取，默认是低电平
		SCLK = 1;//时钟线拉高，准备取出数据
		Return_dat >>= 1;//右移一位准备接受下一位数据
		SCLK = 0;//时钟线拉低，取出数据
	}
	DATA = 0;//这里很重要，在接受八位数据之后一定要放开数据线，否则读回全是0或者85，datasheet上面没写这一点。很多人都卡这里了
	return Return_dat;//传回接收到的八位数据
}
/********************************************************************************************************************************/
/*****************在指定八位地址中写入八位数据******************/
void write_data_to_add(u8 add,u8 dat)											
{	 	
	RESET=0;//复位线拉低
	SCLK=0;//时钟线拉低
	RESET=1;//复位线拉高，准备传输
	Sendchar(add);//发送八位地址
	Sendchar(dat);//发送八位命令或者数据
	SCLK=1;//上升沿把数据送走
	RESET=0;//拉低复位线，传输结束
}
/**************************************************************/
/******************DS1302初始化，初始化时钟********************/
void ds1302_init()				
{														
	write_data_to_add(0x8e,0x00);//关闭写保护
	write_data_to_add(0x80,((21/10)<<4|(21%10)));//秒
	write_data_to_add(0x82,((28/10)<<4|(28%10)));//分钟
	write_data_to_add(0x84,((15/10)<<4|(15%10)));//小时
	write_data_to_add(0x86,((3/10)<<4|(3%10)));//日
	write_data_to_add(0x88,((4/10)<<4|(4%10)));//月
	write_data_to_add(0x8a,3);//星期
	write_data_to_add(0x8c,((19/10)<<4|(19%10)));//年              
	write_data_to_add(0x8e,0x80);	//打开写保护
}
/**************************************************************/
/***************从DS1302中读取八位数据，add为目标地址**********/
u8 read_data_from_1302(u8 add)										          	
{
	u8 i,Return_dat;
	RESET=0;//复位线拉低
	SCLK=0;//时钟线拉低
	RESET=1;//复位线拉高，准备传输
	Sendchar(add);//发送八位地址
	Return_dat=Readchar();//从刚刚发送的八位地址中读出数据
	i=Return_dat/16;//分离出十六进制的高四位
	Return_dat=Return_dat%16;//分离出十六进制的低四位
	Return_dat=i*10+Return_dat;//整合成十进制
	return Return_dat;	//传回数据
	}
/**************************************************************/
extern u8 gewei[7],shiwei[7];
/**************从DS1302中读取八位数据并用串口打印出来*************/
void ds1302_print_data(u8 *read)												 
{
	u8 i=0;
	for(i=0;i<7;i++)//循环七次读出时间寄存器的数据
	{
		shiwei[i]=read_data_from_1302(read[i]);												
	}
	for(i=0;i<7;i++)//分离出十位和个位
	{								
		gewei[i]=shiwei[i]%10;
		shiwei[i]=shiwei[i]/10;
	}
}
