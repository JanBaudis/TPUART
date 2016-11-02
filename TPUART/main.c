/*! \file *********************************************************************
 *  \brief		This file is the main-File. It calls all the fancy Functions and so on.
 *  \author		Jan Baudis
 *	\date		08.09.2016 01:50:07
*****************************************************************************/

#include "main.h"
#include "UART.h"




/*! \brief This is the main-Function.
 *
 *  It calls all the fancy Functions. It does things.
 *
 */
int main(void)
{
	
	char c[20] = "test";
	char temp = 8;
	char output[10];
	
	set_clock_32MHz(); // Sets the Clock to 32MHz
	
	usart_init_tpuart(); // Inits the USART and set it to the corresponding values to talk to the TPUART-Chip
	usart_init_pc(); // Inits the USART and set it to the corresponding values to talk to eg a PC - 57600 8Bit no parity 1start/stop bit
	
	/* Enable global interrupts. */
	sei();
	
	while (true)
	{
		_delay_ms(2000);
		#ifdef DEBUG
		send_string_pgm_to_usart("pc", PSTR("Init_complete!\n\r")); // Sends Debug Info to PC: Init is finished - but not sure if init was successful
		#endif
		
		_delay_ms(2000);
		
		/*temp = receive_char_from_usart("tpuart"); // tries to get uart infos from the tpuart - should be the reset-indication
		itoa(temp, output, 2);
		send_string_to_usart("pc", "Reset-Indication: ");
		send_string_to_usart("pc", output);
		send_string_to_usart("pc", "\n\r");*/
		
		
		/*USART_TXBuffer_PutByte(&USART_data_tp, 0x01); //Sends the U_Reset.request-Service to the TPUART
		
		temp = receive_char_from_usart("tpuart"); // tries to get uart infos from the tpuart - should be the reset-indication
		send_string_to_usart("pc", "Reset-Indication: ");
		send_string_to_usart("pc", output);
		send_string_to_usart("pc", "\n\r");*/
		
		
		/*USART_TXBuffer_PutByte(&USART_data_tp, 0x02); //Sends the U_State.request-Service to the TPUART
		
		temp = receive_char_from_usart("tpuart"); // tries to get uart infos from the tpuart - should be the communication State
		send_string_to_usart("pc", "Communication State: ");
		send_string_to_usart("pc", output);
		send_string_to_usart("pc", "\n\r");*/
		
		
		
		USART_TXBuffer_PutByte(&USART_data_pc, 118);
		itoa(temp, output, 2);
		send_string_to_usart("pc", output);
		
		c[0] = receive_char_from_usart("pc");
		send_string_to_usart("pc", c);
		
		
	}
	
}

