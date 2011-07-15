#ifndef LIBCRC_H
#define LIBCRC_H

#include <stdint.h>

extern uint8_t 	libcrc_crc8(uint8_t * data, size_t size);
extern uint8_t 	libcrc_next_crc8(uint8_t crc, uint8_t byte);

extern uint8_t 	libcrc_sum8(uint8_t * data, size_t size);
extern uint8_t 	libcrc_lcrc(uint8_t * data, size_t size);

extern uint16_t	libcrc_crc16(uint8_t * data, size_t size);

#endif
