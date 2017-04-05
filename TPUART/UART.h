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

#include <string.h>




/*! For easier handling you may define here telling Names for the Macros and Data-structs.*/
/*! Use the USART0 of Port C for the TPUART.*/
#define USART_TP USARTC0

/*! Use the USART1 of Port C for the PC.*/
#define USART_PC USARTC1

/*! Use the USART0 of Port D for the TPUART ext.*/
#define USART_TP_ext USARTD0

/*! Defines for easier handling of the USART PORTs.*/
#define USART_DATA_TP USART_data_c0
#define USART_DATA_PC USART_data_c1
#define USART_DATA_TP_ext USART_data_d0



/*! USART data struct used for USART 0 of Port C.*/
USART_data_t USART_data_c0;

/*! USART data struct used for USART 1 of Port C.*/
USART_data_t USART_data_c1;

/*! USART data struct used for USART 0 of Port D.*/
USART_data_t USART_data_d0;


void usart_init_tpuart(void);
void usart_init_tpuart_ext(void);
void usart_init_pc(void);
void send_string_pgm_to_usart(USART_data_t *USART_data, const char *addr);
void send_string_to_usart(USART_data_t *USART_data, char *s);

char receive_char_from_usart(USART_data_t *USART_data);
void receive_string_from_usart(USART_data_t *USART_data, char* string);

void flush_USART_RXBuffer(USART_data_t *USART_data);


#endif /* UART_H_ */