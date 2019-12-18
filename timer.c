#include "timer.h"

void init_timer(int position, int prescale, int delay){
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
		case 5 :
			PR5 = delay;
			TMR5 = 0;
			T5CONbits.TCKPS = prescale;
			T5CONbits.TGATA = 0;
			T5CONbits.TCS = 0;
			T5CONbist.ON = 1;
			IPC5bits.T5IP = 7;
			IPC5bits.T5IS = 3;
			IFS0bits.T5IF = 0;
			IEC0bits.T5IE = 1;
			break;
		default : return;
	}
}

void set_timer_us(int position, int  period){
	int delay, frequence, prescale;
	switch(position){
		case 1 :
			if(period<10) {prescale = 0; frequence = PB_FRQ; delay = period*4;} // period less than 10 us
			else if(period<10000) {prescale = 1; frequence = PB_FRQ/8; delay = (period*5)/10;} // period less than 10 ms
			else if(period<MILLION) {prescale = 2; frequence = PB_FRQ/64; delay = (period*625)/10000;} // period less than 1 s
			else {prescale = 3; frequence = PB_FRQ/256; delay = (period*15625)/1000000;}
			TIMER1(prescale,delay);
			break;
		default :
			if(period<1000){prescale = 2; frequence = PB_FRQ/4; delay=period; } // period less than  1 ms
			else if(period<10000){prescale = 5; frequence = PB_FRQ/32; delay = (period*125)/1000;} // period less than 10 ms
			else if(period<MILLION){prescale = 6; frequence = PB_FRQ/64; delay = (period*625)/10000;} // period less than 1 s
			else{prescale = 7; frequence = PB_FRQ/256; delay = (period*15625)/1000000;}
			init_timer(position,prescale,delay);
	}
}

void set_timer_Hz(int position, float frequence){
		int period = MILLION/frequence;
		set_timer_us(position,period);
}
