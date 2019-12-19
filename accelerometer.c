#include "accelerometer.h"

int start_accelerometer(void){
	TRISGbits.TRISG3 = 0;
    TRISGbits.TRISG2 = 0;
    
	return start_i2c(0x1d,0x2a);
	}
	
	int read_accelerometer(int buffer[]){
		return read_i2c(0x1d,0x01,6,buffer);
	}
