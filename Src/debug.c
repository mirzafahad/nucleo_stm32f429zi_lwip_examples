/*
 * debug.c
 *
 *  Created on: Jul 31, 2019
 *      Author: fmirz007
 */


#include <debug.h>
#include <stdarg.h>
#include "tiny_vsnprintf.h"
#include "hw_conf.h"
#include "utilities.h"
/* Force include of HAL UART in order to inherit HAL_UART_StateTypeDef definition */
#include "stm32f4xx_hal_uart.h"



static UART_HandleTypeDef DebugUart;
static char BuffTx[256];




void DBG_Init(void)
{
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
		- Word Length = 8 Bits (7 data bit + 1 parity bit) :
					    BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal //  TODO : I am not using the parity bit for now, but may I should
		- Stop Bit    = One Stop bit
		- Parity      = None
		- BaudRate    = 9600 baud
		- Hardware flow control disabled (RTS and CTS signals) */
	DebugUart.Instance          = DBG_USARTx;

	DebugUart.Init.BaudRate     = 9600;
	DebugUart.Init.WordLength   = UART_WORDLENGTH_8B;
	DebugUart.Init.StopBits     = UART_STOPBITS_1;
	DebugUart.Init.Parity       = UART_PARITY_NONE;
	DebugUart.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	DebugUart.Init.Mode         = UART_MODE_TX_RX;
	DebugUart.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&DebugUart);
}



void DBG_Print(const char *format, ...)
{
	va_list args;
	static __IO uint16_t len = 0;
	uint16_t current_len;

	va_start(args, format);

	BACKUP_PRIMASK();
	DISABLE_IRQ();

	if(len != 0)
	{
		if(len != sizeof(BuffTx))
		{
			current_len = len; // use current_len instead of volatile len in computation below
			len = current_len + tiny_vsnprintf_like(BuffTx + current_len, sizeof(BuffTx) - current_len, format, args);
		}
		RESTORE_PRIMASK();
		va_end(args);
		return;
	}
	else
	{
		len = tiny_vsnprintf_like(BuffTx, sizeof(BuffTx), format, args);
	}

	current_len = len;

	RESTORE_PRIMASK();

	HAL_UART_Transmit(&DebugUart, (uint8_t *)BuffTx, current_len, 5000);
	len = 0; // ToDo
	va_end(args);
}


/**
  * @brief Error_Handler
  * @param None
  * @retval None
  */
void DBG_Error_Handler( void )
{
    PRINTF("Error_Handler\n\r");
    while(1);
}

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	DBG_USARTx_TX_GPIO_CLK_ENABLE();
	DBG_USARTx_RX_GPIO_CLK_ENABLE();


	/* Enable USARTx clock */
	DBG_USARTx_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = DBG_USARTx_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = DBG_USARTx_TX_AF;

	HAL_GPIO_Init(DBG_USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = DBG_USARTx_RX_PIN;
	GPIO_InitStruct.Alternate = DBG_USARTx_RX_AF;

	HAL_GPIO_Init(DBG_USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /*##-1- Reset peripherals ##################################################*/
	DBG_USARTx_FORCE_RESET();
	DBG_USARTx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure UART Tx as alternate function  */
	HAL_GPIO_DeInit(DBG_USARTx_TX_GPIO_PORT, DBG_USARTx_TX_PIN);
	/* Configure UART Rx as alternate function  */
	HAL_GPIO_DeInit(DBG_USARTx_RX_GPIO_PORT, DBG_USARTx_RX_PIN);
}
