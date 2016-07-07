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

unsigned int strlen(char *str)
{
    unsigned int n = 0;

    while (str[n++]);

    return n;
}

void *memcpy(void *dst, const void *src, int size)
{
	void *p = dst;

	while (size--)
		*(u8 *)dst++ = *(u8 *)src++;

	return p;
}
#define strcpy(x,y) memcpy((void *)(x), (void *)(y), (strlen(x) + 1))

void itoa(char *str, unsigned long num)
{
	char digits[] = "0123456789";
	char buf[30], *ptr;

	ptr = buf + sizeof(buf) - 1;
	*ptr-- = '\0';

	do {
        	*ptr-- = digits[num % 10];
	        num = num / 10;
	} while (num > 0);

	strcpy(str, ++ptr);
}

void init_kernel()
{
	char hello[] = "HELLO WORLD, timestamp is: ";
	char time[30];

	while(1) {
		itoa(&time, rdtsc());
		terminal_print_string(hello, 0, 1);
		terminal_print_string(time, strlen(hello), 1);
	}
}
