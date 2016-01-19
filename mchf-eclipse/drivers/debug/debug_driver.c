/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014 - 2016                     **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:  	debug_driver.c                                                 **
**  Description:    Simple debug driver that prints on LCD, instead of UART        **
**  Last Modified:                                                                 **
**  Licence:		For radio amateurs experimentation, non-commercial use only!   **
************************************************************************************/

// Common
#include "mchf_board.h"

#include "debug_driver.h"

// Text position declares
#include "ui_driver.h"

// Direct LCD print
#include "ui_lcd_hy28.h"

#include <stdio.h>

// Debug driver public state
__IO DebugDriver dd;



//*----------------------------------------------------------------------------
//* Function Name       : debug_driver_init
//* Object              : All init here
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void debug_driver_init(void)
{
	// Nothing in queue
	dd.waiting = 0;

	// Empty string
	dd.print_buffer[0] = 0;
}

//*----------------------------------------------------------------------------
//* Function Name       : debug_driver_stop
//* Object              : De-init
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void debug_driver_stop(void)
{

}

//*----------------------------------------------------------------------------
//* Function Name       : debug_driver_stop
//* Object              : task processing
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void debug_driver_thread(void)
{
	// Anything in queue ?
	if(!(dd.waiting))
		return;

	// Clear bottom bar area
	UiLcdHy28_DrawFullRect(POS_BOTTOM_BAR_X , (POS_BOTTOM_BAR_Y - 4), 16, 320, Black);

	// Print text from queue
	UiLcdHy28_PrintText(POS_BOTTOM_BAR_X,POS_BOTTOM_BAR_Y,dd.print_buffer,White,Black,4);

	// We are done here
	dd.waiting = 0;
}


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					End of standard driver init, exports follow
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//*----------------------------------------------------------------------------
//* Function Name       : dd_print_text
//* Object              : print text
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void dd_print_text(char *text)
{
#ifndef SIMPLE_DEBUG
	return;
#endif

	if(text == NULL)
		return;

	// Limit size
	if(strlen(text) > 40)
		*(text + 40) = 0; // writing to passed buffer directly is bit unsafe!!

	// Copy to driver buffer
	strcpy(dd.print_buffer,text);

	// Set as pending
	dd.waiting = 1;
}
