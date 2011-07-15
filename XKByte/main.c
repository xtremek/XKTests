 
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <stdint.h>

#include "byte.h"

struct test {
	int size;
	void * data;
} test;

void test_cpu_data()
{
	int i;
	uint64_t data = 1234567890UL;

	uint8_t * p = (uint8_t *)&data;
	printf("Raw CPU Data: ");

	for (i = 0; i < sizeof(data); i++) {
		printf("0x%X ", p[i]);
	}

	printf("\n");
}

void test_byte_split_join()
{
	int i, num = 12567;
	uint8_t bytes[8];

	printf("--- Byte Split & Join Test ---\n");

	bytes_split(num, bytes, 2, BYTE_LITTLE_ENDIAN);

	printf("Bytes: ");
	for (i = 0; i < 2; i++) {
		printf("0x%X ", bytes[i]);
	}
	printf("\n");

	uint64_t val = bytes_join(bytes, 2, BYTE_LITTLE_ENDIAN);
	printf("Val: %d\n", (int)val);
}

void test_size_detect()
{
	int i;

	uint64_t val;

	printf("--- Data Size & Copy Test ---\n");

	// Next test
	uint8_t  data0 = 12;
	uint16_t data1 = 1234;
	uint32_t data2 = 123456;
	uint64_t data3 = 12345678668ULL;

	printf("Data0 Size: %d\n", byte_uint_size(data0));
	printf("Data1 Size: %d\n", byte_uint_size(data1));
	printf("Data2 Size: %d\n", byte_uint_size(data2));
	printf("Data3 Size: %d\n", byte_uint_size(data3));

	struct test test1;
	test1.size = sizeof(data3);
	test1.data = &data3;

	/*uint8_t * ptr = (uint8_t *)test1.data;
	memcpy(&val, ptr, test1.size);*/

	val = 4621241;

	byte_itomem(val, test1.data, test1.size);

	//byte_itomem(val, test1.data, test1.size);

	val = 0;

	uint64_t dt = byte_memtoi(test1.data, test1.size);
	printf("Data: %ld\n", dt);
}

void test_union_data()
{
	int i;
	byte_data_t data;
	data.val = 1234;

	printf("Union Val: %d\n", (int)data.val);
	printf("Union Data: ");
	for (i = 0; i < 8; i++) {
		printf("0x%X ", data.bytes[i]);
	}
	printf("\n");
}

int main(int argc, char ** argv)
{
	int i;
	uint8_t bytes[8];
	
	byte_print_cpu_info();
	printf("\n");
	test_cpu_data();
	printf("\n");
	test_byte_split_join();
	printf("\n");
	test_size_detect();
	printf("\n");
	test_union_data();
	printf("\n");

	return 0;
}
