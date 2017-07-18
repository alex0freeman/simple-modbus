ARCH := x86_64-linux-gnu-
ARCH := arm-linux-
CC := $(ARCH)gcc
STRIP := $(ARCH)strip
FLAGS := -I. -Imodbus -Iuart -g
TEST-DIR := test
MODBUS-DIR := modbus

CRC := $(MODBUS-DIR)/crc-modbus.c
FRAME := $(MODBUS-DIR)/frame-access.c

REQUEST := $(MODBUS-DIR)/check-request.c
REQUEST += $(MODBUS-DIR)/make-request.c

RESPONSE := $(MODBUS-DIR)/make-response.c
RESPONSE += $(MODBUS-DIR)/check-response.c

MODBUS := $(MODBUS-DIR)/modbus.c
MODBUS += $(CRC) $(FRAME)
MODBUS += $(REQUEST)
MODBUS += $(RESPONSE)

UART := uart/uart.c uart/accesstermios.c

TEST-REQUEST := $(MODBUS) $(TEST-DIR)/test-request.c
TEST-RESPONSE:= $(MODBUS) $(TEST-DIR)/test-response.c
TEST-MODBUS := $(UART) $(MODBUS) $(TEST-DIR)/test-modbus.c

alltest:
	make test-request
	make test-response
	make test-modbus

uarttest: *.c
	$(CC) *.c -o $@

test-request: $(TEST-REQUEST)
	$(CC) $+ $(FLAGS) -o $@
	$(STRIP) $@

test-response: $(TEST-RESPONSE)
	$(CC) $+ $(FLAGS) -o $@
	$(STRIP) $@

test-modbus: $(TEST-MODBUS)
	$(CC) $+ $(FLAGS) -o $@
	$(STRIP) $@


copy:
	cp uarttest /srv/tftp/

clean:
	@rm -vf uarttest
	@rm -vf test-modbus
	@rm -vf test-request
	@rm -vf test-response
	@rm -vf modbus/*.o
