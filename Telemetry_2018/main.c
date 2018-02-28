/*
 *  main.c
 *
 *  Created: 30.01.2018 16:00:00
 *  Author: haavardfiskaa
 */ 

//can.c is totally dependent on F_CPU being declared.
//However, it should only be declared once in each project. 
//Therefore, make sure that F_CPU=8000000UL is stated under symbols in the toolchain. 

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "can.h"

#define CAN_MESSAGE_ID_LENGTH 3
#define CAN_MESSAGE_LENGTH_LENGTH 1
#define LED_BLUE PB7
#define LED_GREEN PB6
#define LED_RED	PB5

CanMessage_t rxFrame;
CanMessage_t txFrame;
uint8_t error = 0;

void handling_error();
void transmit_can_to_serial(CanMessage_t dataFrame);

int main(void)
{
	DDRB |= (1<<LED_RED) | (1<<LED_GREEN) | (1<<LED_BLUE);
	PORTB |= (1<<LED_BLUE) | (1<<LED_GREEN);
	PORTB &= ~(1<<LED_RED);
	
	uart_init();
	can_init(0,0);
	fdevopen(uart_tx_char, NULL); 
	//fdevopen will give a warning because it's expecting uart_tx_char to be of type int. 
	//This is because uart_tx_char, in uart.c, is declared as void. 
	
    while(1)
    {
		if (can_read_message_if_new(&rxFrame))
		{
			transmit_can_to_serial(rxFrame);
		}
		
		else {printf("No new can-data \n");}
    }
}

void transmit_can_to_serial(CanMessage_t dataFrame)
{
	printf("[%03X:%d:", dataFrame.id,dataFrame.length);
	
	for(int i = 0; i < dataFrame.length; i++)
	{
		printf("%02X", dataFrame.data.u8[i]);
		uart_tx_char(i);
	}
	
	printf("]\n");
}

void handling_error(){
	error++;
}