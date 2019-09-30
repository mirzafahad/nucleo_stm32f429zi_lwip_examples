# STM32F429ZI_Nucleo_TCP_Echo_Client
TCP Echo Client Example using LwIP Stack (RAW API) for STM32F429ZI Nucleo
<br>
STM32Cube has only one LwIP example for Nucleo-STM32F429ZI (LwIP_HTTP_Server_Netconn_RTOS). 
But has several examples for STM324x9I_EVAL. TCP Echo Client was copied from the Eval example and made necessary changes to
fit in the Nucleo board.

<br>
Change log:<br>
1. Updated header file names.
2. Changed clock from 25MHz(Eval) to 8MHz(Nucleo).
3. Updated Ethernet interface from MII to RMII.
4. PHY IC was updated to LAN8742A
