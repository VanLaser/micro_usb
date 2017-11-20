#include <avr/io.h>
#include <avr/power.h>
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
	const char * print_string = "Sample string\n";
	clock_prescale_set(clock_div_1);

	usb_print_init();

	init_leds();

	// TODO: LUFA does not use the right pins for Arduino Micro (variant of Leonardo)
	// The pins are actually:
	static const uint8_t SS   = 17;
	static const uint8_t MOSI = 16;
	static const uint8_t MISO = 14;
	static const uint8_t SCK  = 15;

	// SPI loopback test (hookup MOSI to MISO)
	SPI_Init(SPI_SPEED_FCPU_DIV_4 | SPI_MODE_MASTER);

	while(1) {
		//puts("test puts\n");
		//print("test print\n");
		//println("test println");

		toggle_leds();

		println("Starting SPI transfer:");
		_delay_ms(100);
		for (const char * pc = print_string; pc != 0; ++pc)
		{
			char c = SPI_TransferByte(*pc);
			pchar(c);
		}

	}

	return 0;
}

