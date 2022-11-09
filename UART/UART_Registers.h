#ifndef __UART_REGISTERS_H__
#define __UART_REGISTERS_H__
#include <stdint.h>

// UART Registers
#define UDR		*((volatile uint8_t*)0x2C)
#define UCSRA	*((volatile uint8_t*)0x2B)
#define UCSRB	*((volatile uint8_t*)0x2A)
#define UCSRC	*((volatile uint8_t*)0x40)
#define UBRRL	*((volatile uint8_t*)0x29)
#define UBRRH	*((volatile uint8_t*)0x40)

// UCSRA Bits
#define RXC		7
#define TXC		6
#define UDRE	5
#define FE		4
#define DOR		3
#define PE		2
#define U2X		1
#define MPCM	0

// UCSRB Bits

#define RXCIE	7
#define TXCIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

// UCSRC Bits
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0

#endif // __UART_REGISTERS_H__
