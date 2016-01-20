/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014 - 2016                     **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:  	usart_l.h                                                      **
**  Description:    usart low level driver									       **
**  Last Modified:                                                                 **
**  Licence:		For radio amateurs experimentation, non-commercial use only!   **
************************************************************************************/

#ifndef __USART_L_H
#define __USART_L_H


// Exports
void usart_l_init(void);
void usart_l_send(char *s);

void usart_l_test(void);

#endif
