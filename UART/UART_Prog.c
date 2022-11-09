#include "UART_Interface.h"
#include "UART_Registers.h"
#include "UART_Config.h"
#include "../DIO/dio.h"


void UART_init(void)
{
    // Pins Configuration
    DIO_pinMode(PORTD, PIN1, OUT); // TX
    DIO_pinMode(PORTD, PIN0, IN);  // RX
    // UCSRA Configuration
    #if DOUBLE_SPEED_ENABLE == ENABLED
        setPin(UCSRA, U2X);
    #else
        clrPin(UCSRA, U2X);
    #endif

    #if MULTI_PROCESSOR_COMMUNICATION == ENABLED
        setPin(UCSRA, MPCM);
    #else
        clrPin(UCSRA, MPCM);
    #endif

    // UCSRB Configuration

    // Interrupts  
    #if RX_INTERRUPT_ENABLE == ENABLED
        setPin(UCSRB, RXCIE);
    #else
        clrPin(UCSRB, RXCIE);
    #endif  

    #if TX_INTERRUPT_ENABLE == ENABLED
        setPin(UCSRB, TXCIE);
    #else
        clrPin(UCSRB, TXCIE);
    #endif

    #if EMPTY_DATA_REGISTER_INTERRUPT_ENABLE == ENABLED
        setPin(UCSRB, UDRIE);
    #else
        clrPin(UCSRB, UDRIE);
    #endif

    setPin(UCSRB, RXEN);  // RX Enable
    setPin(UCSRB, TXEN);  // TX Enable
    
    // Data Size
    #if DATA_SIZE == 9
        setPin(UCSRB, UCSZ2);
    #else
        clrPin(UCSRB, UCSZ2);
    #endif

    // UCSRC Configuration
    uint8_t temp = UCSRC;

    setPin(temp, URSEL);  // UCSRC Register Select

    #if UART_MODE_SELECT == UART_ASYNCHRONOUS_MODE
        clrPin(temp, UMSEL);
    #else
        setPin(temp, UMSEL);
    #endif

    #if PARITY_MODE_SELECT == PARITY_MODE_EVEN
        setPin(temp, UPM1);
        clrPin(temp, UPM0);
    #elif PARITY_MODE_SELECT == PARITY_MODE_ODD
        setPin(temp, UPM1);
        setPin(temp, UPM0);
    #else// Disable Parity
        clrPin(temp, UPM1); 
        clrPin(temp, UPM0);
    #endif

    #if STOP_BITS_SELECT == STOP_BITS_2
        setPin(temp, USBS);
    #else
        clrPin(temp, USBS); // 1 Stop Bit
    #endif

    #if DATA_SIZE == 9
        setPin(temp, UCSZ1);
        setPin(temp, UCSZ0);
    #elif DATA_SIZE == 8
        setPin(temp, UCSZ1);
        clrPin(temp, UCSZ0);
    #elif DATA_SIZE == 7
        clrPin(temp, UCSZ1);
        setPin(temp, UCSZ0);
    #else
        clrPin(temp, UCSZ1);
        clrPin(temp, UCSZ0);
    #endif

    #if UART_MODE_SELECT == UART_SYNCHRONOUS_MODE
        #if CLOCK_POLARITY == 0
            clrPin(temp, UCPOL);
        #else
            setPin(temp, UCPOL);
        #endif
    #endif


    UCSRC = temp; // Write to UCSRC Register

    // UBBR Configuration
    UCSRC = 0; // Clear UBBRH 
    UBRRL = BAUD_9600HZ; 

}

void UART_sendByte(const uint8_t data)
{
    while (getPin(UCSRA, UDRE) == 0); // Wait until UDR is Empty
    setPin(UCSRA, TXC); // Clear TXC Flag
    UDR = data;
}

uint8_t UART_receiveByte(void)
{
    while (getPin(UCSRA, RXC) == 0); // Wait until Data is Received
    setPin(UCSRA, RXC); // Clear RXC Flag
    return UDR;
}
