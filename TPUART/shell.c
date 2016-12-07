/*! \file *********************************************************************
 *  \brief		Implements a basic "shell" to communicate with the TPUART/KNX and Debug things. Data sheet KNX EIB TP-UART 2+ page 22 and following
 *  \author		Jan Baudis
 *	\date		03.12.2016 01:01:54
 *	\note		Buffer Size in the usart_driver.h has to be changed if the commands are too big - it only evaluates the received string when enter is pressed.
 *	\todo		Maybe disable RX for the PC while working on a command! I should switch from USART_TXBuffer_PutByte to send_string or evaluate the retval of USART_TXBuffer_PutByte.
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
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
			send_string_to_usart(&USART_DATA_PC, command);
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
			
			char test[10] = "act_busmon";
			char output[10];
			int i = strncmp(command, test,10);
			itoa(i,output,10);
			send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - strncmp with act_busmon:")); // Sends Debug Info to PC
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
			else if (strncmp(command, "res_busymode",12) == 0)
			{
				res_busymode();
			}
			else if (strncmp(command, "setaddr",7) == 0)
			{
				setaddress();
			}
			else if (strncmp(command, "ackinfo",7) == 0)
			{
				ackInfo();
			}
			else if (strncmp(command, "senddata",8) == 0)
			{
				send_data();
			}
			else if (strncmp(command, "ackinfo",7) == 0)
			{
				ackInfo();
			}
			else if (strncmp(command, "ackinfo",7) == 0)
			{
				ackInfo();
			}
			else if (strncmp(command, "ackinfo",7) == 0)
			{
				ackInfo();
			}
			else if (strncmp(command, "ackinfo",7) == 0)
			{
				ackInfo();
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
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering reset_request()\n\r")); // Sends Debug Info to PC
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
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering state_request()\n\r")); // Sends Debug Info to PC
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
 *		\note ATM there is a (good) chance that the RX Buffer Overflows.
 *
 */
void act_busmon(void) {
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	int i=0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering act_busmon()\n\r")); // Sends Debug Info to PC
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
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering prod_request()\n\r")); // Sends Debug Info to PC
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
 *  Sends the U_ActivateBusyMode to the TPUART.
 *	TP-UART responses on every Packet which is addressed to him with BUSY within 700ms (+-10ms). All Packets are send to the Host and if the Host confirms one with U_Ackinfo it will leave BusyMode as well when reseted.
 *
 *	\todo May add something; Dunno like a Listen Mode for 700ms;
 */
void act_busymode(void) {
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering act_busymode()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ActivateBusyMode...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x21); //Sends the U_ActivateBusyMode to the TPUART

	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusyMode finished!\n\rBe aware that the TPUART is in BusyMode for the next 700ms!\n\r"));
	
}


/*! \brief Shell-Function for the U_ResetBusyMode
 *
 *  Sends the U_ResetBusyMode to the TPUART. So the TPUART immediately leaves the BUSY Mode.
 *
 */
void res_busymode(void) {
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering res_busymode()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_ResetBusyMode...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x22); //Sends the U_ResetBusyMode to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ResetBusyMode finished!\n\rTPUART is no longer in BUSY Mode!\n\r"));
	
}

/*! \brief Shell-Function for the U_SetAddress
 *
 *  Sends the U_SetAddress to the TPUART and prompts for the Address to set.
 *	---------------------------------	---------------------------------
 *	| physical address high			|	| physical address low			|
 *	---------------------------------	---------------------------------
 *	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *	---------------------------------	---------------------------------
 *	| a | a | a | a | l | l | l | l |	| d | d | d | d | d | d | d | d |
 *	---------------------------------	---------------------------------
 *
 */
