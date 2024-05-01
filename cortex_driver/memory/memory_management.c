#include "main.h"
#include "memory_management.h"

extern uint32_t _sdata; // Start address of .data section
extern uint32_t _edata; // End address of .data section
extern uint32_t _sbss;  // Start address of .bss section
extern uint32_t _ebss;  // End address of .bss section
extern uint32_t _suser; // Start address of user_heap_stack, user define 
extern uint32_t _euser; // End address of user_heap_stack, user define

extern uint32_t _estack;
extern uint32_t _sstack;

uint32_t _user_heap_stack;

void calculate_memory_usage(void)
{
    uint32_t data_size = (uint32_t)(&_edata) - (uint32_t)(&_sdata);
    uint32_t bss_size = (uint32_t)(&_ebss) - (uint32_t)(&_sbss);
    uint32_t user_heap_stack_size = (uint32_t)(&_euser) - (uint32_t)(&_suser);
    uint32_t ram_size = ((uint32_t)(&_estack) - (uint32_t)(&_sstack));

    float ram_usage, ram_usage_per;

#if (ITM_PRINTF_LOG_ON == 1)
    printf("ram size: %.2f kbyte\n", (float)(ram_size / 1024));
    printf(".data section size: %lu bytes\n", data_size);
    printf(".bss section size: %lu bytes\n", bss_size);
    printf(".user_heap_stack section size: %.2f kbyte\n", (float)user_heap_stack_size / 1024.0f);
#endif
    ram_usage = (float)(data_size + bss_size + user_heap_stack_size);
    ram_usage_per = (ram_usage / (float)ram_size) * 100.0f;

#if (ITM_PRINTF_LOG_ON == 1)
    printf("ram usage(%%) : %.2f kbyte(%.2f%%)\n", (ram_usage / 1024.0f), ram_usage_per);
#endif
}


void* alloc_memory(size_t size) 
{
    void* ptr = malloc(size);
    
    if (ptr != NULL) {
       _user_heap_stack += size;
    }
    
    return ptr;
}

void free_memory(void* ptr, size_t size) 
{
    free(ptr);
    _user_heap_stack -= size;
}