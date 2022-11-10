#include <avr/io.h>
#include "uart.h"
#include "i2c.h"
#include <util/delay.h>

int main()
{
    _delay_ms(3000);
    i2c_init(i2C_400);
    while(1){
        i2c_transmit(0x27, 'h');
        _delay_ms(10000);
    }
    return 0;

    /*
    uint8_t data[2];
    data[0] = 0b00110100;
    data[1] = 0;
    tw_master_transmit(0x27, data, sizeof(data), false);
    _delay_ms(5);
    tw_master_transmit(0x27, data, sizeof(data), false);
    _delay_ms(110);
    tw_master_transmit(0x27, data, sizeof(data), false);
    _delay_ms(50);
    data[0] = 0b00100100;
    data[1] =0;
    tw_master_transmit(0x27, data, sizeof(data), false);
    _delay_ms(50);

    data[0] = 0b00100100;
    data[1] = 0;
    tw_master_transmit(0x27, data, sizeof(data), false);
    tw_master_transmit(0x27, data, sizeof(data), false);

    _delay_ms(50);

    data[0] = 0b00000100;
    data[1] = 0;
    tw_master_transmit(0x27, data, sizeof(data), false);
    data[0] = 0b10000100;
    data[1] = 0;
    */
}