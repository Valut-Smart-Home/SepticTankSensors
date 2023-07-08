#include <avr/io.h>

void USART_Init()
{
	UCSRA = (1<<U2X); // Better timing error
	UBRRH = 0;
	UBRRL = 12; // 9600 with U2X = 1
	UCSRB = (1<<TXEN); // TX only
	UCSRC = (3<<UCSZ0); // 8N1
}

void WaitHalfSecond()
{
	asm volatile (
	"    ldi  r18, 3	\n"
	"    ldi  r19, 138	\n"
	"    ldi  r20, 86	\n"
	"1:  dec  r20	\n"
	"    brne 1b	\n"
	"    dec  r19	\n"
	"    brne 1b	\n"
	"    dec  r18	\n"
	"    brne 1b	\n"
	"    rjmp 1f	\n"
	"1:	\n"
	);
}

int main(void)
{
	DDRB = 0; // Inputs
	PORTB = 0xFF; // Pull-up
	USART_Init();
    while (1) 
    {
		while ( !( UCSRA & (1<<UDRE)) );
		UDR = PINB;
		WaitHalfSecond();
    }
}

