#ifndef PWM_H
#define PWM_H

#include <xc.h>
#include <sys/attribs.h>

#define INIT_PWM1(timer) init_pwm(1,timer)
#define INIT_PWM2(timer) init_pwm(2,timer)
#define INIT_PWM3(timer) init_pwm(3,timer)
#define INIT_PWM4(timer) init_pwm(4,timer)
#define INIT_PWM5(timer) init_pwm(5,timer)

#define SET_DUTY1(value) set_duty(1,value)
#define SET_DUTY2(value) set_duty(2,value)
#define SET_DUTY3(value) set_duty(3,value)
#define SET_DUTY4(value) set_duty(4,value)
#define SET_DUTY5(value) set_duty(5,value)

void init_pwm(int position, int timer); 
void set_duty(int position, int dutyValue);
#endif
