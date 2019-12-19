#include "spi.h"


void initSpi(void)
{
    // Configure SPIFLASH signals as digital outputs.
    TRISFbits.TRISF8 = 0;
    TRISFbits.TRISF6 = 0;
    TRISFbits.TRISF2 = 0;
    
    // Configure SPIFLASH signals as digital inputs.
    TRISFbits.TRISF7 = 1;

    // configure remapable pins
    RPF2R = 0x08;   // RPF2R = 1000 = SDO1 
    SDI1R = 0x0F;   // SDI1R = 1111 = RPF7

    // configures SPI1
    SPI1BRG = PB_FRQ / (2 * 1000000) - 1;
    SPI1CONbits.CKP = 0;    // SPI Clock Polarity
    SPI1CONbits.CKE = 1;   // SPI Clock Edge  
    SPI1CONbits.SMP = 0;      // SPI Data Input Sample Phase 
    SPI1CONbits.MSTEN = 1;    // Master
    SPI1CONbits.MODE16 = 0;   // 8 bit transfer
    SPI1CONbits.MODE32 = 0;   // 8 bit transfer
    SPI1CON2bits.AUDEN = 0;   // Audio protocol is disabled
    SPI1CONbits.ON = 1;       // enable SPI    
}

unsigned char SPI_RawTransferByte(unsigned char bVal)
{
    while(!SPI1STATbits.SPITBE);	// wait for TX buffer to be empty
    SPI1BUF = bVal;
    while(!SPI1STATbits.SPIRBF);	// wait for RX buffer to be empty
    return SPI1BUF;
}

void SPI_SendOneByteCmd(unsigned char bCmd)
{
    LATFbits.LATF8 = 0; // Activate SS
    SPI_RawTransferByte(bCmd);
    LATFbits.LATF8 = 1; // Desactivate SS
}

