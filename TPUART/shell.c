/*! \file *********************************************************************
 *  \brief		Implements a basic "shell" to communicate with the TPUART/KNX and Debug things
 *  \author		Jan Baudis
 *	\date		03.12.2016 01:01:54
 *	\note		Buffer Size in the usart_driver.h has to be changed if the commands are too big - it only evaluates the received string when enter is pressed.
*****************************************************************************/

#include "shell.h"


/*! \brief Enter the "Shell"
 *
 *  In the "Shell" we e.g. can use the Services of the TPUART
 *
 *	\todo		Maybe its useful to add the usart instances to the params
 */
void enter_shell(void) {
	char* command[33];
	while (1) {
		
	}
}