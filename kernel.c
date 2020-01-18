#include <stddef.h>
#include <stdint.h>

#ifndef raspberrypiver
	uint32_t tempReg;

	#if __AARCH64__
		asm volatile ("mrs %0, midr_el1" : "=r" (tempReg));
	#else
		asm volatile ("mrc p15,0,r0,c0,c0,0" : "=r" (tempReg));
	#endif
	
	//Get the version of Raspberry Pi from the CPU ID
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
		case 3:  
			GPIO_BASE = 0x3F200000;
			UART0_BASE = 0x3F201000;
			break;
		case 4:  
			GPIO_BASE = 0xFE200000;
			UART0_BASE = 0x3F201000;
			break;
		default: 
			GPIO_BASE = 0x20200000; 
			UART0_BASE = 0x20201000;
			break;
	}
	
	GPPUD     = (GPIO_BASE + 0x94),
	GPPUDCLK0 = (GPIO_BASE + 0x98),
	
	UART0_DR     = (UART0_BASE + 0x00),
	UART0_RSRECR = (UART0_BASE + 0x04),
	UART0_FR     = (UART0_BASE + 0x18),
	UART0_ILPR   = (UART0_BASE + 0x20),
	UART0_IBRD   = (UART0_BASE + 0x24),
	UART0_FBRD   = (UART0_BASE + 0x28),
	UART0_LCRH   = (UART0_BASE + 0x2C),
	UART0_CR     = (UART0_BASE + 0x30),
	UART0_IFLS   = (UART0_BASE + 0x34),
	UART0_IMSC   = (UART0_BASE + 0x38),
	UART0_RIS    = (UART0_BASE + 0x3C),
	UART0_MIS    = (UART0_BASE + 0x40),
	UART0_ICR    = (UART0_BASE + 0x44),
	UART0_DMACR  = (UART0_BASE + 0x48),
	UART0_ITCR   = (UART0_BASE + 0x80),
	UART0_ITIP   = (UART0_BASE + 0x84),
	UART0_ITOP   = (UART0_BASE + 0x88),
	UART0_TDR    = (UART0_BASE + 0x8C),
};

void uart_init(){
	mmio_write(UART0_CR, 0x00000000);
	
	mmio_write(GPPUD, 0x00000000);
	delay(150);
	
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
	
	mmio_write(GPPUDCLK0, 0x00000000);
	
	mmio_write(UART0_ICR, 0x7FF);
	
	mmio_write(UART0_IBRD, 1);
	mmio_write(UART0_FBRD, 40);
	
	mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
	
	mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
						   (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
						   
	mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c) {
	while ( mmio_read(UART0_FR) & (1 << 5) ) { }
	mmio_write(UART0_DR, c);
}

unsigned char uart_getc(){
	while ( mmio_read(UART0_FR) & (1 << 4) ) { }
	return mmio_read(UART0_DR);
}

void uart_puts(const char* str){
	for(size_t i = 0; str[i] != '\0'; i++) uart_putc((unsigned char) str[i]);
}