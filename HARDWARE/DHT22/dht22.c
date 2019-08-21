#include "dht22.h"
#include "delay.h"
    
//复位DHT22
void DHT22_Rst(void)	   
{                 
	DHT22_IO_OUT(); 	//SET OUTPUT
	DHT22_DQ_OUT=0; 	//拉低DQ
	delay_ms(18);    	//拉低至少500us
	DHT22_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     //主机拉高20~40us
}
//等待DHT22的回应
//返回1:未检测到DHT22的存在
//返回0:存在
u8 DHT22_Check(void) 	   
{   
	u8 retry=0;
	DHT22_IO_IN();//SET INPUT	 
  while (DHT22_DQ_IN&&retry<100)//DHT22会拉低80us左右
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
  while (!DHT22_DQ_IN&&retry<100)//DHT22拉高后会再次拉高80us左右
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT22读取一个位
//返回值：1/0
u8 DHT22_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT22_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT22_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT22_DQ_IN)return 1;
	else return 0;		   
}
//从DHT22读取一个字节
//返回值：读到的数据
u8 DHT22_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT22_Read_Bit();
	}						    
	return dat;
}
//从DHT22读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT22_Read_Data(u16 *temp,u16 *humi)
{
 	u8 buf[5];
	u8 i;
	DHT22_Rst();
	if(DHT22_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT22_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=(u16)buf[0]<<8|buf[1];
			*temp=(u16)buf[2]<<8|buf[3];
		}
	}else return 1;
	return 0;	    
}
//初始化DHT22的IO口 DQ 同时检测DHT22的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT22_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	 //使能PB端口时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //PB3端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				    //初始化IO口
 	GPIO_SetBits(GPIOB,GPIO_Pin_3);						        //PB3 输出高
			    
	DHT22_Rst();  //复位DHT22
	return DHT22_Check();//等待DHT22的回应
} 
