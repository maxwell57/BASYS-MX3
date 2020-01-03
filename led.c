#include <proc/p32mx370f512l.h>

#include "led.h"

inline void led_initialisation(void){
    //putting each led in output state
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
}

inline void led_global_extinction(void){
    LATAbits.LATA0 = 0;
    LATAbits.LATA1 = 0;
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATAbits.LATA6 = 0;
    LATAbits.LATA7 = 0;
}

void write_led(int position, uint32_t value){
    switch(position){
        case 0 : 
            LATAbits.LATA0 = value;
            break;
        case 1 : 
            LATAbits.LATA1 = value;
            break;
        case 2 : 
            LATAbits.LATA2 = value;
            break;
        case 3 : 
            LATAbits.LATA3 = value;
            break;
        case 4 : 
            LATAbits.LATA4 = value;
            break;
        case 5 : 
            LATAbits.LATA5 = value;
            break;
        case 6 : 
            LATAbits.LATA6 = value;
            break;
        case 7 : 
            LATAbits.LATA7 = value;
            break;
        default : break;
        
    }
}

inline void rgb_initialisation(void){
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD12 = 0;
}

inline void rgb_extinction(void){
    unput_red();
    unput_green();
    unput_blue();
}

inline void unput_red(void){LATDbits.LATD2 = 0;}
inline void unput_green(void){LATDbits.LATD12 = 0;}
inline void unput_blue(void){LATDbits.LATD3 = 0;}

inline void put_red(uint32_t value){LATDbits.LATD2 = value;}
inline void put_green(uint32_t value){LATDbits.LATD12 = value;}
inline void put_blue(uint32_t value){LATDbits.LATD3 = value;}

inline void light_red(void){LATDbits.LATD2 = 1;}
inline void light_green(void){LATDbits.LATD12 = 1;}
inline void light_blue(void){LATDbits.LATD3 = 1;}


/*void init_rgb_pwm(int timer){
	RPD2R=0b1011;  // branche RPD2 (red) sur OC3
	RPD3R=0b1011; // branche RPD3 (blue) sur sur OC4
	RPD12R=0b1011;	 // branche RPD12 (green) sur OC5
	
	INIT_PWM3(timer);
	INIT_PWM4(timer);
	INIT_PWM5(timer);
}

void rgb_pwm(int puissance, int r, int g, int b){
	SET_DUTY3(puissance*r);
	SET_DUTY4(puissance*b);
	SET_DUTY5(puissance*g);
}
*/