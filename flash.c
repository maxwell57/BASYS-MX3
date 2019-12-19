#include "flash.h"

int WaitNotBusy(void){
    int busy;
    do{
        LATFbits.LATF8 = 0;
        SPI_RawTransferByte(05);
        busy = SPI_RawTransferByte(0);
        LATFbits.LATF8 = 1;
	}while(busy&1);
	return 0;
}

int  WriteEnable(void){
	WaitNotBusy();
	SPI_SendOneByteCmd(0x06);
	return 0;  // ou attendre ?
}

int Erase(int adress){
	WriteEnable();
	LATFbits.LATF8 = 0; // Activate SS
	SPI_RawTransferByte(0x20); //Send sector erase cmd
	/* Send adress */
	SPI_RawTransferByte((adress>>16)&0xff); 
	SPI_RawTransferByte((adress>>8)&0xff);
	SPI_RawTransferByte(adress&0xff);
	
	LATFbits.LATF8 = 1; // Desactivate SS
	return WaitNotBusy();
}
 int Write(int page_adress, unsigned char data[], int data_size){
	WriteEnable();
	LATFbits.LATF8 = 0; // Activate SS
	SPI_RawTransferByte(0x02); //Send program page cmd
	 /* Send page adress */
	SPI_RawTransferByte((page_adress>>16)&0xff); 
	SPI_RawTransferByte((page_adress>>8)&0xff);
	SPI_RawTransferByte(page_adress&0xff);
	
	/* Send data */
	int i;
	for(i=0; i<data_size; i++) SPI_RawTransferByte(data[i]);
	
	LATFbits.LATF8 = 1; // Desactivate SS
	return WaitNotBusy();
 }


int Read(int page_adress, unsigned char data[], int data_size){
	LATFbits.LATF8 = 0; // Activate SS
	SPI_RawTransferByte(0x03); //Send program page cmd
	  /* Send page adress */
	 SPI_RawTransferByte((page_adress>>16)&0xff); 
	SPI_RawTransferByte((page_adress>>8)&0xff);
	SPI_RawTransferByte(page_adress&0xff);
	int i;
	for(i=0; i<data_size; i++) data[i] = SPI_RawTransferByte(0);
	
	LATFbits.LATF8 = 1; // Desactivate SS
	return WaitNotBusy();
}
