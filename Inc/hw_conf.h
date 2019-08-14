/*
 * hw_conf.h
 *
 *  Created on: Jul 31, 2019
 *      Author: fmirz007
 */

#ifndef HW_CONF_H_
#define HW_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif


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


/*
 * HX711 Pinouts according to Zones
 */
// {DT_PORT, SCK_PORT, DT_PIN, SCK_PIN, GAIN}
#define ZONE1      {GPIOD, GPIOD, GPIO_PIN_2,  GPIO_PIN_3,  128}
#define ZONE2      {GPIOD, GPIOD, GPIO_PIN_0,  GPIO_PIN_1,  128}
#define ZONE3      {GPIOC, GPIOC, GPIO_PIN_11, GPIO_PIN_12, 128}
#define ZONE4      {GPIOG, GPIOG, GPIO_PIN_9,  GPIO_PIN_10, 128}
#define ZONE5      {GPIOD, GPIOD, GPIO_PIN_6,  GPIO_PIN_7,  128}
#define ZONE6      {GPIOD, GPIOD, GPIO_PIN_4,  GPIO_PIN_5,  128}
#define ZONE7      {GPIOB, GPIOB, GPIO_PIN_9,  GPIO_PIN_8,  128}
#define ZONE8      {GPIOB, GPIOB, GPIO_PIN_7,  GPIO_PIN_6,  128}
#define ZONE9      {GPIOB, GPIOB, GPIO_PIN_5,  GPIO_PIN_4,  128}
#define ZONE10     {GPIOI, GPIOI, GPIO_PIN_7,  GPIO_PIN_6,  128}
#define ZONE11     {GPIOI, GPIOI, GPIO_PIN_5,  GPIO_PIN_4,  128}
#define ZONE12     {GPIOE, GPIOE, GPIO_PIN_1,  GPIO_PIN_0, 128}

#ifdef __cplusplus
}
#endif

#endif /* HW_CONF_H_ */
