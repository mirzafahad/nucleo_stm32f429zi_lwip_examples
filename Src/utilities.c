/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Helper functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "utilities.h"
#include "tiny_sscanf.h"

/*!
 * Redefinition of rand() and srand() standard C functions.
 * These functions are redefined in order to get the same behavior across
 * different compiler toolchains implementations.
 */
// Standard random functions redefinition start
#define RAND_LOCAL_MAX 2147483647L

static uint32_t next = 1;

int32_t rand1( void )
{
    return ( ( next = next * 1103515245L + 12345L ) % RAND_LOCAL_MAX );
}

void srand1( uint32_t seed )
{
    next = seed;
}

// Standard random functions redefinition end
int32_t randr( int32_t min, int32_t max )
{
    return ( int32_t )rand1( ) % ( max - min + 1 ) + min;
}

void memcpy1( uint8_t *dst, const uint8_t *src, uint16_t size )
{
    while( size-- )
    {
        *dst++ = *src++;
    }
}

void memcpyr( uint8_t *dst, const uint8_t *src, uint16_t size )
{
    dst = dst + ( size - 1 );
    while( size-- )
    {
        *dst-- = *src++;
    }
}

void memset1( uint8_t *dst, uint8_t value, uint16_t size )
{
  while( size-- )
  {
    *dst++ = value;
  }
}

int8_t Nibble2HexChar( uint8_t a )
{
  if( a < 10 )
  {
    return '0' + a;
  }
  else if( a < 16 )
  {
    return 'A' + ( a - 10 );
  }
  else
  {
    return '?';
  }
}

void longToByteArray(const uint32_t longData, uint8_t *byteArray)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        byteArray[i] = (uint8_t)( (longData >> (8 * (3-i))) & 0xFF );
    }
}

void byteArrayToLong(uint8_t *byteArray, uint32_t *longData)
{
    *longData = 0;
    for(uint8_t i = 0; i < 4; i++)
    {
        *longData |= ((uint32_t)byteArray[3 - i] << (8 * i));
    }
}

uint8_t stringHexToByteArray(const char *hexString, uint8_t *byteArray, uint8_t byteArraySize)
{
    uint8_t count = 0;
    char hex[3];
    hex[2] = '\0';

    while( (*hexString != '\0') && (*(hexString + 1) != '\0') )
    {
    	// Separate two digits(i.e 1 HexByte) from the hex string
        hex[0] = *hexString;
        hex[1] = *(hexString + 1);

        if((tiny_sscanf(hex, "%hhx",&byteArray[count]) != 1))
        {
            // hex doesn't have valid numbers
            break;
        }

        count++;

        if (count == byteArraySize)
        {
          // We are out of space
          break;
        }
        // Advance string hex pointer by two
        hexString += 2;
    }

    return count;
}


