#include "display.h"


void display_pin_init(){

	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE, ENABLE);// πƒ‹ ±÷”	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_0; 	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_7|GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}
void display_number(u8 num){
	switch (num)
	{
		case 0:A=0,B=0,C=0,D=0,E=0,F=0,G=1,DP=1;break;
		case 1:A=1,B=0,C=0,D=1,E=1,F=1,G=1,DP=1;break;
		case 2:A=0,B=0,C=1,D=0,E=0,F=1,G=0,DP=1;break;
		case 3:A=0,B=0,C=0,D=0,E=1,F=1,G=0,DP=1;break;
		case 4:A=1,B=0,C=0,D=1,E=1,F=0,G=0,DP=1;break;
		case 5:A=0,B=1,C=0,D=0,E=1,F=0,G=0,DP=1;break;
		case 6:A=0,B=1,C=0,D=0,E=0,F=0,G=0,DP=1;break;
		case 7:A=0,B=0,C=0,D=1,E=1,F=1,G=1,DP=1;break;
		case 8:A=0,B=0,C=0,D=0,E=0,F=0,G=0,DP=1;break;	
		case 9:A=0,B=0,C=0,D=0,E=1,F=0,G=0,DP=1;break;
	}
}
void display_weixuan(u8 num){
	switch(num)
	{
		case 1:WEI1=1,WEI2=0,WEI3=0,WEI4=0,WEI5=0,WEI6=0,WEI7=0,WEI8=0;break;
		case 2:WEI1=0,WEI2=1,WEI3=0,WEI4=0,WEI5=0,WEI6=0,WEI7=0,WEI8=0;break;
		case 3:WEI1=0,WEI2=0,WEI3=1,WEI4=0,WEI5=0,WEI6=0,WEI7=0,WEI8=0;break;
		case 4:WEI1=0,WEI2=0,WEI3=0,WEI4=1,WEI5=0,WEI6=0,WEI7=0,WEI8=0;break;
		case 5:WEI1=0,WEI2=0,WEI3=0,WEI4=0,WEI5=1,WEI6=0,WEI7=0,WEI8=0;break;
		case 6:WEI1=0,WEI2=0,WEI3=0,WEI4=0,WEI5=0,WEI6=1,WEI7=0,WEI8=0;break;
		case 7:WEI1=0,WEI2=0,WEI3=0,WEI4=0,WEI5=0,WEI6=0,WEI7=1,WEI8=0;break;
		case 8:WEI1=0,WEI2=0,WEI3=0,WEI4=0,WEI5=0,WEI6=0,WEI7=0,WEI8=1;break;
	}
}
void display_xiaoying(){
	WEI1=0,WEI2=0,WEI3=0,WEI4=0,WEI5=0,WEI6=0,WEI7=0,WEI8=0;
}
