#ifndef I2C_H
#define I2C_H

#include <xc.h>
#include <sys/attribs.h>

int start_i2c(int adress_device, int adress_ctrl_register);
int read_i2c(int adress_device, int adress_start_register, int number_of_registers_to_read, int buf[]);

#endif
