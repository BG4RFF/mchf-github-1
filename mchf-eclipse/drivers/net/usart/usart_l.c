/************************************************************************************
**                                                                                 **
**                               mcHF QRP Transceiver                              **
**                             K Atanassov - M0NKA 2014 - 2016                     **
**                                                                                 **
**---------------------------------------------------------------------------------**
**                                                                                 **
**  File name:  	usart_l.c                                                      **
**  Description:    usart low level driver									       **
**  Last Modified:                                                                 **
**  Licence:		For radio amateurs experimentation, non-commercial use only!   **
************************************************************************************/

// Common
#include "mchf_board.h"
#include <stdio.h>

#include "debug_driver.h"

#include "usart_l.h"

// -------------------------------
// temp publics
#define MAX_STRLEN 50 // this is the maximum string length of our string in characters
volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
// -------------------------------

//*----------------------------------------------------------------------------
//* Function Name       : usart_l_init
//* Object              : USART hardware init
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void usart_l_init(void)
{
#ifndef DEBUG_BUILD

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;//115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

	// Enable UART clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// Connect PXx to USARTx_Tx
	GPIO_PinAFConfig(UART_TX_PIO, UART_TX_SOURCE, GPIO_AF_USART1);
	GPIO_PinAFConfig(UART_RX_PIO, UART_RX_SOURCE, GPIO_AF_USART1);

	// Configure USART Tx as alternate function
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;

	GPIO_InitStructure.GPIO_Pin 	= UART_TX|UART_RX;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(UART_TX_PIO, &GPIO_InitStructure);

	// USART configuration
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Enable USART
	USART_Cmd(USART1, ENABLE);

	// Wait tx ready
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);


	// -------------------
	// Non HW init
	memset(received_string,0,MAX_STRLEN);


#endif
}

//*----------------------------------------------------------------------------
//* Function Name       : usart_l_send
//* Object              : Send string on the UART
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void usart_l_send(char *s)
{
	while(*s)
	{
		USART_SendData(USART1, *s);
		*s++;
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}

ulong count = 0;
ulong cnt = 0;

// test
void usart_l_test(void)
{
	count++;

	if(count !=2000000)
		return;

	dd_print_text("wifi init...");
	usart_l_send("AT+CWMODE=2");

	non_os_delay();
	non_os_delay();
	non_os_delay();
	non_os_delay();

	if(strlen(received_string) > 15)
	{
		dd_print_text("wifi init done.");

		non_os_delay();
		non_os_delay();
		non_os_delay();
		non_os_delay();

		dd_print_text(received_string);
	}
}

//*----------------------------------------------------------------------------
//* Function Name       : USART1_IRQHandler
//* Object              : USART RX interrupts land here
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//* Functions called    :
//*----------------------------------------------------------------------------
void USART1_IRQHandler(void)
{
	if( USART_GetITStatus(USART1, USART_IT_RXNE) )
	{
		char t = USART1->DR;

		if( (t != '\n') && (cnt < MAX_STRLEN) )
		{
			received_string[cnt] = t;
			cnt++;
		}
		else
			cnt = 0;
	}
}

