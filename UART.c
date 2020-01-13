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
        if(U4STAbits.UTXBF) while(U4STAbits.TRMT != 1);
}

static void write_word(char* s){
    int i;
    for(i=0; s[i]!=0; ++i){
        write_char(s[i]);
    }
}

static void write_text(char* t, int size){
    int i;
    for(i=0; i<size; i++){
        write_char(s[i]);
    }
}

static char read_char(void){
    while(U4STAbits.URXDA != 1);
    char c = UARXREG;
    return c;
}

static void read_word(char* s){
    int i=0;
    s[i] = read_char();
    while(s[i]!=0){
        i++;
        s[i] = read_char();
    }
}

static void read_text(char* t){
    int i=0;
    t[i] = read_char();
    while(t[i]!=EOF){
        i++;
        t[i] = read_char();
    }
}