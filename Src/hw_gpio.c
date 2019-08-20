/*
 * hw_gpio.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: fmirz007
 */

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "hw_gpio.h"


/* Private function prototypes -----------------------------------------------*/

/* Exported functions ---------------------------------------------------------*/

void HW_GPIO_Init(GPIO_TypeDef *port, uint16_t GPIO_Pin, GPIO_InitTypeDef *initStruct)
{
    /* Check the parameters */
    assert_param(IS_GPIO_MODE(GPIO_Init->Mode));
    assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    // Enable the corresponding PORT clock
    RCC_GPIO_CLK_ENABLE((uint32_t)port);

    uint32_t pinPos = 1;
    while (GPIO_Pin != 0)
	{
		if (GPIO_Pin & 0x1)
		{
			initStruct->Pin = pinPos;
			HAL_GPIO_Init(port, initStruct);
		}
		pinPos++;
		GPIO_Pin = GPIO_Pin >> 1;
	}
}


