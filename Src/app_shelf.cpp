/*
 * app_shelf.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: fmirz007
 */

#include "hx711.h"
#include "hw_conf.h"

#define NUM_OF_ZONES   (12U)

HX711 Zones[NUM_OF_ZONES] = { {ZONE1},
							  {ZONE2},
							  {ZONE3},
							  {ZONE4},
							  {ZONE5},
							  {ZONE6},
							  {ZONE7},
							  {ZONE8},
							  {ZONE9},
							  {ZONE10},
							  {ZONE11},
							  {ZONE12} };

void Shelf_Init(void)
{
	for(uint8_t i = 0; i < NUM_OF_ZONES; i++)
	{
		Zones[i].begin();
	}
}

void Shelf_GetAllData(uint8_t *buf, size_t bufSize)
{
	uint32_t data;
	size_t bufIndex = 0;

	// Each zone requires 4 bytes
	if(bufSize < (NUM_OF_ZONES * 4))
	{
		return;
	}

	for(uint8_t i = 0; i < NUM_OF_ZONES; i++)
	{
		data = (uint32_t)Zones[i].read_average(10);

		buf[bufIndex++] = (data >> 24) & 0xFF;
		buf[bufIndex++] = (data >> 16) & 0xFF;
		buf[bufIndex++] = (data >> 8) & 0xFF;
		buf[bufIndex++] = data & 0xFF;
	}
}

int32_t Shelf_GetZoneData(uint8_t zoneNum)
{
	if(zoneNum < 1 || zoneNum > NUM_OF_ZONES)
	{
		return -1;
	}

	return Zones[zoneNum - 1].read_average(10);
}


