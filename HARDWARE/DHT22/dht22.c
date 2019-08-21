#include "dht22.h"
#include "delay.h"
    
//��λDHT22
void DHT22_Rst(void)	   
{                 
	DHT22_IO_OUT(); 	//SET OUTPUT
	DHT22_DQ_OUT=0; 	//����DQ
	delay_ms(18);    	//��������500us
	DHT22_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     //��������20~40us
}
//�ȴ�DHT22�Ļ�Ӧ
//����1:δ��⵽DHT22�Ĵ���
//����0:����
u8 DHT22_Check(void) 	   
{   
	u8 retry=0;
	DHT22_IO_IN();//SET INPUT	 
  while (DHT22_DQ_IN&&retry<100)//DHT22������80us����
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
  while (!DHT22_DQ_IN&&retry<100)//DHT22���ߺ���ٴ�����80us����
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//��DHT22��ȡһ��λ
//����ֵ��1/0
u8 DHT22_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT22_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT22_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT22_DQ_IN)return 1;
	else return 0;		   
}
//��DHT22��ȡһ���ֽ�
//����ֵ������������
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
//��DHT22��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT22_Read_Data(u16 *temp,u16 *humi)
{
 	u8 buf[5];
	u8 i;
	DHT22_Rst();
	if(DHT22_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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
//��ʼ��DHT22��IO�� DQ ͬʱ���DHT22�Ĵ���
//����1:������
//����0:����    	 
u8 DHT22_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��PB�˿�ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				  //PB3�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				    //��ʼ��IO��
 	GPIO_SetBits(GPIOB,GPIO_Pin_3);						        //PB3 �����
			    
	DHT22_Rst();  //��λDHT22
	return DHT22_Check();//�ȴ�DHT22�Ļ�Ӧ
} 
