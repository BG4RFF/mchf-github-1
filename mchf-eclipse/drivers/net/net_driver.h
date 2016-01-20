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

#ifndef __NET_DRIVER_H
#define __NET_DRIVER_H


// Exports
void net_driver_init(void);
void net_driver_stop(void);
void net_driver_thread(void);



#endif
