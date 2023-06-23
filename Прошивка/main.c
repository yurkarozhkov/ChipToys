#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL
unsigned int count1=0;

int main(void)
{
	DDRB= 0b00101101;
	PORTB=0b00011010;
	
	MCUCR=0b00110000;             // Sleep enable, mode: power-down
	GIMSK=0b01100000;             // Pin Change Interrupt Enable
	PCMSK=0b00010000;             // PCINT4 & PCINT3 set
	asm("sei");
	
	while(1)
	{
		asm ("sleep");
	}
}
ISR(INT0_vect)
{
	_delay_ms(50);
	if (((PINB)&(0b00000010)) == 0x00)
	{
		count1=0;
		while (((PINB&0b00000010)==0x00)&&(count1<20))
		{
			_delay_ms(50);
			count1++;
		}
		if (count1<=10)
		{
			if ((PINB&0b00000001)==0x00)
			{
				PORTB |= (1<<0); //�������� PB0	
				_delay_ms (1000);	
				PORTB &= (~(1<<3)); //��������� ������� ��  PB3
				_delay_ms (100);
				PORTB |= (1<<3); //���������� 1 �� PB3
			}
			else
			{
				PORTB &= (~(1<<3)); //��������� ������� ��  PB3
				_delay_ms (100);
				PORTB |= (1<<3); //���������� 1 �� PB3
			}
		}
		else
		{
			if ((PINB&0b00000001)==0x00)
			{
				PORTB |= (1<<0); //�������� PB0
				_delay_ms (1000);
				PORTB &= (~(1<<3)); //��������� ������� ��  PB3
				_delay_ms (100);
				PORTB |= (1<<3); //���������� 1 �� PB3
			}
			else
			{
				PORTB &= (~(1<<0)); //��������� ������� ��  PB0		
        
			}
		}
		count1=0;
		_delay_ms(1000);
	}
}
ISR(PCINT0_vect)
{
	
	if ((PINB & 0b00010000)==0x00)
	{
		_delay_ms (50);
		if ((PINB & 0b00010000)==0x00)
		{
				_delay_ms (5000);
				PORTB &= (~(1<<0)); //��������� ������� ��  PB0	
		
		}
	}
}
