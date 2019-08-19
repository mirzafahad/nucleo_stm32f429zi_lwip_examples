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
#define DBG_USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE()
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


/* Definition for Sensor UART */
#define SENSOR_USARTx                        USART1
#define SENSOR_USARTx_CLK_ENABLE()           __HAL_RCC_USART1_CLK_ENABLE()
#define SENSOR_USARTx_RX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define SENSOR_USARTx_TX_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()

#define SENSOR_USARTx_FORCE_RESET()          __HAL_RCC_USART1_FORCE_RESET()
#define SENSOR_USARTx_RELEASE_RESET()        __HAL_RCC_USART1_RELEASE_RESET()

#define SENSOR_USARTx_TX_PIN                 GPIO_PIN_9
#define SENSOR_USARTx_TX_GPIO_PORT           GPIOA
#define SENSOR_USARTx_TX_AF                  GPIO_AF7_USART1
#define SENSOR_USARTx_RX_PIN                 GPIO_PIN_10
#define SENSOR_USARTx_RX_GPIO_PORT           GPIOA
#define SENSOR_USARTx_RX_AF                  GPIO_AF7_USART1


/*
 * HX711 Pinouts according to Zones
 * Default gain is 128->ChannelA
 */
// {DT_PORT, SCK_PORT, DT_PIN, SCK_PIN, GAIN}
#define ZONE1      GPIOD, GPIOD, GPIO_PIN_2,  GPIO_PIN_3
#define ZONE2      GPIOD, GPIOD, GPIO_PIN_0,  GPIO_PIN_1
#define ZONE3      GPIOC, GPIOC, GPIO_PIN_11, GPIO_PIN_12
#define ZONE4      GPIOG, GPIOG, GPIO_PIN_9,  GPIO_PIN_10
#define ZONE5      GPIOD, GPIOD, GPIO_PIN_6,  GPIO_PIN_7
#define ZONE6      GPIOD, GPIOD, GPIO_PIN_4,  GPIO_PIN_5
#define ZONE7      GPIOB, GPIOB, GPIO_PIN_9,  GPIO_PIN_8
#define ZONE8      GPIOB, GPIOB, GPIO_PIN_7,  GPIO_PIN_6
#define ZONE9      GPIOB, GPIOB, GPIO_PIN_5,  GPIO_PIN_4
#define ZONE10     GPIOI, GPIOI, GPIO_PIN_7,  GPIO_PIN_6
#define ZONE11     GPIOI, GPIOI, GPIO_PIN_5,  GPIO_PIN_4
#define ZONE12     GPIOE, GPIOE, GPIO_PIN_1,  GPIO_PIN_0

#ifdef __cplusplus
}
#endif

#endif /* HW_CONF_H_ */
