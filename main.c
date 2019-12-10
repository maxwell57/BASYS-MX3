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


#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      


#pragma config FNOSC =	2      // select oscilator externe (quartz at 8MHz)
#pragma config FSOSCEN =	OFF     // Disable secondary oscilator
#pragma config POSCMOD =	XT      // XT oscilator mode
#pragma config OSCIOFNC =	ON      //
#pragma config FPBDIV =     DIV_2   // Peripheralls run at /2 the speed

#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

void binary_convert(int dest [], int src);

int main(int argc, char** argv)
{
    //srand(time(NULL));
    srand(42);
    int cmp = 1;
    while(cmp){
        cmp++;
        //int target = rand()%256;
        int target = 42;
        int bin_target[8];
        binary_convert(bin_target,target);
        
        TRISAbits.TRISA0 = 0;
        TRISAbits.TRISA1 = 0;
        TRISAbits.TRISA2 = 0;
        TRISAbits.TRISA3 = 0;
        TRISAbits.TRISA4 = 0;
        TRISAbits.TRISA5 = 0;
        TRISAbits.TRISA6 = 0;
        TRISAbits.TRISA7 = 0;
       
        
        /* RGB Led*/
        /*TRISDbits.TRISD2 = 0;
        TRISDbits.TRISD3 = 0;
        TRISDbits.TRISD12 = 0;
        LATDbits.LATD2 = 0;
        LATDbits.LATD3 = 0;
        LATDbits.LATD12 = 0;*/
        
        /* 7 Segments Display*//*
        TRISBbits.TRISB12 = 0;       //AN0
        ANSELBbits.ANSB12 = 0;
        LATBbits.LATB12 = 0;
        
        TRISAbits.TRISA14 = 0;   //CB
        LATAbits.LATA14 = 0;
        
        TRISDbits.TRISD6 = 0;      //CC
        LATDbits.LATD6 = 0;        //position allumée = 0
        
        TRISGbits.TRISG12 = 0;      //CA
        LATGbits.LATG12 = 0;
        
        TRISGbits.TRISG13 = 0;      //CD
        LATGbits.LATG13 = 0;
        
        TRISGbits.TRISG14 = 0;      //DP
        LATGbits.LATG14 = 0;
        
        TRISGbits.TRISG15 = 0;      //CE
        LATGbits.LATG15 = 0;
        
        TRISDbits.TRISD7 = 0;      //CF
        LATDbits.LATD7 = 0;  
        
        TRISDbits.TRISD13 = 0;      //CG
        LATDbits.LATD13 = 0;  
        
        
        TRISBbits.TRISB13 = 0;       //AN1
        ANSELBbits.ANSB13 = 0;
        LATBbits.LATB13 = 0;
        
        TRISAbits.TRISA9 = 0;       //AN2
        ANSELAbits.ANSA9 = 0;
        LATAbits.LATA9 = 0;
        
        
        TRISAbits.TRISA10 = 0;       //AN3
        ANSELAbits.ANSA10 = 0;
        LATAbits.LATA10 = 0;
        */
        if(cmp%4==1){
            TRISBbits.TRISB12 = 0;
            ANSELBbits.ANSB12 = 0;
            LATBbits.LATB12 = 0;
            
            TRISBbits.TRISB13 = 0;
            ANSELBbits.ANSB13 = 0;
            LATBbits.LATB13 = 1;
            
            TRISGbits.TRISG15 = 0;      
            LATGbits.LATG15 = 0;
            
            TRISGbits.TRISG13 = 0;      
            LATGbits.LATG13 = 1;
        
            TRISDbits.TRISD7 = 0;      
            LATDbits.LATD7 = 0; 
            
        }
        if(cmp%4==2){
            TRISBbits.TRISB13 = 0;
            ANSELBbits.ANSB13 = 0;
            LATBbits.LATB13 = 0;
            
            TRISBbits.TRISB12 = 0;
            ANSELBbits.ANSB12 = 0;
            LATBbits.LATB12 = 1;
            
            TRISGbits.TRISG15 = 0;      
            LATGbits.LATG15 = 1;
            
            TRISGbits.TRISG13 = 0;      
            LATGbits.LATG13 = 0;
        
            TRISDbits.TRISD7 = 0;      
            LATDbits.LATD7 = 0;
            
        }
                
        LATAbits.LATA0 = bin_target[0];
        LATAbits.LATA1 = bin_target[1];
        LATAbits.LATA2 = bin_target[2];
        LATAbits.LATA3 = bin_target[3];
        LATAbits.LATA4 = bin_target[4];
        LATAbits.LATA5 = bin_target[5];
        LATAbits.LATA6 = bin_target[6];
        LATAbits.LATA7 = bin_target[7];
        
        int i,j,k,l;
        //for(i=0; i<0xffff; i++);//for(j=0; j<0xffff; j++);// for(k=0; k<0xffff; k++); //for(l=0; l<0xffff; l++) ; //empty loop
        
    }
   
    return (EXIT_SUCCESS);
}

void binary_convert(int dest [], int src){
    int i;
    for(i=0; i<8; i++){
        dest[i] = src%2;     //dest[i] = src&1;
        src=src/2;          //src>>=1;
    }
}