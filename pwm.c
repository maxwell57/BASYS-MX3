#include "pwm.h"

void init_pwm(int position, int timer){
	switch(position){
		case 1 :
			OC1CONbits.ON = 1; //démarer l'outCompare
			OC1CONbits.SIDL = 0; //laisser allumer en mode Idle, aucune incidence
			OC1CONbits.OCTSEL = (timer==2)?0:1; //si timer =2, alors TIMER2, sinon TIMER3
			OC1CONbits.OCM = 0b110; // mode PWM avec faute
			break;
		case 2 :
			OC2CONbits.ON = 1; //démarer l'outCompare
			OC2CONbits.SIDL = 0; //laisser allumer en mode Idle, aucune incidence
			OC2CONbits.OCTSEL = (timer==2)?0:1; //si timer =2, alors TIMER2, sinon TIMER3
			OC2CONbits.OCM = 0b110; // mode PWM avec faute
			break;
		case 3 :
			OC3CONbits.ON = 1; //démarer l'outCompare
			OC3CONbits.SIDL = 0; //laisser allumer en mode Idle, aucune incidence
			OC3CONbits.OCTSEL = (timer==2)?0:1; //si timer =2, alors TIMER2, sinon TIMER3
			OC3CONbits.OCM = 0b110; // mode PWM avec faute
			break;
		case 4 :
			OC4CONbits.ON = 1; //démarer l'outCompare
			OC4CONbits.SIDL = 0; //laisser allumer en mode Idle, aucune incidence
			OC4CONbits.OCTSEL = (timer==2)?0:1; //si timer =2, alors TIMER2, sinon TIMER3
			OC4CONbits.OCM = 0b110; // mode PWM avec faute
			break;
		case 5 :
			OC5CONbits.ON = 1; //démarer l'outCompare
			OC5CONbits.SIDL = 0; //laisser allumer en mode Idle, aucune incidence
			OC5CONbits.OCTSEL = (timer==2)?0:1; //si timer =2, alors TIMER2, sinon TIMER3
			OC5CONbits.OCM = 0b110; // mode PWM avec faute
			break;
		default :  return;
	}
}

void set_duty(int position, int dutyValue){
	switch(position){
		default : return;
		case 1 : OC1RS = dutyValue; break;
		case 2 : OC2RS = dutyValue; break;
		case 3 : OC3RS = dutyValue; break;
		case 4 : OC4RS = dutyValue; break;
		case 5 : OC5RS = dutyValue; break;
	}
}
