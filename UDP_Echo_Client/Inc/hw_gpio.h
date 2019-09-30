/*
 * hw_gpio.h
 *
 *  Created on: Jul 31, 2019
 *      Author: Fahad
 */

#ifndef HW_GPIO_H_
#define HW_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

void HW_GPIO_Init(GPIO_TypeDef *port, uint16_t GPIO_Pin, GPIO_InitTypeDef *initStruct);

#ifdef __cplusplus
}
#endif
#endif /* HW_GPIO_H_ */