void setaddress(void) {
	
	#ifdef DEBUG
	char debug_str[9];
	#endif
	
	char in_address[6];
	char **strtol_ep = NULL;
	uint8_t address[2] = {0,0};
	uint8_t temp = 0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering setaddress()\n\r")); // Sends Debug Info to PC
	#endif
	
	// We need Feedback so set ret_pressed here to 0
	ret_pressed=0;
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter Address:\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------	---------------------------------\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| physical address high			|	| physical address low			|\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------	---------------------------------\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------	---------------------------------\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| a | a | a | a | l | l | l | l |	| d | d | d | d | d | d | d | d |\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------	---------------------------------\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Use only Decimal Numbers and hit Return after it. It will be converted into Binary and shifted to right place.\n\r"));
	
	// a cant be higher than 16
	do 
	{
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter a(0-16):\n\r"));
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, in_address);
		temp=(uint8_t)strtol(in_address,strtol_ep,10);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - a:")); // Sends Debug Info to PC
		utoa(temp, debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while (temp > 16);
	
	address[0] = (temp << 4);
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - physical address high:")); // Sends Debug Info to PC
	utoa(address[0], debug_str, 2);
	send_string_to_usart(&USART_DATA_PC, debug_str);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	#endif
	
	// We need the next Feedback so set ret_pressed here to 0
	ret_pressed=0;
	
	// l cant be higher than 16
	do
	{
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter l(0-16):\n\r"));
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, in_address);
		temp=(uint8_t)strtol(in_address,strtol_ep,10);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - l:")); // Sends Debug Info to PC
		utoa(temp, debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while (temp > 16);
	
	address[0] = (temp ^ address[0]);
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - physical address high:")); // Sends Debug Info to PC
	utoa(address[0], debug_str, 2);
	send_string_to_usart(&USART_DATA_PC, debug_str);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	#endif
	
	// We need the next Feedback so set ret_pressed here to 0
	ret_pressed=0;
	
	// l cant be higher than 255
	do
	{
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter d(0-255):\n\r"));
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, in_address);
		address[1]=(uint8_t)strtol(in_address,strtol_ep,10);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - d:")); // Sends Debug Info to PC
		utoa(address[1], debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while (temp > 255);
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - physical address low:")); // Sends Debug Info to PC
	utoa(address[1], debug_str, 2);
	send_string_to_usart(&USART_DATA_PC, debug_str);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	#endif
	
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_SetAddress...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, 0x28); //Sends the U_SetAddress to the TPUART
	USART_TXBuffer_PutByte(&USART_DATA_TP, address[0]); //Sends the physical address high to the TPUART
	USART_TXBuffer_PutByte(&USART_DATA_TP, address[1]); //Sends the physical address low to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_SetAddress finished!\n\r"));
	
}

/*! \brief Shell-Function for the U_AckInformation-Service
 *
 *  Sends the U_AckInformation to the TPUART. This must be sent latest 2,8ms after receiving the address type octet of an addressed frame. Its used to evaluate the Address on the Host side. More on p. 25 ff off the TPUART 2+ Data sheet.
 *
 *	\todo Implement this as a feature for receiving Frames in general. Since it only makes sense if its send after 2,8ms of an addressed frame. Look up if it can set more than one Flag! - Maybe its also important to implement for the Bus-Sniffer
 *
 */
void ackInfo(void) {
	
	#ifdef DEBUG
	char debug_str[9];
	#endif
	
	char input_flag[4];
	uint8_t flag;
	char **strtol_ep = NULL;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering ackInfo()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter Flags:\n\r"));
	
	
	// We need the next Feedback so set ret_pressed here to 0
	ret_pressed=0;
	
	// input cant be higher than 16
	do
	{
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("1 = Addr; 2 = Busy; 3 = NACK;\n\r"));
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, input_flag);
		flag=(uint8_t)strtol(input_flag,strtol_ep,10);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - flag:")); // Sends Debug Info to PC
		utoa(flag, debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while (flag > 3);
	
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_AckInformation-Service...\n\r"));
	
	USART_TXBuffer_PutByte(&USART_DATA_TP, (flag ^ 0x10)); //Sends the U_AckInformation-Service to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_AckInformation-Service finished!\n\r"));
	
}



/*! \brief Shell-Function for the U_L_DataStart-Service, U_L_DataContinue-Service and U_L_DataEnd-Service to send a KNX-Frame
 *
 *  Sends the U_L_DataStart-Service, U_L_DataContinue-Service and U_L_DataEnd-Service to the TPUART. The Additional Information of the U_L_DataStart-Service contains the EIB-Controlfield Information. And in the the Case of U_L_DataContinue-Service it contains the Payload.
 *	The U_L_DataEnd-Service`s Additional Information contains the Checksum and the command also contains the length.
 *
 *	\note	Be aware the RingBuffer-Size is a limiting factor since the TPUART`s response will is the whole Packet.
 *	\todo	Rework Calc parity. Chance that the RX Buffer overflows!
 *
 */
void send_data(void) {
	
	#ifdef DEBUG
	char debug_str[9];
	#endif
	
	char response[USART_RX_BUFFER_SIZE+1];
	char output[9];
	char input[9];
	char **strtol_ep = NULL;

	char buffer[3];
	
	uint8_t addinfo[63];
	uint8_t dataindex = 0;
	uint8_t parity = 0xFF;
	
	int r = 0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering send_data()\n\r")); // Sends Debug Info to PC
	#endif
	
	
	do
	{
		// We need the next Feedback so set ret_pressed here to 0
		ret_pressed=0;
		
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_DataStart-Service!\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| EIB-Control Field				\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("| F | F | R | 1 | c | c | 0 | 0 |\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("---------------------------------\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("FF = Frame Format; 10 Stad Length; 00 ext; 11 L_POLLDATA\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("R = Repeatflag; 1 = not repeated, 0 = repeated\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("cc = 00 system; 10 alarm; 01 high; 11 normal\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter EIB-Control field!(As Hex with leading 0x otherwise as decimal or if it begins with 0 than its octal!)\n\r"));
		
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, input);
		addinfo[0]=(uint8_t)strtol(input,strtol_ep,0);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - EIB-Control Field:")); // Sends Debug Info to PC
		utoa(addinfo[0], debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while ( (addinfo[0] & 0x13) != 0x10 ); // Check if the Bits which are predefined are correctly set
	
	
	// How many Data bytes ?
	do
	{
		
		// We need the next Feedback so set ret_pressed here to 0
		ret_pressed=0;
		
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_DataContinue-Service!\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter Number of Bytes as decimal(Max 62)!\n\r"));
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, input);
		dataindex=(uint8_t)strtol(input,strtol_ep,10);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Number of Bytes:")); // Sends Debug Info to PC
		utoa(dataindex, debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	} while ( dataindex > 62); // Maximal 62
	
	
	for (int i = 1; i<=dataindex; i++) {
		
		// We need the next Feedback so set ret_pressed here to 0
		ret_pressed=0;
		
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_DataContinue-Service!\n\r"));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Enter Data byte "));
		send_string_to_usart(&USART_DATA_PC, itoa(i, buffer, 10));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR(":(As Hex with leading 0x otherwise as decimal or if it begins with 0 than its octal!)\n\r"));
		
		
		while (ret_pressed != 1);
		receive_string_from_usart(&USART_DATA_PC, input);
		addinfo[i]=(uint8_t)strtol(input,strtol_ep,0);
		
		#ifdef DEBUG
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Data byte ")); // Sends Debug Info to PC
		send_string_to_usart(&USART_DATA_PC, itoa(i, buffer, 10));
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR(": ")); // Sends Debug Info to PC
		utoa(addinfo[i], debug_str, 2);
		send_string_to_usart(&USART_DATA_PC, debug_str);
		send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
		#endif
	}
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_DataEnd-Service!\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Calculating Checksum!\n\r"));
	
	//Calculate Parity - Odd Parity Horizontal - May rework since this has a lot of memory access and is kind of long code; i think its better to just set parity to FF and ^ with the addinfo[i]
	
	for (int i = 1; i <= dataindex; i++) {
		parity = parity ^ addinfo[i];
	}
	
	/*for (int i = 7; i < 0; i--) {
		uint8_t temp = 0;
		for (int j = 1; j <= dataindex; j++) {
			if ( (addinfo[j] & (0x01 << i)) == (0x01 << i) ) {
				temp++;
			}
		}
		if ( (temp & 0x01) == 0x00 ) {
			parity = parity | ( 0x01 << i );
		}
	}*/
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Calculated Parity: "));
	utoa(parity, debug_str, 2);
	send_string_to_usart(&USART_DATA_PC, debug_str);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	#endif
	
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Sending U_L_DataStart/Continue/End-Services...\n\r"));
	
	for (int i = 0; i <= dataindex; i++ ) {
		while(!USART_TXBuffer_FreeSpace(&USART_DATA_TP));
		USART_TXBuffer_PutByte(&USART_DATA_TP, (0x80 | i ) ); //Sends the U_L_DataStart/Continue-Service to the TPUART
		while(!USART_TXBuffer_FreeSpace(&USART_DATA_TP));
		USART_TXBuffer_PutByte(&USART_DATA_TP, addinfo[i]); //Sends the U_L_DataStart/Continue-Service to the TPUART
	}
	
	// U_L_DataEnd
	while(!USART_TXBuffer_FreeSpace(&USART_DATA_TP));
	USART_TXBuffer_PutByte(&USART_DATA_TP, (0x40 | dataindex ) ); //Sends the U_L_DataEnd-Service to the TPUART
	while(!USART_TXBuffer_FreeSpace(&USART_DATA_TP));
	USART_TXBuffer_PutByte(&USART_DATA_TP, parity ); //Sends the U_L_DataEnd-Service to the TPUART
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Waiting 200ms and printing everything received from the TPUART - State.indication and/or Packet itself. Response:\n\r")); // Is the first packet received the Sate.indication or only when an error occurs? TODO
	_delay_ms(200);
	
	// Collects the received Data
	receive_string_from_usart(&USART_DATA_TP, response);

	// Loops till response hits the \0 which the Function receive_string_from_usart Function appends
	while (response[r])	{
		itoa(response[r],output,2);
		strcat(output,"\n\r");
		send_string_to_usart(&USART_DATA_PC, output);
		r++;
	}
	
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_DataStart-Service finished!\n\r"));
	
}


void shell_help(void) {
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Command:")); // Sends Debug Info to PC
	send_string_to_usart(&USART_DATA_PC, command);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("\n\r")); // Sends Debug Info to PC
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Entering shell_help()\n\r")); // Sends Debug Info to PC
	#endif
	
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("Implemented TPUART Functions are:\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_Reset.request = reset_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_State.request = state_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusmon = act_busmon\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ProductID.request = prod_r\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ActivateBusyMode = act_busymode\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_ResetBusyMode = res_busymode\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_SetAddress = setaddr\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_AckInformation = ackinfo\n\r"));
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("U_L_Data-Services = senddata\n\r"));
	
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - Leaving shell_help()\n\r")); // Sends Debug Info to PC
	#endif
}