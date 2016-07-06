#include "types.h"

void init_kernel();

void start_kernel() {
	init_kernel();
	while(1);
}

void terminal_print_string(const char *str, unsigned int x, unsigned int y)
{
	/* Todo: fix this static computation */
	volatile u8* vram = (volatile u8*) 0xB8000 + 2 * (x + y * 80);

	while (*str) {
		*vram++ = *str++;
		*vram++ = 0x57;
	}
}

u32 rdtsc(void) {
	  u32 x;
	  __asm__ volatile ("rdtsc" : "=A" (x));
	  return x;
}

void *memcpy(void *dst, const void *src, int size)
{
	void *p = dst;

	while (size--)
		*(u8 *)dst++ = *(u8 *)src++;

	return p;
}

void init_kernel()
{
	char* terminal_buffer = (char*) 0xB8000;
	char* terminal_color = (char*) 0xB8001;
	char hello[] = "HELLO WORLD";

	terminal_print_string(hello, 0, 1);
}
