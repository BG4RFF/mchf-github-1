/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014 - 2016                     **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:  	net_driver.c                                                   **
**  Description:    esp8266 network driver									       **
**  Last Modified:                                                                 **
**  Licence:		For radio amateurs experimentation, non-commercial use only!   **
************************************************************************************/

// Common
#include "mchf_board.h"
#include <stdio.h>

#include "usart_l.h"

#include "net_driver.h"

//*----------------------------------------------------------------------------
//* Function Name       : net_driver_init
//* Object              : All init here
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void net_driver_init(void)
{
	// Init usart hw
	usart_l_init();
}

//*----------------------------------------------------------------------------
//* Function Name       : net_driver_stop
//* Object              : De-init
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void net_driver_stop(void)
{

}

//*----------------------------------------------------------------------------
//* Function Name       : net_driver_thread
//* Object              : task processing
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void net_driver_thread(void)
{
	usart_l_test();
}
