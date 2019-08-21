/**
  ************************************* Copyright ******************************
  *'  _      _____  _____  _   _
  *' | |    |  ___||  _  || \ | | (C) Copyright 2019,CHUEnliang-Leon,China, SUST.
  *' | |    | |__  | | | ||  \| |             All Rights Reserved
  *' | |    |  __| | | | || . ` |        By(�����Ƽ���ѧ����ϵͳ�Զ���ʵ����)
  *' | |____| |___ \ \_/ /| |\  |         https://blog.csdn.net/LeonSUST
  *' \_____/\____/  \___/ \_| \_/  Mtto: Today is the first day of the rest of your life.
  *'
  * FileName   : main.c
  * Version    : v1.0
  * Author     : CHUEnliang-Leon
  * Date       : 2019-05-21
  * Description:
  ******************************************************************************
 */

#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "12864.h"
#include "ds1302.h"
#include "stdio.h"
#include "display.h"
#include "sys.h"
extern u8 write[];
extern u8 read[];
u8 gewei[7],shiwei[7];

int main(void)
{
    int i=0;
    RCC_DeInit();					//ϵͳʱ�ӳ�ʼ��
    delay_init();	    	  //��ʱ������ʼ��
    ds1302_GPIO_Configuration();	//DS1302���ų�ʼ��
    ds1302_init();        //DS1302��ʼ��
    LCD_GPIO_Init();
    LCD_Init();
    delay_ms(20);
    lcd_clear();
    delay_ms(20);
    lcd_init();
    display_pin_init();
    while(1)
    {
        u8 nianyueri[8];
        u8 shifenmiao[8];
        ds1302_print_data(read);							//ѭ����ȡDS1302ʱ��
        nianyueri[0]=2;
        nianyueri[1]=0;
        nianyueri[2]=shiwei[6];
        nianyueri[3]=gewei[6];
        nianyueri[4]=shiwei[4];
        nianyueri[5]=gewei[4];
        nianyueri[6]=shiwei[3];
        nianyueri[7]=gewei[3];
        shifenmiao[0]=shiwei[2];
        shifenmiao[1]=gewei[2];
        shifenmiao[2]=shiwei[1];
        shifenmiao[3]=gewei[1];
        shifenmiao[4]=shiwei[0];
        shifenmiao[5]=gewei[0];
        shifenmiao[6]=shiwei[5];
        shifenmiao[7]=gewei[5];
//        if(SW0) {
//            if(SW1) {
//                for(i=1; i<=8; i++) {
//                    display_xiaoying();
//                    display_weixuan(i);
//                    display_number(shifenmiao[i-1]);
//                    delay_us(200);
//                }
//            } else {
                lcd_wstr(1,0,"LEON CLOCK");
                lcd_wstr(2,0,"20");
                lcd_pos(2,1);
                write_char(0x30+shiwei[6]);
                write_char(0x30+gewei[6]);
                lcd_wstr(2,2,"��");
                write_char(0x30+shiwei[4]);
                write_char(0x30+gewei[4]);
                lcd_wstr(2,4,"��");
                write_char(0x30+shiwei[3]);
                write_char(0x30+gewei[3]);
                lcd_wstr(2,6,"��");
                lcd_pos(3,1);
                write_char(0x30+shiwei[2]);
                write_char(0x30+gewei[2]);
                lcd_wstr(3,2,"ʱ");
                write_char(0x30+shiwei[1]);
                write_char(0x30+gewei[1]);
                lcd_wstr(3,4,"��");
                write_char(0x30+shiwei[0]);
                write_char(0x30+gewei[0]);
                lcd_wstr(3,6,"��");
                lcd_pos(4,4);
                write_char(0x30+shiwei[5]);
                write_char(0x30+gewei[5]);
                lcd_wstr(4,2,"����");
//            }
//        }
//        else {
//            for(i=1; i<=8; i++) {
//                display_xiaoying();
//                display_weixuan(i);
//                display_number(nianyueri[i-1]);
//                delay_us(200);
//            }
//        }
    }
}


