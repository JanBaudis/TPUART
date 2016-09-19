/*! \file *********************************************************************
 *  \brief		This file is the main-File. It calls all the fancy Functions and so on.
 *  \author		Jan Baudis
 *	\date		08.09.2016 01:50:07
*****************************************************************************/

#include "main.h"


/*! \brief This is the main-Function.
 *
 *  It calls all the fancy Functions. It does things.
 *
 */
int main(void)
{
	set_clock_32MHz(); // Sets the Clock to 32MHz
	
	usart_init_tpuart(); // Inits the USART and set it to the corresponding values to talk to the TPUART-Chip
	usart_init_pc(); // Inits the USART and set it to the corresponding values to talk to eg a PC - 57600 8Bit no parity 1start/stop bit
	
	/* Enable global interrupts. */
	sei();
	
	while (true)
	{
		
	}
	
}

