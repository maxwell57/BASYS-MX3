#include "timer.h"

void init_timer_16(int position, int prescale, int delay){
	switch(position){
		case 1: 
			PR1 = delay;
			TMR1 = 0;
			T1CONbits.TCKPS = prescale;
			T1CONbits.TGATE = 0;
			T1CONbits.TCS = 0;
			T1CONbits.ON = 1;
			IPC1bits.T1IP = 7;
			IPC1bits.T1IS = 3;
			IFS0bits.T1IF = 0;
			IEC0bits.T1IE = 1;
			break;
		case 2:
			PR2 = delay;
			TMR2 = 0;
			T2CONbits.TCKPS = prescale;
			T2CONbits.TGATE = 0;
			T2CONbits.TCS = 0;
			T2CONbits.ON = 1;
			IPC2bits.T2IP = 7;
			IPC2bits.T2IS = 3;
			IFS0bits.T2IF = 0;
			IEC0bits.T2IE = 1;
			break;
		case 3:
			PR3 = delay;
			TMR3 = 0;
			T3CONbits.TCKPS = prescale;
			T3CONbits.TGATE = 0;
			T3CONbits.TCS = 0;
			T3CONbits.ON = 1;
			IPC3bits.T3IP = 7;
			IPC3bits.T3IS = 3;
			IFS0bits.T3IF = 0;
			IEC0bits.T3IE = 1;
			break;
		case 4:
			PR4 = delay;
			TMR4 = 0;
			T4CONbits.TCKPS = prescale;
			T4CONbits.TGATE = 0;
			T4CONbits.TCS = 0;
			T4CONbits.ON = 1;
			IPC4bits.T4IP = 7;
			IPC4bits.T4IS = 3;
			IFS0bits.T4IF = 0;
			IEC0bits.T4IE = 1;
			break;
		default : return;
	}
}

void set_timer_delay(int position, int delay){
	int prescale,frequence;
	if(delay<10){
		delay *= 4;
		prescale = 0;
		frequence = PB_FRQ;
	}
	else if(delay < 100){
		delay *= 5;
		prescale = 3;
		if(position==1) prescale = 1;
		frequence = PB_FRQ/8;
	}
	else if(delay < 1000){
		delay *= 25;
		prescale = 4;
		frequence = PB_FRQ/16;
		if(position==1){
			delay *=50;
			prescale = 1;
			frequence = PB_FRQ/8;
		}
	}
	else if(delay < 10000){
		delay *= 125;
		prescale = 5;
		frequence = PB_FRQ/32;
		if(position==1){
			delay *=500;
			prescale = 1;
			frequence = PB_FRQ/8;
		}
	}
	else if(delay < 100000){
		delay *= 625;
		prescale = 6;
		frequence = PB_FRQ/64;
		if(position==1){
			prescale = 2;
		}
	}
	else if(delay < 1000000){
		delay *= 6250;
		prescale = 6;
		frequence = PB_FRQ/64;
		if(position==1){
			prescale = 2;
		}
	}
	else{
		delay *= 15625;
		prescale = 7;
		frequence = PB_FRQ/256;
	}
	switch(position){
		case 1 :
			T1CONbits.TCKPS = prescale;
			PR1 = (delay*frequence)/1000000;
			break;
		case 2 :
			T2CONbits.TCKPS = prescale;
			PR2 = (delay*frequence)/1000000;
			break;
		case 3 :
			T3CONbits.TCKPS = prescale;
			PR3 = (delay*frequence)/1000000;
			break;
		case 4 :
			T3CONbits.TCKPS = prescale;
			PR4 = (delay*frequence)/1000000;
			break;
		default : return ;
	}
}
