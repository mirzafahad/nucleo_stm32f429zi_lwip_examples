/*
 * debug.c
 *
 *  Created on: Jul 31, 2019
 *      Author: fmirz007
 */


#include "debug.h"
#include "hw_conf.h"
#include "stm32f4xx_hal.h"


/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private variables --------------------------------------------------------*/
static UART_HandleTypeDef DebugUart;




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

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&DebugUart, (uint8_t *)&ch, 1, 5000);

  return ch;
}


/**
  * @brief Error_Handler
  * @param None
  * @retval None
  */
void DBG_Error_Handler( void )
{
    printf("Error_Handler\n\r");
    while(1);
}
