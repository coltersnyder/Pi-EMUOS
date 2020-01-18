;For use with Raspberry Pi 3 and 4

.section ".text.boot"

.globl _start

	.org 0x80000
	
_start:
	mrs x1, mpidr_el1
	and x1, x1, #3
	cbz x1, 2f
1: 	wfe
	b 1b
2:
	ldr x1, =_start
	mov sp, x1
	
	ldr x1, =__bss_start
	ldr w2, =__bss_end
3:	cbz w2, 4f
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, 3b
	
4:	bl kernel_main
	b 1b