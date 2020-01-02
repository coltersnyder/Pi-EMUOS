#include <stddef.h>
#include <stdint.h>

#ifndef raspberrypiver
	uint32_t tempReg;

	#if __AARCH64__
		asm volatile ("mrs %0, midr_el1" : "=r" (tempReg));
	#else
		asm volatile ("mrc p15,0,r0,c0,c0,0" : "=r" (tempReg));
	#endif
	
	switch((reg >> 4) & 0xFFF) {
		case 0xB76:
			#define raspberrypiver 1
			#define mmio_base 0x20000000
			break;
		case 0xC07:
			#define raspberrypiver 2
			#define mmio_base 0x3F000000
			break;
		case 0xD03:
			#define raspberrypiver 3
			#define mmio_base 0x3F000000
			break;
		case 0xD08:
			#define raspberrypiver 4
			#define mmio_base 0xFE000000
			break;
		default:
			#define raspberrypiver 0
			#define mmio_base 0x20000000
			break;
	}
	
#endif

static inline void mmio_write(uint32_t reg, uint32_t data) {
	*(volatile uint32_t*)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg){
	return *(volatile uint32_t*)reg;
}

static inline void delay(int32_t count) {
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		: "=r"(count): [count]"0"(count) : "cc");
}

enum {
	switch(raspberrypiver) {
		case 2:
		case 3:  GPIO_BASE = 0x3F200000; break;
		case 4:  GPIO_BASE = 0xFE200000; break;
		default: GPIO_BASE = 0x20200000; break;
	}
	
	
}