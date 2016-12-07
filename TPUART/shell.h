/*! \file *********************************************************************
 *  \brief		Corresponding header-File
 *  \author		Jan Baudis
 *	\date		03.12.2016 01:03:19
*****************************************************************************/


#ifndef SHELL_H_
#define SHELL_H_

#include "usart_driver.h"
#include "avr_compiler.h"
#include "UART.h"

#include <string.h>


void enter_shell(USART_data_t *USART_data);

void shell_help(void);
void reset_request(void);
void state_request(void);
void act_busmon(void);
void prod_request(void);
void act_busymode(void);
void res_busymode(void);
void setaddress(void);
void ackInfo(void);



#endif /* SHELL_H_ */