#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//zigbee STM32F407开发板
//LED驱动代码	   
//源点计划@S.P.P
//技术QQ群:284711764
//创建日期:2017/1/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 源点计划 2014-2024
//All rights reserved	
//REF：@正点原子
//////////////////////////////////////////////////////////////////////////////////
	    						  
//---------------------------OLED端口定义--------------------------  					   
#define OLED_RST PBout(12) 
#define OLED_RS  PBout(14)

//使用4线串行接口时使用 
#define OLED_SCLK PBout(13)
#define OLED_SDIN PBout(15)
		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);  		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);	 
#endif  
	 







 

