#include <avr/io.h>
#include <util/delay.h>

// usb debugging
#include "usb_debug_only.h"
#include "print.h"

int main() {

	usb_print_init();

	while(1) {
		_delay_ms(1000);  // wait 1s
		puts("test puts\n");
		print("test print\n");
		println("test println");
		printf("test printf: this is the value of PB0: %d\n", PB0);

	}

	return 0;
}

