/*
 * hx711.h
 *
 *  Created on: Jul 30, 2019
 *      Author: Fahad
 */

#ifndef HX711_H_
#define HX711_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef struct sHX711Param
{
	GPIO_TypeDef* dtPort;
	GPIO_TypeDef* sckPort;
	uint16_t dtPin;			// Serial Data Output Pin
	uint16_t sckPin;		// Power Down and Serial Clock Input Pin
	uint8_t gain;			// Amplification factor
}sHX711Param_t;

class HX711
{
	private:
		uint16_t SCK_PIN;
		uint16_t DT_PIN;
		GPIO_TypeDef* SCK_PORT;
		GPIO_TypeDef* DT_PORT;
		uint8_t GAIN;

	public:
		// Initialize library with data output pin, clock input pin and gain factor.
		// Channel selection is made by passing the appropriate gain:
		// - With a gain factor of 64 or 128, channel A is selected
		// - With a gain factor of 32, channel B is selected
		// The library default is "128" (Channel A).
		HX711(sHX711Param_t* hx711Param);
		virtual ~HX711();

		// Check if HX711 is ready
		// from the datasheet: When output data is not ready for retrieval, digital output pin DT is high. Serial clock
		// input SCK should be low. When DT goes to low, it indicates data is ready for retrieval.
		bool is_ready();

		// Wait for the HX711 to become ready
		void wait_ready(void);
		bool wait_ready_timeout(uint32_t timeout = 1000);

		// set the gain factor; takes effect only after a call to read()
		// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
		// depending on the parameter, the channel is also set to either A or B
		void set_gain(uint8_t gain = 128);

		// waits for the chip to be ready and returns a reading
		int32_t read();

		// returns an average reading; times = how many times to read
		int32_t read_average(uint8_t times = 10);

		// puts the chip into power down mode
		void power_down();

		// wakes up the chip after power down mode
		void power_up();
};





#endif /* HX711_H_ */
