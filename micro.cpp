#include <avr/io.h>
#include <util/delay.h>

#include <LUFA/Drivers/Peripheral/SPI.h>

// usb debugging
#include "usb_debug_only.h"
#include "print.h"

inline void init_leds()
{
	DDRB |= _BV(PB0); // set PB0 on port B to output
	DDRD |= _BV(PD5); // set PD5 on port D to output
}

inline void toggle_leds()
{
	PORTD |= _BV(PD5);
	PORTB &= ~_BV(PB0);
	_delay_ms(1000); // wait 1s

	PORTD &= ~_BV(PD5);
	PORTB |= _BV(PB0);
	_delay_ms(1000);  // wait 1s
}


int main() {
	const char PROGMEM * print_string = "Sample string\n";

	usb_print_init();

	init_leds();

	// SPI loopback test (hookup MOSI to MISO)
	SPI_Init(SPI_SPEED_FCPU_DIV_64 | SPI_MODE_MASTER);

	while(1) {
		//puts("test puts\n");
		//print("test print\n");
		//println("test println");

		toggle_leds();

		println("Starting SPI transfer:");
		_delay_ms(100);
		for (int i = 0; i < 128; ++i)
			SPI_SendByte(' ');
		for (const char * pc = print_string; pc != 0; ++pc)
			pchar(SPI_TransferByte(*pc));

	}

	return 0;
}

