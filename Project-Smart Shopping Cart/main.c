#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
void motor_init() {
	DDRA |= 0b00111100;     // PA2–PA5 as output
	DDRA &= ~((1 << PA0) | (1 << PA1)); // PA0, PA1 as input (IR)
}

// === Motor Controls ===
void motor_forward() {
	PORTA &= ~((1 << PA3) | (1 << PA5));
	PORTA |=  (1 << PA2) | (1 << PA4);
}

void motor_reverse() {
	PORTA &= ~((1 << PA2) | (1 << PA4));
	PORTA |=  (1 << PA3) | (1 << PA5);
}

void motor_right() {
	PORTA &= ~((1 << PA3) | (1 << PA4) | (1 << PA5));
	PORTA |=  (1 << PA2);
}

void motor_left() {
	PORTA &= ~((1 << PA2) | (1 << PA3) | (1 << PA5));
	PORTA |=  (1 << PA4);
}

void motor_stop() {
	PORTA &= ~((1 << PA2) | (1 << PA3) | (1 << PA4) | (1 << PA5));
}

void set_speed(uint8_t speed) {
	OCR1A = speed;
	OCR1B = speed;
}

void USART_Init(unsigned int ubrr) {
	UBRRH = (ubrr >> 8);
	UBRRL = ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void USART_Transmit(char data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

char USART_Receive(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}
void USART_SendString(const char* str) {
	while (*str) USART_Transmit(*str++);
}

int main(void) {
	OSCCAL = 0xAD;
	USART_Init(6);  // 9600 baud @ 8 MHz
	motor_init();
	// set_speed(20);
	while (1) {
		USART_Transmit('s');
		char c = USART_Receive();
		
		
		USART_Transmit('>');
		USART_Transmit(c);
		if( c == 'F'){
			motor_forward();
		}
		else if (c == 'B'){
			motor_reverse();
		}
		else if( c == 'R'){
			motor_right();
		}
		else if( c == 'L'){
			motor_left();
		}
		else if ( c == 'S'){
			motor_stop();
		}
		else {
			USART_SendString("Mim give valid input\n");
		}
		USART_Transmit('\n');
		
		
	}
}