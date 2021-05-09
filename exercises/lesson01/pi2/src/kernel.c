#include "mini_uart.h"
#include "reset.h"

void kernel_main(void)
{
	uart_init();
	uart_send_string("Hello, world!\r\n");

	while (1) {
		char c = uart_recv();
		uart_send(c);
		if (c == 'r')
		{
			uart_send_string("Reset System!\r\n");
			reset_cpu();
		}
	}
}
