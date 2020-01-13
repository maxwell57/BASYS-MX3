/* 
 * File:   UART.h
 * Author: visiteur
 *
 * Created on 13 janvier 2020, 12:22
 */

#ifndef UART_H
#define	UART_H

#include <xc.h>
#include <sys/attribs.h>
#define EOF -1

#ifdef	__cplusplus
extern "C" {
#endif

    void init_UART(void);
    static void write_char(char c);
    void write_word(char* s);
    void write_text(char* t, int size);
    
    static char read_char(void);
    void read_word(char* s);
    void read_text(char* t);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

