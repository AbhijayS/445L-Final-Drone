
#ifndef __RADIO_H__
#define __RADIO_H__
#define RADIO_THROTTLE ((GPIO_PORTC_DATA_R>>5)&1)
extern volatile int went_high;
void radio_init();
int radio_throttle();
#endif
