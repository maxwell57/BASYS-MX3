#ifndef TIMER_H
#define TIMER_H

#define PB_FRQ 4000000
#define MILLION 1000000

#include <xc.h>
#include <sys/attribs.h>


#define TIMER1(a,b) init_timer(1,a,b)
#define TIMER2(a,b) init_timer(2,a,b)
#define TIMER3(a,b) init_timer(3,a,b)
#define TIMER4(a,b) init_timer(4,a,b)
#define TIMER5(a,b) init_timer(5,a,b)

#define TIMER1US(period) set_timer_us(1,period)
#define TIMER2US(period) set_timer_us(2,period)
#define TIMER3US(period) set_timer_us(3,period)
#define TIMER4US(period) set_timer_us(4,period)
#define TIMER5US(period) set_timer_us(5,period)

#define TIMER1HZ(frequence) set_timer_Hz(1,frequence)
#define TIMER2HZ(frequence) set_timer_Hz(2,frequence)
#define TIMER3HZ(frequence) set_timer_Hz(3,frequence)
#define TIMER4HZ(frequence) set_timer_Hz(4,frequence)
#define TIMER5HZ(frequence) set_timer_Hz(5,frequence)

#ifdef	__cplusplus
extern "C" {
#endif

void init_timer(int position, int prescale, int delay);
void set_timer_us(int position, int  period);
void set_timer_Hz(int position, float frequence);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */
