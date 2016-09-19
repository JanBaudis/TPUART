/*! \file *********************************************************************
 *  \brief		This file contains the Function to init, calibrate and change the clock.
 *  \author		Jan Baudis
  *	\date		11.09.2016 14:24:30
*****************************************************************************/

#include "clock.h"

/*! \brief This function inits, calibrates and changes the clock.
 *
 *  It enables the 32kHz ref Clock for the Autocalibration and also executes the calibration. 
 *  Afterwards it enables and changes to the 32MHz internal Clock and also disables the 
 *  2MHz & 32kHz clocks. Eventually it Locks the current Clock config.
 *
 */
void set_clock_32MHz(void){
	
	CLKSYS_Enable(OSC_RC32KEN_bm); // Enable the 32KHz internal Clock
	do {} while (CLKSYS_IsReady(OSC_RC32KRDY_bm) == 0); // wait till the Clock is ready
	
	CLKSYS_AutoCalibration_Enable(OSC_RC32MCREF_gm, false); // Calibrate the 32MHz Clock
	
	CLKSYS_Enable(OSC_RC32MEN_bm); // Enable the 32MHz internal Clock
	do {} while (CLKSYS_IsReady(OSC_RC32MRDY_bm) == 0); // wait till the Clock is ready
	CLKSYS_Main_ClockSource_Select(CLK_SCLKSEL_RC32M_gc); // Select the 32MHz clock
	
	#define F_CPU 32000000UL // Sets the F_CPU Macro to the new Clock Value
	
	CLKSYS_Disable(OSC_RC32MEN_bm); // Disable 2MHz Clock
	CLKSYS_Disable(OSC_RC32KEN_bm); // Disable 32kHz Clock
	
	CLKSYS_Configuration_Lock(); // Lock the Clock Config till reset
	
}