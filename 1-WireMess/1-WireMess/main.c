/*
 * 1-WireMess.c
 *
 * Created: 6/11/2016 5:20:12 PM
 * Author : Noah
 */
 #define F_CPU 8000000L

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "OneWire.h"
#include "BasicSerial.h"

#define CS PB1

static inline void SPIInit(){
	DDRB &= ~(1 << PB2);
	USICR = (1 << USICS1) | (1 << USIWM0) | (1 << USIOIE);
	USISR = (1 << USIOIF);
	USIDR = 0;
}

void serOut(const char* str)
{
	while (*str) TxByte(*str++);
}

char* itoa(int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

int main(void)
{
	_delay_ms(5000);
	serOut("Booting up...");

	cli();

    DDRB  = 0b111110 & ~(1 << CS);
    PORTB = 0b101001 & ~(1 << CS);

	PORTB |= (1 << PB4);
	_delay_ms(500);

	//SPIInit();

	OWSetup(true);

	sei();

	serOut("Done\n");

	while(true){
		char temp[] = "\0\0\0\0";
		OWCheckRecv(temp);
		if(temp[0] != '\0'){
			serOut(temp);
			serOut("\n");
			if(!memcmp(temp, "BEE", 3)){
				PORTB &= ~(1 << PB4);
				_delay_ms(200);
				PORTB |= (1 << PB4);
			}
		}
	}	
}

//ISR(USI_OVF_vect){
//	USISR = (1 << USIOIF);
//}



