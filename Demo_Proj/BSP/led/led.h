#ifndef _LED_H
#define _LED_H

#include "sys.h"


#define LED0 PHout(10)   //LED0
#define LED1 PHout(11)   //LED1
#define LED2 PHout(12)	 //LED2

void LED_Init(void);
#endif
