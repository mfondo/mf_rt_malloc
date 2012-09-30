#include <stdio.h>
#include <string.h>
#define MF_RT_MALLOC_DEBUG
#include "mf_rt_malloc.h"

int main(int argc, char *argv[]) {
	unsigned int lengthBytes = 8 * sizeof(char*);
	char* memory[lengthBytes];
	unsigned int chunkSizeBytes = 1 * sizeof(char*);
	memset(&memory, 0, lengthBytes);
	//printf("ptrsize:%ld\n", sizeof(char*));
	if(rt_malloc_init(&memory, lengthBytes, chunkSizeBytes)) {
		printf("init error\n");
		return -1;
	}
	printMemory(&memory, lengthBytes, "mainAfterInit");

	char* ptr1 = rt_malloc(&memory);
	memset(ptr1, 1, chunkSizeBytes);
	printf("ptr1:%p\n", ptr1);
	printMemory(&memory, lengthBytes, "ptr1");

	char* ptr2 = rt_malloc(&memory);
	memset(ptr2, 2, chunkSizeBytes);
	printf("ptr2:%p\n", ptr2);
	printMemory(&memory, lengthBytes, "ptr2");

	char* ptr3 = rt_malloc(&memory);
	memset(ptr3, 3, chunkSizeBytes);
	printf("ptr3:%p\n", ptr3);
	printMemory(&memory, lengthBytes, "ptr3");

	char* ptr4 = rt_malloc(&memory);
	//ptr4 should be NULL
	printf("ptr4:%p\n", ptr4);
	printMemory(&memory, lengthBytes, "ptr4");

	rt_free(&memory, ptr3);
	printMemory(&memory, lengthBytes, "free ptr3");

	rt_free(&memory, ptr1);
	printMemory(&memory, lengthBytes, "free ptr1");

	rt_free(&memory, ptr2);
	printMemory(&memory, lengthBytes, "free ptr2");

	ptr1 = rt_malloc(&memory);
	memset(ptr1, 0, chunkSizeBytes);
	printf("ptr1:%p\n", ptr1);
	printMemory(&memory, lengthBytes, "ptr1");

	ptr2 = rt_malloc(&memory);
	memset(ptr2, 0, chunkSizeBytes);
	printf("ptr2:%p\n", ptr2);
	printMemory(&memory, lengthBytes, "ptr2");

	ptr3 = rt_malloc(&memory);
	memset(ptr3, 0, chunkSizeBytes);
	printf("ptr3:%p\n", ptr3);
	printMemory(&memory, lengthBytes, "ptr3");

	ptr4 = rt_malloc(&memory);
	//ptr4 should be NULL
	printf("ptr4:%p\n", ptr4);
	printMemory(&memory, lengthBytes, "ptr4");

	return 0;
}

