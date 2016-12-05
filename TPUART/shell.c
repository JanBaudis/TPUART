/*! \file *********************************************************************
 *  \brief		Implements a basic "shell" to communicate with the TPUART/KNX and Debug things. Data sheet KNX EIB TP-UART 2+ page 22 and following
 *  \author		Jan Baudis
 *	\date		03.12.2016 01:01:54
 *	\note		Buffer Size in the usart_driver.h has to be changed if the commands are too big - it only evaluates the received string when enter is pressed.
 *	\todo		Maybe disable RX for the PC while working on a command!
*****************************************************************************/

#include "shell.h"

extern int volatile ret_pressed;

char command[33];


/*! \brief Enter the "Shell"
 *
 *  In the "Shell" we can e.g. use the Services of the TPUART
 *
 *  \param USART_data The USART_data_t struct instance.
 */
void enter_shell(USART_data_t *USART_data) {
	while (1) {
		if (ret_pressed == 1) {
			receive_string_from_usart(&USART_DATA_PC, command);
			
			#ifdef DEBUG
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
			send_string_to_usart(&USART_DATA_PC, command);
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
			
			char test[10] = "act_busmon";
			char output[10];
			int i = strncmp(command, test,10);
			itoa(i,output,10);
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("strncmp with act_busmon:")); // Sends Debug Info to PC
			send_string_to_usart(&USART_DATA_PC, output);
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
			
			#endif
			
			if (strncmp(command, "reset_r",7) == 0)
			{
				reset_request();
			}
			else if (strncmp(command, "state_r",7) == 0)
			{
				state_request();
			}
			else if (strncmp(command, "act_busmon",10) == 0)
			{
				act_busmon();
			}
			else if (strncmp(command, "prod_r",6) == 0)
			{
				prod_request();
			}
			else if (strncmp(command, "act_busymode",12) == 0)
			{
				act_busymode();
			}
			else if (strcmp(command, "xxx") == 0)
			{
				// do something else
			}
			else if (strcmp(command, "xxx") == 0)
			{
				// do something else
			}
			else if (strcmp(command, "xxx") == 0)
			{
				// do something else
			}
			else /* default: */
			{
				shell_help();
			}
			
			ret_pressed = 0;
		}
	}
}

/*! \brief Shell-Function for the U_reset.request-Service
 *
 *  Sends the U_reset.request to the TPUART and prints the Output as bits to the PC
 *
 */
void reset_request(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering reset_request()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_Reset.request...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x01); //Sends the U_Reset.request-Service to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Waiting(50ms) for the U_Reset.indication-Service...\n\rResponse:\n\r"));
	_delay_ms(50);
	
	// Collects the received Data
	receive_string_from_usart(&USART_DATA_TP, response);

	// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
	while (response[i])
	{
		itoa(response[i],output,2);
		strcat(output,"\n\r");
		send_string_to_usart(&USART_DATA_PC, output);
		i++;
	}
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_Reset.request finished!\n\r"));
	
}

/*! \brief Shell-Function for the U_state.request-Service
 *
 *  Sends the U_state.request to the TPUART and prints the Output as bits to the PC
 *
 */
void state_request(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering state_request()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_State.request...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x02); //Sends the U_state.request-Service to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Waiting(50ms) for the Communication state...\n\rResponse:\n\r"));
	_delay_ms(50);
	
	// Collects the received Data
	receive_string_from_usart(&USART_DATA_TP, response);

	// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
	while (response[i])
	{
		itoa(response[i],output,2);
		strcat(output,"\n\r");
		send_string_to_usart(&USART_DATA_PC, output);
		i++;
	}
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_state.request finished!\n\r"));
	
}

/*! \brief Shell-Function for the U_ActivateBusmon-Service
 *
 *  Sends the U_ActivateBusmon to the TPUART and prints the Output as bits to the PC. Listens till it receives any Key from the PC. Then it Resets the Chip since its the Only way to quit the Busmon-Mode of the TPUART.
 *
 *		\todo Implement an end of Packet detection to print out some useful Information for the Bits.
 *
 */
void act_busmon(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering act_busmon()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ActivateBusmon...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x05); //Sends the U_ActivateBusmon-Service to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Received Packets:\n\r"));
	
	while (!USART_RXBufferData_Available(&USART_DATA_PC))
	{
		// Collects the received Data every 50ms
		_delay_ms(50);
		receive_string_from_usart(&USART_DATA_TP, response);

		// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
		while (response[i])
		{
			itoa(response[i],output,2);
			strcat(output,"\n\r");
			send_string_to_usart(&USART_DATA_PC, output);
			i++;
		}
	}
	
	// Flush the Buffer to remove the any key
	flush_USART_RXBuffer(&USART_DATA_TP);
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusmon finished!\n\r"));
	reset_request();
	
}

/*! \brief Shell-Function for the U_ProductID.request-Service
 *
 *  Sends the U_ProductID.request to the TPUART and prints the Output as bits to the PC
 *
 */
void prod_request(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering prod_request()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ProductID.request...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x20); //Sends the U_ProductID.request to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Waiting(50ms) for the U_ProductID.response...\n\rResponse:\n\r"));
	_delay_ms(50);
	
	// Collects the received Data
	receive_string_from_usart(&USART_DATA_TP, response);

	// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
	while (response[i])
	{
		itoa(response[i],output,2);
		strcat(output,"\n\r");
		send_string_to_usart(&USART_DATA_PC, output);
		i++;
	}
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ProductID.request finished!\n\r"));
	
}

/*! \brief Shell-Function for the U_ActivateBusyMode
 *
 *  Sends the U_ActivateBusyMode to the TPUART and prints the Output as bits to the PC.
 *	TP-UART responses on every Packet which is addressed to him with BUSY within 700ms (+-10ms). All Packets are send to the Host and if the Host confirms one with U_Ackinfo it will leave BusyMode as well when reseted.
 *
 *	\todo May add something; Dunno like a Listen Mode for 700ms;
 */
void act_busymode(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering act_busymode()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ActivateBusyMode...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x21); //Sends the U_ActivateBusyMode to the TPUART

	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusyMode finished!\n\r Be aware that the TPUART is in BusyMode for the next 700ms!\n\r"));
	
}


/*! \brief Shell-Function for the U_ProductID.request-Service
 *
 *  Sends the U_ProductID.request to the TPUART and prints the Output as bits to the PC
 *
 */
void prod_request(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering prod_request()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ProductID.request...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x20); //Sends the U_ProductID.request to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Waiting(50ms) for the U_ProductID.response...\n\rResponse:\n\r"));
	_delay_ms(50);
	
	// Collects the received Data
	receive_string_from_usart(&USART_DATA_TP, response);

	// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
	while (response[i])
	{
		itoa(response[i],output,2);
		strcat(output,"\n\r");
		send_string_to_usart(&USART_DATA_PC, output);
		i++;
	}
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ProductID.request finished!\n\r"));
	
}


void shell_help(void) {
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Entering shell_help()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Implemented TPUART Functions are:\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_Reset.request = reset_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_State.request = state_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusmon = act_busmon\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ProductID.request = prod_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusyMode = act_busymode\n\r"));
	
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Leaving shell_help()\n\r")); // Sends Debug Info to PC
	#endif
}