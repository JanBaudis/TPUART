/*! \file *********************************************************************
 *  \brief		This file is the Headerfile for the main-File. It contains general things like the F_CPU Macro etc.
 *  \author		Jan Baudis
 *	\date		11.09.2016 14:24:45
*****************************************************************************/

/*! \mainpage TPUART
 *
 */


#ifndef MAIN_H_
#define MAIN_H_



#include <avr/io.h>
#include <avr/pgmspace.h>
#include "clksys_driver.h"
#include "clock.h"
#include "UART.h"
#include "shell.h"

#ifndef F_CPU
/*! \brief Define default CPU frequency, if this is not already defined. */
#define F_CPU 32000000UL
#endif



#endif /* MAIN_H_ */