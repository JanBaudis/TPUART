/*! \file *********************************************************************
 *  \brief		This file contains the Basic Functions to use the interrupt driven USART Driver provided by Atmel
 *				Many things taken from the esart_example_interrupt.c-File provided by Atmel
 *  \author		Jan Baudis
 *	\date		13.09.2016 16:17:44
*****************************************************************************/

#include "UART.h"

/*! \brief This Method enables and initializes the USART for the specific purpose to communicate with the TPUART1 Chip
 *
 *			It Uses the USARTC0 and:
 *				- 8 bit character size
 *				- Even parity
 *				- 1 stop bit
 *				- 19200 Baud
 *
 *		\todo Check if the TPUART2 Parity Specs from the DS also applies to the TPUART1 - TPUART1 Datasheet(p.10) is missing the parity specs - TPUART2 DS(p.21) says even, so lets try even
*/
void usart_init_tpuart(void){
	
	// Using the USART0 of Port C - so set the IO Pins as in- and output.
	PORTC.DIRCLR   = PIN2_bm; // Sets PC2 (RXD0) as input.
	PORTC.DIRSET   = PIN3_bm; // Sets PC3 (TXD0) as output.
	
	/* Use USARTC0 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_tp, &USART_TP, USART_DREINTLVL_LO_gc);
	
	/* USARTC0, 8 Data bits, Even Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_tp.usart, USART_CHSIZE_8BIT_gc,USART_PMODE_EVEN_gc, false); //TPUART1 Datasheet(p.10) is missing the parity specs - TPUART2 DS(p.21) says even, so lets try even
	
	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_tp.usart, USART_RXCINTLVL_LO_gc);
	
	/* Set Baudrate to 19200 bps:
	 * Use the 32MHz clock.
	 * If ScaleFactor < 0 BSEL = (1/(2^(ScaleFactor)*16))*(((I/O clock frequency)/Baudrate)-1) is documented in the avr1307-docs but the excel sheet from atmel says 1651
	 */
	USART_Baudrate_Set(&USART_TP, 1651 , 0x0C); // The third param uses uint8 - little bit confusing but as long as the 4bits for the BSCALE are set/coded correct (two`s complement)-7(1001) to +7(0111) - so i think its better to use the hexadecimal way
	
	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_tp.usart);
	USART_Tx_Enable(USART_data_tp.usart);
	
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
*/
void usart_init_pc(void){
	
	// Using the USART1 of Port C - so set the IO Pins as in- and output.
	PORTC.DIRCLR   = PIN6_bm; // Sets PC2 (RXD0) as input.
	PORTC.DIRSET   = PIN7_bm; // Sets PC3 (TXD0) as output.
	
	/* Use USARTC1 and initialize buffers. */
	USART_InterruptDriver_Initialize(&USART_data_pc, &USART_PC, USART_DREINTLVL_LO_gc);
	
	/* USARTC1, 8 Data bits, No Parity, 1 Stop bit. */
	USART_Format_Set(USART_data_pc.usart, USART_CHSIZE_8BIT_gc,USART_PMODE_DISABLED_gc, false);
	
	/* Enable RXC interrupt. */
	USART_RxdInterruptLevel_Set(USART_data_pc.usart, USART_RXCINTLVL_LO_gc);
	
	/* Set Baudrate to 57600 bps:
	 * Use the 32MHz clock.
	 * If ScaleFactor < 0 BSEL = (1/(2^(ScaleFactor)*16))*(((I/O clock frequency)/Baudrate)-1) is documented in the avr1307-docs but the excel sheet from atmel says 1079
	 */
	USART_Baudrate_Set(&USART_PC, 1079 , 0x0B); // The third param uses uint8 - little bit confusing but as long as the 4bits for the BSCALE are set/coded correct (two`s complement)-7(1001) to +7(0111) - so i think its better to use the hexadecimal way
	
	/* Enable both RX and TX. */
	USART_Rx_Enable(USART_data_pc.usart);
	USART_Tx_Enable(USART_data_pc.usart);
	
	/* Enable PMIC interrupt level low. */
	PMIC.CTRL |= PMIC_LOLVLEX_bm;
	
}



/*! \brief This Method uses the Program Space for Debug Strings and sends them to the given USART.
 *
 *		\param usart_data	The USART_data_t struct instance.
 *		\param addr			const char* to the pgmspace.
*/
void send_string_pgm_to_usart(USART_data_t * usart_data, const char *addr){
	char c;
	while (1) {
		bool byteToBuffer = false;
		c = pgm_read_byte(addr++);
		if (c == '\0') break; // When String Terminator reached break out of the while loop
		while (!byteToBuffer) {
			byteToBuffer = USART_TXBuffer_PutByte(&usart_data, c);
		}
	}
}


/*! \brief This Method sends Strings to the given USART.
 *
 *		\param usart_data	The USART_data_t struct instance.
 *		\param s			char*.
*/
void send_string_to_usart(USART_data_t * usart_data, char *s){
	while (*s){ // so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)"
		bool byteToBuffer = false;
		while (!byteToBuffer) {
			byteToBuffer = USART_TXBuffer_PutByte(&usart_data, *s);
		}
		s++;
	}
}


int main(void)
{
	/* counter variable. */
	uint8_t i;

	

	/* Send sendArray. */
	i = 0;
	while (i < NUM_BYTES) {
		bool byteToBuffer;
		byteToBuffer = USART_TXBuffer_PutByte(&USART_data_tp, sendArray[i]);
		if(byteToBuffer){
			i++;
		}
	}

	/* Fetch received data as it is received. */
	i = 0;
	while (i < NUM_BYTES) {
		if (USART_RXBufferData_Available(&USART_data_tp)) {
			receiveArray[i] = USART_RXBuffer_GetByte(&USART_data_tp);
			i++;
		}
	}

	/* Test to see if sent data equals received data. */
	/* Assume success first.*/
	success = true;
	for(i = 0; i < NUM_BYTES; i++) {
		/* Check that each element is received correctly. */
		if (receiveArray[i] != sendArray[i]) {
			success = false;
		}
	}

	/* If success the program ends up inside the if statement.*/
	if(success){
		while(true);
	}else{
	  	while(true);
	}
}


/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTC0_RXC_vect)
{
	USART_RXComplete(&USART_data_tp);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTC0_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_tp);
}

/*! \brief Receive complete interrupt service routine.
 *
 *  Receive complete interrupt service routine.
 *  Calls the common receive complete handler with pointer to the correct USART
 *  as argument.
 */
ISR(USARTC1_RXC_vect)
{
	USART_RXComplete(&USART_data_pc);
}


/*! \brief Data register empty  interrupt service routine.
 *
 *  Data register empty  interrupt service routine.
 *  Calls the common data register empty complete handler with pointer to the
 *  correct USART as argument.
 */
ISR(USARTC1_DRE_vect)
{
	USART_DataRegEmpty(&USART_data_pc);
}
