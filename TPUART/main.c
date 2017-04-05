/*! \file *********************************************************************
 *  \brief		This file is the main-File. It calls all the fancy Functions and so on.
 *  \author		Jan Baudis
 *	\date		08.09.2016 01:50:07
*****************************************************************************/

#include "main.h"
#include "UART.h"

extern int volatile ret_pressed;

uint8_t USART_test(USART_data_t * usart_data)
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;

	bufPtr = &usart_data->buffer;
	ans = (bufPtr->RX[bufPtr->RX_Tail]);

	return ans;
}


/*! \brief This is the main-Function.
 *
 *  It calls all the fancy Functions. It does things.
 *
 */
int main(void)
{
	set_clock_32MHz(); // Sets the Clock to 32MHz
	
	//Simple Delay cause the TPUART may need some time if both started simultaneously
	_delay_ms(200);
	usart_init_tpuart(); // Inits the USART and set it to the corresponding values to talk to the TPUART-Chip
	usart_init_tpuart_ext(); // Inits the second TPUART
	usart_init_pc(); // Inits the USART and set it to the corresponding values to talk to eg a PC - 57600 8Bit no parity 1start/stop bit
	
	/* Enable global interrupts. */
	sei();
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Inits complete!\n\r")); // Sends Debug Info to PC: Init is finished - but not sure if init was successful
	#endif
	
	while (true)
	{
		/*! Enter the "Shell"!*/
		//enter_shell();
		
		send_string_to_usart(&USART_DATA_PC, "Test!\n\r");
		
		
		_delay_ms(200);
		
		
		
		
		
		//USART_TXBuffer_PutByte(&USART_DATA_PC, 118);
		//itoa(temp, output, 2);
		//send_string_to_usart("pc", output);
		
		while (1) {
			_delay_ms(2000);
			
			//uint8_t v2 = USART_test(&USART_DATA_PC);
			
			//v2 = USART_data_c1.buffer.RX[0];
			
			/*v = receive_char_from_usart(&USART_DATA_PC);
			
			v2 = USART_data_c1.buffer.RX[(USART_data_c1.buffer.RX_Tail - 1) & USART_RX_BUFFER_MASK];
			uint8_t v3 = (USART_data_c1.buffer.RX_Tail - 1) & USART_RX_BUFFER_MASK;
			utoa(v3, output, 2);
			send_string_to_usart(&USART_DATA_PC, "RX-Feld:\n\r");
			send_string_to_usart(&USART_DATA_PC, output);
			send_string_to_usart(&USART_DATA_PC, "\n\r");
			
			utoa(v, output, 2);
			send_string_to_usart(&USART_DATA_PC, "Received Char:\n\r");
			send_string_to_usart(&USART_DATA_PC, output);
			send_string_to_usart(&USART_DATA_PC, "\n\r");

			utoa(v2, output, 2);
			send_string_to_usart(&USART_DATA_PC, "Received Char in dem Buffer:\n\r");
			send_string_to_usart(&USART_DATA_PC, output);
			send_string_to_usart(&USART_DATA_PC, "\n\r");*/
			enter_shell(&USART_DATA_PC);
			
			if(ret_pressed) {
				char output2[20];
				send_string_to_usart(&USART_DATA_PC, "Ret pre\n\rAnd rec:");
				receive_string_from_usart(&USART_DATA_PC, output2);
				/*output2[0] = receive_char_from_usart(&USART_DATA_PC);
				output2[1] = receive_char_from_usart(&USART_DATA_PC);
				output2[2] = '\0';*/
				send_string_to_usart(&USART_DATA_PC, output2);
				send_string_to_usart(&USART_DATA_PC, "\n\r");
				ret_pressed = 0;
			}
			
			
		} 
		
		
	}
	
}

