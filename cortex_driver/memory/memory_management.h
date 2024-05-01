#ifndef __MEMORY_MANAGEMENT_H__
#define __MEMORY_MANAGEMENT_H__

void calculate_memory_usage(void);

void* alloc_memory(size_t size);
void my_free(void* ptr, size_t size);
#endif