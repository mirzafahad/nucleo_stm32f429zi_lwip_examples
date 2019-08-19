/*
 * hw_uart1.h
 *
 *  Created on: Aug 19, 2019
 *      Author: fmirz007
 */

#ifndef HW_UART1_H_
#define HW_UART1_H_

#ifdef __cplusplus
extern "C" {
#endif

void HW_Uart1_Init(void);
void HW_Uart1_Send(uint8_t *pData, size_t size);

#ifdef __cplusplus
}
#endif
#endif /* HW_UART1_H_ */
