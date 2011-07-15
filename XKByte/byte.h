#ifndef UTILS_BYTE_H
#define UTILS_BYTE_H

#include <stdint.h>

// Additional defines for irregular sized integers
#define INT24_MIN				-0x800000
#define INT24_MAX				0x7FFFFF
#define INT40_MIN				-0x8000000000LL
#define INT40_MAX				0x7FFFFFFFFFLL
#define INT48_MIN				-0x800000000000LL
#define INT48_MAX				0x7FFFFFFFFFFFLL
#define INT56_MIN				-0x80000000000000LL
#define INT56_MAX				0x7FFFFFFFFFFFFFLL

#define UINT24_MAX				0xFFFFFF
#define UINT40_MAX				0xFFFFFFFFFFLL
#define UINT48_MAX				0xFFFFFFFFFFFFLL
#define UINT56_MAX				0xFFFFFFFFFFFFFFLL

#define BYTE_LITTLE_ENDIAN      0
#define BYTE_BIG_ENDIAN         1

typedef uint64_t byte_int_t;

/*#define	byte_swap64(x)  (((uint64_t)(x) << 56) | \
                        (((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
                        (((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
                        (((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
                        (((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
                        (((uint64_t)(x) >> 24) & 0xff0000ULL) | \
                        (((uint64_t)(x) >> 40) & 0xff00ULL) | \
                        ((uint64_t)(x)  >> 56))*/


extern void byte_print_cpu_info();
extern int byte_int_size(int64_t n);
extern int byte_uint_size(uint64_t n);

extern byte_int_t bytes_join(uint8_t * data,
							int size,
							int byte_order);

extern void		  bytes_split(byte_int_t uint,
							  uint8_t * bytes,
							  int size,
							  int byte_order);

extern byte_int_t byte_memtoi(void * src, int size);
extern void		byte_itomem(byte_int_t src, void * dest, int size);

#endif
