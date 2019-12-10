#include "segments_display.h"

inline void segments_display_initialisation(void){
    //cathodes
    TRISGbits.TRISG12 = 0; //CA
    TRISAbits.TRISA14 = 0; //CB
    TRISDbits.TRISD6 = 0; //CC
    TRISGbits.TRISG13 = 0; //CD
    TRISGbits.TRISG15 = 0; //CE
    TRISDbits.TRISD7 = 0; //CF
    TRISDbits.TRISD13 = 0; //CG
    TRISGbits.TRISG14 = 0; //DP
    
    //anodes
    TRISBbits.TRISB12 = 0; //AN0
    ANSELBbits.ANSB12 = 0;
    TRISBbits.TRISB13 = 0; //AN1
    ANSELBbits.ANSB13 = 0;
    TRISAbits.TRISA9 = 0; //AN2
    ANSELAbits.ANSA9 = 0;
    TRISAbits.TRISA10 = 0; //AN3
    ANSELAbits.ANSA9 = 0;
}

void digit_7_segments_display(int digit){
    //cathods only
    switch(digit%10){
        case 0 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 0; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 1; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 1 : 
            LATGbits.LATG12 = 1; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 1; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 1; //CF
            LATDbits.LATD13 = 1; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 2 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 1; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 0; //CE
            LATDbits.LATD7 = 1; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 3 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 1; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 4 : 
            LATGbits.LATG12 = 1; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 1; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 5 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 1; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 6 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 1; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 0; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 7 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 1; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 1; //CF
            LATDbits.LATD13 = 1; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 8 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 0; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        case 9 : 
            LATGbits.LATG12 = 0; //CA
            LATAbits.LATA14 = 0; //CB
            LATDbits.LATD6 = 0; //CC
            LATGbits.LATG13 = 0; //CD
            LATGbits.LATG15 = 1; //CE
            LATDbits.LATD7 = 0; //CF
            LATDbits.LATD13 = 0; //CG
            LATGbits.LATG14 = 1; //DP
            break;
        default : break;
    }
}

void choose_anode(int position){
    switch(position){
        case 0 : 
            LATAbits.LATA10 = 1;
            LATAbits.LATA9 = 1;
            LATBbits.LATB13 = 1;
            LATBbits.LATB12 = 0;
            break;
        case 1 : 
            LATAbits.LATA10 = 1;
            LATAbits.LATA9 = 1;
            LATBbits.LATB13 = 0;
            LATBbits.LATB12 = 1;
            break;
        case 2 : 
            LATAbits.LATA10 = 1;
            LATAbits.LATA9 = 0;
            LATBbits.LATB13 = 1;
            LATBbits.LATB12 = 1;
            break;
        case 3 : 
            LATAbits.LATA10 = 0;
            LATAbits.LATA9 = 1;
            LATBbits.LATB13 = 1;
            LATBbits.LATB12 = 1;
            break;
        
    }
    
}

inline void stop_anodes(void){
    LATAbits.LATA10 = 1;
    LATAbits.LATA9 = 1;
    LATBbits.LATB13 = 1;
    LATBbits.LATB12 = 1;
}

inline void set_number_position(int position, int number){
    stop_anodes();
    digit_7_segments_display(number);
    choose_anode(position);
}