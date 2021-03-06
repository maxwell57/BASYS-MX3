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


#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      


#pragma config FNOSC =	2      // select oscilator externe (quartz at 8MHz)
#pragma config FSOSCEN =	OFF     // Disable secondary oscilator
#pragma config POSCMOD =	XT      // XT oscilator mode
#pragma config OSCIOFNC =	ON      //
#pragma config FPBDIV =     DIV_2   // Peripheralls run at /2 the speed

#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

enum state{etat1, etat2, etat3};

void binary_convert(int dest [], int src);

void separate_digits(int ret[], int number);


inline int get_number(void){
    return SWITCH0 
        + (SWITCH1<<1) 
        + (SWITCH2<<2) 
        + (SWITCH3<<3)
        + (SWITCH4<<4)
        + (SWITCH5<<5)
        + (SWITCH6<<6)
        + (SWITCH7<<7);
}

int MyStateMachine(int state);

inline void light_leds(void){
    LED0(SWITCH0);
    LED1(SWITCH1);
    LED2(SWITCH2);
    LED3(SWITCH3);
    LED4(SWITCH4);
    LED5(SWITCH5);
    LED6(SWITCH6);
    LED7(SWITCH7);
}



int main(int argc, char** argv)
{
    led_initialisation();
    switch_initialisation();
    rgb_initialisation();
    segments_display_initialisation();
    
    /* buttons initialisation*/
    TRISFbits.TRISF0 = 1;
    TRISAbits.TRISA15 = 1;
    TRISBbits.TRISB8 = 1;
    ANSELBbits.ANSB8 = 0;
    int pushed_L = 0;
    int d =0;
    int state = etat1;
    int number, digits[4], accu, current;
    while(1){
       
        rgb_extinction();
        
        number = get_number();
        if(PORTAbits.RA15==1){ //is button D pushed ?
            current = accu;
        }
        else current = number;
        
        separate_digits(digits,current);
        set_number_position(d,digits[d]);
        d++;
        if(d==4) d=0;
        if(PORTFbits.RF0==1){ //is button C pushed ?
            accu = number;
            light_green();
        }
        else if(PORTBbits.RB8==1 && pushed_L==0){
            accu += number;
            light_blue();
            pushed_L=1;
        }
        else if(PORTBbits.RB8==0){
            pushed_L = 0;
        }
        //state = MyStateMachine(state);
        
        
        int i,j,k,l;
        //for(i=0; i<8; i++) write_led(i,read_switch(i));
        light_leds();
        for(i=0; i<0xff; i++);//for(j=0; j<0xffff; j++);// for(k=0; k<0xffff; k++); //for(l=0; l<0xffff; l++) ; //empty loop
        
    }
   
    return (EXIT_SUCCESS);
}

void binary_convert(int dest [], int src){
    int i;
    for(i=0; i<8; i++){
        dest[i] = src%2;     //dest[i] = src&1;
        src=src/2;          //src>>=1;
    }
}


int MyStateMachine(int state){
    switch(state){
        case etat1 : 
            LED0(1);
            LED1(0);
            LED2(0);
            if(SWITCH0==1){
               state = etat2;
            }
            break;
        case etat2 :
            LED0(0);
            LED1(1);
            LED2(0);
            if(SWITCH1==1){
                state = etat3;
            }
            break;
        case etat3 :
            LED0(0);
            LED1(0);
            LED2(1);
            if(SWITCH2==1){
                state = etat1;
            }
            break;
        default : return -1;
    }
    return state;
}



void separate_digits(int ret[], int number){
    int i;
    for(i=0; i<4; i++){
        ret[i] = number%10;
        number /= 10;
    }
}