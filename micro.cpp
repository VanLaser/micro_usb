#include <avr/io.h>
#include <avr/power.h>
#include <string.h>
#include <util/delay.h>

// usb debugging
#include "usb_debug_only.h"
#include "print.h"

inline void init_leds()
{
	DDRB |= _BV(0); // set PB0 on port B to output
	DDRD |= _BV(5); // set PD5 on port D to output
}

inline void toggle_leds()
{
	PORTD |= _BV(5);
	PORTB &= ~_BV(0);
	_delay_ms(300); // wait 1s

	PORTD &= ~_BV(5);
	PORTB |= _BV(0);
	_delay_ms(300);  // wait 1s
}


void spi_init()
{
	// set SS as OUTPUT
	DDRB  |= _BV(0);
	PORTB |= _BV(0); //HIGH

	// enable SPI in master mode
	SPCR = (_BV(MSTR) | _BV(SPE));

	// set SCK and MOSI as output
	DDRB |= (_BV(1) | _BV(2));

	// set MISO as input pullup
	DDRB  &= ~_BV(3);
	PORTB |=  _BV(3);

	// standard mode, 16MHz/4 = 4Mhz
	SPSR = 0;
}

uint8_t spi_transfer(uint8_t data) {
	SPDR = data;
	while (!(SPSR & _BV(SPIF))) ; // wait
	return SPDR;
}

int main() {
	char str[128];
	int n = 0;
	clock_prescale_set(clock_div_1);

	usb_print_init();

	init_leds();

	// SPI loopback test (needs MOSI connected to MISO)

	spi_init();

	_delay_ms(1000);
	while(1) {
		//toggle_leds();

		sprintf(str, "Writing SPI string %d\n", n);
		int len = strlen(str);

		PORTB &= ~_BV(0);
		for (int i = 0; i < len; i++)
			pchar(spi_transfer(str[i]));

		PORTB |= _BV(0);

		++n;
	}

	return 0;
}

