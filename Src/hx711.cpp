/*
 * hx711.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: Fahad
 */


#include "utilities.h"
#include "hx711.h"
#include "hw_gpio.h"



HX711::HX711(sHX711Param_t &hx711Param)
{
	SCK_PIN  = hx711Param.sckPin;
	DT_PIN   = hx711Param.dtPin;
	SCK_PORT = hx711Param.sckPort;
	DT_PORT  = hx711Param.dtPort;
	GAIN     = hx711Param.gain;
}

HX711::HX711(GPIO_TypeDef* dtPort, GPIO_TypeDef* sckPort, uint16_t dtPin, uint16_t sckPin, uint8_t gain)
{
	SCK_PIN  = sckPin;
	DT_PIN   = dtPin;
	SCK_PORT = sckPort;
	DT_PORT  = dtPort;
	GAIN     = gain;
}

HX711::~HX711()
{
}

void HX711::begin()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HW_GPIO_Init(SCK_PORT, SCK_PIN, &GPIO_InitStruct);

	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HW_GPIO_Init(DT_PORT, DT_PIN, &GPIO_InitStruct);

	set_gain(GAIN);
}

void HX711::set_gain(uint8_t gain)
{
	switch (gain)
	{
		case 128:		// channel A, gain factor 128
		{
			GAIN = 1;
			break;
		}
		case 64:		// channel A, gain factor 64
		{
			GAIN = 3;
			break;
		}
		case 32:		// channel B, gain factor 32
		{
			GAIN = 2;
			break;
		}
	}

	HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	read();
}

bool HX711::is_ready()
{
	return (HAL_GPIO_ReadPin(DT_PORT, DT_PIN) == GPIO_PIN_RESET);
}


int32_t HX711::read()
{
	// Wait for the chip to become ready.
	if(wait_ready_timeout(2000) == false)
	{
		return -1;
	}

	// Define structures for reading data into.
	int32_t buffer = 0;


	// Protect the read sequence from system interrupts.  If an interrupt occurs during
	// the time the SCK signal is high it will stretch the length of the clock pulse.
	// If the total pulse time exceeds 60 uSec this will cause the HX711 to enter
	// power down mode during the middle of the read sequence.  While the device will
	// wake up when SCK goes low again, the reset starts a new conversion cycle which
	// forces DT high until that cycle is completed.
	//
	// The result is that all subsequent bits read will read back as 1,
	// corrupting the value returned by read().  The DISABLE_IRQ() macro disables
	// interrupts during the sequence and then restores the interrupt mask to its previous
	// state after the sequence completes, insuring that the entire read-and-gain-set
	// sequence is not interrupted.

	// Disable interrupts.
	BACKUP_PRIMASK();
	DISABLE_IRQ();

	// Pulse the clock pin 24 times to read the data.
	for (uint8_t i = 0; i < 24; i++)
	{
		HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);

		buffer = buffer << 1 ;

		if (HAL_GPIO_ReadPin(DT_PORT, DT_PIN))
		{
			buffer++;
		}

		HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	}

	// Set the channel and the gain factor for the next reading using the clock pin.
	for (uint8_t i = 0; i < GAIN; i++)
	{
		HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SCK_PORT, SCK_PIN, GPIO_PIN_RESET);
	}

	// Enable interrupts again.
	RESTORE_PRIMASK();

	if(buffer & 0x800000)
	{
		buffer = ((uint32_t)0xFF << 24) | buffer;
	}

	return buffer;
}


void HX711::wait_ready()
{
	// Wait for the chip to become ready.
	// This is a blocking implementation and will
	// halt the sketch until a load cell is connected.
	while (!is_ready());
}

int32_t HX711::read_average(uint8_t times)
{
	int32_t sum = 0;

	for (uint8_t i = 0; i < times; i++)
	{
		sum += read();
	}

	return sum / times;
}

// timeout in milisecond
bool HX711::wait_ready_timeout(uint32_t timeout)
{
	// Wait for the chip to become ready until timeout.

	uint32_t tickstart = HAL_GetTick();
	while((uint32_t)(HAL_GetTick() - tickstart) < timeout)
	{
		if(is_ready())
		{
			return true;
		}
	}
	return false;
}
