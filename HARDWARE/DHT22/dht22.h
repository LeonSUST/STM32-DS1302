#ifndef __DHT22_H
#define __DHT22_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DHT22������ʪ�ȴ�������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO��������
#define DHT22_IO_IN()  {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=8<<12;}
#define DHT22_IO_OUT() {GPIOB->CRL&=0XFFFF0FFF;GPIOB->CRL|=3<<12;}
////IO��������											   
#define	DHT22_DQ_OUT PBout(3) //���ݶ˿�	PB3 
#define	DHT22_DQ_IN  PBin(3)  //���ݶ˿�	PB3 


u8 DHT22_Init(void);//��ʼ��DHT22
u8 DHT22_Read_Data(u16 *temp,u16 *humi);//��ȡ��ʪ��
u8 DHT22_Read_Byte(void);//����һ���ֽ�
u8 DHT22_Read_Bit(void);//����һ��λ
u8 DHT22_Check(void);//����Ƿ����DHT22
void DHT22_Rst(void);//��λDHT22    
#endif















