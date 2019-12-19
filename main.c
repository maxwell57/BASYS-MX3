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
#include <math.h>

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
int number, buf[6];

void binary_convert(int dest[], int src);

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
void niveau_x(void){
    
    led_global_extinction();
    
    if(buf[0]<-30) LED0(1);
    else if(buf[0]<-20) LED1(1);
    else if(buf[0]<-10) LED2(1);
    else if(buf[0]<0) LED3(1);
    else if(buf[0]<10) LED4(1);
    else if(buf[0]<20) LED5(1);
    else if(buf[0]<30) LED6(1);
    else LED7(1);
    
}
void niveau_y(void){
    
    led_global_extinction();
    
    if(buf[2]<-30) LED0(1);
    else if(buf[2]<-20) LED1(1);
    else if(buf[2]<-10) LED2(1);
    else if(buf[2]<0) LED3(1);
    else if(buf[2]<10) LED4(1);
    else if(buf[2]<20) LED5(1);
    else if(buf[2]<30) LED6(1);
    else LED7(1);
}

void niveau_z(void){
    
    led_global_extinction();
    
    if(buf[2]<-30) LED0(1);
    else if(buf[4]<-20) LED1(1);
    else if(buf[4]<-10) LED2(1);
    else if(buf[4]<0) LED3(1);
    else if(buf[4]<10) LED4(1);
    else if(buf[4]<20) LED5(1);
    else if(buf[4]<30) LED6(1);
    else LED7(1);
}

void equilibre_x_y(void){

    led_global_extinction();
    
     if(fabs(buf[0])<3 && fabs(buf[2])<3){
     LED0(1);
     LED1(1);
     LED2(1);
     LED3(1);
     LED4(1);
     LED5(1);
     LED6(1);
     LED7(1);
     
    }
    else if(fabs(buf[2])<10 && fabs(buf[0])<10) {LED3(1);LED4(1);}
    else if(fabs(buf[2])<20 && fabs(buf[0])<20) {LED2(1);LED5(1);}
    else if(fabs(buf[2])<40 &&fabs(buf[0])<40) {LED1(1);LED6(1);}
    else if(fabs(buf[2])<60 && fabs(buf[0])<60) {LED0(1);LED7(1); ledpwm(100, 0, 255, 0);}
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
RPD3R=0b1011;
RPD12R=0b1011;

OC3CONbits.ON=1;

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
int start_accelerometre(void){
    TRISGbits.TRISG3 = 0;
    TRISGbits.TRISG2 = 0;
    
    I2C1BRG = 2;
    I2C1CONbits.ON = 1;
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN) ; //empty loop
    I2C1TRN = 0X3A; //you, the accelerometer, listen to me !
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk 
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1TRN = 0x002a; //address of CTRL_REG1;
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1TRN = 1; //address of CTRL_REG1;
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1;
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
    return 0;
}
int accelerometre(void){
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
    
    //I2C1BRG = 2;
    //I2C1CONbits.ON = 1;
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN) ; //wait 'til finish sending signal
    I2C1TRN = 0X3A; //you, the accelerometer, listen to me !
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk 
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1TRN = 0x01; //address of OUT_X_MSB;
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN) ;//wait 'til finish
    I2C1TRN = 0X3B; //Talk to me, slave
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    int i,u;
    for(i=0; i<6; i++){
        I2C1CONbits.RCEN = 1;
        I2C1CONbits.ACKDT=(i==5)?1:0;
        while(I2C1CONbits.RCEN);
        u = (char)I2C1RCV;
        if((buf[i]-u)*(buf[i]-u)>=4)buf[i] = u;
        I2C1CONbits.ACKEN = 1;
        //while(I2C1CONbits.ACKEN) ;
        
    }
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
    number = buf[0];
    rgb_extinction();
    ledpwm(1,buf[0],buf[2],buf[4]);
    
    /*
    if (read_switch(0)) niveau_x();
    else if(read_switch(1)) niveau_y();
    else niveau_z();
    */
        if (read_switch(1))
            equilibre_x_y();
        else if (read_switch(2))
            niveau_x();
        else if (read_switch(3))
            niveau_y();
        else
            niveau_z();
    return 0;
}

       
int main(int argc, char** argv)
{
    led_initialisation();
    if(start_accelerometre()) number = 9999;
    else number = 1010;
    switch_initialisation();
    rgb_initialisation();
    segments_display_initialisation();
    //rgb_extinction();
    //stop_anodes();
    //UART1();
    //TRISFbits.TRISF12=0;
    //TRISFbits.TRISF13=1;
    //ledpwm(10,41,223,199);
   
   
    
    //char tab[24]="Denis est malin\n\r";
    
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
    
    
    while(1){
        if(accelerometre()) number = 1111;
        DelayAprox100Us(10);
        //rgb_extinction();
        //caractere('e');
        
        
        //if(number>1) PR3 = (number*16);//(number/10)*(1*PB_FRQ/256);
        //else PR3 = 0;
        //PORTBbits.RB14=number%2;
        //d++;
        //if(d>10) d=0;
        //int i;
        //for(i=0; i<440; i++);
        
        //number = get_number();
        
        /*separate_digits(digits,current);
        int d,e; for(d=0; d<4; d++){
            set_number_position(d,digits[d]);
            DelayAprox100Us(15);
        }*/
        //d++;
        //if(d==4) d=0;
        //state = MyStateMachine(state);
        
        
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

void binary_convert(int dest[], int src){
    int i;
    for(i=0; i<8; i++){
        dest[i] = src%2;     //dest[i] = src&1;
        src=src/2;          //src>>=1;
    }
}

void separate_digits(int ret[], int number){
    int i;
    if(number>=0){
        for(i=0; i<4; i++){
            ret[i] = number%10;
            number /= 10;
        }
    }
    else{
        number *=-1;
        for( i=0; i<3; i++){
            ret[i] = number%10;
            number /= 10;
        }
        ret[3] = -1;
    }
}


