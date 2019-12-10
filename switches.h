/* 
 * File:   switches.h
 * Author: visiteur
 *
 * Created on 10 décembre 2019, 14:13
 */

#ifndef SWITCHES_H
#define	SWITCHES_H

#include <xc.h>
#include <sys/attribs.h>

#define SWITCH0 read_switch(0)
#define SWITCH1 read_switch(1)
#define SWITCH2 read_switch(2)
#define SWITCH3 read_switch(3)
#define SWITCH4 read_switch(4)
#define SWITCH5 read_switch(5)
#define SWITCH6 read_switch(6)
#define SWITCH7 read_switch(7)

#ifdef	__cplusplus
extern "C" {
#endif

void switches_initialisation(void);
uint32_t read_switch(int position);


#ifdef	__cplusplus
}
#endif

#endif	/* SWITCHES_H */

