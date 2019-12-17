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


/*** some mayby useful macros***/

/* generics */
#define LED0(a) write_led(0,a)
#define LED1(a) write_led(1,a)
#define LED2(a) write_led(2,a)
#define LED3(a) write_led(3,a)
#define LED4(a) write_led(4,a)
#define LED5(a) write_led(5,a)
#define LED6(a) write_led(6,a)
#define LED7(a) write_led(7,a)

/* explicits */
#define LED0_ON LED0(1)
#define LED0_OFF LED0(0)
#define LED1_ON LED1(1)
#define LED1_OFF LED1(0)
#define LED2_ON LED2(1)
#define LED2_OFF LED2(0)
#define LED3_ON LED3(1)
#define LED3_OFF LED3(0)
#define LED4_ON LED4(1)
#define LED4_OFF LED4(0)
#define LED5_ON LED5(1)
#define LED5_OFF LED5(0)
#define LED6_ON LED6(1)
#define LED6_OFF LED6(0)
#define LED7_ON LED7(1)
#define LED7_OFF LED7(0)

/* booleans */
#define IS_LED0_ON (LATAbits.LATA0>0)?1:0
#define IS_LED1_ON (LATAbits.LATA1>0)?1:0
#define IS_LED2_ON (LATAbits.LATA2>0)?1:0
#define IS_LED3_ON (LATAbits.LATA3>0)?1:0
#define IS_LED4_ON (LATAbits.LATA4>0)?1:0
#define IS_LED5_ON (LATAbits.LATA5>0)?1:0
#define IS_LED6_ON (LATAbits.LATA6>0)?1:0
#define IS_LED7_ON (LATAbits.LATA7>0)?1:0


/*** RGB macros ***/
#define RED_ON light_red();
#define RED_OFF unput_red();
#define GREEN_ON ligth_green();
#define GREEN_OFF unput_green();
#define BLUE_ON light_blue();
#define BLUE_OFF unput_blue();

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


#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

