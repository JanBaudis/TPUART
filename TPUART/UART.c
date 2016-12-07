/*! \file *********************************************************************
 *  \brief		This file contains the Basic Functions to use the interrupt driven USART Driver provided by Atmel and it sets the ISRs
 *				Many things taken from the usart_example_interrupt.c-File provided by Atmel
 *  \author		Jan Baudis
 *	\date		13.09.2016 16:17:44
 *	\todo		Change the UART-Functions - add an extra value for the Port used and not an simple string to select it in the Function for both Init Functions
*****************************************************************************/

#include "UART.h"

volatile int ret_pressed = 0;



/*! \brief This Method enables and initializes the USART for the specific purpose to communicate with the TPUART1 Chip
 *
 *			It Uses the USARTC0 and:
 *				- 8 bit character size
 *				- Even parity
 *				- 1 stop bit
 *				- 19200 Baud
 *
 *		\todo Check if the TPUART2 Parity Specs from the DS also applies to the TPUART1 - TPUART1 Datasheet(p.10) is missing the parity specs - TPUART2 DS(p.21) says even, so lets try even; Maybe merge the Init functions
 *		\note The Code is taken from the usart_example_interrupt.c-File and is edited to the needed values
 *
*/
void usart_init_tpuart(void){
	
	// Using the USART0 of Port C - so set the IO Pins as in- and output.
	PORTC.DIRCLR   = PIN2_bm; // Sets PC2 (RXD0) as input.
	PORTC.DIRSET   = PIN3_bm; // Sets PC3 (TXD0) as output.
	
	/* Use USARTC0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_DATA_TP, &USART_TP, USART_DREINTLVL_LO_gc);
	
	/* USARTC0, 8 Data bits, Even Parity, 1 Stop bit. */
	USART_Format_Set(USART_DATA_TP.usart, USART_CHSIZE_8BIT_gc,USART_PMODE_EVEN_gc, false); //TPUART1 Datasheet(p.10) is missing the parity specs - TPUART2 DS(p.21) says even, so lets try even
	
	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_DATA_TP.usart, USART_RXCINTLVL_LO_gc);
	
	/* Set Baudrate to 19200 bps:
	 * Use the 32MHz clock.
	 * If ScaleFactor < 0 BSEL = (1/(2^(ScaleFactor)*16))*(((I/O clock frequency)/Baudrate)-1) is documented in the avr1307-docs but the excel sheet from atmel says 1651
	 */
	USART_Baudrate_Set(&USART_TP, 1651 , 0x0C); // The third param uses uint8 - little bit confusing but as long as the 4bits for the BSCALE are set/coded correct (two`s complement)-7(1001) to +7(0111) - so i think its better to use the hexadecimal way
	
	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_DATA_TP.usart);
	USART_Tx_Enable(USART_DATA_TP.usart);
	
	/* Enable PMIC interrupt level low. */
	PMIC.CTRL |= PMIC_LOLVLEX_bm;
	
}

/*! \brief This Method enables and initializes the USART for the specific purpose to communicate with e.g. a PC
 *
 *			It Uses the USARTC1 and:
 *				- 8 bit character size
 *				- No parity
 *				- 1 stop bit
 *				- 57600 Baud
 *
 *		\todo	Maybe merge the init Functions. But think of a good way to configure the Params like Baudrate, Parity etc
 *		\note The Code is taken from the usart_example_interrupt.c-File and is edited to the needed values
 *
*/
void usart_init_pc(void){
	
	// Using the USART1 of Port C - so set the IO Pins as in- and output.
	PORTC.DIRCLR   = PIN6_bm; // Sets PC6 (RXD1) as input.
	PORTC.DIRSET   = PIN7_bm; // Sets PC7 (TXD1) as output.
	
	/* Use USARTC1 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_DATA_PC, &USART_PC, USART_DREINTLVL_LO_gc);
	
	/* USARTC1, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_DATA_PC.usart, USART_CHSIZE_8BIT_gc,USART_PMODE_DISABLED_gc, false);
	
	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_DATA_PC.usart, USART_RXCINTLVL_LO_gc);
	
	/* Set Baudrate to 57600 bps:
	 * Use the 32MHz clock.
	 * If ScaleFactor < 0 BSEL = (1/(2^(ScaleFactor)*16))*(((I/O clock frequency)/Baudrate)-1) is documented in the avr1307-docs but the excel sheet from atmel says 1079
	 */
	USART_Baudrate_Set(&USART_PC, 1079 , 0x0B); // The third param uses uint8 - little bit confusing but as long as the 4bits for the BSCALE are set/coded correct (two`s complement)-7(1001) to +7(0111) - so i think its better to use the hexadecimal way
	
	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_DATA_PC.usart);
	USART_Tx_Enable(USART_DATA_PC.usart);
	
	/* Enable PMIC interrupt level low. */
	PMIC.CTRL |= PMIC_LOLVLEX_bm;
	
}



