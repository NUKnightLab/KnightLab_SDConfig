#ifndef _KL_SDCONFIG_H
#define _KL_SDCONFIG_H

#include <SPI.h>
#include <SdFat.h>
#include "nlist.h"

char* LStrip(char *val);
char* RStrip(char *val);
int readSDConfig(char *configFileName);
#endif
