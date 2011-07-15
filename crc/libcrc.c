
#include <stdio.h>

#include "libcrc.h"

#define LIBCRC_POLY_16 0xA001

uint8_t libcrc_crc8(uint8_t * data, size_t size)
{
	int i;
	uint8_t crc = 0;

	// Calculate the CRC by using the XOR operator on each byte in the buffer
	for (i = 0; i < size; i++) {
		crc ^= data[i];
	}

	return crc;
}

uint8_t libcrc_next_crc8(uint8_t crc, uint8_t byte)
{
	return crc ^ byte;
}

uint8_t libcrc_sum8(uint8_t * data, size_t size) 
{
	int i;
	uint8_t crc = 0;

	for (i = 0; i < size; i++) {
		crc += data[i];
	}

	return crc;
}

uint8_t libcrc_lcrc(uint8_t * data, size_t size)
{
	uint8_t crc = 0;

	crc = libcrc_sum8(data, size);
	crc = ~crc + 1;

	return crc;
}

uint16_t libcrc_crc16(uint8_t * data, size_t size)
{
	uint16_t crc = 0xFFFF;
	int i, j;

	for (i = 0; i < size; i++) {
		crc = (crc ^ data[i]);

		for (j = 0; j < 8; j++) {
			if (crc & 0x0001) {
				crc = (crc >> 1) ^ LIBCRC_POLY_16;
			} else {
				crc = (crc >> 1);
			}
		}
	}

	return crc;
}

