/* 
 * File:   main.c
 * Author: karlito
 *
 * Created on December 1, 2019, 5:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <time.h>

/* personnal libraries*/
#include "led.h"
#include "switches.h"
#include "segments_display.h"
#include "timer.h"
#include "pwm.h"
#include "i2c.h"
#include "accelerometer.h"
#include "spi.h"
#include "flash.h"


#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      


#pragma config FNOSC =	2           // select oscilator externe (quartz at 8MHz)
#pragma config FSOSCEN =	OFF     // Disable secondary oscilator
#pragma config POSCMOD =	XT      // XT oscilator mode
#pragma config OSCIOFNC =	ON      //
#pragma config FPBDIV =     DIV_2   // Peripheralls run at /2 the speed
#define PB_FRQ 4000000

#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1


#define macro_enable_interrupts() \
{  unsigned int val = 0;\
    asm volatile("mfc0 %0,$13":"=r"(val));  \
    val |= 0x00800000;  \
    asm volatile("mtc0 %0,$13" : "+r"(val)); \
    INTCONbits.MVEC = 1; \
__builtin_enable_interrupts(); }

//#define macro_enable_interrupts INTEnableSystemMultiVectoredInt()

#define macro_disable_interrupts __builtin_disable_interrupts()
//#define macro_disable_interrupts INTDisableInterrupts()

int number;

void binary_convert(int dest [], int src);

void separate_digits(int ret[], int number);

void __ISR(_TIMER_1_VECTOR, ipl7) display_number(void){
    static int i=0;
    int digit[4]; 
    separate_digits(digit,number);
    set_number_position(i,digit[i]);
    //LED0(i%2);
    i = (i+1)%4;
    IFS0bits.T1IF = 0;
}

void DelayAprox100Us( unsigned int  t100usDelay )
{
    int j;
    while ( 0 < t100usDelay )
    {
        t100usDelay--;
        j = 14;
        while ( 0 < j )
        {
            j--;
        }   // end while 
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
        asm volatile("nop"); // do nothing
         
    }   // end while
}

/*inline int get_number(void){
    return SWITCH0 
        + (SWITCH1<<1) 
        + (SWITCH2<<2) 
        + (SWITCH3<<3)
        + (SWITCH4<<4)
        + (SWITCH5<<5)
        + (SWITCH6<<6)
        + (SWITCH7<<7);
}
*/

void led_number(unsigned char val){
    LED0(val%2);
    val /= 2;
    LED1(val%2);
    val /= 2;
    LED2(val%2);
    val /= 2;
    LED3(val%2);
    val /= 2;
    LED4(val%2);
    val /= 2;
    LED5(val%2);
    val /= 2;
    LED6(val%2);
    val /= 2;
    LED7(val%2);
}
       
int main(int argc, char** argv)
{
    segments_display_initialisation();
    led_initialisation();
    unsigned char data[4] = {4,3,2,1};
    
    TIMER1HZ(240);
    macro_enable_interrupts();
    number = data[0] + 10*data[1] + 100*data[2] + 1000*data[3];
    
    initSpi();
    Erase(0x01);
    //DelayAprox100Us(10000);
    Write(0x01,data,4);
    int i;
    for(i=0; i<4; i++) data[i] = 0;
    number = data[0] + 10*data[1] + 100*data[2] + 1000*data[3];
    
    Read(0x01,data,4);
    number = data[0] + 10*data[1] + 100*data[2] + 1000*data[3];
    led_number(data[0]);
    while(1) ;
    return (EXIT_SUCCESS);
}

void binary_convert(int dest [], int src){
    int i;
    for(i=0; i<8; i++){
        dest[i] = src%2;     //dest[i] = src&1;
        src=src/2;          //src>>=1;
    }
}

void separate_digits(int ret[], int number){
    int i;
    for(i=0; i<4; i++){
        ret[i] = number%10;
        number /= 10;
    }
}


