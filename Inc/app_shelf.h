/*
 * app_shelf.h
 *
 *  Created on: Aug 14, 2019
 *      Author: fmirz007
 */

#ifndef APP_SHELF_H_
#define APP_SHELF_H_


void Shelf_Init(void);
void Shelf_GetAllData(uint8_t *buf, size_t bufSize);
int32_t Shelf_GetZoneData(uint8_t zoneNum);


#endif /* APP_SHELF_H_ */
