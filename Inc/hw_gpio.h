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

 /**
  * @brief GPIOs Macro
  */
 #define RCC_GPIO_CLK_ENABLE(__GPIO_PORT__)                     \
   do {                                                         \
     switch (__GPIO_PORT__)                                     \
     {                                                          \
       case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_ENABLE(); break;    \
       case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_ENABLE(); break;    \
       case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_ENABLE(); break;    \
       case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_ENABLE(); break;    \
       case GPIOE_BASE: __HAL_RCC_GPIOE_CLK_ENABLE(); break;    \
       case GPIOF_BASE: __HAL_RCC_GPIOF_CLK_ENABLE(); break;    \
       case GPIOG_BASE: __HAL_RCC_GPIOG_CLK_ENABLE(); break;    \
       case GPIOH_BASE: __HAL_RCC_GPIOH_CLK_ENABLE(); break;    \
       case GPIOI_BASE: __HAL_RCC_GPIOI_CLK_ENABLE(); break;    \
       case GPIOJ_BASE: __HAL_RCC_GPIOJ_CLK_ENABLE(); break;    \
       case GPIOK_BASE: default: __HAL_RCC_GPIOK_CLK_ENABLE();  \
     }                                                          \
   } while (0)

 #define RCC_GPIO_CLK_DISABLE(__GPIO_PORT__)                     \
   do {                                                          \
     switch (__GPIO_PORT__)                                      \
     {                                                           \
       case GPIOA_BASE: __HAL_RCC_GPIOA_CLK_DISABLE(); break;    \
       case GPIOB_BASE: __HAL_RCC_GPIOB_CLK_DISABLE(); break;    \
       case GPIOC_BASE: __HAL_RCC_GPIOC_CLK_DISABLE(); break;    \
       case GPIOD_BASE: __HAL_RCC_GPIOD_CLK_DISABLE(); break;    \
       case GPIOE_BASE: __HAL_RCC_GPIOE_CLK_DISABLE(); break;    \
       case GPIOF_BASE: __HAL_RCC_GPIOF_CLK_DISABLE(); break;    \
       case GPIOG_BASE: __HAL_RCC_GPIOG_CLK_DISABLE(); break;    \
       case GPIOH_BASE: __HAL_RCC_GPIOH_CLK_DISABLE(); break;    \
       case GPIOI_BASE: __HAL_RCC_GPIOI_CLK_DISABLE(); break;    \
       case GPIOJ_BASE: __HAL_RCC_GPIOJ_CLK_DISABLE(); break;    \
       case GPIOK_BASE: default: __HAL_RCC_GPIOK_CLK_DISABLE();  \
     }                                                           \
   } while (0)

void HW_GPIO_Init(GPIO_TypeDef *port, uint16_t GPIO_Pin, GPIO_InitTypeDef *initStruct);

#ifdef __cplusplus
}
#endif
#endif /* HW_GPIO_H_ */
