#include "i2c.h" 

int start_i2c(int adress_device, adress_ctrl_register){
	I2C1BRG = 2;
	I2C1CONbits.ON = 1;
   I2C1CONbits.SEN = 1;
   while(I2C1CONbits.SEN) ; //wait start signal well send
   I2C1TRN = (adress_device << 1)&0b11111110; //listen to me, slave
   while(I2C1STATbits.TRSTAT); //wait 'til I finish talk 
   if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
   I2C1TRN = adress_ctrl_register; 
   while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
   if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
   I2C1TRN = 1;
   while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
   if(I2C1STATbits.ACKSTAT) return 1;
   I2C1CONbits.PEN = 1;
   while(I2C1CONbits.PEN);
   return 0;
}


int read_i2c(int adress_device, int adress_start_register, int number_of_registers_to_read, int buf[]){
	I2C1CONbits.SEN = 1;
   while(I2C1CONbits.SEN) ; //wait 'til finish sending signal
   I2C1TRN = (adress_device<<1)&0b11111110; // listen to me, slave
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk 
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1TRN = adress_start_register;
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    I2C1CONbits.RSEN = 1;
    while(I2C1CONbits.RSEN) ;//wait 'til finish
    I2C1TRN = (adress_device<<1)&0b11111111 //Talk to me, slave
    while(I2C1STATbits.TRSTAT); //wait 'til I finish talk
    if(I2C1STATbits.ACKSTAT) return 1; //did you understand me ?
    int i,u;
    for(i=0; i<number_of_registers_to_read; i++){
        I2C1CONbits.RCEN = 1;
        I2C1CONbits.ACKDT=(i==(number_of_registers_to_read-1))?1:0;
        while(I2C1CONbits.RCEN);
        u = (char)I2C1RCV;
        if((buf[i]-u)*(buf[i]-u)>=4)buf[i] = u;
        I2C1CONbits.ACKEN = 1;
    }
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
    return 0;
}