/*! \brief This Method uses the Program Space for e.g. Debug Strings and sends them to the given USART.
 *
 *		\param USART_data	The USART_data_t struct instance.
 *		\param addr			const char* to the pgmspace.
 *
*/
void send_string_pgm_to_usart(USART_data_t *USART_data, const char *addr){
	char c;
	bool temp;
	
	while (1) {
		bool byteToBuffer = false;
		c = pgm_read_byte(addr++);
		if (c == '\0') break; // When String Terminator reached break out of the while loop
		while (!byteToBuffer) {
			temp = USART_TXBuffer_PutByte(&(*USART_data), c);
			byteToBuffer = temp;
		}
	}
}


/*! \brief This Method sends Strings to the given USART.
 *
 *		\param USART_data	The USART_data_t struct instance.
 *		\param s			char* to transmit.
 *
*/
void send_string_to_usart(USART_data_t *USART_data, char *s){
	bool byteToBuffer;
	bool temp;

	
	while (*s){ // so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)"
		temp = USART_TXBuffer_PutByte(&(*USART_data), *s);
		byteToBuffer = temp;
		if(byteToBuffer) s++;
	}
}


/*! \brief This Method reads out the data of the RingBuffer and returns a string.
 *
 *		\param USART_data	The USART_data_t struct instance.
 *		\param output		The String-Pointer where the Output is stored
 *
 *		\todo	May add the ret val boolean to indicate if data was received at all
 *
*/
void receive_string_from_usart(USART_data_t *USART_data, char *output){
	
	int i = 0;
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - receive_string_from_usart entered!\n\r")); // Sends Debug Info to PC
	#endif
	
	while (USART_RXBufferData_Available(&(*USART_data))) {
		output[i] = USART_RXBuffer_GetByte(&(*USART_data));
		i++;
	}
	
	output[i]='\0';
	
	#ifdef DEBUG
	send_string_to_usart(&USART_DATA_PC, "DEBUG - Output(May contain nonsense since its binary and interpreted as ascii):\n\r");
	send_string_to_usart(&USART_DATA_PC, output);
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - receive_string_from_usart about to quit!\n\r")); // Sends Debug Info to PC
	#endif
}


/*! \brief This Method waits till one char is in the given USART-Buffer - No Timeout, Blocks!!!!.
 *
 *		\param USART_data	The USART_data_t struct instance.
 *
*/
char receive_char_from_usart(USART_data_t *USART_data){
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - receive_char_from_usart entered!\n\r")); // Sends Debug Info to PC
	#endif
	
	char c;
	
	while (!USART_RXBufferData_Available(&(*USART_data)));
	c = USART_RXBuffer_GetByte(&(*USART_data));
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - receive_char_from_usart about to quit!\n\r")); // Sends Debug Info to PC
	#endif
	
	return c;
}

/*! \brief This Method flushs the RX Buffer
 *
 *		\param USART_data	The USART_data_t struct instance.
 *
*/
void flush_USART_RXBuffer(USART_data_t *USART_data){
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - flush_USART_RXBuffer entered!\n\r")); // Sends Debug Info to PC
	#endif
	
	while (USART_RXBufferData_Available(&(*USART_data))) {
		/*uint8_t dump = 1;
		dump =*/ 
		USART_RXBuffer_GetByte(&(*USART_data));
	}
	
	#ifdef DEBUG
	send_string_pgm_to_usart(&USART_DATA_PC, PSTR("DEBUG - flush_USART_RXBuffer about to quit!\n\r")); // Sends Debug Info to PC
	#endif
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 *
 *	\todo Think about if volatile for the USART_DATA_TP is needed!
 *
 */
ISR(USARTC0_RXC_vect)
{
	USART_RXComplete(&USART_DATA_TP);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 *
 *	\todo Think about if volatile for the USART_DATA_TP is needed!
 *
 */
ISR(USARTC0_DRE_vect)
{
	USART_DataRegEmpty(&USART_DATA_TP);
}

/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 *
 *	\todo Think about if volatile for the USART_DATA_PC is needed!
 *	\note Added a check to see if the Return-Key was pressed to trigger the "Shell"
 *
 */
ISR(USARTC1_RXC_vect)
{
	USART_RXComplete(&USART_DATA_PC);
	
	/*! If it receives the Return-Key(13) it changes ret_pressed so the Shell can evalute the command */
	if (USART_data_c1.buffer.RX[(USART_data_c1.buffer.RX_Head - 1) & USART_RX_BUFFER_MASK] == 0x0D) {
		ret_pressed = 1;
	} 
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 *
 *	\todo Think about if volatile for the USART_DATA_PC is needed!
 *
 */
ISR(USARTC1_DRE_vect)
{
	USART_DataRegEmpty(&USART_DATA_PC);
}
