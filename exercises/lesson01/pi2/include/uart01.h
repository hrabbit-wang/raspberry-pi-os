#ifndef	_UART01_H
#define	_UART01_H

void uart01_init ( void );
char uart01_recv ( void );
void uart01_send ( char c );
void uart01_send_string(char* str);

#endif  /*_UART_H */