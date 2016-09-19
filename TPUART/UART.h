/*! \file *********************************************************************
 *  \brief		This File contains the Macros and so to use the Interrupt driven USART Driver provided by Atmel.
 *				Many things taken from the esart_example_interrupt.c-File provided by Atmel
 *  \author		Jan Baudis
 *	\date		13.09.2016 16:17:27
*****************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "usart_driver.h"
#include "avr_compiler.h"


/*! Use the USART0 of Port C for the TPUART*/
#define USART_TP USARTC0

/*! Use the USART1 of Port C for the PC*/
#define USART_PC USARTC1

/*! USART data struct used for TPUART. */
USART_data_t USART_data_tp;

/*! USART data struct used for PC. */
USART_data_t USART_data_pc;

void usart_init_tpuart(void);
void usart_init_pc(void);
void send_string_pgm_to_usart(USART_data_t * usart_data, const char *addr);
void send_string_to_usart(USART_data_t * usart_data, char *s);


#endif /* UART_H_ */