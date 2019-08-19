/*
 * hw_uart1.c
 *
 *  Created on: Aug 19, 2019
 *      Author: fmirz007
 */
#include <stdint.h>
#include "debug.h"
#include "hw_uart1.h"
#include "hw_conf.h"
#include "stm32f4xx_hal.h"

static UART_HandleTypeDef SensorUart;




void HW_Uart1_Init(void)
{
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
		- Word Length = 8 Bits
		- Stop Bit    = One Stop bit
		- Parity      = None
		- BaudRate    = 9600 baud
		- Hardware flow control disabled (RTS and CTS signals) */
	SensorUart.Instance          = SENSOR_USARTx;

	SensorUart.Init.BaudRate     = 9600;
	SensorUart.Init.WordLength   = UART_WORDLENGTH_8B;
	SensorUart.Init.StopBits     = UART_STOPBITS_1;
	SensorUart.Init.Parity       = UART_PARITY_NONE;
	SensorUart.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	SensorUart.Init.Mode         = UART_MODE_TX_RX;
	SensorUart.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&SensorUart);
}

void HW_Uart1_Send(uint8_t *pData, size_t size)
{
	if(HAL_UART_Transmit(&SensorUart, pData, size, 5000) != HAL_OK)
	{
		printf("UART1 Tx failed!\r\n");
	}
}
