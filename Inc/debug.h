
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Sends string on com port
 * @param  String
 * @retval None
 */
void DBG_Print(const char *format, ...);
void DBG_Init(void);


#define PRINTF(...)     DBG_Print(__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H__*/
