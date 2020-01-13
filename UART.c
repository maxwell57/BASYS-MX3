#include "UART.h"

void init_UART(void){
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

static void write_char(char c){
        U4TXREG = c;
}

static void(char* s){
    int i;
    for(i=0; s[i]!=0; ++i){
        write_char(s[i]);
        if(U4STAbits.UTXBF) while(U4STAbits.TRMT != 1);
    }
}