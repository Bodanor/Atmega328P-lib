CC = avr-gcc
CFLAGS = -Os -Wall -Wextra -Wshadow -Wdouble-promotion -Wundef -fno-common -Wconversion -ffunction-sections -Wpadded -mmcu=atmega328p -DF_CPU=16000000UL -I/usr/lib/avr/include -Wl,--gc-sections

# TODO: We can also include the Werror 

C_SOURCES := $(wildcard *.c src/*.c)
C_HEADERS := include/$(wildcard *.h)
C_OBJECTS := $(C_SOURCES:%c=%o)
HEADERS_PATH = include/

OUTPUT_FILE = output

DEVICE_PATH = /dev/ttyACM0

PROGRAMMER= avrdude
PROGRAMMER_ARGS:= F -V -c arduino -p ATMEGA328P -P $(DEVICE_PATH) -b 115200 -U flash:w:$(OUTPUT_FILE).hex

all: $(OUTPUT_FILE).hex

$(OUTPUT_FILE).hex: $(OUTPUT_FILE)
	avr-objcopy -O ihex -R .eeprom $^ $@

$(OUTPUT_FILE): $(C_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(C_OBJECTS)


flash:
	$(PROGRAMMER) $(PROGRAMMER_ARGS)


%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERS_PATH)

clean:
	rm -rf *.o
	rm -rf $(OUTPUT_FILE).hex
	rm -rf $(OUTPUT_FILE)
	rm -rf src/*.o

