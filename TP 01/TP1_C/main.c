/*
 * TP1_C.c
 *
 * Created: 13/08/2021 19:06:07
 * Author : Suyan
 */ 

#include <avr/io.h>

extern void Pisca_Led();


int main(void)
{	
    /* Replace with your application code */
    while (1) 
    {
		Pisca_Led();
    }
}

