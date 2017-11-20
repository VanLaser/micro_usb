#ifndef print_h__
#define print_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/pgmspace.h>
#include "usb_debug_only.h"

// run this at start
void usb_print_init(void);

// this macro allows you to write print("some text") and
// the string is automatically placed into flash memory :)
#define dbg_print(s) print_P(PSTR(s))
#define pchar(c) usb_debug_putchar(c)

// define printf-like macros
#define puts(s)          xputs(PSTR(s))
#define print(s)         xputs(PSTR(s))
#define println(s)       xputs(PSTR(s "\r\n"))
#define printf(fmt, ...) xprintf(PSTR(fmt), ##__VA_ARGS__)
#define sprintf(buf, fmt, ...) xsprintf(buf, PSTR(fmt), ##__VA_ARGS__)

void print_P(const char *s);
void phex(unsigned char c);
void phex16(unsigned int i);

#ifdef __cplusplus
}
#endif

#endif
