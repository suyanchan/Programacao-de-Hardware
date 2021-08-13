
/*
 * Assembler1.S
 *
 * Created: 13/08/2021 19:06:56
 *  Author: Suyan
 */ 
  #include <avr/io.h>

 .global Pisca_Led
	Pisca_Led:

		.nolist
		.list
		.ORG 0x000 
			rjmp INICIO
		

		INICIO:
      
		ldi r17, 0b00000000 
		out DDRB, r17
		ldi r17, 0b11111111  
		out DDRC, r17
		ldi r17, 0b00000000
		out DDRD, r17

		ldi r17, 0b00001111
		out PORTB, r17
		ldi r17, 0b11110000
		out PORTC, r17
		ldi r17, 0b11110000
		out PORTD, r17
 
		LOOP:
      
		ldi r17, 0b11110000
		out PORTD, r17

		ldi r17, 0b00001111
		out PORTD, r17

		   rjmp LOOP                
      