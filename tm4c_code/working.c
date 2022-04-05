#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/UART.h"

//volatile int went_high = 0;

//extern void GPIOPortC_ISR(void);

void radio_init() {
    SYSCTL_RCGCGPIO_R   |=  (1<<2); // enable port c clock
    GPIO_PORTC_DIR_R    &= ~(1<<5); // set pin 5 as input
    GPIO_PORTC_PUR_R    |= (1<<5); // enable pc5 pullup
    GPIO_PORTC_DEN_R    |=  (1<<5); // digital enable pin 5
    // TODO: lock the pin

   GPIO_PORTC_IM_R      &= ~(1<<5); // disable pc5 interrupts
   GPIO_PORTC_IS_R; // pc5 edges detected
   GPIO_PORTC_IBE_R     |= (1<<5); // pc5 both edges detected
   GPIO_PORTC_IEV_R;
   GPIO_PORTC_ICR_R      = (1<<5); // clear pc5 interrupts
   GPIO_PORTC_IM_R      |= (1<<5); // enable pc5 interrupts

   NVIC_EN0_R |= (1<<2); // enable nvic port c
}
extern void GPIOPortC_Handler(void) {
    GPIO_PORTF_DATA_R ^= 0x02;
}
int main(void) {
    radio_init();
    while(1){}
}