
#ifndef _TALKIE_I2S_H
#define _TALKIE_I2S_H

#include "talkie/config.h"

// void i2s_0_begin();

void i2s_1_begin();
void i2s_1_read(void *dest, size_t size, size_t *bytes_read);

#endif
