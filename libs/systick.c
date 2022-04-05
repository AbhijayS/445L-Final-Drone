#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

void enable_systick() {
    NVIC_ST_RELOAD_R = 0xFFFFFF; // max systick value
    NVIC_ST_CURRENT_R = 0; // write any value
    NVIC_ST_CTRL_R = 7; // enable systick using system clock
}

void get_systick() {
    int sys = NVIC_ST_CURRENT_R;
}
