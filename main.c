/*
 * main.c
 *
 * Created: 4/29/2021 7:54:43 PM
 *  Author: mcvpi
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
//#include <asf.h>
#include <xc.h>

void init_IO();
void flash();
float input_A(float counter_A);
float input_B(float counter_B);
void display_A(float counter_A);
void display_B(float counter_B);
// void display_output_G(float counter_A);

// Define LED Display
// BS-C536RI - Common Cathode
// BS-A536RI - Common Anode
#define F0 0x3F     // Zero;
#define F1 0x0C		// One
#define F2 0x5B		// Two
#define F3 0x5E		// Three
#define F4 0x6C		// Four
#define F5 0x76		// Five
#define F6 0x77		// Six
#define F7 0x1C		// Seven
#define F8 0x7F		// Eight
#define F9 0x7E		// Nine


#define DELAY 500		// ms
#define ON 0
#define OFF 1

int main()
{
    init_IO();
	flash();
		
	float Display_Led_One = 0;
	float Display_Led_Two = 0;
	
	while(1)
	{
		Display_Led_One = input_A(Display_Led_One);
		
		Display_Led_Two = input_B(Display_Led_Two);
		
		display_A(Display_Led_One);
		
		display_B(Display_Led_Two);
		
		//display_output_G(counter_A);	
	}
	
	
}

void init_IO()
{
	DDRA = 0xFF;			// PORT A - ALL OUTPUTS; INPUT LED 1
	DDRD = 0xFF;			// PORT D - ALL OUTPUTS; INPUT LED 2
	
	DDRF = 0xFF;			// PORT F - ALL OUTPUTS; OUTPUT LED 2
	DDRB = 0xFF;			// PORF B - ALL OUTPUTS; OUTPUT LED 2
	
	DDRG = 0x18;			// PORT G - (PG4, PG3), input (PG2,PG1,PG0)
	PORTG = 0x07;			// PORT G - Pull ups on PG1, PG2, PG3
	
	/* PORTG |= (_BV(3) | _BV(4)); */
}

void flash()
{
	for (int j = 0; j <= 9; j++) {
		switch(j) {
			case 0:
				PORTA = F0;
				PORTD = F0;
				PORTF = F0;
				PORTB = F0;
				_delay_ms(DELAY);
				break;
			case 1:
				PORTA = F1;
				PORTD = F1;
				PORTF = F1;
				PORTB = F1;
				_delay_ms(DELAY);
				break;
			case 2:
				PORTA = F2;
				PORTD = F2;
				PORTF = F2;
				PORTB = F2;
				_delay_ms(DELAY);
			case 3:
				PORTA = F3;
				PORTD = F3;
				PORTF = F3;
				PORTB = F3;
				_delay_ms(DELAY);
				break;
			case 4:
				PORTA = F4;
				PORTD = F4;
				PORTF = F4;
				PORTB = F4;
				_delay_ms(DELAY);
				break;
			case 5:
				PORTA = F5;
				PORTD = F5;
				PORTF = F5;
				PORTB = F5;
				_delay_ms(DELAY);
				break;
			case 6:
				PORTA = F6;
				PORTD = F6;
				PORTF = F6;
				PORTB = F6;
				_delay_ms(DELAY);
				break;
			case 7:
				PORTA = F7;
				PORTD = F7;
				PORTF = F7;
				PORTB = F7;
				_delay_ms(DELAY);
				break;
			case 8:
				PORTA = F8;
				PORTD = F8;
				PORTF = F8;
				PORTB = F8;
				_delay_ms(DELAY);
				break;
			case 9:
				PORTA = F9;
				PORTD = F9;
				PORTF = F9;
				PORTB = F9;
				_delay_ms(DELAY);
				break;
		}
	}
}

float input_A(float counter_A)
{
	int switch_LED1 = OFF;					// initialise bit value to 1

	switch_LED1 = PING & _BV(PG0); 			// Assign PG0 to pushbutton 1

	_delay_ms(3*DELAY/15);					// some delay

	if (switch_LED1 == ON)           			// bit value is 0
	{
		if (counter_A == 9)				// counter at max value
		counter_A = 0;				// change counter value to zero
		else
		counter_A++;				// increment
	}
	return counter_A;
}

float input_B(float counter_B)
{
	int switch_LED2 = OFF;

	switch_LED2 = PING & _BV(PG1); 			// Assign PG1 to pushbutton 2

	_delay_ms(3*DELAY/15);					// some delay

	if (switch_LED2 == ON)           			// bit value is 0
	{
		if (counter_B == 9)				// counter at min value
		counter_B = 0;				// change counter value to three
		else
		counter_B++;				// decrement
	}
	return counter_B;
}

void display_A(float counter_A)
{
	int increment_LED1 = OFF;
	increment_LED1 = PING & _BV(PG0);

	if (increment_LED1 == ON)
	{
		if (counter_A == 0)
		PORTA = F0;				// display '0'
		else if (counter_A == 1)
		PORTA = F1;				// display '1'
		else if (counter_A == 2)
		PORTA = F2;				// display '2'
		else if (counter_A == 3)
		PORTA = F3;				// display '3'
		else if (counter_A == 4)
		PORTA = F4;				// display '4'
		else if (counter_A == 5)
		PORTA = F5;				// display '5'
		else if (counter_A == 6)
		PORTA = F6;				// display '6'
		else if (counter_A == 7)
		PORTA = F7;				// display '7'
		else if (counter_A == 8)
		PORTA = F8;				// display '8'
		else if (counter_A == 9)
		PORTA = F9;				// display '9'
		_delay_ms(DELAY);					// display for 3 seconds
	}
}

void display_B(float counter_B)
{
	int increment_LED2 = OFF;
	increment_LED2 = PING & _BV(PG1);

	if (increment_LED2 == ON)
	{
		if (counter_B == 0)
		PORTD = F0;				// display '0'
		else if (counter_B == 1)
		PORTD = F1;				// display '1'
		else if (counter_B == 2)
		PORTD = F2;				// display '2'
		else if (counter_B == 3)
		PORTD = F3;				// display '3'
		else if (counter_B == 4)
		PORTD = F4;				// display '4'
		else if (counter_B == 5)
		PORTD = F5;				// display '5'
		else if (counter_B == 6)
		PORTD = F6;				// display '6'
		else if (counter_B == 7)
		PORTD = F7;				// display '7'
		else if (counter_B == 8)
		PORTD = F8;				// display '8'
		else if (counter_B == 9)
		PORTD = F9;				// display '9'
		_delay_ms(DELAY);					// display for 3 seconds
	}
}
/*
void display_output_G(float counter_A)
{
	if (counter_A == 0)
	PORTG |= (_BV(3) | _BV(4));			// bit values 1 - Both Red LEDs off
	else if (counter_A == 1)
	{
		PORTG |= _BV(3);				// bit value 1 - Red LED off
		PORTG &= ~_BV(4);				// bit value 0 - Red LED on
	}
	else if (counter_A == 2)
	{
		PORTG &= ~_BV(3);				// bit value 0 - Red LED on
		PORTG |= _BV(4);				// bit value 1 - Red LED off
	}
	else
	PORTG &= ~(_BV(3) | _BV(4));			// bit value 0 - Both Red LEDs on
}
*/