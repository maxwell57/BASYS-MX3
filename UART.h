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

#ifdef	__cplusplus
extern "C" {
#endif

    void init_UART(void);
    static void write_char(char c);
    static void write_word(char* s);
    static void write_text(char* t, int size);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

