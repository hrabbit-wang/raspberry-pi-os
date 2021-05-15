#include "mini_uart.h"
#include "uart01.h"
#include "reset.h"

#define BUF_SIZE 256

void preprocessor(char* p_c)
{
	if (*p_c == '\r') {
		*p_c = '\n';
	} else if (*p_c == 127) {
		uart01_send('\b');
		uart01_send(' ');
		*p_c = '\b';
	}
}

void reset_buffer(char* buf, unsigned int size)
{
	for (unsigned int idx = 0; idx < size; idx++) {
		*(buf + idx) = 0;
	}
}

int is_string(const char* buf, const char* str)
{
	int is_equal = 1;
	unsigned int idx = 0;
    for (int i = 0; str[i] != '\0'; i ++) {
		if (buf[i] != str[i]) {
			is_equal = 0;
			break;
		}
	}

	return is_equal;
}

void kernel_main(void)
{
	unsigned int command = -1;
	unsigned int buf_cur_idx = 0u;
	char command_buff[BUF_SIZE];
	reset_buffer(command_buff, BUF_SIZE);
	uart01_init();
	uart01_send_string("Hello, world!\r\n");

	while (1) {
		char c = uart01_recv();
		preprocessor(&c);
		uart01_send(c);

		command_buff[buf_cur_idx++] = c;
		if (c == '\n') {
			command = is_string(command_buff, "reset");
			reset_buffer(command_buff, BUF_SIZE);
			buf_cur_idx= 0u;

			if (command) {
				uart01_send_string("Reset System!\r\n");
				delay(10);
				reset_cpu();
			}
		}
	}
}
