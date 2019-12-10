/* 
 * File:   segments_display.h
 * Author: visiteur
 *
 * Created on 10 décembre 2019, 14:24
 */

#ifndef SEGMENTS_DISPLAY_H
#define	SEGMENTS_DISPLAY_H

#include <xc.h>
#include <sys/attribs.h>

#define D7S0(a) set_number_position(0,a)
#define D7S1(a) set_number_position(1,a)
#define D7S2(a) set_number_position(2,a)
#define D7S3(a) set_number_position(3,a)

#ifdef	__cplusplus
extern "C" {
#endif

void segments_display_initialisation(void);
void digit_7_segments_display(int digit);
void choose_anode(int position);
void stop_anodes(void);
void set_number_position(int position, int number);



#ifdef	__cplusplus
}
#endif

#endif	/* SEGMENTS_DISPLAY_H */

