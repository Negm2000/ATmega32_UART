#ifndef DBD80D37_C841_4996_8305_17772FF59F27
#define DBD80D37_C841_4996_8305_17772FF59F27
#include <stdint.h>


void UART_init(void);
void UART_sendByte(uint8_t data);
uint8_t UART_receiveByte(void);
void UART_sendString(uint8_t*);


#endif /* DBD80D37_C841_4996_8305_17772FF59F27 */
