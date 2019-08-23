
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"

/**
 * @brief  Initialize debug port
 * @param  String
 * @retval None
 */
void DBG_Init(void);
void HW_Uart3_Send(uint8_t *pData, size_t size);


#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H__*/
