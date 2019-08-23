/*
 * hw_conf.h
 *
 *  Created on: Jul 31, 2019
 *      Author: fmirz007
 */

#ifndef HW_CONF_H_
#define HW_CONF_H_


/* Definition for Debug UART */
#define DBG_USARTx                           USART3
#define DBG_USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define DBG_USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define DBG_USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define DBG_USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define DBG_USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

#define DBG_USARTx_TX_PIN                    GPIO_PIN_8
#define DBG_USARTx_TX_GPIO_PORT              GPIOD
#define DBG_USARTx_TX_AF                     GPIO_AF7_USART3
#define DBG_USARTx_RX_PIN                    GPIO_PIN_9
#define DBG_USARTx_RX_GPIO_PORT              GPIOD
#define DBG_USARTx_RX_AF                     GPIO_AF7_USART3



#endif /* HW_CONF_H_ */
