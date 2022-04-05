#include <stdlib.h>
#include "PLL.h"
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "UART.h"
#include "radio.h"

// valvano code from PWM.c
// period is 16-bit number of PWM clock cycles in one period (3<=period)
// period for PB6 and PB7 must be the same
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
// PWM clock rate = processor clock rate/SYSCTL_RCC_PWMDIV
//                = BusClock/2
//                = 80 MHz/2 = 40 MHz (in this example)
// Output on PB6/M0PWM0
// void PWM0A_Init_20MHz(uint16_t period, uint16_t duty){
//   SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
//   SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
//   while((SYSCTL_PRGPIO_R&0x02) == 0){};
//   GPIO_PORTB_AFSEL_R |= 0x40;           // enable alt funct on PB6
//   GPIO_PORTB_PCTL_R &= ~0x0F000000;     // configure PB6 as PWM0
//   GPIO_PORTB_PCTL_R |= 0x04000000;
//   GPIO_PORTB_AMSEL_R &= ~0x40;          // disable analog functionality on PB6
//   GPIO_PORTB_DEN_R |= 0x40;             // enable digital I/O on PB6
//   SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
//       (SYSCTL_RCC_R & (~0x000E0000));
//   SYSCTL_RCC_R |= 1<<17; // divide by 4
//   PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
//   PWM0_0_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
//   // PB6 goes low on LOAD
//   // PB6 goes high on CMPA down
//   PWM0_0_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
//   PWM0_0_CMPA_R = duty - 1;             // 6) count value when output rises
//   PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
//   PWM0_ENABLE_R |= 0x00000001;          // enable PB6/M0PWM0
// }
// unsigned long Led;

void Delay(void){unsigned long volatile time;
  time = 800000;
  while(time){
		time--;
  }
}
int main(void){
  PLL_Init(Bus80MHz);
  UART_Init();
  radio_init();
  PortF_Init();
  UART_OutString("Ready to go!\n");
  while(1) {
  }
  
  // while(1){
  //  //if(PF4 == 0x0){
  //   Led = 0x02;            // reverse value of LED
  //   GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
  //   Delay();
  //   Led = 0x04;            // reverse value of LED
  //   GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
  //   Delay();
  //   Led = 0x08;            // reverse value of LED
  //   GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
  //   Delay();
  //   /*Led = 0x0A;            // reverse value of LED
  //   GPIO_PORTF_DATA_R = Led;   // write value to PORTF DATA register,toggle led
  //   Delay();*/
  //  // }
  // }

  PWM0A_Init_20MHz(40000, 40000); // 500Hz @ 50% duty cycle => 1% power

  
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
