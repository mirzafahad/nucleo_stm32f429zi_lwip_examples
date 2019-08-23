/**
  ******************************************************************************
  * @file    LwIP/LwIP_TCP_Echo_Client/Src/main.c 
  * @author  MCD Application Team
  * @brief   This sample code implements a TCP Echo Client application based on 
  *          Raw API of LwIP stack. This application uses STM32F4xx the 
  *          ETH HAL API to transmit and receive data. 
  *          The communication is done with a web browser of a remote PC.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "app_ethernet.h"
#include "tcp_echoclient.h"
#include "debug.h"
#include "app_shelf.h"
#include "hw_uart1.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct netif gnetif;
uint8_t DataBuffer[70];

typedef enum eAppState
{
	CONNECT,
	CONNECTED,
	SEND_DATA,
	CLOSE
}eAppState_t;

eAppState_t AppState = SEND_DATA;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void BSP_Config(void);
static void Netif_Config(void);
void app_fsm(void);
uint32_t prepare_packet(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();  
  
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();
  
  DBG_Init();

  printf("#Debug Port#\r\n");
  printf("------------\r\n");
  printf("Initializing Ethernet and Sensor Interface...\r\n");


  HW_Uart1_Init();


  /* Configure the BSP */
  BSP_Config();
    
  /* Initialize the LwIP stack */
  lwip_init();
  
  /* Configure the Network interface */
  Netif_Config();
  
  /* Notify user about the network interface config */
  User_notification(&gnetif);

  Shelf_Init();
  printf("Done!\r\n");


  /* Infinite loop */
  while (1)
  {
	  app_fsm();
	  /* Read a received packet from the Ethernet buffers and send it
         to the lwIP for handling */
	  //ethernetif_input(&gnetif);
	  /* Handle timeouts */
	  //sys_check_timeouts();


#ifdef USE_DHCP
    /* handle periodic timers for LwIP */
    DHCP_Periodic_Handle(&gnetif);
#endif 
  }
}

/**
  * @brief  Configures the BSP.
  * @param  None
  * @retval None
  */
static void BSP_Config(void)
{
  /* Configure LED1, LED2 */
  //BSP_LED_Init(LED1);
  //BSP_LED_Init(LED2);
  
  /* Set Systick Interrupt to the highest priority */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0x0, 0x0);

  /* Configure User Button */
  //BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
}

/**
  * @brief  Configures the network interface
  * @param  None
  * @retval None
  */
static void Netif_Config(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#ifdef USE_DHCP
  ip_addr_set_zero_ip4(&ipaddr);
  ip_addr_set_zero_ip4(&netmask);
  ip_addr_set_zero_ip4(&gw);
#else
  IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
  IP_ADDR4(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
  IP_ADDR4(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
#endif /* USE_DHCP */

  /* Add the network interface */
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /* Registers the default network interface. */
  netif_set_default(&gnetif);

  if (netif_is_link_up(&gnetif))
  {
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void app_fsm(void)
{
	switch(AppState)
	{
		case CONNECT:
		{
			if(tcp_GetConnectionStatus() == false)
			{
				tcp_echoclient_connect();
				AppState = CONNECTED;
			}
			else
			{
				AppState = SEND_DATA;
			}

			break;
		}
		case CONNECTED:
		{
			if(tcp_GetConnectionStatus() == true)
			{
				AppState = SEND_DATA;
			}
			break;
		}
		case SEND_DATA:
		{
			uint32_t packetSize = prepare_packet();

			//tcp_SendData(DataBuffer, sizeof(DataBuffer));

			//HW_Uart1_Send(DataBuffer, packetSize);
		    //printf("%08X\r\n", (unsigned int)Shelf_GetZoneData(1));
			HW_Uart3_Send(DataBuffer, packetSize);

			//AppState = CONNECT;

			break;
		}
		default:
		{
			AppState = CONNECT;
			break;
		}

	}
}

uint32_t prepare_packet(void)
{
	uint32_t bufIndex = 0;
	uint8_t McuUniqueID[8];

	McuUniqueID[0] = *((uint8_t *) 0x1fff7a10);
	McuUniqueID[1] = *((uint8_t *) 0x1fff7a11);
	McuUniqueID[2] = *((uint8_t *) 0x1fff7a12);
	McuUniqueID[3] = *((uint8_t *) 0x1fff7a13);
	McuUniqueID[4] = *((uint8_t *) 0x1fff7a18);
	McuUniqueID[5] = *((uint8_t *) 0x1fff7a19);
	McuUniqueID[6] = *((uint8_t *) 0x1fff7a1a);
	McuUniqueID[7] = *((uint8_t *) 0x1fff7a1b);

	for(uint8_t i = 1; i <= 8; i++)
	{
		DataBuffer[bufIndex++] = i;
	}

	for(uint8_t i = 0; i < sizeof(McuUniqueID); i++)
	{
		DataBuffer[bufIndex++] = McuUniqueID[i];
	}

	Shelf_GetAllData(&DataBuffer[bufIndex], (sizeof(DataBuffer) - bufIndex));

	return (bufIndex + 48);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
