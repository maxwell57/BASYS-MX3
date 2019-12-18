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


int calcul_frequence(int i)
{ switch(i){ 
		case 0 : return PB_FRQ/1;     
		case 1 : return  PB_FRQ/8;   
		case 2 : return PB_FRQ/64;   
		case 3 : return PB_FRQ/256; 
		default : return -1;               
	}
}


enum state{etat1, etat2, etat3};
int number;

void binary_convert(int dest [], int src);

void separate_digits(int ret[], int number);

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

/*void __ISR(_TIMER_1_VECTOR, ipl7) Timer1ISR(void){
    //rgb_extinction();
    static int d=0;
    //if(d==0) light_red();
    //else if(d==1) light_blue();
    //else if(d==2) light_green();
    d = (d+1)%3;
    IFS0bits.T1IF = 0;
}*/

void __ISR(_TIMER_2_VECTOR,ipl7) sevenSegmentsDisplay(void){
    static int d=0;
    int digits[4];
    separate_digits(digits,number);
    set_number_position(d,digits[d]);
    d =(d+1)%4;
    IFS0bits.T2IF = 0;
}

void __ISR(_TIMER_3_VECTOR,ipl7) buzzer(void){
    PORTBbits.RB14 = 1;
    PORTBbits.RB14 = 0;
    IFS0bits.T3IF = 0;
}

void __ISR(_TIMER_4_VECTOR,ipl7) bipper(void){
    static int c=0;
    if(c) LED0(1);
    else LED0(0);
    c = (c+1)%16;
    IFS0bits.T4IF = 0;
}

void UART1(void){

    
    U4MODEbits.ON = 1;   
    U4MODEbits.SIDL= 0;
    U4MODEbits.IREN = 0;
    U4MODEbits.RTSMD = 0;
    U4MODEbits.UEN = 0;
    U4MODEbits.WAKE = 0;
    U4MODEbits.LPBACK = 0;
    U4MODEbits.ABAUD = 0;
    U4MODEbits.RXINV = 0;
    U4MODEbits.BRGH = 0;            
    U4MODEbits.PDSEL= 0;
    U4MODEbits.STSEL = 0;
    
    U4STAbits.UTXEN = 1;
    U4STAbits.URXEN = 1;
    
    U4RXR=0b1001;
    RPF12R=0b0010;
            
    U4BRG = 25;
    
}

void caractere (char c)
{
    U4TXREG = c;
}

void phrase (char* s)
{
    int i;
    for(i=0;s[i]!=0;i++){
    U4TXREG = s[i];
    if(U4STAbits.UTXBF) while(U4STAbits.TRMT != 1);
    }
}

char recup_caractere ()
{
    while(U4STAbits.URXDA != 1);
    char c= U4RXREG ;
    return c;
}

void ledpwm(int puissance, int R, int G, int B)
{
RPD2R=0b1011; //connecting led to ocx
RPD3R=0b1011;
RPD12R=0b1011;

OC3CONbits.ON=1;
OC3CONbits.SIDL=0; //Continue in Idle
OC3CONbits.OCTSEL=1; //set timer 0=TMR2, 1=TMR3
OC3CONbits.OCM=6; //PWM mode, fault disabled

OC3RS=R*puissance;   //R

OC4CONbits.ON=1;
OC4CONbits.SIDL=0;
OC4CONbits.OCTSEL=1;
OC4CONbits.OCM=6;  

OC4RS=B*puissance;   //B
        
OC5CONbits.ON=1;
OC5CONbits.SIDL=0;
OC5CONbits.OCTSEL=1;
OC5CONbits.OCM=6;

OC5RS=G*puissance;  //G


}

void accelerometre(void){
    //I2C1CONbits.ON;
    //I2C1STATbits.R_W;
    //I2C1ADD = 0x1d; // 0x3A in write mode, 0x3B in read mode
    
    //single byte read :
    // 0 : Start condition
    // 1 : Master write, send register adress
    // 2 : repeat Start condition
    // 3 : Master read, and send NAK
    // 4 : Stop condition
    
    //multi-bytes read :
    // 0 : Start Condition
    // 1 : Master write, send register adress
    // 2 : repeat Start condition
    // 3 : Master read, slave send register adress and increment it, Master send AK
    // 4 : Master send NAK
    // 5 : Stop condition
    
    int buf[6];
    I2C1BRG = 0x00ec;
    I2C1CONbits.ON = 1;
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN) ; //empty loop
    I2C1TRN = 0X3A; //you, the accelerometer, listen to me !
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk 
    if(I2C1STATbits.ACKSTAT) return; //did you understand me ?
    I2C1TRN = 0x01; //address of OUT_X_MSB;
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return; //did you understand me ?
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN) ;
    int i;
    for(i=0; i<6; i++){
        buf[i] = I2C1RCV;
        I2C1CONbits.ACKEN = 1;
        while(I2C1CONbits.ACKDT);
    }
    I2C1CONbits.PEN = 1;
    number = buf[3];
    //rgb_extinction();
    //ledpwm(10,buf[0],buf[2],buf[4]);
    //if(buf[0]>0) LED0(1);
}
       
