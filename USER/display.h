#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "sys.h"

#define A  PGout(7)
#define B  PGout(6)
#define C  PGout(5)
#define D  PGout(4)
#define E  PAout(8)
#define F  PCout(7)
#define G  PCout(6)
#define DP PGout(8)

#define SW0 PEin(0)
#define SW1 PEin(1)

#define WEI1 PFout(13)
#define WEI2 PGout(0)
#define WEI3 PEout(9)
#define WEI4 PFout(12)
#define WEI5 PEout(8)
#define WEI6 PEout(7)
#define WEI7 PEout(10)
#define WEI8 PFout(11)



void display_pin_init(void);
void display_number(u8 num);
void display_weixuan(u8 num);
void display_xiaoying(void);





#endif
