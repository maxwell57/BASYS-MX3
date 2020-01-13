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

void write_word(char* s){
    int i;
    for(i=0; s[i]!=0; ++i){
        write_char(s[i]);
    }
}

void write_text(char* t, int size){
    int i;
    for(i=0; i<size; i++){
        write_char(t[i]);
    }
}

static char read_char(void){
    while(U4STAbits.URXDA != 1);
    char c = U4RXREG;
    return c;
}

void read_word(char* s){
    int i=0;
    s[i] = read_char();
    while(s[i]!=0){
        i++;
        s[i] = read_char();
    }
}

void read_text(char* t){
    LATAbits.LATA0 = 1;
    int i=0;
    t[i] = read_char();
    LATAbits.LATA1 = 1;
    int sortie = 0;
    int n=0;
    while(!sortie){
        i++;
        t[i] = read_char();
        if(t[i] == '0') n++;
        else n = 0;
        if(n==4) sortie = 1;
    }
    LATAbits.LATA2 = 1;
}