int main(int argc, char** argv)
{
    //led_initialisation();
    //switch_initialisation();
    rgb_initialisation();
    //rgb_extinction();
    segments_display_initialisation();
    //stop_anodes();
    //UART1();
    //TRISFbits.TRISF12=0;
    //TRISFbits.TRISF13=1;
    ledpwm(10,41,223,199);
   
   
    
    char tab[24]="Denis est malin\n\r";
    
    //enable timer 1
    //PR1 =(1*PB_FRQ/256);
    /*TMR1 = 0;
    T1CONbits.TCKPS = 3;
    T1CONbits.TGATE = 0;
    T1CONbits.TCS = 0;
    T1CONbits.ON = 1;
    IPC1bits.T1IP = 7;
    IPC1bits.T1IS = 3;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;*/
    
    PR2 = 2*PB_FRQ;
    TMR2 = 0;
    T2CONbits.TCKPS = 1;
    T2CONbits.TGATE = 0;
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;
    IPC2bits.T2IP = 7;
    IPC2bits.T2IS = 3;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    
    PR3 = 2*PB_FRQ;
    TMR3 = 0;
    T3CONbits.TCKPS = 0;
    T3CONbits.TGATE = 0;
    T3CONbits.TCS = 0;
    T3CONbits.ON = 1;
    IPC3bits.T3IP = 7;
    IPC3bits.T3IS = 3;
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    
    
    //enable timer4 for testing purpose
    //PR4 = 0xfc;//4*PB_FRQ/256;
    TMR4 = 0;
    T4CONbits.TCKPS = 3;
    T4CONbits.TGATE = 0;
    T4CONbits.TCS = 0;
    T4CONbits.ON = 1;
    IPC4bits.T4IP = 7;
    IPC4bits.T4IS = 3;
    IFS0bits.T4IF = 0;
    IEC0bits.T4IE = 1;
    
    
    macro_enable_interrupts();
    
    /* buttons initialisation*/
    TRISFbits.TRISF0 = 1;
    TRISAbits.TRISA15 = 1;
    TRISBbits.TRISB8 = 1;
    ANSELBbits.ANSB8 = 0;
    int pushed_L = 0;
    //int d =0;
    int state = etat1;
    int digits[4], accu, current;
    int flag = 1;
    TRISBbits.TRISB14 = 0;
    ANSELBbits.ANSB14 = 0;
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSB2 = 1;
    
    //AD1PCFG = 0xfffb;
    AD1CON1 = 0x0000;
    AD1CHS = 0X00020000;
    AD1CSSL = 0;
    AD1CON3 = 0X0002;
    AD1CON2 = 0;
    AD1CON1SET = 0x8000;
    RPB14R = 0x0C;
    
    phrase(tab);
    
    while(1){
        accelerometre();
        //rgb_extinction();
        //caractere('e');
        //AD1CON1SET = 0x0002;
        //DelayAprox100Us(10);
        //AD1CON1CLR = 0x002;
        //while(!(AD1CON1 & 0x0001)) ;
        //number = ADC1BUF0;
        
        
        //PR3 = 0;
        //if(number>0) PR4 = 2*calcul_frequence(T4CONbits.TCKPS)/number;
        //else PR4 = 0;
        //if(number>1) PR3 = (number*16);//(number/10)*(1*PB_FRQ/256);
        //else PR3 = 0;
        //PORTBbits.RB14=number%2;
        //d++;
        //if(d>10) d=0;
        //int i;
        //for(i=0; i<440; i++);
        
        //number = get_number();
        //if(PORTAbits.RA15==1){ //is button D pushed ?
        //    current = accu;
        //}
        //else current = number;
        
        /*separate_digits(digits,current);
        int d,e; for(d=0; d<4; d++){
            set_number_position(d,digits[d]);
            DelayAprox100Us(15);
        }*/
        //d++;
        //if(d==4) d=0;
        //if(PORTFbits.RF0==1){ //is button C pushed ?
        //    accu = number;
        //    light_green();
        //}
        //else if(PORTBbits.RB8==1 && pushed_L==0){
        //    accu += number;
        //    light_blue();
        //    pushed_L=1;
        //}
        //else if(PORTBbits.RB8==0){
        //    pushed_L = 0;
        //}
        //state = MyStateMachine(state);
        
        
        //int i,j,k,l;
        //PORTBbits.RB14 = PORTBbits.RB2;
        /*for(i=0; i<number; i++) 
            if(i<100) PORTBbits.RB14 = (i%2);
            else if(i<200) PORTBbits.RB14 = (i%3)>0;
            else if(i<300) PORTBbits.RB14 = (i%4)>0;
            else if(i<400) PORTBbits.RB14 = (i%5)>0;
            else if(i<500) PORTBbits.RB14 = (i%6)>0;
            else if(i<600) PORTBbits.RB14 = (i%7)>0;
            else if(i<700) PORTBbits.RB14 = (i%6)>0;
            else if(i<800) PORTBbits.RB14 = (i%5)>0;
            else if(i<900) PORTBbits.RB14 = (i%4)>0;
            else if(i<1000) PORTBbits.RB14 = (i%3)>0;
         */
        //PORTBbits.RB14 = (number<1024);
        //for(i=0; i<0xff; i++){
        //if(d = number%4) PORTBbits.RB14 = 1;
        //else PORTBbits.RB14 = 0;
        //}
        //light_leds();
        //for(i=0; i<0xff; i++);//for(j=0; j<0xffff; j++);// for(k=0; k<0xffff; k++); //for(l=0; l<0xffff; l++) ; //empty loop
        //caractere(recup_caractere ());
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


