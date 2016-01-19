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

#ifndef __DEBUG_DRIVER_H
#define __DEBUG_DRIVER_H

// CAT driver public structure
typedef struct DebugDriver
{
	// queue flag, single item for now, maybe extend to large queue ??
	uchar	waiting;

	// Align needed ?
	uchar 	dum1;
	ushort	dum2;

	uchar	print_buffer[40];

} DebugDriver;

// Exports - regular init
void debug_driver_init(void);
void debug_driver_stop(void);
void debug_driver_thread(void);

// Exports - printing routines
void dd_print_text(char *text);

#endif
