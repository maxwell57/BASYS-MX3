#include <proc/p32mx370f512l.h>

#include "switches.h"

inline void switch_initialisation(void){
    //put each switch in input mod and disable analogic mod for switch 5,6, and 7
    TRISFbits.TRISF3 = 1;
    TRISFbits.TRISF5 = 1; 
    TRISFbits.TRISF4 = 1;
    TRISDbits.TRISD15 = 1;
    TRISDbits.TRISD14 = 1;
    TRISBbits.TRISB11 = 1;
    ANSELBbits.ANSB11 = 0;
    TRISBbits.TRISB10 = 1;
    ANSELBbits.ANSB10 = 0;
    TRISBbits.TRISB9 = 1;
    ANSELBbits.ANSB9 = 0;
}

uint32_t read_switch(int position){
    switch(position){
        case 0 : return PORTFbits.RF3;
            break;
        case 1 : return PORTFbits.RF5;
            break;
        case 2 : return PORTFbits.RF4;
            break;
        case 3 : return PORTDbits.RD15;
            break;
        case 4 : return PORTDbits.RD14;
            break;
        case 5 : return PORTBbits.RB11;
            break;
        case 6 : return PORTBbits.RB10;
            break;
        case 7 : return PORTBbits.RB9;
            break;
        default : break;
    }
    return 0;
}
