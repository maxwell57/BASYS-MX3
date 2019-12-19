#ifned FLASH_H
#define FLASH_H

#include <xc.h>
#include <sys/attribs.h>

#include "spi.h"

int WaitNotBusy(void);
int  WriteEnable(void);
int Erase(int adress);
int Write(int page_adress, unsigned char data[], int data_size);
int Read(int page_adress, unsigned char data[], int data_size);

#endif
