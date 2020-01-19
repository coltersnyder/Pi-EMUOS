#include "kernel.h"

#if defined(__cplusplus)
extern "C"
#endif
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags){
	(void) r0;
	(void) r1;
	(void) atags;

	uart_init();
	uart_puts("Ok then\r\n");
	while(1) uart_putc(uart_getc());
}