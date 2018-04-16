#ifndef _KL_SDCONFIG_H
#define _KL_SDCONFIG_H

#include <SPI.h>
#include <SdFat.h>
#include "nlist.h"

int readSDConfig(const char *configFileName);
char* stripExtraSpaces(char* val);
#endif
