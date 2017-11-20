MCU          = atmega32u4
ARCH         = AVR8
BOARD        = MICRO
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = micro
SRC          = $(TARGET).cpp usb_debug/usb_debug_only.c usb_debug/print.c usb_debug/xprintf.S
LUFA_PATH    = lufa/LUFA
CC_FLAGS     = -Iusb_debug -DF_CPU=$(F_CPU)UL
LD_FLAGS     =

# Arduino Leanardo compatible flashing
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_PORT = /dev/ttyACM0


# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

flash: $(TARGET).hex
	ls /dev/tty* > /tmp/1; \
		echo "Detecting USB port, reset your controller now.\c"; \
		while [ -z $$USB ]; do \
		sleep 1; \
		echo ".\c"; \
		ls /dev/tty* > /tmp/2; \
		USB=`diff /tmp/1 /tmp/2 | grep -o '/dev/tty.*'`; \
		done; \
		echo ""; \
		echo "Detected controller on USB port at $$USB"; \
		sleep 1; \
		avrdude -p $(MCU) -c avr109 -P $$USB -U flash:w:$(TARGET).hex;

