#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <xc.h>
#include <sys/attribs.h>

#include "i2c.h"

int start_accelerometer(void);
int read_accelerometer(int buffer[]);

#endif
