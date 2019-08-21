#include "stdio.h"
#include "ds1302.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

u8 read[] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};//���롢�֡�ʱ���ա��¡��ܡ���ļĴ�����ַ
u8 write[] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};//д�롢�֡�ʱ���ա��¡��ܡ���ļĴ�����ַ
/*******************��������******************************************/
void ds1302_GPIO_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOG, ENABLE);//ʹ��ʱ��	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; //REST		
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;				  //E5-DATA����ΪҪ��˫���䣬��������Ϊ��©
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;//DATA
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;//SCLK 		
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
}
/*****************************************************************/
/********************���Ͱ�λ����*********************************/
void Sendchar(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SCLK = 0;//����ʱ���ߣ�׼����������
				if(dat & 0x01)//�ж��������һλ�Ǹ߻��ǵ�
					DATA=1;
				else
					DATA=0;
				dat >>= 1;//����׼��������һλ
				SCLK = 1;//����ʱ���ߣ����ݳɹ�����
	}
}
/********************************************************************/
/*************************************************��ȡ��λ����******************************************************************/
u8 Readchar()
{
	u8 Return_dat,i;
	for(i=0;i<8;i++)
	{																						
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==1)//�ж�������״̬�Ǹ߻��ǵͣ�ע��һ����	GPIO_ReadInputDataBit��		
			Return_dat = Return_dat|0x80;//����Ǹߵ�ƽ��ȡ�����ݣ����ǵĻ�����Ҫȡ��Ĭ���ǵ͵�ƽ
		SCLK = 1;//ʱ�������ߣ�׼��ȡ������
		Return_dat >>= 1;//����һλ׼��������һλ����
		SCLK = 0;//ʱ�������ͣ�ȡ������
	}
	DATA = 0;//�������Ҫ���ڽ��ܰ�λ����֮��һ��Ҫ�ſ������ߣ��������ȫ��0����85��datasheet����ûд��һ�㡣�ܶ��˶���������
	return Return_dat;//���ؽ��յ��İ�λ����
}
/********************************************************************************************************************************/
/*****************��ָ����λ��ַ��д���λ����******************/
void write_data_to_add(u8 add,u8 dat)											
{	 	
	RESET=0;//��λ������
	SCLK=0;//ʱ��������
	RESET=1;//��λ�����ߣ�׼������
	Sendchar(add);//���Ͱ�λ��ַ
	Sendchar(dat);//���Ͱ�λ�����������
	SCLK=1;//�����ذ���������
	RESET=0;//���͸�λ�ߣ��������
}
/**************************************************************/
/******************DS1302��ʼ������ʼ��ʱ��********************/
void ds1302_init()				
{														
	write_data_to_add(0x8e,0x00);//�ر�д����
	write_data_to_add(0x80,((21/10)<<4|(21%10)));//��
	write_data_to_add(0x82,((28/10)<<4|(28%10)));//����
	write_data_to_add(0x84,((15/10)<<4|(15%10)));//Сʱ
	write_data_to_add(0x86,((3/10)<<4|(3%10)));//��
	write_data_to_add(0x88,((4/10)<<4|(4%10)));//��
	write_data_to_add(0x8a,3);//����
	write_data_to_add(0x8c,((19/10)<<4|(19%10)));//��              
	write_data_to_add(0x8e,0x80);	//��д����
}
/**************************************************************/
/***************��DS1302�ж�ȡ��λ���ݣ�addΪĿ���ַ**********/
u8 read_data_from_1302(u8 add)										          	
{
	u8 i,Return_dat;
	RESET=0;//��λ������
	SCLK=0;//ʱ��������
	RESET=1;//��λ�����ߣ�׼������
	Sendchar(add);//���Ͱ�λ��ַ
	Return_dat=Readchar();//�Ӹոշ��͵İ�λ��ַ�ж�������
	i=Return_dat/16;//�����ʮ�����Ƶĸ���λ
	Return_dat=Return_dat%16;//�����ʮ�����Ƶĵ���λ
	Return_dat=i*10+Return_dat;//���ϳ�ʮ����
	return Return_dat;	//��������
	}
/**************************************************************/
extern u8 gewei[7],shiwei[7];
/**************��DS1302�ж�ȡ��λ���ݲ��ô��ڴ�ӡ����*************/
void ds1302_print_data(u8 *read)												 
{
	u8 i=0;
	for(i=0;i<7;i++)//ѭ���ߴζ���ʱ��Ĵ���������
	{
		shiwei[i]=read_data_from_1302(read[i]);												
	}
	for(i=0;i<7;i++)//�����ʮλ�͸�λ
	{								
		gewei[i]=shiwei[i]%10;
		shiwei[i]=shiwei[i]/10;
	}
}
