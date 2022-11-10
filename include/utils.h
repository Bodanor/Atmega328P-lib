#ifndef __UTILS_H__
#define __UTILS_H__

#include <avr/io.h>
#include <string.h>


void itoa(unsigned int n, char *s);
void atohex(uint8_t src, char *dst);
#endif