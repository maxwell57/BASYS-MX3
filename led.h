/* 
 * File:   led.h
 * Author: visiteur
 *
 * Created on 10 décembre 2019, 13:55
 */

#ifndef LED_H
#define	LED_H

#include <xc.h>
#include <sys/attribs.h>

//#include "pwm.h"

#define LED0(a) write_led(0,a)
#define LED1(a) write_led(1,a)
#define LED2(a) write_led(2,a)
#define LED3(a) write_led(3,a)
#define LED4(a) write_led(4,a)
#define LED5(a) write_led(5,a)
#define LED6(a) write_led(6,a)
#define LED7(a) write_led(7,a)


#ifdef	__cplusplus
extern "C" {
#endif

    void led_initialisation(void);
    void led_global_extinction(void);
    void write_led(int position, uint32_t value);
    
    void rgb_initialisation(void);
    void rgb_extinction(void);
    
    void unput_red(void);
    void unput_green(void);
    void unput_blue(void);
    
    void put_red(uint32_t value);
    void put_green(uint32_t value);
    void put_blue(uint32_t value);
    
    void light_red(void);
    void light_green(void);
    void light_blue(void);

	//void init_rgb_pwm(int timer);
	//void rgb_pwm(int puissance, int r, int g, int b);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

