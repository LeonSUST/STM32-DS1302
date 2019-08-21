#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

#define SCLK  PGout(15)
#define RESET PCout(5)
#define DATA  PBout(5)



u8 read_data_from_1302(u8 add);								 
void ds1302_GPIO_Configuration(void);
void write_data_to_add(u8 add,u8 dat);			 
void ds1302_init(void);
void ds1302_print_data(u8 *read);
void Sendchar(u8 com);
u8 Readchar(void);
#endif

