#define LAST_PTR_OFFSET (0)
#define NEXT_TO_ALLOC_PTR_OFFSET (1 * sizeof(char*))
#define FIRST_CHUNK_PTR_OFFSET (2 * sizeof(char*))

#ifdef MF_RT_MALLOC_DEBUG
void printMemory(void* memory, unsigned int memoryLengthBytes, char* tag) {
        unsigned int i = 0;
	printf("%s\n", tag);

	char** ptr = memory;
	char* endMemory = ((char*)memory) + memoryLengthBytes;
	while(ptr < endMemory) {
                printf("offset:%d mem:%p val:%p\n", i, ptr, *ptr);
		ptr++;
		i++;
	}
}
#endif

int rt_malloc_init(void* memory, unsigned int memoryLengthBytes, unsigned int chunkSizeBytes) {
	if(memoryLengthBytes <= 2 * sizeof(char*)) {
		return -1;
	}
	//in reverse order create chunk ptrs, once we collide with the beginning pointers, we stop
	char* chunkPos = ((char*)memory) + (memoryLengthBytes - chunkSizeBytes);
	char** tmp = ((char*)memory) + NEXT_TO_ALLOC_PTR_OFFSET;
	*tmp = ((char*)memory) + FIRST_CHUNK_PTR_OFFSET;
	char** chunkPtr = *tmp;
	while(1) {
		*chunkPtr = chunkPos;
		chunkPos -= chunkSizeBytes;
		if(chunkPtr + 1 >= chunkPos) {
			break;
		}
		chunkPtr++;
	}
	tmp = ((char*)memory) + LAST_PTR_OFFSET;
	*tmp = chunkPtr;
	return 0;
}

void* rt_malloc(void* memory) {
	char** nta = ((char*)memory) + NEXT_TO_ALLOC_PTR_OFFSET;
	char** lastPtr = ((char*)memory) + LAST_PTR_OFFSET;
	if(*nta > *lastPtr) {
		return 0;
	}
	void* ret = *((char**)(*nta));
	((char**)(*nta))++;
	return ret;
}

void rt_free(void* memory, void* ptr) {
	char** nta = ((char*)memory) + NEXT_TO_ALLOC_PTR_OFFSET;
	((char**)(*nta))--;
	nta = (char**)(*nta);
	*nta = ptr;
}
