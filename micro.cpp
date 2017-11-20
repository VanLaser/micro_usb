#include <avr/io.h>
#include <util/delay.h>

// usb debugging
#include "usb_debug_only.h"
#include "print.h"

int main() {

	DDRB |= _BV(PB0); // set PB0 on port B to output
	DDRD |= _BV(PD5); // set PD5 on port D to output

	usb_print_init();

	while(1) {
		_delay_ms(1000);  // wait 1s
		PORTD |= _BV(PD5);
		PORTB &= ~_BV(PB0);
		_delay_ms(1000); // wait 1s
		PORTD &= ~_BV(PD5);
		PORTB |= _BV(PB0);

		//puts("test puts\n");
		//print("test print\n");
		//println("test println");

		printf("The value of PB0 is: %d\n", PB0);
	}

	return 0;
}

