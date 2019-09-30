# STM32F429ZI Nucleo LwIP Examples
TCP and UDP Echo Client Example using LwIP Stack (RAW API) for Nucleo-F429ZI
<br><br>
STM32Cube has only one LwIP example for Nucleo-F429ZI (LwIP_HTTP_Server_Netconn_RTOS). 
But has several examples for STM324x9I_EVAL. TCP and UDP Echo Client was copied from the Eval example and necessary changes were made 
to fit in the Nucleo board.

<br>
Change log:<br>
1. Updated header file names.<br>
2. Changed clock from 25MHz(Eval) to 8MHz(Nucleo).<br>
3. Updated Ethernet interface from MII to RMII.<br>
4. PHY IC was updated to LAN8742A<br>
