#ifndef __I2C_H__
#define __I2C_H__

#include <avr/io.h>
#include <util/twi.h>
#include <stdint.h>

#include "utils.h"
#include "uart.h"

#define i2C_BRATE(HZ) ((F_CPU/HZ) -16)/2
#define I2C_100 100000
#define i2C_200 200000
#define i2C_400 400000

void i2c_init(uint64_t brate);
/*
 * Return :
	0 : Operation success
 	-1 if Slave Address could not be sent
	-2 If Slave data could not be sent

 */
short i2c_transmit(uint8_t i2c_address_device, uint8_t data);
short i2c_receive(uint8_t i2c_address_device, uint8_t *data, uint8_t read_ack);
#endif