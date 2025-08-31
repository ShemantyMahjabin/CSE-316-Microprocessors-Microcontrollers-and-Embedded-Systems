/*
 * led2.c
 *
 * Created: 5/18/2025 12:18:01 PM
 * Author : Fatin
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char rowWiseLetter[8] = {
	0b11111000,
	0b10000100,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000010,
	0b10000100,
	0b11111000
};

volatile uint8_t shiftLeftRight = 0;
volatile uint8_t shiftTopBottom = 0;

void init_interrupts() {
	MCUCR |= (1 << ISC01) | (1 << ISC00);  // INT0 on rising edge
	MCUCR |= (1 << ISC11) | (1 << ISC10);  // INT1 on rising edge

	GICR |= (1 << INT0) | (1 << INT1);     // Enable INT0 and INT1

	sei(); // Enable global interrupts
}

ISR(INT0_vect) {
	shiftLeftRight ^= 1; // Toggle left-right shifting
}

ISR(INT1_vect) {
	shiftTopBottom ^= 1; // Toggle top-bottom shifting
}

void displayFrame() {
	for (int i = 0; i < 8; i++) {
		PORTA = (1 << i);               // Select row i (set only bit i)
		PORTB = ~rowWiseLetter[i];       // C selects column (0 for selection)
		_delay_ms(2.5);                   // Small delay to stabilize the LED display
	}
}

void shift_pattern_left_wrap() {
	for (int i = 0; i < 8; i++) {
		uint8_t msb = (rowWiseLetter[i] & 0x80) >> 7;  // Extract most significant bit
		rowWiseLetter[i] = (rowWiseLetter[i] << 1) | msb;    // Shift left and wrap MSB to LSB
	}
}

void shift_pattern_right_wrap() {
	for (int i = 0; i < 8; i++) {
		uint8_t lsb = rowWiseLetter[i] & 0x01;            // Extract least significant bit
		rowWiseLetter[i] = (rowWiseLetter[i] >> 1) | (lsb << 7); // Shift right and wrap LSB to MSB
	}
}

void shift_pattern_up_wrap() {
	uint8_t topRow = rowWiseLetter[0];
	for (int i = 0; i < 7; i++) {
		rowWiseLetter[i] = rowWiseLetter[i + 1];
	}
	rowWiseLetter[7] = topRow;  // Wrap the top row to the bottom
}

void shift_pattern_down_wrap() {
	uint8_t bottomRow = rowWiseLetter[7];
	for (int i = 7; i > 0; i--) {
		rowWiseLetter[i] = rowWiseLetter[i - 1];
	}
	rowWiseLetter[0] = bottomRow;  // Wrap the bottom row to the top
}



int main(void) {
	DDRA = 0xFF;  // Set PORTA as output (rows)
	DDRB = 0xFF;  // Set PORTB as output (columns)

	while (1) {
		for (int i = 0; i < 20; i++)
		displayFrame();  // Keep refreshing display to avoid flickering
	}
	
	return 0;
}