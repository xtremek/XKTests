#include <stdio.h>
#include <stdint.h>

#include "libcrc.h"

int main(int argc, char ** argv) 
{
		uint8_t crc = 0;

		uint8_t data[] = { 	0x00, 0x00, 0x00, 0x86, 
									  		0x03, 0x87, 0xAA, 0x22,
												0x06, 0x20, 0xFE, 0x20,
												0x00, 0x20, 0x03
		};

		crc = libcrc_sum8(data, sizeof(data));

		printf("CRC: 0x%X\n", crc);
}
