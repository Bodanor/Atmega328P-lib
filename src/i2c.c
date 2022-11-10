#include "i2c.h"

static short i2c_start(void);
static short i2c_stop(void);
static short i2c_write_address(uint8_t i2c_address_device);
static short i2c_write_data(uint8_t data);
static uint8_t i2c_read(uint8_t ack);

void i2c_init(uint64_t brate)
{
	#ifdef DEBUG
		USART_Init(B9600);
		USART_SendStr("[INFO] I2C Init...\r\n");
	#endif

	/*
	* We don't need a prescalar here
	*/

	switch(brate){
		case I2C_100:
			#ifdef DEBUG
				USART_SendStr("[INFO] I2C Baud is 100Hz\r\n");
			#endif
			TWBR = i2C_BRATE(brate);
			break;
		case i2C_200:
			#ifdef DEBUG
				USART_SendStr("[INFO] I2C Baud is 200Hz\r\n");
			#endif
			TWBR = i2C_BRATE(brate);
			break;
		case i2C_400:
			#ifdef DEBUG
				USART_SendStr("[INFO] I2C Baud is 400Hz\r\n");
			#endif
			TWBR = i2C_BRATE(brate);
			break;
		/*
		* If none of the predefined b-rate are in used then set the default to 100Hz
		*/
		default:
			#ifdef DEBUG
				USART_SendStr("[INFO] I2C Baud is 100Hz\r\n");
			#endif
			TWBR = i2C_BRATE(I2C_100);
			break;
	}

	#ifdef DEBUG
		USART_SendStr("[SUCCESS] I2C Init Success !\r\n");
	#endif

}

short i2c_start()
{
	#ifdef DEBUG
		USART_SendStr("[INFO] Sending Start condition bit ...\r\n");
	#endif

	/*
	* Interrupt Flag
	* Start Condition Flag
	* Enable flag
	*/
	
	TWCR = (1<< TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* TWINT bit should be set if the above task has benn comleted */
	while ((TWCR & (1 << TWINT)) == 0)
		;
	
	/*
	 * Check the Status register and check for the conditon start status : 0x08
	 * Return a value to indicated wether there was an erro or not.
	 */
	if (TW_STATUS != TW_START)
		return -1;
	else
		return 0;
}

static short i2c_stop(void)
{

	#ifdef DEBUG
		USART_SendStr("[INFO] Stop condition sent !\r\n");
	#endif
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

}
short i2c_transmit(uint8_t i2c_address_device, uint8_t data)
{
	if (i2c_start() == -1){

		#ifdef DEBUG
			USART_SendStr("[ERROR] Start condition could not be send !\r\n");
		#endif

		return -1;
	}

	#ifdef DEBUG
			USART_SendStr("[SUCCESS] Start condition sent !\r\n");
	#endif

	if (i2c_write_address((i2c_address_device << 1 ) | TW_WRITE) == -1)
	{
		#ifdef DEBUG
			USART_SendStr("[ERROR] ACK not received from slave !\r\n");
		#endif
		return -1;

	}

	#ifdef DEBUG
		USART_SendStr("[SUCCESS] ACK received from slave !\r\n");
	#endif
	
	if (i2c_write_data(data) == -1){
		#ifdef DEBUG
			USART_SendStr("[ERROR] ACK not received from slave !\r\n");
		#endif
		return -2;
	}

	return 0;
	
}

static short i2c_write_address(uint8_t i2c_address_device)
{
	#ifdef DEBUG
		char s[10];
		USART_SendStr("[INFO] Sending I2C Slave Address : ");
		atohex(i2c_address_device >> 1, s);
		USART_SendStr(s);
		USART_SendStr(" !\r\n");
	#endif

	TWDR = i2c_address_device;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while ((TWCR & (1 << TWINT)) == 0)
		;
	/*
	 * Master Trasmit will receive ACK in transmit mode
	 * OR
	 * Master Transmit will receive ACK in Receive mode
	*/
	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
	{
		return -1;
	}
	else
		return 0;

}

static short i2c_write_data(uint8_t data)
{
	#ifdef DEBUG
		char s[10];
		USART_SendStr("[INFO] Sending I2C Data : ");
		atohex(data, s);
		USART_SendStr(s);
		USART_SendStr(" !\r\n");
	#endif

	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while ((TWCR &(1 << TWINT)) == 0)
		;
	
	if (TW_STATUS != TW_MT_DATA_ACK)
		return -1;
	else{
		i2c_stop();
		return 0;
	}
}
static uint8_t i2c_read(uint8_t ack)
{
	uint8_t data;

	#ifdef DEBUG
		USART_SendStr("[INFO] Reading I2C Data..\r\n");
	#endif

	TWCR = (1 << TWINT) | (1 << TWEN);
	if (ack)
		TWCR |= (1 << TWEA);

	while ((TWCR & (1 << TWINT)))
			;
	
	if (ack)
	{
		if (TW_STATUS != TW_MR_DATA_ACK)
			return -1;
		
	}
	else{
		if (TW_STATUS != TW_MR_DATA_NACK)
			return -1;
	}

	data = TWDR;

	#ifdef DEBUG
		char s[10];
		USART_SendStr("[INFO] Received Data : ");
		atohex(data, s);
		USART_SendStr(s);
		USART_SendStr(" !\r\n");
	#endif

	return data;

}

short i2c_receive(uint8_t i2c_address_device, uint8_t *data, uint8_t read_ack)
{
	if (i2c_start() == -1){

		#ifdef DEBUG
			USART_SendStr("[ERROR] Start condition could not be send !\r\n");
		#endif

		return -1;
	}

	#ifdef DEBUG
			USART_SendStr("[SUCCESS] Start condition sent !\r\n");
	#endif

	if (i2c_write_address((i2c_address_device << 1 ) | TW_READ) == -1)
	{
		#ifdef DEBUG
			USART_SendStr("[ERROR] ACK not received from slave !\r\n");
		#endif
		return -1;

	}

	#ifdef DEBUG
		USART_SendStr("[SUCCESS] ACK received from slave !\r\n");
	#endif
	
	*data = i2c_read(read_ack);

	i2c_stop();

	return 0;


}