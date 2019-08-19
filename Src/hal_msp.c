/*
 * hal_msp.c
 *
 *  Created on: Aug 19, 2019
 *      Author: fmirz007
 */

#include "hw_conf.h"
#include "stm32f4xx_hal.h"
#include "hw_gpio.h"

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

    /***************************************************************/
    /*      GPIO Configuration   for UART1 or for UART3            */
    /*      for USART1 use:                                        */
	/*           PA10    ------> USART1_RX                         */
	/*           PA9     ------> USART1_TX                         */
	/*      for USART3 use:                                        */
	/*           PD9     ------> USART2_RX                         */
	/*           PD8     ------> USART2_TX                         */
	/***************************************************************/

	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;

    if(huart->Instance == USART1)
	{
		// Peripheral clock enable
		__HAL_RCC_USART1_CLK_ENABLE();
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HW_GPIO_Init(GPIOA, GPIO_PIN_9|GPIO_PIN_10, &GPIO_InitStruct);
	}
	else if(huart->Instance == USART3)
	{
		// Peripheral clock enable
		__HAL_RCC_USART3_CLK_ENABLE();
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HW_GPIO_Init(GPIOD, GPIO_PIN_8|GPIO_PIN_9, &GPIO_InitStruct);
	}

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
	// TODO
    /*##-1- Reset peripherals ##################################################*/
	//DBG_USARTx_FORCE_RESET();
	//DBG_USARTx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure UART Tx as alternate function  */
	//HAL_GPIO_DeInit(DBG_USARTx_TX_GPIO_PORT, DBG_USARTx_TX_PIN);
	/* Configure UART Rx as alternate function  */
	//HAL_GPIO_DeInit(DBG_USARTx_RX_GPIO_PORT, DBG_USARTx_RX_PIN);
}