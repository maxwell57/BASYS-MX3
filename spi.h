/* 
 * File:   spi.h
 * Author: Clément Roblot
 *
 * Created on December 18, 2019, 1:24 PM
 */

#ifndef SPI_H
#define	SPI_H

#include <xc.h>
#include <sys/attribs.h>
//#include "config.h"

#define PB_FRQ 4000000


void initSpi(void);


unsigned char SPI_RawTransferByte(unsigned char bVal);
void SPI_SendOneByteCmd(unsigned char bCmd);






#endif	/* SPI_H */

