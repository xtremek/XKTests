
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes.h"

#ifdef __AVR32_ABI_COMPILER__
#include <machine/endian.h>
#else
#include <endian.h>
#endif

#include "byte.h"

//#ifdef BYTE_AVR32_TINY

#include <utils/str.h>

int byte_get_idx(int idx, int size, int byte_order)
{
	if (byte_order == BYTE_LITTLE_ENDIAN) {
		return (sizeof(byte_int_t) - 1) - idx;
	} else {
		return (sizeof(byte_int_t) - size) + idx;
	}
}

byte_int_t bytes_join(uint8_t * bytes, int size, int byte_order)
{
	if (size > 0 && size <= sizeof(byte_int_t)) {
		int i;

		byte_int_t val = 0;
		uint8_t * p = (uint8_t *)&val;

		for (i = 0; i < size; i++) {
			int idx = byte_get_idx(i, size, byte_order);

			p[idx] = bytes[i];
		}

		return val;
	}

	return 0;
}

void bytes_split(byte_int_t uint, uint8_t * bytes, int size, int byte_order)
{
	if (size > 0 && size <= sizeof(byte_int_t)) {
		int i;

		uint8_t * p = (uint8_t *)&uint;

		for (i = 0; i < size; i++) {
			int idx = byte_get_idx(i, size, byte_order);

			bytes[i] = p[idx];
		}
	}
}

byte_int_t byte_memtoi(void * src, int size)
{
    byte_int_t val = 0;
    int offset = (sizeof(val) - size);

	memmove((uint8_t *)&val + offset, src, size);
	
	return val;
}

void byte_itomem(byte_int_t src, void * dest, int size)
{
    int offset = (sizeof(src) - size);

	memmove(dest, (uint8_t *)&src + offset, size);
}

//#else

/*uint64_t byte_uint_to_le(uint64_t val)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	return val;
#else
	return byte_swap64(val);
#endif
}

uint64_t byte_uint_to_be(uint64_t val)
{
#if BYTE_ORDER == BIG_ENDIAN
	return val;
#else
	return byte_swap64(val);
#endif
}


uint64_t bytes_swap(uint64_t data, bool byte_order)
{
	uint64_t d = data;

	if (byte_order == LITTLE_ENDIAN) {
		d = byte_uint_to_le(data);
	} else {
		d = byte_uint_to_be(data);
	}

    return d;
}

int byte_get_offset(int idx, int size, int byte_order)
{	
#if BYTE_ORDER == LITTLE_ENDIAN
	if (byte_order == BYTE_BIG_ENDIAN) {
		return (8 - 1) - idx;
	} else {
		return idx;
	}
#else
	if (byte_order == BYTE_LITTLE_ENDIAN) {
		return (8 - 1) - idx;
	} else {
		return (8 - size) + idx;
	}
#endif
}

uint64_t bytes_join(uint8_t * bytes, int size, int byte_order)
{
	if (size > 0 && size <= 8) {
		int i;


		uint64_t val = 0;
		uint8_t * p = (uint8_t *)&val;

		for (i = 0; i < size; i++) {
			int idx = byte_get_offset(i, size, byte_order);
			p[idx] = bytes[i];
		}

		return val;
	}

	return 0;
}

bool bytes_split(uint64_t uint, uint8_t * bytes, int size, int byte_order)
{
	if (size > 0 && size <= 8) {
		int i;

		uint8_t * p = (uint8_t *)&uint;

		for (i = 0; i < size; i++) {
			int idx = byte_get_offset(i, size, byte_order);

			bytes[i] = p[idx];
		}

	} else {
		return false;
	}

	return true;
}


uint64_t byte_memtoi(void * src, int size)
{
	uint64_t val = 0;

	uint8_t * ptr = (uint8_t *)src;
#if BYTE_ORDER == LITTLE_ENDIAN
	val = bytes_join(ptr, size, BYTE_LITTLE_ENDIAN);
#else
	val = bytes_join(ptr, size, BYTE_BIG_ENDIAN);
#endif

	return val;
}

void byte_itomem(uint64_t src, void * dest, int size)
{
	uint8_t * ptr = (uint8_t *)dest;
#if BYTE_ORDER == LITTLE_ENDIAN
	bytes_split(src, ptr, size, BYTE_LITTLE_ENDIAN);
#else
	bytes_split(src, ptr, size, BYTE_BIG_ENDIAN);
#endif
}
*/

//#endif


#ifdef DEBUG
void byte_print_cpu_info()
{
	printf("--- CPU Info ---\n");
	printf("Standard Types: \n");
	printf("  Sizeof char:     %d\n", sizeof(char));
	printf("  Sizeof int:      %d\n", sizeof(int));
	printf("  Sizeof long:     %d\n", sizeof(long));
	printf("  Sizeof llong:    %d\n", sizeof(long long));
	printf("\n");
	printf("Unsigned Types: \n");
	printf("  Sizeof uint8_t:  %d\n", sizeof(uint8_t));
	printf("  Sizeof uint16_t: %d\n", sizeof(uint16_t));
	printf("  Sizeof uint32_t: %d\n", sizeof(uint32_t));
	printf("  Sizeof uint64_t: %d\n", sizeof(uint64_t));
	printf("\n");
	printf("Float Types: \n");
	printf("  Sizeof float:    %d\n", sizeof(float));
	printf("  Sizeof double:   %d\n", sizeof(double));
	printf("  Sizeof ldouble:  %d\n", sizeof(long double));
	printf("\n");
	printf("Endianess:         ");

#if BYTE_ORDER == LITTLE_ENDIAN
	printf("Little Endian");
#else
	printf("Big Endian");
#endif

	printf("\n");
}
#endif

int byte_int_size(int64_t n)
{
	int num = 0;
	if (n <= INT8_MAX && n >= INT8_MIN) {
		num = 1;
	} else if (n <= INT16_MAX && n >= INT16_MIN) {
		num = 2;
	} else if (n <= INT24_MAX && n >= INT24_MIN) {
		num = 3;
	} else if (n <= INT32_MAX && n >= INT32_MIN) {
		num = 4;
	} else if (n <= INT40_MAX && n >= INT40_MIN) {
		num = 5;
	} else if (n <= INT48_MAX && n >= INT48_MIN) {
		num = 6;
	} else if (n <= INT56_MAX && n >= INT56_MIN) {
		num = 7;
	} else if (n <= INT64_MAX && n >= INT64_MIN) {
		num = 8;
	}

	return num;
}

int byte_uint_size(uint64_t n)
{
	int num = 0;

    if (n <= UINT8_MAX) {
    	num = 1;
    } else if (n <= UINT16_MAX && n > UINT8_MAX) {
    	num = 2;
    } else if (n <= UINT24_MAX && n > UINT16_MAX) {
    	num = 3;
    } else if (n <= UINT32_MAX && n > UINT24_MAX) {
        num = 4;
    } else if (n <= UINT40_MAX && n > UINT32_MAX) {
        num = 5;
    } else if (n <= UINT48_MAX && n > UINT40_MAX) {
        num = 6;
    } else if (n <= UINT56_MAX && n > UINT48_MAX) {
        num = 7;
    } else if (n <= UINT64_MAX && n > UINT56_MAX) {
        num = 8;
    }

    return num;
}
